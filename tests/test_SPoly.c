#include "../headers/SPoly.h"
#define KEY1 1
#define KEY2 4
#define KEY3 0

#define VALUE1 5
#define VALUE2 -8
#define VALUE3 3

IType test_insert(Poly *poly) {
    insert(KEY1, VALUE1, poly);
    insert(KEY2, VALUE2, poly);
    insert(KEY3, VALUE3, poly);
    return 0;
}

IType test_search(Poly *poly) {
    PolyElem *temp;
    temp = search(KEY1, poly);
    if (temp == NULL || temp->coefficient != VALUE1) {
        return -3;
    }
    temp = search(KEY2, poly);
    if (temp == NULL || temp->coefficient != VALUE2) {
        return -3;
    }
    temp = search(KEY3, poly);
    if (temp == NULL || temp->coefficient != VALUE3) {
        return -3;
    }
    temp = search(45, poly);
    if (temp != NULL) {
        return -4;
    }
    return 0;
}

IType test_add(Poly* poly1, Poly* poly2) {
    if (poly2->sortedDegrees[0] != 0) {
        insert(0, -3, poly2);
    }
    insert(KEY1, VALUE2, poly2);
    display(add(poly1, poly2));
    return 0;
}

IType test_unsub(Poly* poly) {
    display(unsub(poly));
    return 0;
}

IType test_sub(Poly* poly1, Poly* poly2) {
    display(sub(poly1, poly2));
    return 0;
}

IType test_mul() {
    Poly* poly1 = createNewPoly(2);
    Poly* poly2 = createNewPoly(3);
    insert(0, 3, poly1);
    insert(2, 2, poly1);
    insert(7, 4, poly2);
    insert(5, 3, poly2);
    insert(1, -9, poly2);
    printf("MULTIPLICATION TESTS\n");
    display(mul(poly1, poly2, 1));
    display(mul(poly1, poly2, 3));
    display(mul(poly1, poly2, -5));
    display(mul(poly2, NULL, -5));
    display(mul(NULL, NULL, -5));
    printf("\n\n");
    return 0;
}

IType test_divide() {
    Poly* poly1 = createNewPoly(3);
    insert(2, 1, poly1);
//    insert(1, 4, poly1);
    insert(0, 4, poly1);
    Poly* poly2 = createNewPoly(2);
    insert(1, 1, poly2);
    insert(0, 2, poly2);
    display(divide(poly1, poly2, 2));
    display(divide(poly1, NULL, 2));
    return 0;
}

IType test_mod() {
    Poly* poly1 = createNewPoly(3);
    insert(2, 1, poly1);
    insert(1, 4, poly1);
    insert(0, 4, poly1);
    Poly* poly2 = createNewPoly(2);
    insert(1, 1, poly2);
    insert(0, -2, poly2);
    display(mod(poly1, poly2, 1));
    return 0;
}

IType test_value(Poly* poly, DType x) {
    printf("f(x) = %f\n", value(poly, x));
    return 0;
}

IType test_derivative(Poly* poly) {
    display(poly);
    display(derivative(poly));
    display(derivative(derivative(poly)));
    return 0;
}

IType test_integral(Poly* poly, DType C) {
    display(derivative(integral(poly, C)));
    display(integral(poly, C));
    return 0;
}

IType test_integrate(Poly* poly, DType a, DType b) {
    printf("integrate - %f\n", integrate(poly, a, b));
    return 0;
}

IType test_normalize() {
    DType coefficients[7] = {4, -3, 6, 8, 4, 7, -4};
    DType expectedCoefficients[7] = {1, -0.75, 1.5, 2, 1, 1.75, -1};
    IType degrees[7] = {54, 34, 76, 4, 78, 3, 6};
    Poly* poly = createNewPoly(7);
    for (IType c = 0; c < 8; c++) {
        insert(degrees[c], coefficients[c], poly);
    }
    poly = normalize(poly);
    for (IType c = 0; c < poly->count; c++) {
        if (search(degrees[c], poly)->coefficient - expectedCoefficients[c] > 0.00001) {
            return -10;
        }
    }
    return 0;
}


IType test_polyRealRoots() {
    Poly* poly = createNewPoly(10);
    DLine line;
    line.x1 = -100;
    line.x2 = 100;
    line.dx = 0.00001;
    insert(9, 1, poly);
    insert(8, -138, poly);
    insert(7, 3971, poly);
    insert(6, -1238, poly);
    insert(5, -381060, poly);
    insert(4, 1141784, poly);
    insert(3, 9266208, poly);
    insert(2, -32916096, poly);
    insert(1, -68193792, poly);
    insert(0, 243855360, poly);
    IType rootsCount = 0;
    DType testRoots[7] = {-8, -4, 3, 5, 6, 36, 98};
    DType* roots = polyRealRoots(poly, &rootsCount, line);
    for (int i = 0; i < rootsCount; ++i) {
        if (roots[i] - testRoots[i] > line.dx) return -20;
    }
    return 0;
}
