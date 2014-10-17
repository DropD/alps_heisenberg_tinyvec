#ifndef TINIVEC_KERNELS_HPP
#define TINIVEC_KERNELS_HPP

#include <immintrin.h>

/** 
 * determine the vectorization step length, aka how many doubles can we fit into a register? 
 */
#ifdef __AVX__
    #define STEP = 4
struct INTRIN_OPT {};
#else
    #ifdef __SSE2__
        #define STEP = 2
struct INTRIN_OPT {};
    #else
        #define STEP = 1
    #endif
#endif

/**
 * recursively call binary operator kernels 
 */
template <class OP, int N, int M>
struct _vectorize {
    static inline const void apply(tinyvector<double, M, INTRIN_OPT> & left, const vec & right, const int start) {
        _vectorize<OP, STEP>::apply(left, right, start);
        _vectorize<OP, N - STEP>::apply(left, right, start + STEP);
    }
};

template <class OP>
struct _vectorize<OP, 0>
{
    template <class vec>
    static inline const void apply(vec & left, const vec & right, const int start) { }
};

template <class OP>
struct _vectorize<OP, 1>
{
    template <class vec>
    static inline const void apply(vec & left, const vec & right, const int start) {
        OP::apply_single(left, right, start);
    }
};

#ifdef __SSE2__
template <class OP>
struct _vectorize<OP, 2>
{
    template <class vec>
    static inline const void apply(vec & left, const vec & right, const int start) {
        double * l = left.data();
        const double * r = right.data();
        __m128 mml, mmr, mms;
        mml = _mm_load_pd(l + start);
        mmr = _mm_load_pd(r + start);
        mms = OP::apply_sse(mml, mmr);
        __mm_store_pd(l + start, mms);
    }
};
#endif

#ifdef __AVX__
template <class OP>
struct _vectorize<OP, 4>
{
    template <class vec>
    static inline const void apply(vec & left, const vec & right, const int start) {
        double * l = left.data();
        const double * r = right.data();
        __m256 mml, mmr, mms;
        mml = _mm256_load_pd(l + start);
        mmr = _mm256_load_pd(r + start);
        mms = OP::apply_avx(mml, mmr);
        _mm_store_pd(l + start, mms);
    }
};
#endif

struct _plus
{
    template <class vec>
    static inline const void apply_single(vec & left, const vec & right, const int start) {
        left[start] += right[start];
    }
#ifdef __SSE2__
    static inline const __m128 apply_sse(__m128 & mml, __m128 & mmr) {
        return _mm_add_pd(mml, mmr);
    }
#endif
#ifdef __AVX__
    static inline const __m256 apply_avx(__m256 & mml, __m256 & mmr) {
        return _mm256_add_pd(mml, mmr);
    }
#endif
};

struct _minus
{
    template <class vec>
    static inline const void apply_single(vec & left, const vec & right, const int start) {
        left[start] -= right[start];
    }
#ifdef __SSE2__
    static inline const __m128 apply_sse(__m128 & mml, __m128 & mmr) {
        return _mm_sub_pd(mml, mmr);
    }
#endif
#ifdef __AVX__
    static inline const __m256 apply_avx(__m256 & mml, __m256 & mmr) {
        return _mm256_sub_pd(mml, mmr);
    }
};

struct _multiply
{
    template <class vec>
    static inline const void apply_single(vec & left, const vec & right, const int start) {
        left[start] *= right[start];
    }
#ifdef __SSE2__
    static inline const __m128 apply_sse(__m128 & mml, __m128 & mmr) {
        return _mm_mul_pd(mml, mmr);
    }
#endif
#ifdef __AVX__
    static inline const __m256 apply_avx(__m256 & mml, __m256 & mmr) {
        return _mm256_mul_pd(mml, mmr);
    }
};

struct _divide
{
    template <class vec>
    static inline const void apply_single(vec & left, const vec & right, const int start) {
        left[start] /= right[start];
    }
#ifdef __SSE2__
    static inline const __m128 apply_sse(__m128 & mml, __m128 & mmr) {
        return _mm_div_pd(mml, mmr);
    }
#endif
#ifdef __AVX__
    static inline const __m256 apply_avx(__m256 & mml, __m256 & mmr) {
        return _mm256_div_pd(mml, mmr);
    }
#endif
};

/**
 * no vectorization
 */

//~ // standard operator += 
//~ template <int N> struct  _plus { };
//~ 
//~ template <>
//~ struct  _plus<0> {
    //~ static inline const void apply(vec & left, const vec & right, const int start) {}
//~ };
//~ 
//~ template <>
//~ struct _plus<1> {
    //~ template <class vec>
    //~ static inline const void apply(vec & left, const vec & right, const int start) {
        //~ left[start] += right[start];
    //~ }
//~ };
//~ 
//~ // standard operator -= 
//~ template <int N> struct _minus { };
//~ 
//~ template <>
//~ struct _minus<0>
//~ {
    //~ template <class vec>
    //~ static inline const void apply(vec & left, const vec & right, const int start) {}
//~ };
//~ 
//~ template <>
//~ struct _minus<1>
//~ {
    //~ template <class vec>
    //~ static inline const void apply(vec & left, const vec & right, const int start) {
        //~ left[start] -= right[start];
    //~ }
//~ };
//~ 
//~ // standard operator *= 
//~ template <int N> struct _times { };
//~ 
//~ template <>
//~ struct _times<0>
//~ {
    //~ template <class vec>
    //~ static inline const void apply(vec & left, const vec & right, const int start) { }
//~ };
//~ 
//~ template <>
//~ struct _times<1>
//~ {
    //~ template <vec>
    //~ static inline const void apply(vec & left, const vec & right, const int start) {
        //~ left[start] *= right[start];
    //~ }
//~ };
//~ 
//~ // standard operator /= 
//~ template <int N> struct _divide { };
//~ 
//~ template <>
//~ struct _divide<0>
//~ {
    //~ static inline const void apply(vec & left, const vec & right, const int start) { }
//~ };
//~ 
//~ template <>
//~ struct _divide<1>
//~ {
    //~ static inline const void apply(vec & left, const vec & right, const int start) {
        //~ left[start] /= right[start];
    //~ }
//~ };
//~ 
//~ /**
 //~ * SSE kernels
 //~ */
//~ #ifdef __SSE2__
//~ // plus
//~ template <>
//~ struct _plus<2>
//~ {
    //~ static inline const void apply(vec & left, const vec & right, const int start) {
        //~ double * l = left.data();
        //~ const double * r = right.data();
    //~ }
//~ };
//~ <{}>
//~ 
#endif
