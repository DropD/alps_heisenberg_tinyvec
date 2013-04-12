#include "heisenberg.hpp"

#include <boost/lambda/lambda.hpp>

heisenberg_sim::heisenberg_sim(parameters_type const & params, std::size_t seed_offset) 
    : alps::mcbase(params, seed_offset)
    , length(parameters["L"])
    , sweeps(0)
    , thermalization_sweeps(int(parameters["THERMALIZATION"]))
    , total_sweeps(int(parameters["SWEEPS"]))
    , beta(1. / double(parameters["T"]))
    , spin_dim(parameters["SPINDIM"])
    , spins()
{
    spins = std::vector<dvec>(length, dvec(spin_dim));
    for(int i = 0; i < length; ++i) {

        for(int j = 0; j < spin_dim; ++j) {

            double elem = 2*random() - 1;
            //double elem = (random() < 0.5 ? 1 : -1);
            spins[i][j] = elem;
        }

        double sabs = abs(spins[i]);
        for(int j = 0; j < spin_dim; ++j) {

            spins[i][j] /= sabs;
        }
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
    for(int j = 0; j < length; ++j) {

        using std::exp;
        int i = int(double(length) * random());
        int right = (i + 1 < length ? i+1 : 0);
        int left = (i + 1 < length ? length-1 : i-1);
        double p = exp(2. * beta * (spins[i] * (spins[right] + spins[left])));
        if (p >= 1. || random() < p) {
            spins[i] = -1. * spins[i];
        }
    }
}

void heisenberg_sim::measure() {
    sweeps++;
    if (sweeps > thermalization_sweeps) {
        dvec tmag(spin_dim);
        double ten = 0;
        double sign = 1;
        std::vector<double> corr(length);

        for(int i = 0; i < length; ++i) {
            tmag = tmag + spins[i];
            sign  = sign * spins[i][0];
            ten  += -(spins[i] * spins[i + 1 < length ? i+1 : 0]);

            for(int d = 0; d < length; ++d) {
                corr[d] += spins[i] * spins[(i+d) % length];
            }
        }
        std::transform(corr.begin(), corr.end(), corr.begin(), boost::lambda::_1 / double(length));
        ten /= length;
        tmag = tmag / length;
        measurements["Energy"] << ten;
        measurements["Magnetization"] << tmag;
        measurements["Magnetization^2"] << tmag * tmag;
        measurements["Magnetization^4"] << tmag * tmag * tmag * tmag;
        measurements["Correlations"] << corr;
    }
}

double heisenberg_sim::fraction_completed() const {
    return (sweeps < thermalization_sweeps ? 0 : (sweeps - thermalization_sweeps) / double(total_sweeps));
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
    ar.set_context("simulation/realizations/0/clones/0/checkpoint");
    ar["sweeps"] >> sweeps;
    ar["spins"]  >> spins;
    ar.set_context(context);
}

inline dvec operator+ (dvec lhs, dvec rhs) {
    assert(lhs.size() == rhs.size());
    size_t n = lhs.size();

    dvec res(n);
    for(int i = 0; i < n; ++i) {
        res[i] = lhs[i] + rhs[i];
    }

    return res;
}

inline double operator* (dvec lhs, dvec rhs) {
    assert(lhs.size() == rhs.size());
    size_t n = lhs.size();

    double res = 0;
    for(int i = 0; i < n; ++i) {
        res += lhs[i] * rhs[i];
    }

    return res;
}

inline dvec operator* (double lhs, dvec rhs) {
    dvec res = rhs;
    
    for(int i = 0; i < rhs.size(); ++i) {
        res[i] *= lhs;
    }

    return res;
}

inline dvec operator/ (dvec lhs, double rhs) {
    dvec res = lhs;

    for(int i = 0; i < lhs.size(); ++i) {
        res[i] /= rhs;
    }

    return res;
}

inline double abs(dvec vec) {
    return std::sqrt(vec * vec);
}
