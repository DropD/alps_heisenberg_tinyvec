#ifndef TVEC_BENCHMARKER_HPP
#define TVEC_BENCHMARKER_HPP

#include "tinyvector.hpp"
#include "rdtsc.h"

#include <alps/ngs/random01.hpp>
#include <alps/random/uniform_on_sphere_n.h>

#include <vector>
#include <iostream>

template<class Op, int N, class Opt>
class tv_benchmarker {
    public:
        typedef tinyvector<double, N, Opt> tinivec;
        tv_benchmarker(int size) : data(size, tinivec(0)),  _result(0), _error(0) {
            for(int i = 0; i < size; ++i) {
                tinivec tmp;
                tmp.initialize(0);
                tmp = random_spin();
                std::cout << "tmp: " << tmp << std::endl;
                std::cout << "size: " << size << std::endl;
                std::cout << "data size: " << data.size() << std::endl;
                std::cout << "i: " << i << std::endl;
                data[i] = tmp;
                std::cout << data[i] << std::endl;
            }
            //~ _result.initialize(0);
            //~ _error.initialize(0);
            std::cout << "err = " << _error << std::endl;
        }

        double calibrate_and_run() {
            std::cout << "err = " << _error << std::endl;
            int num_runs = 1;
            double cycles;
            tsc_counter start, end;
            while(num_runs < (1<<14)) {
                CPUID(); RDTSC(start);
                for(int i = 0; i < num_runs; ++i) {
                    run();
                }
                RDTSC(end); CPUID();

                cycles = (double)(COUNTER_DIFF(end, start));
                if(cycles >= 1e8) break;
                num_runs *= 2;
            }


            tinivec sumsum, refsum;
            sumsum.initialize(0);
            CPUID(); RDTSC(start);
            for(int i = 0; i < num_runs; ++i)
                sumsum += run();
            RDTSC(end); CPUID();

            refsum.initialize(0);
            for(int i = 0; i < num_runs; ++i) {
                tinivec rs;
                rs.initialize(0);
                for(int j = 0; j < data.size(); ++j) {
                    for(int k = 0; k < N; ++k)
                        Op::apply(rs[k], data[j][k]);
                }
                refsum += rs;
            }

            cycles = (double)(COUNTER_DIFF(end, start)) / num_runs;
            _result = sumsum;
            for(int i = 0; i < N; ++i)
                _error[i]  = sumsum[i] - refsum[i];

            std::cout << "sumsum = " << sumsum << std::endl;
            std::cout << "refsum = " << refsum << std::endl;
            std::cout << "err = " << _error << std::endl;

            const double tol = 1e-4;
            for(int i = 0; i < N; ++i) {
                double diff = _error[i];
                if(diff > tol || diff < -tol) {
                    cycles = -cycles;
                    break;
                }
            }
            return cycles;
        }

        tinivec run() {
            tinivec sum;
            sum.initialize(0);
            for(int i = 0; i < data.size(); ++i)
                Op::apply(sum, data[i]);
            return sum;
        }

        tinivec result() { return _result; }
        tinivec error() { return _error; }

        tinivec  random_spin() {
            return vgen(r01.engine());
        }

    private:
        std::vector<tinivec> data __attribute__(( aligned( 16 * sizeof(double) )));
        alps::random01 r01;
        alps::uniform_on_sphere_n<N, double, tinivec> vgen;
        tinivec _result, _error __attribute__(( aligned( 16 * sizeof(double) )));
};

#endif
