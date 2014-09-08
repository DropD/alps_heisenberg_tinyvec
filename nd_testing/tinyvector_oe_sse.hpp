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

template <int N, class divisor>
class tv_addinplace_oe_sse {
    public:
        static inline const tinyvector<N, OE_SSE> & apply(tinyvector<N, OE_SSE> &left, const tinyvector<N, OE_SSE> &right) {
            double * l = left.data();
            const double * r = right.data();
            __m128 mx_left, mx_right, mx_sum;
            for(int i = 0; i < N/2; ++i) {
                // load left & right
                mx_left =  _mm_load_pd(l + 2 * i);
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

#endif
