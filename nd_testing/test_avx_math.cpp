#define USE_SSE_AUTO
#define SSE_MATHFUN_WITH_CODE
#include "sse_mathfun.h"

#include <immintrin.h>

#include <boost/random.hpp>
#include <boost/array.hpp>

#include <vector>
#include <cmath>
#include <iostream>


template <class RealType>
struct random01 : public boost::variate_generator<boost::mt19937, boost::uniform_01<RealType> > {
    random01(int seed = 42) 
        : boost::variate_generator<boost::mt19937, boost::uniform_01<RealType> >(boost::mt19937(seed), boost::uniform_01<RealType>()) 
    {} 
};

int main(int argc, char const *argv[]) {

    const int N = 4;

    random01<float>  rand_s(42);
    random01<double> rand_d(42);
    typedef boost::array<float, N> v4ps __attribute__((aligned(8 * sizeof(float))));
    typedef boost::array<double, N> v4pd __attribute__((aligned(8 * sizeof(double))));
    v4ps input, sinus, cosinus;
    v4pd input_pd, sinus_pd, cosinus_pd;

    std::cout << "bla 2" << std::endl;

    for (int i = 0; i < N; ++i) {
        double r = 3.1415926536 * (4. * rand_d() - 2.); 
        input_pd[i] = r;
        input[i] = float(r);
        sinus[i] = -1.;
        cosinus[i] = -1.;
        sinus_pd[i] = -1;
        cosinus_pd[i] = -1;
    }

    __m128 i, s, c;
    i = _mm_load_ps( input.data() );
    sincos_ps(i, &s, &c);
    _mm_store_ps( sinus.data(), s );
    _mm_store_ps( cosinus.data(), c );

    __m256 id, sd, cd;
    id = _mm256_load_pd( input_pd.data() );
    sincos256_pd(id, &sd, &cd);
    _mm256_store_pd( sinus_pd.data(), sd );
    _mm256_store_pd( cosinus_pd.data(), cd );

    for (int i = 0; i < N; ++i) {

        double s0 = sinus_pd[i];
        float s1  = sinus[i];
        double s2 = std::sin(input[i]);

        double c0  = cosinus_pd[i];
        float c1  = cosinus[i];
        double c2 = std::cos(input[i]);

        double es0 = s0 - s2;
        double ec0 = c0 - c2;
        float es1 = s1 - float(s2);
        float ec1 = c1 - float(c2);

        std::cout << "sin(" << input[i] << ") = [ " << s0 << ", " << s1 << ", " << s2 << "] -> Error: " << es0 << ", " << es1 << std::endl;
        std::cout << "cos(" << input[i] << ") = [ " << c0 << ", " << c1 << ", " << c2 << "] -> Error: " << ec0 << ", " << ec1 << std::endl;
    }
}
