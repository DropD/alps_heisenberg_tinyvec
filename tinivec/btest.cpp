#include "benchmark_2.hpp"
#include <iostream>
#include <fstream>

int main (int argc, char const* argv[])
{
    if (argc < 3) {
        std::cout << "usage: btest n <outfile>" << std::endl;
        return 1;
    }

    std::cout << "starting test from " << 16 << " to " << (1<<atoi(argv[1])) << std::endl;
    std::cout << "writing results to " << argv[2] << std::endl;

    std::ofstream fout;
    fout.open(argv[2]);

    for(int i = 7; i < atoi(argv[1]); ++i) {
        int size = 1 << i;
        fout << size << " "
            << benchmark_test<2>(size)
            << benchmark_test<3>(size) 
            << benchmark_test<4>(size) 
            << benchmark_test<8>(size) 
            << benchmark_test<16>(size)
            << std::endl;
    }                                     

    fout.close();
    
    return 0;
}
