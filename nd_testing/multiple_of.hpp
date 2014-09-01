#ifndef MULTIPLE_OF_HPP
#define MULTIPLE_OF_HPP

struct one {};
struct two{};
struct four {};
//~ 
//~ template <int N>
//~ struct one_or_two_ { typedef one value; };
//~ 
//~ template <>
//~ struct one_or_two_<0> { typedef two value; };
//~ 
//~ template <int N>
//~ struct two_or_four_ { typedef two value; };
//~ 
//~ template <>
//~ struct two_or_four_<0> { typedef four value; };
//~ 
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

#endif
