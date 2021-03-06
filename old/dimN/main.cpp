#include "heisenberg.hpp"

#include <alps/ngs.hpp>
#include <alps/ngs/make_parameters_from_xml.hpp>

#include <boost/chrono.hpp>
#include <boost/filesystem/path.hpp>

#include <string>
#include <iostream>
#include <stdexcept>

int main (int argc, char *argv[])
{
    try{
        alps::parseargs options(argc, argv);
        std::string checkpoint_file = options.input_file.substr(0, options.input_file.find_last_of('.')) + ".clone0.h5";
        
        alps::parameters_type<heisenberg_sim>::type parameters;
        if (boost::filesystem::extension(options.input_file) == ".xml")
            parameters = alps::make_parameters_from_xml(options.input_file);
        else if (boost::filesystem::extension(options.input_file) == ".h5")
            alps::hdf5::archive(options.input_file)["/parameters"] >> parameters;
        else
            parameters = alps::parameters_type<heisenberg_sim>::type(options.input_file);

        heisenberg_sim sim(parameters);

        if (options.resume)
            sim.load(checkpoint_file);

        sim.run(alps::stop_callback(options.timelimit));

        sim.save(checkpoint_file);

        using alps::collect_results;
        alps::results_type<heisenberg_sim>::type results = collect_results(sim);

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
