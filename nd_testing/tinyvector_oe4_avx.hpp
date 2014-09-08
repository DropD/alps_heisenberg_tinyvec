/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_OE4_AVX
#define TINYVECTOR_OE4_AVX

#include "multiple_of.hpp"

#include <immintrin.h>
#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct OE4_AVX {};

template <int N, class divisor>
class tv_addinplace_oe4_avx {
    public:
        static inline const tinyvector<N, OE4_AVX> & apply(tinyvector<N, OE4_AVX> &left, const tinyvector<N, OE4_AVX> &right);
};

template <int N>
class tv_addinplace_oe4_avx<N, one> {
    public:
        static inline const tinyvector<N, OE4_AVX> & apply(tinyvector<N, OE4_AVX> &left, const tinyvector<N, OE4_AVX> &right) {
            for(int i = 0; i < N; ++i)
                left[i] += right[i];
            return left;
        }
};

template <int N> 
class tv_addinplace_oe4_avx<N, two> {
    public:
        static inline const tinyvector<N, OE4_AVX> & apply(tinyvector<N, OE4_AVX> &left, const tinyvector<N, OE4_AVX> &right) {
            double * l = left.data();
            const double * r = right.data();
            __m128 mx_left, mx_right, mx_sum;
            for(int i = 0; i < N/2; ++i) {
                // load left & right
                mx_left  = _mm_load_pd(l + 2 * i);
                mx_right = _mm_load_pd(r + 2 * i);
                // add
                mx_sum = _mm_add_pd(mx_left, mx_right);
                // store left
                _mm_store_pd(l + 2 * i, mx_sum);
            }
            return left;
        }
};

template <int N> 
class tv_addinplace_oe4_avx<N, four> {
    public:
        static inline const tinyvector<N, OE4_AVX> & apply(tinyvector<N, OE4_AVX> &left, const tinyvector<N, OE4_AVX> &right) {
            double * l = left.data();
            const double * r = right.data();
            __m256 mx_left, mx_right, mx_sum;
            for(int i = 0; i < N/4; ++i) {
                // load
                mx_left  = _mm256_load_pd(l + 4 * i);
                mx_right = _mm256_load_pd(r + 4 * i);
                // add
                mx_sum = _mm256_add_pd(mx_left, mx_right);
                // store
                _mm256_store_pd(l + 4 * i, mx_sum);
            }
            return left;
        }
};

template <int N>
inline const tinyvector<N, OE4_AVX> & operator+=(tinyvector<N, OE4_AVX> &left, const tinyvector<N, OE4_AVX> &right) {
    return tv_addinplace_oe4_avx<N, typename multiple_of<N>::divisor>::apply(left, right);
}

#endif
