#include <iostream>
#include "ComplexPolynomial.h"

ComplexPolynomial::ComplexPolynomial() {
    coefficients = nullptr;
    size = 0;
    derivative_coeffs = nullptr;
}
ComplexPolynomial::ComplexPolynomial(base * coeffs, int n) {
    coefficients = new base[n];
    size = n;
    for(int i = 0; i < n; i++) coefficients[i] = coeffs[i];
    derivative_coeffs = new base[size-1];
}

ComplexPolynomial::~ComplexPolynomial() {
    delete [] coefficients;
    delete [] derivative_coeffs;
}

ComplexPolynomial & ComplexPolynomial::operator=(const ComplexPolynomial &rhs) {
    if (this == &rhs) return *this;

    else {
        delete[] coefficients;
        coefficients = new base[rhs.size];
        size = rhs.size;

        for (int i = 0; i < size; i++)
            coefficients[i] = rhs.coefficients[i];
    }

    return *this;
}

ComplexPolynomial ComplexPolynomial::operator+(const ComplexPolynomial & rhs) {
    int new_size = (rhs.size > size) ? rhs.size : size;
    base * new_coeffs = new base[new_size];

    for (int i = 0; i < new_size; i++) {
        base comp_num(0, 0);
        new_coeffs[i] = comp_num;
        if (i < size) new_coeffs[i] = new_coeffs[i] + (coefficients[i]);
        if (i < rhs.size) new_coeffs[i] = new_coeffs[i] + (rhs.coefficients[i]);
    }

    ComplexPolynomial new_cp(new_coeffs, new_size);

    return new_cp;
}
ComplexPolynomial ComplexPolynomial::operator-(const ComplexPolynomial & rhs) {
    int new_size = (rhs.size > size) ? rhs.size : size;
    base new_coeffs[new_size];

    for (int i = 0; i < new_size; i++) {
        base comp_num(0, 0);
        new_coeffs[i] = comp_num;
        if (i < size) new_coeffs[i] = new_coeffs[i] + (coefficients[i]);
        if (i < rhs.size) new_coeffs[i] = new_coeffs[i] - (rhs.coefficients[i]);
    }

    ComplexPolynomial new_cp(new_coeffs, new_size);

    return new_cp;
}

ComplexPolynomial & ComplexPolynomial::operator+=(const ComplexPolynomial & rhs) {
    int new_size = (rhs.size > size) ? rhs.size : size;
    base * new_coeffs = new base[new_size];

    for (int i = 0; i < new_size; i++) {
        base comp_num(0, 0);
        new_coeffs[i] = comp_num;
        if (i < size) new_coeffs[i] += coefficients[i];
        if (i < rhs.size) new_coeffs[i] += rhs.coefficients[i];
    }

    delete[] coefficients;
    base comp_num(0, 0);
    coefficients = new base[new_size];
    size = new_size;
    for (int i = 0; i < new_size; i++) coefficients[i] = comp_num;

    return *this;
}
ComplexPolynomial & ComplexPolynomial::operator-=(const ComplexPolynomial & rhs) {
    int i;
    int new_size = (rhs.size > size) ? rhs.size : size;
    base * new_coeffs = new base[new_size];

    for (i = 0; i < new_size; i++) {
        base comp_num(0, 0);
        new_coeffs[i] = comp_num;
        if (i < size) new_coeffs[i] = new_coeffs[i] + (coefficients[i]);
        if (i < rhs.size) new_coeffs[i] = new_coeffs[i] - (rhs.coefficients[i]);
    }

    delete[] coefficients;
    coefficients = new base[new_size];
    size = new_size;
    for (i = 0; i < new_size; i++) coefficients[i] = new_coeffs[i];

    return *this;
}

void ComplexPolynomial::differentiate() {
    if ( size == 0 ) return;
    for (int i = 0; i < size - 1; i++){
        double re = coefficients[i + 1].real() * (i + 1);
        double im = coefficients[i + 1].imag() * (i + 1);

        base comp_num(re, im);

        derivative_coeffs[i] = comp_num;
    }
}

ComplexPolynomial ComplexPolynomial::calc_derivative() {
    differentiate();
    ComplexPolynomial der(derivative_coeffs, size - 1);
    return der;
}

base ComplexPolynomial::evaluate(base x){
    base p;
    for (int i = 0; i < size; i++ ){
        p = p + ( coefficients[i] * (pow(x, i)));
    }
    return p;
}

base ComplexPolynomial::evaluate_derivative(base x) {
    ComplexPolynomial der_polynomial = calc_derivative();
    base der_evaluated = der_polynomial.evaluate(x);
    return der_evaluated;
}

void ComplexPolynomial::generate(int n) {
    base * rnd_coeffs = generate_random_coeffs(n);

    coefficients = new base[n];
    derivative_coeffs = new base[n-1];

    for (int i = 0; i < n; i++) {
        coefficients[i] = rnd_coeffs[i];
        size = n;
    }
}

void ComplexPolynomial::print(ostream & out) const {
    if (size == 0) return;

    for (int i = size - 1; i > 0; i--)
        out << coefficients[i] << "x^" << i << " + ";
    out << coefficients[0];
}

ostream & operator<<(ostream & out, const ComplexPolynomial & cp) {
    cp.print(out);
    return out;
}
