#ifndef HEISENBERG_HPP
#define HEISENBERG_HPP

#include <alps/ngs.hpp>

#include <boost/function.hpp>
#include <boost/filesystem/path.hpp>

#include <vector>
#include <string>

typedef std::vector<double> dvec;

class ALPS_DECL heisenberg_sim : public alps::mcbase {

    public:

        heisenberg_sim(parameters_type const & params, std::size_t seed_offset = 0);

        virtual void update();
        virtual void measure();
        virtual double fraction_completed() const;

        using alps::mcbase::save;
        virtual void save(alps::hdf5::archive & ar) const;

        using alps::mcbase::load;
        virtual void load(alps::hdf5::archive & ar);

    private:
        dvec get_random_spin();

    private:

        int length;
        int sweeps;
        int thermalization_sweeps;
        int total_sweeps;
        double beta;
        std::vector<dvec> spins;
        int spin_dim;

};
 
inline dvec operator+ (dvec lhs, dvec rhs);

inline double operator* (dvec lhs, dvec rhs);

inline dvec operator* (double lhs, dvec rhs);

inline dvec operator/ (dvec lhs, double rhs);

inline double abs(dvec vec);

#endif
