#ifndef TEST_SPOLY_H
#define TEST_SPOLY_H
IType test_insert(Poly *poly);
IType test_search(Poly *poly);
IType test_add(Poly* poly1, Poly* poly2);
IType test_unsub(Poly* poly);
IType test_sub(Poly* poly1, Poly* poly2);
IType test_mul();
IType test_divide();
IType test_mod();
IType test_value(Poly* poly, DType x);
IType test_derivative(Poly* poly);
IType test_integral(Poly* poly, DType C);
IType test_integrate(Poly* poly, DType a, DType b);
IType test_normalize();
IType test_polyRealRoots();
#endif //TEST_SPOLY_H
