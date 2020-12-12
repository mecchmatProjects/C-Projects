#define DEBUG 0


/** Structure for representing polynomial
 *
 * @param degrees - represent coefficients near x^[index]
 * @param length - length of polynomial
 *
 * Example:
 *      Usage example ypu can find in program below XD
 * */
typedef struct {
    int *degrees;
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
void create(polynomial *p, int n);


/** delete_polynomial - free space after polynomial usage
 *
 * @param p - Polynomial which space needed to be free
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void delete_polynomial(polynomial *p);


/** check_possible_overflow - implementing of check if answer polynomial have enough space for answer
 *
 * @param p - Polynomial which needed to check
 * @param n - Number of coefficients in polynomial needed to place answer
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void check_possible_overflow(polynomial *p, int n);


/** print_polynomial - implementing of inputting polynomial from console
 *
 * @param p - Polynomial which needed to input
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void input_polynomial(polynomial *p);


/** print_polynomial - implementing of human readable output for polynomial
 *
 * @param p - Polynomial which needed to output
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void print_polynomial(polynomial *p);

/** polynomial_plus - implementing plussing for polynomials free size
 *
 * @param p1 - First term
 * @param p2 - Second term
 * @param p3 - Polynomial for result
 *
 * Example:
 *      Usage example you can get in main() below
 * */
void polynomial_plus(polynomial *p1, polynomial *p2, polynomial *p3);


/** polynomial_multiply - Implementation multiplication between 2 polynomial
 *
 * @param p1 - Term 1 multiplication
 * @param p2 - Term 2 multiplication
 * @param p3 - Variable for answer
 */
void polynomial_multiply(polynomial *p1, polynomial *p2, polynomial *p3);


/** polynomial_minus - Implementation subtraction between 2 polynomials
 *
 * @param p1 - Term 1 of subtraction
 * @param p2 - Term 2 of subtraction
 * @param p3 - Variable for answer
 */
void polynomial_minus(polynomial *p1, polynomial *p2, polynomial *p3);

/** polynomial_derivative - Implementation polynomial derivation
 *
 * @param p1 - Polynomial which need to be derivatived
 * @param p2 - Variable for answer
 */
void polynomial_derivative(polynomial *p1, polynomial *p2);

/** polynomial_integral - Implementation polynomial integral
 *
 * @param p1 - Polynomial which need to take integral from
 * @param p2 - Variable for answer
 */
void polynomial_integral(polynomial *p1, polynomial *p2);
