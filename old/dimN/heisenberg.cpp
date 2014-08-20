#include "heisenberg.hpp"

#include <boost/lambda/lambda.hpp>

void operator/=(dvec &lhs, double rhs);
void operator+=(dvec &lhs, dvec rhs);
void operator-=(dvec &lhs, dvec rhs);
dvec operator-(dvec lhs, dvec rhs);
dvec operator-(dvec vec);
double abs(dvec vec);

heisenberg_sim::heisenberg_sim(parameters_type const & parms, std::size_t seed_offset)
    : alps::mcbase(parms, seed_offset)
    , length(parameters["L"])
    , size(length*length)
    , sweeps(0)
    , thermalization_sweeps(int(parameters["THERMALIZATION"]))
    , total_sweeps(int(parameters["SWEEPS"]))
    , beta(1. / double(parameters["T"]))
    , spin_dim(int(parameters["SPINDIM"]))
    , spins(size)
    , Jx(double(parameters["Jx"]))
    , Jy(double(parameters["Jy"]))
{
    for(int i = 0; i < size; ++i) {
        spins[i] = get_random_spin();
    }
    measurements
        << alps::ngs::RealObservable("Energy")
        << alps::ngs::RealVectorObservable("Magnetization")
        << alps::ngs::RealObservable("Magnetization^2")
        << alps::ngs::RealObservable("Magnetization^4")
        << alps::ngs::RealVectorObservable("Correlations")
    ;
}

void heisenberg_sim::update() {
    for (int j = 0; j < size; ++j) {
        dvec new_spin = get_random_spin();
        using std::exp;
        int i = int(double(size) * random());
        //int right = ( i + 1 < size ? i + 1 : 0 );
        //int left = ( i - 1 < 0 ? size - 1 : i - 1 );
        //double p = exp(beta * ((spins[i] - new_spin) * (spins[right] + spins[left])));
        dvec nn_sum = get_nn_sum(i);
        double p = exp(beta * ((spins[i] - new_spin) * (nn_sum)));
        if ( p >= 1. || random() < p )
            spins[i] = new_spin;
    }
}

void heisenberg_sim::measure() {
    sweeps++;
    if (sweeps > thermalization_sweeps) {
        dvec  tmag(spin_dim, 0);
        double ten = 0;
        std::vector<double> corr(size);
        for (int i = 0; i < size; ++i) {
            tmag += spins[i];
            ten += -Jx * (spins[i] * spins[ i + 1 < size ? i + 1 : 0 ]);
            ten += -Jy * (spins[i] * spins[i - length < 0 ? i + size - length : i - length]);
            for (int d = 0; d < size; ++d)
                corr[d] += spins[i] * spins[( i + d ) % size ];
        }
        std::transform(corr.begin(), corr.end(), corr.begin(), boost::lambda::_1 / double(size));
        ten /= size;
        tmag /= size;
        measurements["Energy"] << ten;
        measurements["Magnetization"] << tmag;
        measurements["Magnetization^2"] << tmag * tmag;
        measurements["Magnetization^4"] << tmag * tmag * tmag * tmag;
        measurements["Correlations"] << corr;
    }
}

double heisenberg_sim::fraction_completed() const {
    return (sweeps < thermalization_sweeps ? 0. : ( sweeps - thermalization_sweeps ) / double(total_sweeps));
}

void heisenberg_sim::save(alps::hdf5::archive & ar) const {
    mcbase::save(ar);

    std::string context = ar.get_context();
    ar.set_context("/simulation/realizations/0/clones/0/checkpoint");
    ar["sweeps"] << sweeps;
    ar["spins"] << spins;
    ar.set_context(context);
}

void heisenberg_sim::load(alps::hdf5::archive & ar) {
    mcbase::load(ar);

    length = int(parameters["L"]);
    size   = length * length;
    thermalization_sweeps = int(parameters["THERMALIZATION"]);
    total_sweeps = int(parameters["SWEEPS"]);
    beta = 1. / double(parameters["T"]);

    std::string context = ar.get_context();
    ar.set_context("/simulation/realizations/0/clones/0/checkpoint");
    ar["sweeps"] >> sweeps;
    ar["spins"] >> spins;
    ar.set_context(context);
}

dvec heisenberg_sim::get_random_spin() {
    dvec new_spin;
    for(int i = 0; i < spin_dim; ++i) {
        new_spin.push_back(2. * random() - 1.);
    }
    new_spin /= abs(new_spin);
    return new_spin;
}

dvec heisenberg_sim::get_nn_sum(int i) {
    int left  = (i % length ? i - 1 : i + length - 1);
    int right = (i % length == length - 1 ? i - length + 1 : i + 1);
    int upper = (i - length < 0 ? i + size - length : i - length);
    int lower = (i + length < size ? i + length : i - size + length);
    return Jx * (spins[left] + spins[right]) + Jy * (spins[upper] + spins[lower]);
}

void operator+=(dvec &lhs, dvec rhs) {
    for(int i = 0; i < lhs.size(); ++i)
        lhs[i] += rhs[i];
}

dvec operator+(dvec lhs, dvec rhs) {
    lhs += rhs;
    return lhs;
}

double operator*(dvec lhs, dvec rhs) {
    double res = 0;
    for(int i = 0; i < lhs.size(); ++i)
        res += lhs[i] * rhs[i];
    return res;
}

dvec operator*(double lhs, dvec rhs) {
    dvec res = rhs;
    for(int i = 0; i < rhs.size(); ++i)
        res[i] *= lhs;
    return res;
}

void operator/=(dvec &lhs, double rhs) {
    for(int i = 0; i < lhs.size(); ++i)
        lhs[i] /= rhs;
}

void operator-=(dvec &lhs, dvec rhs) {
    for(int i = 0; i < lhs.size(); ++i)
        lhs[i] -= rhs[i];
}

dvec operator-(dvec lhs, dvec rhs) {
    lhs -= rhs;
    return lhs;
}

dvec operator-(dvec vec) {
    dvec res(vec.size());
    for(int i = 0; i < res.size(); ++i)
        res[i] = -vec[i];
    return res;
}

double abs(dvec vec) {
    return std::sqrt(vec * vec);
}
