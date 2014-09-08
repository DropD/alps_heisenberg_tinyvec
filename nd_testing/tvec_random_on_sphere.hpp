#ifndef TVEC_RANDOM_ON_SPHERE_HPP
#define TVEC_RANDOM_ON_SPHERE_HPP

#ifndef PI
#define PI 3.1415926
#endif

template<int N, class VEC, class ENGINE>
class tvec_random_on_sphere {
    tvec_random_on_sphere(ENGINE & eng) : _eng(eng), _buffer(16) {}
    VEC operator()() {
        VEC random_vector;
        tv_ros_impl<N>(random_vector, _eng, 0);
        return random_vector;
    }
    private:
        ENGINE & _eng;
        std::vector<double> _buffer;
}

template <int N>
struct tv_ros_impl {
    template<class VEC, class ENGINE>
    static void inline normals(VEC &vector, ENGINE &eng, const int &index) {
        tv_ros_impl<8>(vector, eng, index);
        tv_ros_impl<N-8>(vector, eng, index + 8);
    }
};

template <>
struct tv_ros_impl<8> {
    template<class VEC, class ENGINE>
    static void inline normals(VEC &vector, ENGINE &eng, const int &index) {
        __m256 mmu, mmv, mm2;
        __m256 mma, mmb, mmc, mmd, mme;
        __m256 mmx, mmy;

        double a, b, c, d, e, f, g, h;
        a = 2 * eng() - 1; e = 2 * PI * (2 * eng() - 1);
        b = 2 * eng() - 1; f = 2 * PI * (2 * eng() - 1);
        c = 2 * eng() - 1; g = 2 * PI * (2 * eng() - 1);
        d = 2 * eng() - 1; h = 2 * PI * (2 * eng() - 1);

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


#endif
