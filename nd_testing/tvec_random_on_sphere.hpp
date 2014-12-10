#ifndef TVEC_RANDOM_ON_SPHERE_HPP
#define TVEC_RANDOM_ON_SPHERE_HPP

#define USE_SSE_AUTO
#define SSE_MATHFUN_WITH_CODE
#include "sse_mathfun.h"

#include <boost/array.hpp>

#ifndef MyPI
#define MyPI 3.1415926
#endif

template <int N>
struct tv_ros_impl {
    template<class VEC, class ENGINE>
    static void inline normals(VEC &vector, ENGINE &eng, const int &index) {}
};
 
template <>
struct tv_ros_impl<8> {
    template<class VEC, class ENGINE>
    static void inline normals(VEC &vector, ENGINE &eng, const int &index) {
        __m128 mmu, mmv, mm2;
        __m128 mma, mmb, mmc, mmd, mme;
        __m128 mmx, mmy;

        float a, b, c, d, e, f, g, h;
        a = 2 * eng() - 1; e = 2 * MyPI * (2 * eng() - 1);
        b = 2 * eng() - 1; f = 2 * MyPI * (2 * eng() - 1);
        c = 2 * eng() - 1; g = 2 * MyPI * (2 * eng() - 1);
        d = 2 * eng() - 1; h = 2 * MyPI * (2 * eng() - 1);

        mmu = _mm_set_ps(a, b, c, d);
        mmv = _mm_set_ps(e, f, g, h);
        mm2 = _mm_set_ps(-2, -2, -2, -2);

        mma = log_ps(mmu);
        mmb = _mm_mul_ps(mma, mm2);
        mmc = _mm_sqrt_ps(mmb);

        sincos_ps(mmv, &mmd, &mme);

        mmx = _mm_mul_ps(mmc, mme);
        mmy = _mm_mul_ps(mmc, mmd);

        float * v = vector.data() + index;
        _mm_store_ps(v, mmx);
        _mm_store_ps(v + 4, mmy);
    } 
};

template <>
struct tv_ros_impl<16> {
    template<class VEC, class ENGINE>
    static void inline normals(VEC &vector, ENGINE &eng, const int &index) {
        tv_ros_impl<8>::normals(vector, eng, index);
        tv_ros_impl<8>::normals(vector, eng, index + 8);
    }
};
 
template<int N, class VEC>
class tvec_random_on_sphere {

    public:
        tvec_random_on_sphere() : _cursor(16) {}

        template <class ENGINE>
        VEC operator()(ENGINE &eng) {
            VEC random_vector;
            for (int i = 0; i < N; ++i) {
                random_vector[i] = get_buffered(eng);
            }
            return random_vector;
        }

        template <class ENGINE>
        void refresh(ENGINE &eng) {
            tv_ros_impl<16>::normals(_buffer, eng, 0);
            _cursor = 0;
        }

        template <class ENGINE>
        double get_buffered(ENGINE & eng) {
            if(_cursor >= 16)
            {
                refresh(eng);
            }
            double normal = double(_buffer[_cursor]);
            ++_cursor;
            return normal;
        }

    private:
        boost::array<float, 16> _buffer __attribute__((aligned( 16 * sizeof(float))));
        int _cursor;
};

#endif
