#include "tinyvector.hpp"
#include "bench_op.hpp"

int main(int argc, char const *argv[])
{
    bench_op<_plus>("res_plus.txt");

    return 0;
}
