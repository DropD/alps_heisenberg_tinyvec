#include "tinyvector.hpp"

#include <vector>

template<class TV>
TV sum(std::vector<TV> vec) {
    double * v = vec.data();
    num_doubles = vec.size() * TV::dim;
    leftovers  = num_doubles % 16;
    for(int i = 0; i < vec.size() * TV::dim / 16; ++i)
}
