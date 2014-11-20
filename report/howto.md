# HowTo: O(n) Spin Simulation

This document describes how to use the ALPS C++ Libraries to simulate a classical O(n) spin model using local updates.
It is meant as a starting point to write your own spin simulations using ALPS in C++.

## The relevant parts of the API

The following ALPS Headers will be used:

 * alps/mcbase.hpp
 * alps/ngs/numeric.hpp
 * alps/ngs/make_deprecated_parameters.hpp
 * alps/random/uniform_on_sphere_n.hpp
 * alps/lattice.h
 * alps/hdf5/archive.hpp
 * alps/hdf5/vector.hpp
 * alps/hdf5/array.hpp

## A Basic MC Simulation

### Simulation class

The simulation will be a derivate of alps::mcbase which already implements all the common tasks of Monte Carlo simulations. 
The functions specific to a certain model are exposed as virtual functions and must be implemented when writing a simulation.
Take a look at a minimal declaration of an simulation.

```C++ hl_lines="11 13"
/* my_mc_sim.hpp */

#include <alps/mcbase.hpp>
#include <alps/hdf5/archive.hpp>

class ALPS_DECL my_mc_sim : public alps::mcbase {

public:
    my_mc_sim(parameters_type const & parms, std::size_t seed_offset = 0);

    virtual void update(); // this will execute the MC update
    virtual void measure(); // this will perform measurements
    virtual double fraction_completed() const; // this is used as a "progress bar"

    using alps::mcbase::save;
    virtual void save(alps::hdf5::archive & ar) const; // save intermediate state

    using alps::mcbase::load;
    virtual void load(alps::hdf5::archive & ar); // load intermediate state to run from there.

private:
    // internal data
};
```

The highlighted functions `update()` and `measure()` define the behaviour of the model and they are called by mcbase's `run()` method each simulation step.
The Constructor is where parameters can be read into the simulation and internal data can be initialized.
The `save` and `load` functions can be used to store and load intermediate state of the run, allowing interrupted simulations to take up from where they left.

### Main Function
Now here is a basic main program that could be to run the simulation.

```C++
/* my_mc_main.cpp */

#include "my_mc_sim.hpp"
#include <alps/parseargs.hpp>
#include <alps/stop_callback.hpp>


int main(int argc, char *argv[]) {
    // get commandline options and parameters
    alps::parseargs options(argc, argv);
    parameters = alps::parameters_type<sim_type>::type(options.input_file);

    // run the simulation
    my_mc_sim sim(parameters);
    sim.run(alps::stop_callback(options.timelimit)); //run the simulation

    // save the results in a hdf5 archive
    alps::hdf5::archive ar(options.output_file, "w");
    ar["/parameters"] << parameters;
    ar["/simulation/results"] << results;

    return EXIT_SUCCESS;
}
```
