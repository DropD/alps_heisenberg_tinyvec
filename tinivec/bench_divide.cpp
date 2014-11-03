#include "tinyvector.hpp"
#include "bench_op.hpp"

int main(int argc, char const *argv[])
{
    bench_op<_divide>("res_divide.txt");

    return 0;
}
