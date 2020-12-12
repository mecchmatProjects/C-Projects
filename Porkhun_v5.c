#define DEBUG 0


#include <stdio.h>
#include <stdlib.h>


/** Structure for representing polynomial
 *
 * @param degrees - represent coefficients near x^[index]
 * @param length - length of polynomial
 *
 * Example:
 *      Usage example ypu can find in program below XD
 * */
typedef struct {
    float *degrees;
    int length;
} polynomial;


/** create - giving space for new polynomial
 *
 * @param p - Polynomial which needed to give space
 * @param n - Number of elements in polynomial
 *
 * Example:
 *      Usage example you can get in check_possible_overflow() or print_polynomial() below
 * */
void create(polynomial *p, int n) {
    p->degrees = malloc(n * sizeof(float ));
    p->length = n;
}


/** delete_polynomial - free space after polynomial usage
 *
 * @param p - Polynomial which space needed to be free
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void delete_polynomial(polynomial *p) {
    p->length = 0;
    p->degrees = NULL;
}


/** check_possible_overflow - implementing of check if answer polynomial have enough space for answer
 *
 * @param p - Polynomial which needed to check
 * @param n - Number of coefficients in polynomial needed to place answer
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void check_possible_overflow(polynomial *p, int n) {
    if (p->length == 0) {
        create(p, n);
    } else if (p->degrees[p->length - 1] != 0) {
        p->length = n;
        p->degrees = realloc(p->degrees, p->length * sizeof(float));
    }
}


/** print_polynomial - implementing of inputting polynomial from console
 *
 * @param p - Polynomial which needed to input
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void input_polynomial(polynomial *p) {
    int n;
    printf("Input polynomial size: ");
    scanf("%d", &n);
    create(p, n);

    printf("Input polynomial\n");
    for (int index = 0; index < n; index++) {
        printf("Input coefficient for x^%d: ", index);
        scanf("%f", &(p->degrees[index]));
    }
}


/** print_polynomial - implementing of human readable output for polynomial
 *
 * @param p - Polynomial which needed to output
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void print_polynomial(polynomial *p) {
    int printed = 0;
    for (int index = p->length - 1; index >= 0; index--) {
        if (DEBUG == 1) {
            printf("index: %d\n", index);
        }

        if (p->degrees[index] < 0){
            printf(" - ");
        } else if (p->degrees[index] > 0 && printed == 1) {
            printf(" + ");
        }

        if (p->degrees[index] == 0) {
            continue;
        } else if (index == 0) {
            printf("%f", p->degrees[index]);
        } else if (p->degrees[index] > 0) {
            printf("%fx^%d", p->degrees[index], index);
        } else {
            printf("%fx^%d", -1 * p->degrees[index], index);
        }
        printed = 1;
    }

    int zeros = 0;
    for (int index = p->length - 1; index >= 0; index--) {
        if (p->degrees[index] == 0) {
            zeros++;
        }
    }

    if (zeros == p->length) {
        printf("0");
    }

    printf("\n");
}

/** polynomial_plus - implementing plussing for polynomials free size
 *
 * @param p1 - First term
 * @param p2 - Second term
 * @param p3 - Polynomial for result
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void polynomial_plus(polynomial *p1, polynomial *p2, polynomial *p3) {
    delete_polynomial(p3);

    if (DEBUG == 1) {
        printf("Next line error\n");
    }
    check_possible_overflow(p3, p1->length > p2->length ? p1->length : p2->length);
    if (DEBUG == 1) {
        printf("Next line error\n");
    }

    if (DEBUG == 1) {
        printf("len1: %d\nlen2: %d\nlen3: %d\n", p1->length, p2->length, p3->length);
        printf("cycle upper boarder: %d\n", p1->length > p2->length ? p1->length : p2->length);
    }

    for (int index = 0; index < (p1->length > p2->length ? p1->length : p2->length); index++) {
        if (index >= p1->length) {
            p3->degrees[index] = p2->degrees[index];
        } else if (index >= p2->length) {
            p3->degrees[index] = p1->degrees[index];
        } else {
            p3->degrees[index] = p2->degrees[index] + p1->degrees[index];
        }
    }
}


/** polynomial_multiply - Implementation multiplication between 2 polynomial
 *
 * @param p1 - Term 1 multiplication
 * @param p2 - Term 2 multiplication
 * @param p3 - Variable for answer
 */
void polynomial_multiply(polynomial *p1, polynomial *p2, polynomial *p3) {
    delete_polynomial(p3);

    check_possible_overflow(p3, p1->length * p2->length);
    for (int index = 0; index < p3->length; index++) {
        p3->degrees[index] = 0;
    }

    for (int term1 = 0; term1 < p1->length; term1++) {
        for (int term2 = 0; term2 < p2->length; term2++) {
            p3->degrees[term1 + term2] += p1->degrees[term1] * p2->degrees[term2];
        }
    }
}


/** polynomial_minus - Implementation subtraction between 2 polynomials
 *
 * @param p1 - Term 1 of subtraction
 * @param p2 - Term 2 of subtraction
 * @param p3 - Variable for answer
 */
void polynomial_minus(polynomial *p1, polynomial *p2, polynomial *p3) {
    if (DEBUG == 1) {
        printf("Next line error\n");
    }

    delete_polynomial(p3);

    if (DEBUG == 1) {
        printf("Next line error\n");
    }

    check_possible_overflow(p3, p1->length > p2->length ? p1->length : p2->length);

    if (DEBUG == 1) {
        printf("Next line error\n");
    }

    for (int index = 0; index < (p1->length > p2->length ? p1->length : p2->length); index++) {
        if (index >= p1->length) {
            p3->degrees[index] = -p2->degrees[index];
        } else if (index >= p2->length) {
            p3->degrees[index] = p1->degrees[index];
        } else {
            p3->degrees[index] = p1->degrees[index] - p2->degrees[index];
        }
    }
}


/** polynomial_derivative - Implementation polynomial derivation
 *
 * @param p1 - Polynomial which need to be derivatived
 * @param p2 - Variable for answer
 */
void polynomial_derivative(polynomial *p1, polynomial *p2) {
    delete_polynomial(p2);
    check_possible_overflow(p2, p1->length - 1);

    for (int index = 1; index < p1->length; index++) {
        p2->degrees[index - 1] = index * p1->degrees[index];
    }
}


/** polynomial_integral - Implementation polynomial integral
 *
 * @param p1 - Polynomial which need to take integral from
 * @param p2 - Variable for answer
 */
void polynomial_integral(polynomial *p1, polynomial *p2) {
    delete_polynomial(p2);
    check_possible_overflow(p2, p1->length + 1);

    for (int index = 0; index < p1->length; index++) {
        p2->degrees[index + 1] = p1->degrees[index] / (index + 1);
    }
}

int main() {
    polynomial p1, p2, p3;

    input_polynomial(&p1);
    input_polynomial(&p2);

    print_polynomial(&p1);
    print_polynomial(&p2);

    printf("Plussing p1 and p2 result: ");
    polynomial_plus(&p1, &p2, &p3);
    print_polynomial(&p3);

    printf("Multiplying p1 and p2 result: ");
    polynomial_multiply(&p1, &p2, &p3);
    print_polynomial(&p3);

    printf("Subtraction p1 and p2 result: ");
    polynomial_minus(&p1, &p2, &p3);
    print_polynomial(&p3);

    printf("Derivative p1: ");
    polynomial_derivative(&p1, &p3);
    print_polynomial(&p3);

    printf("Integral p1: ");
    polynomial_integral(&p1, &p3);
    print_polynomial(&p3);

    delete_polynomial(&p1);
    delete_polynomial(&p2);
    delete_polynomial(&p3);

    return 0;
}