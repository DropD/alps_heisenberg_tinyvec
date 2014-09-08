#include "bench_plus.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main (int argc, char const* argv[])
{
    double a, b, c;

    std::cout << "i " << "2D " << "3D " << "4D" << std::endl;

    for(int i = 16; i < 1<<16; i *= 2) {
        tv_benchmarker<2, UVEC> uv2(i);
        tv_benchmarker<3, UVEC> uv3(i);
        tv_benchmarker<4, UVEC> uv4(i);

        std::cout << i << " ";

        a = uv2.calibrate_and_run();
        std::cout << uv2.error() << " ";

        b = uv3.calibrate_and_run();
        std::cout << uv3.error() << " ";

        c = uv4.calibrate_and_run();
        std::cout << uv4.error() << std::endl;
    }

    return 0;
}
