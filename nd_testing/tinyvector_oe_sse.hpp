/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_OE_SSE
#define TINYVECTOR_OE_SSE

#include "multiple_of.hpp"

#include <immintrin.h>
#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct OE_SSE {};

//~ 
//~ template <int N>
//~ class tinyvector {
    //~ public:
        //~ typename integer<N>::is::even_or_odd even_or_odd;
//~ 
        //~ inline const double operator[](int i) const { return _data[i]; };
        //~ inline double & operator[](int i) { return _data[i]; };
//~ 
        //~ void initialize(double init) {
            //~ for(int i = 0; i < N; ++i)
                //~ _data[i] = init;
        //~ }
        //~ inline const double * data() const { return _data.data(); }
        //~ void save(alps::hdf5::archive & ar) const {
            //~ ar << alps::make_pvp("data", _data);
        //~ }
        //~ void load(alps::hdf5::archive & ar) {
            //~ ar >> alps::make_pvp("data", _data);
        //~ }
    //~ private:
        //~ boost::array<double, N> _data;
//~ };

template <int N, class divisor>
class tv_addinplace_oe_sse {
    public:
        static inline const tinyvector<N, OE_SSE> & apply(tinyvector<N, OE_SSE> &left, const tinyvector<N, OE_SSE> &right) {
            //~ double * l = left.data();
            //~ const double * r = right.data();
            __m128 mx_left, mx_right, mx_sum;
            for(int i = 0; i < N/2; ++i) {
                // load left & right
                mx_left =  _mm_loadu_pd(&left.front() + 2 * i);
                mx_right = _mm_loadu_pd(&right.front() + 2 * i);
                // add
                mx_sum = _mm_add_pd(mx_left, mx_right);
                // store left
                _mm_storeu_pd(&left.front() + 2 * i, mx_sum);
            }
            return left;
        }
};

template <int N> 
class tv_addinplace_oe_sse<N, one> {
    public:
        static inline const tinyvector<N, OE_SSE> & apply(tinyvector<N, OE_SSE> &left, const tinyvector<N, OE_SSE> &right) {
            for(int i = 0; i < N; ++i)
                left[i] += right[i];
            return left;
        }
};

template <int N>
inline const tinyvector<N, OE_SSE> & operator+=(tinyvector<N, OE_SSE> &left, const tinyvector<N, OE_SSE> &right) {
    return tv_addinplace_oe_sse<N, typename multiple_of<N>::divisor>::apply(left, right);
}
//~ 
//~ template <int N>
//~ inline const tinyvector<N> & operator-=(tinyvector<N> &left, const tinyvector<N> &right) {
    //~ for(int i = 0; i < N; ++i)
        //~ left[i] -= right[i];
    //~ return left;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> & operator*=(tinyvector<N> &left, double right) {
    //~ for(int i = 0; i < N; ++i)
        //~ left[i] *= right;
    //~ return left;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> & operator/=(tinyvector<N> &left, double right) {
    //~ for(int i = 0; i < N; ++i)
        //~ left[i] /= right;
    //~ return left;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> operator+(const tinyvector<N> &left, const tinyvector<N> &right) {
    //~ tinyvector<N> result(left);
    //~ return result += right;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> operator-(const tinyvector<N> &left, const tinyvector<N> &right) {
    //~ tinyvector<N> result(left);
    //~ return result -= right;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> operator-(const tinyvector<N> &spin) {
    //~ tinyvector<N> result;
    //~ for(int i = 0; i < N; ++i)
        //~ result[i] = - spin[i];
    //~ return result;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> operator*(const tinyvector<N> &left, double right) {
    //~ tinyvector<N> result(left);
    //~ return result *= right;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> operator*(double left, const tinyvector<N> &right) {
    //~ return right * left;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> operator/(const tinyvector<N> &left, double right) {
    //~ tinyvector<N> result(left);
    //~ return result /= right;
//~ }
//~ 
//~ template <int N>
//~ double dot(const tinyvector<N> &left, const tinyvector<N> &right) {
    //~ double result = 0.;
    //~ for(int i = 0; i < N; ++i)
        //~ result += left[i] * right[i];
    //~ return result;
//~ }
//~ 
//~ template <int N>
//~ double abs(const tinyvector<N> &spin) {
   //~ return std::sqrt(dot(spin, spin));
//~ }
//~ 
//~ template <int N>
//~ std::ostream& operator<<(std::ostream& os, const tinyvector<N>& spin)
//~ {
    //~ os << "[ ";
    //~ for(int i = 0; i < N; ++i)
        //~ os << spin[i] << " ";
    //~ os << " ]";
    //~ return os;
//~ }
//~ 
//~ template <int N>
//~ inline const std::vector<double> vector_from_tinyvector(const tinyvector<N> &spin) {
    //~ std::vector<double> result;
    //~ for(int i = 0; i < N; ++i)
        //~ result.push_back(spin[i]);
    //~ return result;
//~ }
//~ 
//~ template <int N>
//~ inline const tinyvector<N> spin_from_vector(const std::vector<double> &vec) {
    //~ tinyvector<N> result;
    //~ for(int i = 0; i < N; ++i)
        //~ result[i] = vec[i];
    //~ return result;
//~ }

#endif
