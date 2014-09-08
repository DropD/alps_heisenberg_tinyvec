#ifndef MULTIPLE_OF_HPP
#define MULTIPLE_OF_HPP

struct one {};
struct two {};
struct four {};

struct false_t {};
struct true_t  {};

template <int N, int mod>
struct one_or_two_or_four_ { typedef one value; };

template <int N>
struct one_or_two_or_four_<N, 0> { typedef four value; };

template <int N>
struct one_or_two_or_four_<N, 2> { typedef two value; };

template <int N> 
struct multiple_of { 
    typedef typename one_or_two_or_four_<N, N % 4>::value divisor; 
}; 

/* get multiple of 16 and mod */
template <int N>
struct is_zero { typedef false_t value; };

template <>
struct is_zero<0> { typedef true_t value; };

template <int N>
struct zero_or_one { static const int value = 1; };

template<>
struct zero_or_one<0> { static const int value = 0; };

template <int N>
struct unroll_16 { 
    static const int iter = N / 16 - zero_or_one<N % 16>::value; 
    static const int leftover = N % 16;
};

#endif
