/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_UROLL_MAN_HPP
#define TINYVECTOR_UROLL_MAN_HPP

#include "multiple_of.hpp"

#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct UROLL {};

template <int N, int M>
class tv_addinplace_unroll {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            for(int i = start; i < UR::iter; ++i)
            tv_addinplace_unroll<N, 16>::apply(left, right, i * 16);
            tv_addinplace_unroll<N, UR::leftover>::apply(left, right, 16 * UR::iter);
        }
};

template <int N>
class tv_addinplace_unroll<N, 0> {
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {}
};

template <int N> 
class tv_addinplace_unroll<N, 1> {
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            left[start] += right[start];
        }
};

template <int N> 
class tv_addinplace_unroll<N, 2> {
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
        }
};

template <int N> 
class tv_addinplace_unroll<N, 3> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 2>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 1>::apply(left, right, start + 2);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 4> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 2>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 2>::apply(left, right, start + 2);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 5> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 4>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 1>::apply(left, right, start + 4);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 6> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 4>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 2>::apply(left, right, start + 4);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 7> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 4>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 3>::apply(left, right, start + 4);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 8> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 4>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 4>::apply(left, right, start + 4);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 9> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 1>::apply(left, right, start + 8);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 10> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 2>::apply(left, right, start + 8);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 11> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 3>::apply(left, right, start + 8);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 12> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 4>::apply(left, right, start + 8);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 13> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 5>::apply(left, right, start + 8);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 14> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 6>::apply(left, right, start + 8);  
        }
};

template <int N> 
class tv_addinplace_unroll<N, 15> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 7>::apply(left, right, start + 8); 
        }
};

template <int N> 
class tv_addinplace_unroll<N, 16> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right, const int start) {
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 0);
            tv_addinplace_unroll<N, 8>::apply(left, right, start + 8);
        }
};

template <int N>
inline const tinyvector<N, UROLL> & operator+=(tinyvector<N, UROLL> &left, const tinyvector<N, UROLL> &right) {
    tv_addinplace_unroll<N, N>::apply(left, right, 0);
    return left;
}

#endif
