#ifndef BENCH_OP_HPP
#define BENCH_OP_HPP

#include "benchmark.hpp"

#include <iostream>
#include <fstream>
#include <string>

template<class OP>
void bench_op(const char * argv[])
{
    std::string output(argv[1]);
    int max_exponent = atoi(argv[2]);
    
    std::ofstream fout;
    fout.open(output.c_str());
    
    fout << "SIZE" << " "

        << "2D_NO" << " "
        << "3D_NO" << " "
        << "4D_NO" << " "
        << "8D_NO" << " "
        << "16D_NO" << " "

        << "2D_IN" << " "
        << "3D_IN" << " "
        << "4D_IN" << " "
        << "8D_IN" << " "
        << "16D_IN" << " "

    << std::endl;

    for(int i = 16; i < 1<<max_exponent; i *= 2) {
        tv_benchmarker<OP, 2, NO_OPT> no2(i/2);
        tv_benchmarker<OP, 2, INTRIN_OPT> mm2(i/2);

        tv_benchmarker<OP, 3, NO_OPT> no3(i/3);
        tv_benchmarker<OP, 3, INTRIN_OPT> mm3(i/3);

        tv_benchmarker<OP, 4, NO_OPT> no4(i/4);
        tv_benchmarker<OP, 4, INTRIN_OPT> mm4(i/4);

        tv_benchmarker<OP, 8, NO_OPT> no8(i/8);
        tv_benchmarker<OP, 8, INTRIN_OPT> mm8(i/8);

        tv_benchmarker<OP, 16, NO_OPT> no16(i/16);
        tv_benchmarker<OP, 16, INTRIN_OPT> mm16(i/16);

        fout << i << " "
            << no2.calibrate_and_run() << " "
            << no3.calibrate_and_run() << " "
            << no4.calibrate_and_run() << " "
            << no8.calibrate_and_run() << " "
            << no16.calibrate_and_run() << " "

            << mm2.calibrate_and_run() << " "
            << mm3.calibrate_and_run() << " "
            << mm4.calibrate_and_run() << " "
            << mm8.calibrate_and_run() << " "
            << mm16.calibrate_and_run() << " "
            
            << std::endl;

        std::cout << i << " "
            << no2.error() << " "
            << no3.error() << " "
            << no4.error() << " "
            << no8.error() << " "
            << no16.error() << " "

            << mm2.error() << " "
            << mm3.error() << " "
            << mm4.error() << " "
            << mm8.error() << " "
            << mm16.error() << " "
            
            << std::endl;

    }

    fout.close();
}

#endif
