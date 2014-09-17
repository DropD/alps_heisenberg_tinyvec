#ifndef TVEC_RANDOM_ON_SPHERE_HPP
#define TVEC_RANDOM_ON_SPHERE_HPP

#include <boost/array.hpp>

static const double pi = 3.1415926;

template <int N>
struct tv_ros_impl {
    template<class VEC, class ENGINE>
    static void inline normals(VEC &vector, ENGINE &eng, const int &index) { }
};
 
template <>
struct tv_ros_impl<8> {
    template<class VEC, class ENGINE>
    static void inline normals(VEC &vector, ENGINE &eng, const int &index) {
        __m256 mmu, mmv, mm2;
        __m256 mma, mmb, mmc, mmd, mme;
        __m256 mmx, mmy;

        double a, b, c, d, e, f, g, h;
        a = 2 * eng() - 1; e = 2 * pi * (2 * eng() - 1);
        b = 2 * eng() - 1; f = 2 * pi * (2 * eng() - 1);
        c = 2 * eng() - 1; g = 2 * pi * (2 * eng() - 1);
        d = 2 * eng() - 1; h = 2 * pi * (2 * eng() - 1);

        mmu = _mm256_set_pd(a, b, c, d);
        mmv = _mm256_set_pd(e, f, g, h);
        mm2 = _mm256_set_pd(-2, -2, -2, -2);

        mma = _mm256_log_pd(mmu);
        mmb = _mm256_mul_pd(mma, mm2);
        mmc = _mm256_sqrt_pd(mmb);

        mmd = _m256_sincos_pd(mme, mmv);

        mmx = _mm256_mul_pd(mmc, mme);
        mmy = _mm256_mul_pd(mmc, mmd);

        double * v = vector.data() + index;
        _mm256_store_pd(v, mmx);
        _mm256_store_pd(v + 4, mmy);
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
        tvec_random_on_sphere() : _cursor(16) { }

        template<class ENGINE>
        VEC operator()(ENGINE & eng) {
            VEC random_vector;
            for(int i = 0; i < N; ++i) {
                random_vector[i] = get_buffered(eng);
            }
            return random_vector;
        }

        template<class ENGINE>
        void refresh(ENGINE & eng) {
            tv_ros_impl<16>::normals(_buffer, eng, 0); 
            _cursor = 0;
        }

        template<class ENGINE>
        double get_buffered(ENGINE & eng) {
            if (_cursor >= 16) {
                refresh(eng);
            }
            double normal = _buffer[_cursor];
            ++_cursor;
            return normal;
        }

    private:
        boost::array<double, 16> _buffer __attribute__((aligned(16 * sizeof(double))));
        int _cursor;
};

#endif
