#include "heisenberg.hpp"

#include <boost/lambda/lambda.hpp>

void operator/=(dvec &lhs, double rhs);
void operator+=(dvec &lhs, dvec rhs);

heisenberg_sim::heisenberg_sim(parameters_type const & parms, std::size_t seed_offset)
    : alps::mcbase(parms, seed_offset)
    , length(parameters["L"])
    , sweeps(0)
    , thermalization_sweeps(int(parameters["THERMALIZATION"]))
    , total_sweeps(int(parameters["SWEEPS"]))
    , beta(1. / double(parameters["T"]))
    , spins(length)
{
    for(int i = 0; i < length; ++i)
        spins[i].push_back(random() < 0.5 ? 1 : -1);
    measurements
        << alps::ngs::RealObservable("Energy")
        << alps::ngs::RealVectorObservable("Magnetization")
        << alps::ngs::RealObservable("Magnetization^2")
        << alps::ngs::RealObservable("Magnetization^4")
        << alps::ngs::RealVectorObservable("Correlations")
    ;
}

void heisenberg_sim::update() {
    for (int j = 0; j < length; ++j) {
        using std::exp;
        int i = int(double(length) * random());
        int right = ( i + 1 < length ? i + 1 : 0 );
        int left = ( i - 1 < 0 ? length - 1 : i - 1 );
        double p = exp( 2. * beta * (spins[i] * ( spins[right] + spins[left])));
        if ( p >= 1. || random() < p )
            spins[i][0] = -spins[i][0];
    }
}

void heisenberg_sim::measure() {
    sweeps++;
    if (sweeps > thermalization_sweeps) {
        dvec  tmag(1, 0);
        double ten = 0;
        //double sign = 1;
        std::vector<double> corr(length);
        for (int i = 0; i < length; ++i) {
            tmag += spins[i];
            //sign *= spins[i][0];
            ten += -(spins[i] * spins[ i + 1 < length ? i + 1 : 0 ]);
            for (int d = 0; d < length; ++d)
                corr[d] += spins[i] * spins[( i + d ) % length ];
        }
        std::transform(corr.begin(), corr.end(), corr.begin(), boost::lambda::_1 / double(length));
        ten /= length;
        tmag /= length;
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
    thermalization_sweeps = int(parameters["THERMALIZATION"]);
    total_sweeps = int(parameters["SWEEPS"]);
    beta = 1. / double(parameters["T"]);

    std::string context = ar.get_context();
    ar.set_context("/simulation/realizations/0/clones/0/checkpoint");
    ar["sweeps"] >> sweeps;
    ar["spins"] >> spins;
    ar.set_context(context);
}

void operator+=(dvec &lhs, dvec rhs) {
    lhs[0] += rhs[0];
}

dvec operator+(dvec lhs, dvec rhs) {
    lhs += rhs;
    return lhs;
}

double operator*(dvec lhs, dvec rhs) {
    return lhs[0] * rhs[0];
}

dvec operator*(double lhs, dvec rhs) {
    return dvec(1, lhs*rhs[0]);
}

void operator/=(dvec &lhs, double rhs) {
    lhs[0] /= rhs;
}
