#include "tinyvector.hpp"
#include "bench_op.hpp"

int main(int argc, char const *argv[])
{
    bench_op<_multiply>("bm_multiply.dat");

    return 0;
}
