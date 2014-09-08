#include "bench_plus.hpp"

int main (int argc, char const* argv[])
{

    typedef NO_OPT opt;

    std::vector<double> results_2;
    std::vector<double> results_4;
    std::vector<double> results_8;

    for(int i = 1e2; i < 1e8; 10 * i) {
        tv_benchmarker<2, opt> tb2(i);
        tv_benchmarker<4, opt> tb4(i);
        tv_benchmarker<8, opt> tb8(i);
        tv_benchmarker<16, opt> tb8(i);

        results_2.push_back(tb2.calibrate_and_run())
        results_4.push_back(tb4.calibrate_and_run())
        results_8.push_back(tb8.calibrate_and_run())
        results_8.push_back(tb8.calibrate_and_run())
    }

    return 0;
}
