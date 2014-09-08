/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_HPP
#define TINYVECTOR_HPP


#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

#include "tinyvector_default.hpp"
#include "tinyvector_oe.hpp"
#include "tinyvector_oe4.hpp"
#include "tinyvector_oe_sse.hpp"
#include "tinyvector_unroll.hpp"
#include "tinyvector_unroll_man.hpp"

#ifdef __AVX__
#include "tinyvector_oe4_avx.hpp"
#include "tinyvector_unroll_avx.hpp"
#include "tinyvector_ultimate.hpp"
#else
#endif

#endif
