/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_DEFAULT_HPP
#define TINYVECTOR_DEFAULT_HPP

//~ #include "ndim_spin.hpp"

#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct NO_OPT {};

template <int N, class Opt>
class tinyvector {
    public:
        tinyvector() : _data() {}
        tinyvector(const std::vector<double> &vec) {
            for(int i = 0; i < N; ++i)
                _data[i] = vec[i];
        }

        const double * data() const { return _data.data(); }
        double * data() { return _data.c_array(); }

        const double & front() const { return _data.front(); }
        double & front() {return _data.front(); }

        inline const double operator[](int i) const { return _data[i]; };
        inline double & operator[](int i) { return _data[i]; };

        void initialize(double init) {
            for(int i = 0; i < N; ++i)
                _data[i] = init;
        }

        static inline const std::vector<double> vector(const tinyvector<N, Opt> & tv){
            std::vector<double> result;
            for(int i = 0; i < N; ++i)
                result.push_back(tv[i]);
            return result;
        }

        void save(alps::hdf5::archive & ar) const {
            ar << alps::make_pvp("data", _data);
        }
        void load(alps::hdf5::archive & ar) {
            ar >> alps::make_pvp("data", _data);
        }
    private:
        boost::array<double, N> _data;
};

template <int N, class Opt>
inline const tinyvector<N, Opt> & operator+=(tinyvector<N, Opt> &left, const tinyvector<N, Opt> &right) {
    for(int i = 0; i < N; ++i)
        left[i] += right[i];
    return left;
};

template <int N, class Opt>
inline const tinyvector<N, Opt> & operator-=(tinyvector<N, Opt> &left, const tinyvector<N, Opt> &right) {
    for(int i = 0; i < N; ++i)
        left[i] -= right[i];
    return left;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> & operator*=(tinyvector<N, Opt> &left, double right) {
    for(int i = 0; i < N; ++i)
        left[i] *= right;
    return left;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> & operator/=(tinyvector<N, Opt> &left, double right) {
    for(int i = 0; i < N; ++i)
        left[i] /= right;
    return left;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> operator+(const tinyvector<N, Opt> &left, const tinyvector<N, Opt> &right) {
    tinyvector<N, Opt> result(left);
    return result += right;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> operator-(const tinyvector<N, Opt> &left, const tinyvector<N, Opt> &right) {
    tinyvector<N, Opt> result(left);
    return result -= right;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> operator-(const tinyvector<N, Opt> &spin) {
    tinyvector<N, Opt> result;
    for(int i = 0; i < N; ++i)
        result[i] = - spin[i];
    return result;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> operator*(const tinyvector<N, Opt> &left, double right) {
    tinyvector<N, Opt> result(left);
    return result *= right;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> operator*(double left, const tinyvector<N, Opt> &right) {
    return right * left;
}

template <int N, class Opt>
inline const tinyvector<N, Opt> operator/(const tinyvector<N, Opt> &left, double right) {
    tinyvector<N, Opt> result(left);
    return result /= right;
}

template <int N, class Opt>
double dot(const tinyvector<N, Opt> &left, const tinyvector<N, Opt> &right) {
    double result = 0.;
    for(int i = 0; i < N; ++i)
        result += left[i] * right[i];
    return result;
}

template <int N, class Opt>
double abs(const tinyvector<N, Opt> &spin) {
   return std::sqrt(dot(spin, spin));
}

template <int N, class Opt>
std::ostream& operator<<(std::ostream& os, const tinyvector<N, Opt>& spin)
{
    os << "[ ";
    for(int i = 0; i < N; ++i)
        os << spin[i] << " ";
    os << " ]";
    return os;
}

#endif
