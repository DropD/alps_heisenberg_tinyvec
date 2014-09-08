/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_ULTIMATE_HPP
#define TINYVECTOR_ULTIMATE_HPP

#include "multiple_of.hpp"

#include <immintrin.h>

#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct TVEC {};

template <int N, template<int, int> class OP>
class tv_inplace_tvec {
    typedef unroll_16<N> UR;
    public:
        template <class R>
        static inline const void apply(tinyvector<N, TVEC> &left, R &right, const int start) {
            //~ for(int i = start; i < UR::iter; ++i)
                //~ OP<N, 16>::apply(left, right, i * 16);
            //~ OP<N, UR::leftover>::apply(left, right, 16 * UR::iter);
            OP<N, N>::apply(left, right, start);
        }
};

template <int N, int M>
class PLUS {
    public:
        static inline const void apply(tinyvector<N, TVEC> &left, const tinyvector<N, TVEC> &right, const int start) {
            PLUS<N, 4>::apply(left, right, start);
            PLUS<N, M-4>::apply(left, right, start + 4);
        }
};

template <int N>
class PLUS<N, 0> {
    public:
        static inline const void apply(tinyvector<N, TVEC> &left, const tinyvector<N, TVEC> &right, const int start) {}
};

template <int N> 
class PLUS<N, 1> {
    public:
        static inline const void apply(tinyvector<N, TVEC> &left, const tinyvector<N, TVEC> &right, const int start) {
            left[start] += right[start];
        }
};

template <int N> 
class PLUS<N, 2> {
    public:
        static inline const void apply(tinyvector<N, TVEC> &left, const tinyvector<N, TVEC> &right, const int start) {
            double * l = left.data();
            const double * r = right.data();
            __m128 mml, mmr, mms;
            mml = _mm_load_pd(l + start);
            mmr = _mm_load_pd(r + start);
            mms = _mm_add_pd(mml, mmr);
            _mm_store_pd(l + start, mms);
        }
};

template <int N> 
class PLUS<N, 3> {
    public:
        static inline const void apply(tinyvector<N, TVEC> &left, const tinyvector<N, TVEC> &right, const int start) {
            PLUS<N, 2>::apply(left, right, start);
            left[start + 2] += right[start + 2];
        }
};

template <int N> 
class PLUS<N, 4> {
    public:
        static inline const void apply(tinyvector<N, TVEC> &left, const tinyvector<N, TVEC> &right, const int start) {
            double * l = left.data();
            const double * r = right.data();
            __m256 mml, mmr, mms;
            mml = _mm256_load_pd(l + start);
            mmr = _mm256_load_pd(r + start);
            mms = _mm256_add_pd(mml, mmr);
            _mm256_store_pd(l + start, mms); 
        }
};

template <int N>
inline const tinyvector<N, TVEC> & operator+=(tinyvector<N, TVEC> &left, const tinyvector<N, TVEC> &right) {
    tv_inplace_tvec<N, PLUS>::apply(left, right, 0);
    return left;
}

#endif
