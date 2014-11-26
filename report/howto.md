# HowTo: O(n) Spin Simulation

This document describes how to use the ALPS C++ Libraries to simulate a classical O(n) spin model using local updates.
It is meant as a starting point to write your own spin simulations using ALPS in C++. The code examples are shortened for readability and may or may not compile.

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

### Running the Simulation
Now here is a basic main program that could be used to run the simulation.
All except the highlighted lines of the main body deal with I/O for parameters and results.
This progam assumes the name of a parameter file and optionally an output file to be given as a commandline argument. 

```C++ hl_lines="13 14"
/* my_mc_main.cpp */

#include "my_mc_sim.hpp"
#include <alps/parseargs.hpp>
#include <alps/stop_callback.hpp>

int main(int argc, char *argv[]) {
    // get commandline options and parameters
    alps::parseargs options(argc, argv);
    parameters = alps::parameters_type<sim_type>::type(options.input_file);

    // create and run the simulation
    my_mc_sim sim(parameters);
    sim.run(alps::stop_callback(options.timelimit));

    // save the results in a hdf5 archive
    alps::hdf5::archive ar(options.output_file, "w");
    ar["/parameters"] << parameters;
    ar["/simulation/results"] << results;

    return EXIT_SUCCESS;
}
```

## Implementing the Model
The model used in this example is the O(N) model, a generalization of the Ising Model to spins of N dimensions.
Special cases include the XY (N = 2) and Heisenberg (N = 3) models.
The generalization is achieved in this example by templating the simulation class on the dimension N.

```C++
#include "tinyvector.hpp"
template <int N>
class ALPS_DECL my_mc_sim : public alps::mcbase {
    public:
        typedef tinyvector<double, N> spintype;
    private:
        std::vector< spintype > spins;
        alps::graph_helper<> lattice;
};
```

The class template `tinyvector` (provided in the code) is a wrapper around boost::array with appropriate operators.
The simulation class contains a vector of tinyvectors as a representation of the system's spins.

Next it needs a datastructure to hold the topology of the system. 
ALPS provides the Lattice classes for this purpose we access the lattices via the `graph_helper` class template.
Refer to the documentations for alps::lattice and boost::graph for more detail.

### The update() function
This method contains the monte carlo step of the model, in this case a single spin update.

The `random_spin` method is a convenience wrapper around ALPS' `uniform_on_sphere_n` functionality 
which provides normalized direction vectors uniformly distributed across an n-dimensional sphere.

```C++
template<int N>
void my_mc_sim< N >::update() {
    for (int j = 0; j < num_sites; ++j) {

        // get a random site
        int i = int(double(num_sites) * random());
        site_descriptor site_i = lattice.site(i);

        // sum of neighbors
        spintype nn_sum;
        nn_sum.initialize(0);
        neighbor_iterator nn_it, nn_end;
        for (boost::tie(nn_it, nn_end) = lattice.neighbors(site_i); nn_it != nn_end; ++nn_it) {
            nn_sum += spins[*nn_it];
        }

        // single spin update, accept if delta_H < 0 or with probability p
        spintype new_spin = random_spin();
        double delta_H = dot(new_spin - spins[i], nn_sum);
        double p = exp( -beta * delta_H );
        if ( p >= 1. || random() < p )
            spins[i] = new_spin;
    }
}
```

### The measure() function
 
## API Headers for reference

The following ALPS Headers will be used:

 * alps/mcbase.hpp
 * alps/ngs/numeric.hpp
 * alps/ngs/make_deprecated_parameters.hpp
 * alps/random/uniform_on_sphere_n.hpp
 * alps/lattice.h
 * alps/hdf5/archive.hpp
 * alps/hdf5/vector.hpp
 * alps/hdf5/array.hpp
 
