#ifndef NDIM_SIM_TEST_HPP
#define NDIM_SIM_TEST_HPP

#include "ndim_spin.hpp"

#include <alps/parseargs.hpp>
#include <alps/stop_callback.hpp>
#include <alps/ngs/make_parameters_from_xml.hpp>

#include <boost/chrono.hpp>
#include <boost/filesystem/path.hpp>

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

template<int N, class Opt>
void get_random_tv(std::vector<tinyvector<N, Opt> > & rtv) {
    alps::uniform_on_sphere_n <N, double, std::vector<double> > vgen;
    alps::random01 r01;

    for(int i = 0; i < rtv.size(); ++i)
        rtv[i] = vgen(r01.engine());
}

template<int N, class Opt>
tinyvector<N, Opt> microbench_plus(std::vector<tinyvector<N, Opt> > & rtv) {
    tinyvector<N, Opt> sum;
    for(int j = 0; j < 100000; ++j) {
        for(int i = 0; i < rtv.size(); ++i)
            sum += rtv[i];
    }
    return sum;
}

template<int N, class Opt>
int run_bench_plus(int M) {
    std::vector<tinyvector<N, Opt> > random_tv(M);
    get_random_tv(random_tv);

    std::cout << microbench_plus(random_tv) << std::endl;
    std::cout << "done." << std::endl;
    return 0;
}


template<int N, class Opt>
int run_test(int argc, char *argv[]) {
    typedef ndim_spin_sim<N, Opt> sim_type;
    try {
        alps::parseargs options(argc, argv);
        std::string checkpoint_file = options.input_file.substr(0, options.input_file.find_last_of('.')) +  ".clone0.h5";

        // TODO: make load_params
        typedef typename alps::parameters_type<sim_type>::type param_type;
        param_type parameters;
        // TODO: better check the first few bytes. provide an ALPS function to do so
        if (boost::filesystem::extension(options.input_file) == ".xml") {
            parameters = alps::make_parameters_from_xml(options.input_file);
        }
        else if (boost::filesystem::extension(options.input_file) == ".h5") {
            alps::hdf5::archive(options.input_file)["/parameters"] >> parameters;
        }
        else {
            parameters = param_type(options.input_file);
        }

        sim_type sim(parameters);

        if (options.resume)
            sim.load(checkpoint_file);

        sim.run(alps::stop_callback(options.timelimit));

        sim.save(checkpoint_file);

        using alps::collect_results;
        typename alps::results_type<sim_type>::type results = collect_results(sim);

        std::cout << results << std::endl;
        alps::hdf5::archive ar(options.output_file, "w");
        ar["/parameters"] << parameters;
        ar["/simulation/results"] << results;

    } catch (std::exception const & e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif
