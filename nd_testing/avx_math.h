#ifndef AVX_MATH_H
#define AVX_MATH_H

#include <immintrin.h>

inline __m256 _mm256_sincos_pd(__m256 * mem_addr, __m256 x) {
    __m256 xmm1, xmm2, sign_bit_sin, y, y2, z, swap_sign_bit_sin, poly_mask; 
    __m256 sign_bit_cos;
    __m256 pi_div_4, minus_cephes_DP1, minus_cephes_DP2, minus_cephes_DP3;
    __m256 coscof_p0, coscof_p1, coscof_p2, pd_1, pd_0p5;
    __m256 sincof_p0, sincof_p1, sincof_p2;
    __m128i emm2, pi32_0, pi32_1, pi32_inv1, pi32_2, pi32_4;
    __m256 inv_sign_mask, sign_mask;

    const long long sm  =  0x8000000000000000LL;
    const long long ism = ~0x8000000000000000LL;

    const double pd4    =  1.27323954473516;

    const double mcc1   =  -0.78515625;
    const double mcc2   =  -2.4187564849853515625e-4;
    const double mcc3   =  -3.77489497744594108e-8;

    const double ccp0   =  2.443315711809948E-005;
    const double ccp1   = -1.388731625493765E-003;
    const double ccp2   =  4.166664568298827E-002;

    const double scp0   = -1.9515295891E-4;
    const double scp1   =  8.3321608736E-3;
    const double scp2   = -1.6666654611E-1;

    inv_sign_mask = _mm256_set_epi64x(ism, ism, ism, ism);
    sign_mask = _mm256_set_epi64x(sm, sm, sm, sm);

    pi_div_4 = _mm256_set_pd(pd4, pd4, pd4, pd4);
    pd_1 = _mm256_set_pd(1., 1., 1., 1.);
    pd_0p5 = _mm256_set_pd(0.5, 0.5, 0.5, 0.5);

    pi32_0 = _mm_set_epi32(0, 0, 0, 0);
    pi32_1 = _mm_set_epi32(1, 1, 1, 1);
    pi32_inv1 = _mm_set_epi32(~1, ~1, ~1, ~1);
    pi32_2 = _mm_set_epi32(2, 2, 2, 2);
    pi32_4 = _mm_set_epi32(4, 4, 4, 4);

    minus_cephes_DP1 = _mm256_set_pd(mcc1, mcc1, mcc1, mcc1);
    minus_cephes_DP2 = _mm256_set_pd(mcc2, mcc2, mcc2, mcc2);
    minus_cephes_DP3 = _mm256_set_pd(mcc3, mcc3, mcc3, mcc3);

    coscof_p0 = _mm256_set_pd(ccp0, ccp0, ccp0, ccp0);
    coscof_p1 = _mm256_set_pd(ccp1, ccp1, ccp1, ccp1);
    coscof_p2 = _mm256_set_pd(ccp2, ccp2, ccp2, ccp2);

    sincof_p0 = _mm256_set_pd(scp0, scp0, scp0, scp0);
    sincof_p1 = _mm256_set_pd(scp1, scp1, scp1, scp1);
    sincof_p2 = _mm256_set_pd(scp2, scp2, scp2, scp2);

    sign_bit_sin = x;

    /* take the absolute value */
    x = _mm256_and_pd(x, inv_sign_mask);
    /* extract the sign bit (upper one) */
    sign_bit_sin = _mm256_and_pd(sign_bit_sin, sign_mask);

    /* scale by 4 / Pi */
    y = _mm256_mul_pd(x, pi_div_4);
    /* store int part of y in emm2 */
    emm2 = _mm256_cvttpd_epi32(y);

    /* j = (j + 1) & (~1) (see cephes sources) */
    emm2 = _mm_and_epi32( _mm_add_epi32( _mm256_cvttpd_epi32(y), pi32_1), pi32_inv1);
    y = _mm256_cvtepi32_pd(emm2);

    /* get the swap sign flag for the sine */
    swap_sign_bit_sin = _mm256_cvtps_pd(_mm_castepi32_ps( _mm_slli_epi32( _mm_and_epi32(emm2, pi32_2), 29) ));

    /* get the polynom selection mask for the sine */
    poly_mask         = _mm256_cvtps_pd(_mm_castepi32_ps( _mm_cmpeq_epi32( _mm_and_epi32(emm2, pi32_2), pi32_0) ));

    /* The magic pass: "Extended precision modular arithmetic"
     x = ((x - y * DP1) - y * DP2) - y * DP3; */
    __m256 temp1 = _mm256_add_pd(minus_cephes_DP1, minus_cephes_DP2);
    __m256 temp2 = _mm256_add_pd(temp1, minus_cephes_DP3);
    x = _mm256_add_pd( x, _mm256_mul_pd( y, temp2 ) );

    __m128 temp3 = _mm_sub_epi32(emm2, pi32_2);
    __m128 temp4 = _mm_andnot_epi32(temp3, pi32_4);
    __m128 temp5 = _mm_slli_epi32(temp4, 29);
    sign_bit_cos = _mm256_cvtps_pd(_mm_castepi32_ps( temp5 ));

    sign_bit_sin = _mm256_xor_pd(sign_bit_sin, swap_sign_bit_sin);

    /* evaluate the first polynom (0 <= x <= Pi/4) */
    z = _mm256_mul_pd(x, x);
    __m256 temp_c0 = _mm256_mul_pd(coscof_p0, z);
    __m256 temp_c1 = _mm256_add_pd(temp_c0, coscof_p1);
    __m256 temp_c2 = _mm256_mul_pd(temp_c1, z);
    __m256 temp_c3 = _mm256_add_pd(temp_c2, coscof_p2);
    __m256 temp_c4 = _mm256_mul_pd(temp_c3, z);
    __m256 temp_c5 = _mm256_sub_pd(temp_c4, pd_0p5);
    __m256 temp_c6 = _mm256_mul_pd(temp_c5, z);
    y = _mm256_mul_pd(temp_c6, pd_1);

    /* evaluate the second polynom (Pi / 4 <= x <= 0) */
    __m256 temp_s0 = _mm256_mul_pd(sincof_p0, z);
    __m256 temp_s1 = _mm256_add_pd(temp_s0, sincof_p1);
    __m256 temp_s2 = _mm256_mul_pd(temp_s1, z);
    __m256 temp_s3 = _mm256_add_pd(temp_s2, sincof_p2);
    __m256 temp_s4 = _mm256_mul_pd(temp_s3, z);
    __m256 temp_s5 = _mm256_add_pd(temp_s4, pd_1);
    y2 = _mm256_mul_pd(temp_s5, x);

    /* select the correct result from the two polynoms */
    xmm1 = _mm256_add_pd( _mm256_andnot_pd(poly_mask, y), _mm256_and_pd(poly_mask, y2) );
    xmm2 = _mm256_sub_pd( _mm256_add_pd(y, y2), xmm1 );
    /* update the sign */
    (*mem_addr) = _mm256_xor_pd(xmm2, sign_bit_cos);
    return _mm256_xor_pd(xmm1, sign_bit_sin);
}

#endif
