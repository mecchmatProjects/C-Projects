#include "BigNumber.c"
/* File  BigNumber.h
Realization of BigNumber
Done by Zelenko Petro & Goryslavets Dmytro Statistics 2 curs
Email:  zelenko.peter369@gmail.com & d.goryslavets@ukr.net
Date 26.05.2019 */
/*constant of max length of number*/
extern const int nmax;
/*Structure of number */
/*typedef struct
{
    unsigned int* num; // pointer on array of coefficient
    int len;          // length of array
    short sign;      // sign of number(can be: +1, -1)
}Tlong;*/

extern char *substring(const char *string, int position, int length); // make a cut of string from position with length length

extern Tlong add_abs(Tlong *a, Tlong *b); // addition of numbers by modulus(bitwise, in the columns)

extern Tlong sub_abs(Tlong *a,Tlong *b); // subtraction of numbers by modulus (in a column, from a larger one less)

extern int comp_abs(Tlong* a, Tlong* b);// comparison of two numbers by module

extern int compare(Tlong *a,Tlong *b);//comparison of two numbers taking into account the sign

extern Tlong add(Tlong *a, Tlong *b);//addition with a sign

extern Tlong sub(Tlong *a, Tlong *b);//pictures based on the sign

extern Tlong convert(long long a); // conversion of a "short" number into a long one

extern void setlen(Tlong *res);//correction of the length of the number (if the length is incorrect then it changes with the correct one)

extern Tlong mul(Tlong *a, Tlong *b);//multiplication of two numbers

extern void shift(Tlong *a, int k);//shift the number left (right - k - negative) to k positions

extern Tlong add_scal(Tlong *a, long long b);//adding short to a long number

extern Tlong sub_scal(Tlong *a, long long b);//subtraction from a short long number

extern Tlong mul_scal(Tlong *a, long long b);// multiplying for a short one

extern int compare_scal(Tlong *a, long long b); //comparison of long and short numbers

extern Tlong divT(Tlong *a, Tlong *b);//dividing two numbers all the way

extern Tlong modT(Tlong *a, Tlong *b);// the remainder of the division of two large numbers

extern Tlong divT_scal(Tlong *a, long long b);//dividing long on short

extern Tlong divscal_T(long long b, Tlong *a);//dividing a short on a long whole

extern Tlong modT_scal(Tlong *a, long long b);//the remainder of the division is long to short

extern Tlong modscal_T(long long b, Tlong *a);//the remainder of dividing short by long

extern Tlong copyT(Tlong *a);//copying long

extern Tlong NSD(Tlong *a, Tlong *b);//search for the largest common divider

extern Tlong NSK(Tlong *a, Tlong *b);//search for the smallest common multiple

extern int input_from_str(Tlong *x, const char *str, int systema_chislennya);//entering a number from a string

extern int append(Tlong *x, unsigned int a);//add a new junior level with the displacement of the whole number

extern int update(Tlong *x, int k, unsigned int a);//replacement of the value of the k-th category

extern int input_from_console(Tlong *x, int systema_chislennya);//entering a number from the console in the number system bitwise
// the number should be entered in the format 123 123 123.
// the point at the end is obligatory

extern int inputTextFile(char* file, Tlong *x, int systema_chislennya);//enter a number from the file file in the system with one long number

extern int input_console_oneline(Tlong *x, int systema_chislennya);//entering a large number in the console in a single-line system, for example: 12348298428374982348729874834

extern int inputBinaryFile(char* file, Tlong* x);//read from a binary file in this way as write

extern int outputBinaryFile(char* file, Tlong* x);//output in a binary file in this way: first, a short digit(sign) of the number and then all the digits

extern int outputTextFile(char* file, Tlong *a, int width, int heigh);//output to a text file bitwise with the ability to select the width and height of the table

extern int destroy(Tlong *x);//release of memory
