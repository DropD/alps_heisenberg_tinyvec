#ifndef BENCHMARK_TWO_HPP   
#define BENCHMARK_TWO_HPP   

#include "rdtsc.h"
#include "tinyvector.hpp"

#include <alps/ngs/random01.hpp>
#include <alps/random/uniform_on_sphere_n.h>

#include <vector>
#include <iostream>
#include <exception>

struct wrong_result_exception : public std::exception {
    const char* what() const _NOEXCEPT{ return "wrong result"; }
};

#define RUN_OP(result, data, op) \
    for(int i = 0; i < size; ++i) {     \
        op::apply(result[i], data[i]);     \
    }

#define CALIBRATE_AND_RUN(result, data, op, cycles) \
    while(num_runs < (1<<20)) {                                 \
        CPUID(); RDTSC(start);                                  \
        for(int r = 0; r < num_runs; ++r) {                     \
            RUN_OP(result, data, op)                            \
        }                                                       \
        RDTSC(end); CPUID();                                    \
                                                                \
        cycles = (double)(COUNTER_DIFF(end, start));            \
        if(cycles >= 5e8) break;                                \
        num_runs *= 2;                                          \
    }                                                           \
    /*result.initialize(0);*/                                       \
    CPUID(); RDTSC(start);                                      \
    RUN_OP(result, data, op);                                   \
    RDTSC(end); CPUID();                                        \
    cycles = (double)(COUNTER_DIFF(end, start)) / num_runs;     \
    num_runs = 1;

#define BENCHMARK_OP(nres, ndat, ores, odat, op, nc, oc, su) \
    for(int i = 0; i < size; ++i) {                          \
        tinyvec tmp = ngen(r01.engine());                    \
        rn[i] = tmp;                                         \
        ro[i] = tmp;                                         \
    }                                                        \
                                                             \
    nc = oc = 0;                                             \
    CALIBRATE_AND_RUN(nres, ndat, op, nc);                   \
    CALIBRATE_AND_RUN(ores, odat, op, oc);                   \
    su = nc/oc;                                              \
                                                             \
    try {                                                    \
        for(int i = 0; i < N; ++i) {                         \
            for(int j = 0; j < N; ++j) {                     \
                double diff = nres[i][j] - ores[i][j];       \
                if (diff > tol || diff < -tol) {             \
                    throw wrong_result_exception();          \
                }                                            \
            }                                                \
        }                                                    \
    }                                                        \
    catch (std::exception e) {                               \
        std::cout << e.what();                               \
        return 1;                                            \
    }
 


template<int N>
tinyvector<double, 4, NO_OPT> benchmark_test(int ndoubles) {
    typedef tinyvector<double, N, NO_OPT>     tinyvec;
    typedef tinyvector<double, N, INTRIN_OPT> opttvec;

    alps::random01 r01;
    alps::uniform_on_sphere_n<N, double, tinyvec> ngen;

    int size = ndoubles / N;
    std::vector<tinyvec> rn(size), resn(size);
    std::vector<opttvec> ro(size), reso(size);

    tinyvec nres(0);
    opttvec ores(0);

    tinyvector<double, 4, NO_OPT> speedups(0);
    
    // run benchmarks
    int num_runs = 1;
    double ncycles, ocycles;
    tsc_counter start, end;
    double tol = 1e-4;

    BENCHMARK_OP(resn, rn, reso, ro, _plus,     ncycles, ocycles, speedups[0]);
    BENCHMARK_OP(resn, rn, reso, ro, _minus,    ncycles, ocycles, speedups[1]);
    BENCHMARK_OP(resn, rn, reso, ro, _divide,   ncycles, ocycles, speedups[2]);
    BENCHMARK_OP(resn, rn, reso, ro, _multiply, ncycles, ocycles, speedups[3]);

    return speedups;

}

#endif
