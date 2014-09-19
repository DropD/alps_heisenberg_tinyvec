/* tinivec for alps
*/

#ifndef TINIVEC_HPP
#define TINIVEC_HPP

#include <boost/array.hpp>
#include <alps/hdf5.hpp>

template <int N>
class tinivec {
    public:
        typedef boost::array<double, N> datatype;

        inline double & operator[](int i) { return _data[i]; }
        inline const double & operator[](int i) const { return _data[i]; }

        template <class Expr> // tinivec or tinivec_expr
        inline void operator=(const Expr<N> & other) {
            for(int i = 0; i < N; ++i)
                _data[i] = other[i];
        }

        template <class Expr>
        inline const tinivec<N> & operator+=(const Expr & other) {
            for(int i = 0; i < N; ++i)
                _data[i] += other[i];
        }

    private:
        datatype _data;
};

template <class op<N> >
class tinivec_expr {
    public:
        template<class L<N>, class R<N> >
        tinivec_expr(const L<N> & left, const R<N> & right) : _left(left), _right(right) {}

        inline double & operator[](int i) { return op::apply(_left[i], _right[i]); }
        inlnine const double & operator[](int i) const { return op::apply(_left[i], _right[i]); }

    private:
        const L<N> & _left;
        const R<N> & _right;
};

template <int N>
class tinivec_add {
    public:
        tinivec<N> apply(const double & left, const double & right) { return left + right; }
};

template <int N, class L<N>, class R<N> >
inline tinivec_expr<tinivec_add<N> > operator+(const L<N> & left, const L<N> & right) { 
    return tinivec_expr(left, tinivec_add<N>, right); 
}

#endif
