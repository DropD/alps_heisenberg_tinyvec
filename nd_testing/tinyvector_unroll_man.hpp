/* helper.hpp for ndim_spin example
 */

#ifndef TINYVECTOR_UM_MAN_HPP
#define TINYVECTOR_UM_MAN_HPP

#include "multiple_of.hpp"

#include <boost/array.hpp>
#include <alps/hdf5.hpp>

#include <vector>
#include <cmath>
#include <iostream>

struct UM {};

template <int N, int M>
class tv_addinplace_um {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            for(int i = start; i < UR::iter; ++i)
                tv_addinplace_um<N, 16>::apply(left, right, i * 16);
            tv_addinplace_um<N, UR::leftover>::apply(left, right, 16 * UR::iter);
        }
};

template <int N>
class tv_addinplace_um<N, 0> {
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {}
};

template <int N> 
class tv_addinplace_um<N, 1> {
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start] += right[start];
        }
};

template <int N> 
class tv_addinplace_um<N, 2> {
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
        }
};

template <int N> 
class tv_addinplace_um<N, 3> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
        }
};

template <int N> 
class tv_addinplace_um<N, 4> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3];
        }
};

template <int N> 
class tv_addinplace_um<N, 5> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4]; 
        }
};

template <int N> 
class tv_addinplace_um<N, 6> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];  
        }
};

template <int N> 
class tv_addinplace_um<N, 7> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];   
        }
};

template <int N> 
class tv_addinplace_um<N, 8> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];    
        }
};

template <int N> 
class tv_addinplace_um<N, 9> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];     
        }
};

template <int N> 
class tv_addinplace_um<N, 10> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];      
            left[start + 9] += right[start + 9];      
        }
};

template <int N> 
class tv_addinplace_um<N, 11> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];      
            left[start + 9] += right[start + 9];       
            left[start + 10] += right[start + 10];       
        }
};

template <int N> 
class tv_addinplace_um<N, 12> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];      
            left[start + 9] += right[start + 9];       
            left[start + 10] += right[start + 10];        
            left[start + 11] += right[start + 11];        
        }
};

template <int N> 
class tv_addinplace_um<N, 13> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];      
            left[start + 9] += right[start + 9];       
            left[start + 10] += right[start + 10];        
            left[start + 11] += right[start + 11];         
            left[start + 12] += right[start + 12];         
        }
};

template <int N> 
class tv_addinplace_um<N, 14> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];      
            left[start + 9] += right[start + 9];       
            left[start + 10] += right[start + 10];        
            left[start + 11] += right[start + 11];         
            left[start + 12] += right[start + 12];          
            left[start + 13] += right[start + 13];          
        }
};

template <int N> 
class tv_addinplace_um<N, 15> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];      
            left[start + 9] += right[start + 9];       
            left[start + 10] += right[start + 10];        
            left[start + 11] += right[start + 11];         
            left[start + 12] += right[start + 12];          
            left[start + 13] += right[start + 13];           
            left[start + 14] += right[start + 14];           
        }
};

template <int N> 
class tv_addinplace_um<N, 16> {
    typedef unroll_16<N> UR;
    public:
        static inline const void apply(tinyvector<N, UM> &left, const tinyvector<N, UM> &right, const int start) {
            left[start + 0] += right[start + 0];
            left[start + 1] += right[start + 1];
            left[start + 2] += right[start + 2];
            left[start + 3] += right[start + 3]; 
            left[start + 4] += right[start + 4];  
            left[start + 5] += right[start + 5];   
            left[start + 6] += right[start + 6];    
            left[start + 7] += right[start + 7];     
            left[start + 8] += right[start + 8];      
            left[start + 9] += right[start + 9];       
            left[start + 10] += right[start + 10];        
            left[start + 11] += right[start + 11];         
            left[start + 12] += right[start + 12];          
            left[start + 13] += right[start + 13];           
            left[start + 14] += right[start + 14];            
            left[start + 15] += right[start + 15];            
        }
};

template <int N>
inline const tinyvector<N, UM> & operator+=(tinyvector<N, UM> &left, const tinyvector<N, UM> &right) {
    tv_addinplace_um<N, N>::apply(left, right, 0);
    return left;
}

#endif
