#include "benchmark.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main (int argc, char const* argv[])
{
    std::string output = "plus.txt";
    if(argc > 1)
        output = argv[1];

    std::ofstream fout;
    fout.open(output.c_str());

    std::cout << "SIZE" << " "

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

    for(int i = 1; i < 1<<20; i *= 2) {
        tv_benchmarker<_plus, 2, NO_OPT> no2(i);
        tv_benchmarker<_plus, 2, INTRIN_OPT> mm2(i);

        tv_benchmarker<_plus, 3, NO_OPT> no3(i);
        tv_benchmarker<_plus, 3, INTRIN_OPT> mm3(i);

        tv_benchmarker<_plus, 4, NO_OPT> no4(i);
        tv_benchmarker<_plus, 4, INTRIN_OPT> mm4(i);

        tv_benchmarker<_plus, 8, NO_OPT> no8(i);
        tv_benchmarker<_plus, 8, INTRIN_OPT> mm8(i);

        tv_benchmarker<_plus, 16, NO_OPT> no16(i);
        tv_benchmarker<_plus, 16, INTRIN_OPT> mm16(i);

        std::cout << i << " "
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

        fout << i << " "
            << no2.result() << " "
            << no3.result() << " "
            << no4.result() << " "
            << no8.result() << " "
            << no16.result() << " "

            << mm2.result() << " "
            << mm3.result() << " "
            << mm4.result() << " "
            << mm8.result() << " "
            << mm16.result() << " "

            << std::endl;

    }

    fout.close();

    return 0;
}
