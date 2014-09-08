#include "test.hpp"

int main(int argc, char *argv[]) {
    return run_bench_plus<16, NO_OPT>(10000);
}
