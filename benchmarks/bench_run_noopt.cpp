#include "bench_plus.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main (int argc, char const* argv[])
{
    std::string output = "results.txt";
    if(argc > 1)
        output = argv[1];

    std::ofstream fout;
    fout.open(output.c_str());

    typedef NO_OPT opt;

    std::cout << "SIZE" << " ";
    std::cout << "2D" << " ";
    std::cout << "4D" << " ";
    std::cout << "8D" << " ";
    std::cout << "16D" << " ";
    std::cout << "32D" << std::endl;

    for(int i = 16; i < 1<<16; i *= 2) {
        tv_benchmarker<2, opt> tb2(i);
        tv_benchmarker<4, opt> tb4(i);
        tv_benchmarker<8, opt> tb8(i);
        tv_benchmarker<16, opt> tb16(i);
        tv_benchmarker<32, opt> tb32(i);

        std::cout << i << " "
                  << tb2.calibrate_and_run() << " "
                  << tb4.calibrate_and_run() << " "
                  << tb8.calibrate_and_run() << " "
                  << tb16.calibrate_and_run() << " "
                  << tb32.calibrate_and_run() << " "
                  << std::endl;

        fout      << i << " "
                  << tb2.result() << " " << tb4.result() << " " << tb8.result() << " "
                  << tb16.result() << " " << tb32.result()
                  << std::endl;
    }

    fout.close();

    return 0;
}
