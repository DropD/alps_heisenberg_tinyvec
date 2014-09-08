/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_UVEC_MAN_HPP
#define TINYVECTOR_UVEC_MAN_HPP

#include "multiple_of.hpp"

#include <immintrin.h>

#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct UVEC {};

template <int N, int M>
class tv_addinplace_uvec {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            for(int i = start; i < UR::iter; ++i)
                tv_addinplace_uvec<N, 16>::apply(left, right, i * 16);
            tv_addinplace_uvec<N, UR::leftover>::apply(left, right, 16 * UR::iter);
        }
};

template <int N>
class tv_addinplace_uvec<N, 0> {
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {}
};

template <int N> 
class tv_addinplace_uvec<N, 1> {
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            left[start] += right[start];
        }
};

template <int N> 
class tv_addinplace_uvec<N, 2> {
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
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
class tv_addinplace_uvec<N, 3> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 2>::apply(left, right, start);
            left[start + 2] += right[start + 2];
        }
};

template <int N> 
class tv_addinplace_uvec<N, 4> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
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
class tv_addinplace_uvec<N, 5> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 4>::apply(left, right, start);
            left[start + 4] += right[start + 4]; 
        }
};

template <int N> 
class tv_addinplace_uvec<N, 6> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 4>::apply(left, right, start);
            tv_addinplace_uvec<N, 2>::apply(left, right, start + 4);
        }
};

template <int N> 
class tv_addinplace_uvec<N, 7> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 4>::apply(left, right, start);
            tv_addinplace_uvec<N, 3>::apply(left, right, start + 4);
        }
};

template <int N> 
class tv_addinplace_uvec<N, 8> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            double * l = left.data();
            const double * r = right.data();
            __m256 mml1, mmr1, mms1;
            __m256 mml2, mmr2, mms2;

            mml1 = _mm256_load_pd(l + start);
            mmr1 = _mm256_load_pd(r + start);
            mms1 = _mm256_add_pd(mml1, mmr1);
            _mm256_store_pd(l + start, mms1);  

            mml2 = _mm256_load_pd(l + start + 4);
            mmr2 = _mm256_load_pd(r + start + 4);
            mms2 = _mm256_add_pd(mml2, mmr2);
            _mm256_store_pd(l + start + 4, mms2);

        }
};

template <int N> 
class tv_addinplace_uvec<N, 9> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 8>::apply(left, right, start);
            left[start + 8] += right[start + 8];     
        }
};

template <int N> 
class tv_addinplace_uvec<N, 10> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 8>::apply(left, right, start);
            tv_addinplace_uvec<N, 2>::apply(left, right, start + 8);
        }
};

template <int N> 
class tv_addinplace_uvec<N, 11> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 8>::apply(left, right, start);
            tv_addinplace_uvec<N, 3>::apply(left, right, start + 8);
        }
};

template <int N> 
class tv_addinplace_uvec<N, 12> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            double * l = left.data();
            const double * r = right.data();
            __m256 mml1, mmr1, mms1;
            __m256 mml2, mmr2, mms2;
            __m256 mml3, mmr3, mms3;

            mml1 = _mm256_load_pd(l + start);
            mmr1 = _mm256_load_pd(r + start);
            mms1 = _mm256_add_pd(mml1, mmr1);
            _mm256_store_pd(l + start, mms1);  

            mml2 = _mm256_load_pd(l + start + 4);
            mmr2 = _mm256_load_pd(r + start + 4);
            mms2 = _mm256_add_pd(mml2, mmr2);
            _mm256_store_pd(l + start + 4, mms2);

            mml3 = _mm256_load_pd(l + start + 8);
            mmr3 = _mm256_load_pd(r + start + 8);
            mms3 = _mm256_add_pd(mml3, mmr3);
            _mm256_store_pd(l + start + 8, mms3);
        }
};

template <int N> 
class tv_addinplace_uvec<N, 13> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 12>::apply(left, right, start);
            left[start + 12] += right[start + 12];
        }
};

template <int N> 
class tv_addinplace_uvec<N, 14> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 12>::apply(left, right, start);
            tv_addinplace_uvec<N, 2>::apply(left, right, start + 12);
        }
};

template <int N> 
class tv_addinplace_uvec<N, 15> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            tv_addinplace_uvec<N, 12>::apply(left, right, start);
            tv_addinplace_uvec<N, 3>::apply(left, right, start + 12);
        }
};

template <int N> 
class tv_addinplace_uvec<N, 16> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right, const int start) {
            double * l = left.data();
            const double * r = right.data();
            __m256 mml1, mmr1, mms1;
            __m256 mml2, mmr2, mms2;
            __m256 mml3, mmr3, mms3;
            __m256 mml4, mmr4, mms4;

            mml1 = _mm256_load_pd(l + start);
            mmr1 = _mm256_load_pd(r + start);
            mms1 = _mm256_add_pd(mml1, mmr1);
            _mm256_store_pd(l + start, mms1);  

            mml2 = _mm256_load_pd(l + start + 4);
            mmr2 = _mm256_load_pd(r + start + 4);
            mms2 = _mm256_add_pd(mml2, mmr2);
            _mm256_store_pd(l + start + 4, mms2);

            mml3 = _mm256_load_pd(l + start + 8);
            mmr3 = _mm256_load_pd(r + start + 8);
            mms3 = _mm256_add_pd(mml3, mmr3);
            _mm256_store_pd(l + start + 8, mms3); 

            mml4 = _mm256_load_pd(l + start + 12);
            mmr4 = _mm256_load_pd(r + start + 12);
            mms4 = _mm256_add_pd(mml4, mmr4);
            _mm256_store_pd(l + start + 12, mms4);  
        }
};

template <int N>
inline const tinyvector<N, UVEC> & operator+=(tinyvector<N, UVEC> &left, const tinyvector<N, UVEC> &right) {
    tv_addinplace_uvec<N, N>::apply(left, right, 0);
    return left;
}

#endif
