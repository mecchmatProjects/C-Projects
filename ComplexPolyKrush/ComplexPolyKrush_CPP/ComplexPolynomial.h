#ifndef COMPLEXPOLYKRUSH_CPP_COMPLEXPOLYNOMIAL_H
#define COMPLEXPOLYKRUSH_CPP_COMPLEXPOLYNOMIAL_H

#include "utils.cpp"

class ComplexPolynomial {
private:
    int size;
    base * coefficients;
    base * derivative_coeffs;
    void differentiate();
public:
    ComplexPolynomial();
    ComplexPolynomial(base * coeffs, int n);
    ~ComplexPolynomial();

    ComplexPolynomial & operator=(const ComplexPolynomial & rhs);

    ComplexPolynomial operator+(const ComplexPolynomial & rhs);
    ComplexPolynomial operator-(const ComplexPolynomial & rhs);

    ComplexPolynomial & operator+=(const ComplexPolynomial & rhs);
    ComplexPolynomial & operator-=(const ComplexPolynomial & rhs);


    ComplexPolynomial calc_derivative();
    base evaluate(base x);
    base evaluate_derivative(base x);
    void generate(int n);

    string print_poly();
    friend ostream& operator<<(ostream& out, const ComplexPolynomial& cp);
    void print(ostream & out) const;
};


#endif //COMPLEXPOLYKRUSH_CPP_COMPLEXPOLYNOMIAL_H
