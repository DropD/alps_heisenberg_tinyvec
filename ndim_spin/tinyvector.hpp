/* helper.hpp for ndim_spin example
 */

#ifndef HEISENBERG_HELPER_HPP
#define HEISENBERG_HELPER_HPP

//~ #include "ndim_spin.hpp"

#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct even {};
struct odd  {};

template <int N>
struct zerocomp { typedef odd even_or_odd; };

template <>
struct zerocomp<0> { typedef even even_or_odd; };

template <int N> 
struct integer { typedef zerocomp<N % 2> is; };

template <int N>
class tinyvector {
    public:
        typename integer<N>::is::even_or_odd even_or_odd;

        inline const double operator[](int i) const { return _data[i]; };
        inline double & operator[](int i) { return _data[i]; };

        void initialize(double init) {
            for(int i = 0; i < N; ++i)
                _data[i] = init;
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

template <int N, class evenodd>
class tv_addinplace {
    public:
        static inline const tinyvector<N> & apply(tinyvector<N> &left, const tinyvector<N> &right);
};

template <int N>
class tv_addinplace<N, odd> {
    public:
        static inline const tinyvector<N> & apply(tinyvector<N> &left, const tinyvector<N> &right) {
            for(int i = 0; i < N; ++i)
                left[i] += right[i];
            return left;
        }
};

template <int N> 
class tv_addinplace<N, even> {
    public:
        static inline const tinyvector<N> & apply(tinyvector<N> &left, const tinyvector<N> &right) {
            for(int i = 0; i < N/2; ++i) {
                left[2*i]       += right[2*i];
                left[2*i + 1]   += right[2*i + 1];
            }
            return left;
        }
};

template <int N>
inline const tinyvector<N> & operator+=(tinyvector<N> &left, const tinyvector<N> &right) {
    return tv_addinplace<N, typename integer<N>::is::even_or_odd>::apply(left, right);
}

template <int N>
inline const tinyvector<N> & operator-=(tinyvector<N> &left, const tinyvector<N> &right) {
    for(int i = 0; i < N; ++i)
        left[i] -= right[i];
    return left;
}

template <int N>
inline const tinyvector<N> & operator*=(tinyvector<N> &left, double right) {
    for(int i = 0; i < N; ++i)
        left[i] *= right;
    return left;
}

template <int N>
inline const tinyvector<N> & operator/=(tinyvector<N> &left, double right) {
    for(int i = 0; i < N; ++i)
        left[i] /= right;
    return left;
}

template <int N>
inline const tinyvector<N> operator+(const tinyvector<N> &left, const tinyvector<N> &right) {
    tinyvector<N> result(left);
    return result += right;
}

template <int N>
inline const tinyvector<N> operator-(const tinyvector<N> &left, const tinyvector<N> &right) {
    tinyvector<N> result(left);
    return result -= right;
}

template <int N>
inline const tinyvector<N> operator-(const tinyvector<N> &spin) {
    tinyvector<N> result;
    for(int i = 0; i < N; ++i)
        result[i] = - spin[i];
    return result;
}

template <int N>
inline const tinyvector<N> operator*(const tinyvector<N> &left, double right) {
    tinyvector<N> result(left);
    return result *= right;
}

template <int N>
inline const tinyvector<N> operator*(double left, const tinyvector<N> &right) {
    return right * left;
}

template <int N>
inline const tinyvector<N> operator/(const tinyvector<N> &left, double right) {
    tinyvector<N> result(left);
    return result /= right;
}

template <int N>
double dot(const tinyvector<N> &left, const tinyvector<N> &right) {
    double result = 0.;
    for(int i = 0; i < N; ++i)
        result += left[i] * right[i];
    return result;
}

template <int N>
double abs(const tinyvector<N> &spin) {
   return std::sqrt(dot(spin, spin));
}

template <int N>
std::ostream& operator<<(std::ostream& os, const tinyvector<N>& spin)
{
    os << "[ ";
    for(int i = 0; i < N; ++i)
        os << spin[i] << " ";
    os << " ]";
    return os;
}

template <int N>
inline const std::vector<double> vector_from_tinyvector(const tinyvector<N> &spin) {
    std::vector<double> result;
    for(int i = 0; i < N; ++i)
        result.push_back(spin[i]);
    return result;
}

template <int N>
inline const tinyvector<N> spin_from_vector(const std::vector<double> &vec) {
    tinyvector<N> result;
    for(int i = 0; i < N; ++i)
        result[i] = vec[i];
    return result;
}

#endif
