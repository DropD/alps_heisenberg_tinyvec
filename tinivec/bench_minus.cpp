#include "tinyvector.hpp"
#include "bench_op.hpp"

int main(int argc, char const *argv[])
{
    bench_op<_minus>("res_minus.txt");

    return 0;
}
