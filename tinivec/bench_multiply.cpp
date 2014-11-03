#include "tinyvector.hpp"
#include "bench_op.hpp"

int main(int argc, char const *argv[])
{
    bench_op<_multiply>("res_multiply.txt");

    return 0;
}
