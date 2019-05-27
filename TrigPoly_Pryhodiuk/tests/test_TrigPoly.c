#include "../headers/TrigPoly.h"

int main(){
    /***I'm so sorry for numeration.
    It's easier to numerate like this, but harder
    to search for tests :(
    ***/

    int i = 1;
    // struct declaration
    TrigPoly trigPoly1;
    TrigPoly trigPoly2;
    TrigPoly trigPoly3;
    TrigPoly loadTrig;

    //test 1 output(TrigPoly poly, int type, int width, int precision)
    //test 1 - TrigPoly generate(int n);
    //generate poly with length 4 and show it
    printf("\ntest %i", i);
    printf("\nFirstly let's generate poly with length 4");
    trigPoly1 = generate(4);
    output(trigPoly1, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++;


    //test 2 output(TrigPoly poly, int type, int width, int precision)
    //test 2 - TrigPoly generate(int n);
    //generate poly with length 0 and show it
    printf("\ntest %i", i);
    printf("\nSecondly let's generate poly with length 0 and show it in g type");
    trigPoly2 = generate(0);
    output(trigPoly2, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++;

    //test 3 output(TrigPoly poly, int type, int width, int precision)
    //test 3 - TrigPoly generate(int n);
    //generate poly with length -2 and show it
    printf("\ntest %i", i);
    printf("\nThirdly let's generate poly with length -2 and show it in scintific type");
    trigPoly3 = generate(-2);
    output(trigPoly3, 2, 4, 2);
    printf("\n------------------------------------------------");
    i++;


    //test 1 coolOutput(TrigPoly poly, int type, int width, int precision)
    //show first poly in Dtype with width = 4 and precision = 2
    printf("\ntest %i", i);
    coolOutput(trigPoly1, 0, 4, 2);
    i++;
    printf("\n------------------------------------------------");

    //test 2 coolOutput(TrigPoly poly, int type, int width, int precision)
    //show first poly in g with width = 3 and precision = 3
    printf("\ntest %i", i);
    coolOutput(trigPoly1, 1, 3, 3);
    i++;
    printf("\n------------------------------------------------");

    //test 3 coolOutput(TrigPoly poly, int type, int width, int precision)
    //show first poly in scientific type with width = 5 and precision = 3
    printf("\ntest %i", i);
    coolOutput(trigPoly3, 2, 5, 3);
    i++;
    printf("\n------------------------------------------------");

    //test 4 coolOutput(TrigPoly poly, int type, int width, int precision)
    //show third poly in type number 5 with width = -5 and precision = -3
    printf("\ntest %i", i);
    coolOutput(trigPoly3, 5, -5, -3);
    i++;
    printf("\n------------------------------------------------");


    //test 2 - output(TrigPoly poly, int type, int width, int precision)
    //show first poly in scientific type with width = -1 and precision = 0
    printf("\ntest %i", i);
    output(trigPoly1, 2, -1, 0);
    i++;
    printf("\n------------------------------------------------");

    ///honestly, func output and coolOutput are copypaste of each other, so
    ///there is no necessity in making same tests
    destroy(&trigPoly1);
    destroy(&trigPoly2);
    destroy(&trigPoly3);


    //test 1 - int inputStringOfCoef(TrigPoly * x, char * str)
    //input to a poly from string. correct line
    printf("\ntest %i", i);
    printf("\nInput string to poly. Correct line: -4.5 999.6 -7.112 80 17");
    inputStringOfCoef(&trigPoly1, "-4.5 999.6 -7.112 80 17");
    output(trigPoly1, 0, 4, 2);
    i++;
    printf("\n------------------------------------------------");

    //test 2 - int inputStringOfCoef(TrigPoly * x, char * str)
    //input to a poly from string. incorrect line
    printf("\ntest %i", i);
    printf("\nInput string to poly. Incorrect length line: -4.5 999.6 -7.112 80");
    inputStringOfCoef(&trigPoly2, "-4.5 999.6 -7.112 80");
    i++;
    printf("\n------------------------------------------------");


    //test 1 - int  outputTextFile(str * file, TrigPoly p);
    //input to a poly from TextFile. correct address
    printf("\ntest %i", i);
    printf("\n%s", (outputTextFile("test1_outputTextFile.txt", trigPoly1, 0, 5, 3)) ?
           "Input to the text file is done" : "Input to the text file gone wrong");
    i++;
    printf("\n------------------------------------------------");

    //test 2 - int  outputTextFile(str * file, TrigPoly p);
    //input to a poly from TextFile. incorrect address
    printf("\ntest %i", i);
    printf("\n%s", (outputTextFile("C:\\Dan\\cabage.\\test2_outputTextFile.txt", trigPoly1, 0, 5, 3)) ?
           "Input to the text file is done" : "Input to the text file gone wrong");
    i++;
    printf("\n------------------------------------------------");

    //test 3 - int  outputTextFile(str * file, TrigPoly p);
    //input to a poly from TextFile. empty poly
    printf("\ntest %i", i);
    printf("\n%s", (outputTextFile("test1_outputTextFile.txt", trigPoly3, 0, 5, 3)) ?
           "Input to the text file is done" : "Input to the text file gone wrong");
    i++;
    printf("\n------------------------------------------------");

    destroy(&trigPoly1);
    destroy(&trigPoly3);

    //test 1 - int  inputTextFile(str * file, TrigPoly * p);
    //input from a TextFile to a poly. correct address, but second line has an element which goes for another poly
    printf("\ntest %i", i);
    printf("\n%s", (inputTextFile("test1_outputTextFile.txt", &trigPoly1)) ?
           "Output from the text file is done" : "Output from the text file gone wrong");
    coolOutput(trigPoly1, 0, 5, 3);
    i++;
    printf("\n------------------------------------------------");

    //test 2 - int inputTextFile(str * file, TrigPoly * p);
    //input from a TextFile to a poly. incorrect address
    printf("\ntest %i", i);
    printf("\n%s", (inputTextFile("C:\\Dan\\cabage.\\test2_outputTextFile.txt", &trigPoly2)) ?
           "Output from the text file is done" : "Output from the text file gone wrong");
    i++;
    printf("\n------------------------------------------------");

    //test 3 - int inputTextFile(str * file, TrigPoly * p);
    //input from a TextFile to a poly. empty poly
    printf("\ntest %i", i);
    printf("\n%s", (inputTextFile("test2_outputTextFile.txt", &trigPoly3)) ?
           "Output from the text file is done" : "Output from the text file gone wrong");
    i++;
    coolOutput(trigPoly3, 0, 5, 3);
    printf("\n------------------------------------------------");

    destroy(&trigPoly1);
    destroy(&trigPoly3);

    //test 1 - int  int outputBinaryFile(char * filename, TrigPoly p);
    //correct address
    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5 11.1 22.2 33.3 -44.4");
    printf("\n%s", (outputBinaryFile("test1_outputBinaryFile.dat", trigPoly1)) ?
           "Input to the binary file is done" : "Input to the binary file gone wrong");
    i++;
    printf("\n------------------------------------------------");

    //test 2 - int outputBinaryFile(char * filename, TrigPoly p);
    //incorrect address
    printf("\ntest %i", i);
    printf("\n%s", (outputBinaryFile("C:\\Dan\\cabage.\\test2_outputBinaryFile.dat", trigPoly1)) ?
           "Input to the binary file is done" : "Input to the binary file gone wrong");
    i++;
    printf("\n------------------------------------------------");

    //test 3 - int outputBinaryFile(char * filename, TrigPoly p);
    //empty poly
    printf("\ntest %i", i);
    printf("\n%s", (outputBinaryFile("test2_outputBinaryFile.dat", trigPoly3)) ?
           "Input to the binary file is done" : "Input to the binary file gone wrong");
    i++;
    printf("\n------------------------------------------------");

    destroy(&trigPoly1);


    //test 1 - int  inputBinaryFile(str * file, TrigPoly * p);
    //correct address, but second line has an element which goes for another poly
    printf("\ntest %i", i);
    printf("\n%s", (inputBinaryFile("test1_outputBinaryFile.dat", &trigPoly1)) ?
           "Output from the binary file is done" : "Output from the binary file gone wrong");
    coolOutput(trigPoly1, 0, 5, 3);
    printf("\n------------------------------------------------");
    i++;

    //test 2 - int  inputBinaryFile(str * file, TrigPoly * p);
    //incorrect address
    printf("\ntest %i", i);
    printf("\n%s", (inputBinaryFile("C:\\Dan\\cabage.\\test2_outputBinaryFile.dat", &trigPoly2)) ?
           "Output from the binary file is done" : "Output from the binary file gone wrong");
    printf("\n------------------------------------------------");
    i++;

    //test 3 - int inputBinaryFile(str * file, TrigPoly * p);
    //empty poly
    printf("\ntest %i", i);
    printf("\n%s", (inputBinaryFile("test2_outputBinaryFile.dat", &trigPoly3)) ?
           "Output from the binary file is done" : "Output from the binary file gone wrong");
    coolOutput(trigPoly3, 0, 5, 3);
    printf("\n------------------------------------------------");
    i++;

    destroy(&trigPoly1);
    destroy(&trigPoly3);


    //test 1 TrigPoly add(TrigPoly p1, TrigPoly p2)
    //       TrigPoly sub(TrigPoly p1, TrigPoly p2)
    //if trigPoly1.n bigger than trigPoly2.n

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "5.2 1 0 4 5 6 7");
    inputStringOfCoef(&trigPoly2, "5.2 3 1 7 2");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Sum of polynomials is equal:");
    trigPoly3 = add(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("Subtraction of polynomials is equal:");
    trigPoly3 = sub(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    destroy(&trigPoly3);

    //test 2 TrigPoly add(TrigPoly p1, TrigPoly p2)
    //       TrigPoly sub(TrigPoly p1, TrigPoly p2)
    //if trigPoly1.n less than trigPoly2.n

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "0.5 8 4 7 1");
    inputStringOfCoef(&trigPoly2, "0.5 2 6 3 6 7 2");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Sum of polynomials is equal:");
    trigPoly3 = add(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("Subtraction of polynomials is equal:");
    trigPoly3 = sub(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    destroy(&trigPoly3);

    //test 3 TrigPoly add(TrigPoly p1, TrigPoly p2)
    //       TrigPoly sub(TrigPoly p1, TrigPoly p2)
    //if trigPoly1.n equals trigPoly2.n and polynomials have different alpha

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "1.3 0 1 2 3");
    inputStringOfCoef(&trigPoly2, "7.2 0 1 2 3");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Sum of polynomials is equal:");
    trigPoly3 = add(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("Subtraction of polynomials is equal:");
    trigPoly3 = sub(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    destroy(&trigPoly3);

    //test 1 TrigPoly mul(TrigPoly p1, TrigPoly p2)
    //polies' sizes are equal and polynomials have different alpha

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "8.3 0 1 1 0");
    inputStringOfCoef(&trigPoly2, "8.3 0 2 2 0");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Multiplication of polynomials is equal:");
    trigPoly3 = mul(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    destroy(&trigPoly3);

    //test 2 TrigPoly mul(TrigPoly p1, TrigPoly p2)
    //if polynomials have different size and alpha

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "7.5 1 1 1 1");
    inputStringOfCoef(&trigPoly2, "8.3 9 4 6 2 2.3 -7");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("\nIt is not the end. Make this test as a comment & you will be able to continue testing");
    printf("Multiplication of polynomials is equal:\n");
    trigPoly3 = mul(trigPoly1, trigPoly2);
    coolOutput(trigPoly3, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    destroy(&trigPoly3);

    /*test 1 int unadd(TrigPoly p1, TrigPoly p2)
             int unsub(TrigPoly p1, TrigPoly p2)
              different size, one angle
                p1 += p2,
                p1 -= p2; */

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "-3.5 0.0 1.0");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    inputStringOfCoef(&trigPoly2, "-3.5 0.0 1.0 -7.8 16.4");
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("\np1 += p2\np1 = ");
    unadd(&trigPoly1, trigPoly2);
    coolOutput(trigPoly1, 0, 4, 2);
    printf("\nSo p1 -= p2 will give us first version of p1.\np1 = ");
    unsub(&trigPoly1, trigPoly2);
    coolOutput(trigPoly1, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);

    /*test 2 int unadd(TrigPoly p1, TrigPoly p2)
             int unsub(TrigPoly p1, TrigPoly p2)
    p1 += p2, different size, one angle, but another one poly is zero
    p1 -= p2; */

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "-3.5 1.0 -1.0");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    inputStringOfCoef(&trigPoly2, "-3.5");
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("\np1 += p2\np1 = ");
    unadd(&trigPoly1, trigPoly2);
    coolOutput(trigPoly1, 0, 4, 2);
    printf("\nSo p1 -= p2 will give us first version of p1.\np1 = ");
    unsub(&trigPoly1, trigPoly2);
    coolOutput(trigPoly1, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    printf("\n------------------------------------------------");

    /*test 3 int unadd(TrigPoly p1, TrigPoly p2)
             int unsub(TrigPoly p1, TrigPoly p2)
    p1 += p2, same sizes, but different angles
    p1 -= p2; */

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "-3.5 0.0 1.0");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    inputStringOfCoef(&trigPoly2, "0.1 0.0 11.0");
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("\np1 += p2\np1 = ");
    unadd(&trigPoly1, trigPoly2);
    coolOutput(trigPoly1, 0, 4, 2);
    printf("\nSo p1 -= p2 will give us first version of p1.\np1 = ");
    unsub(&trigPoly1, trigPoly2);
    coolOutput(trigPoly1, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    printf("\n------------------------------------------------");

    /*test 1 int unmul(TrigPoly p1, TrigPoly p2)
              one size, different angle
                p1 += p2,
                p1 -= p2; */

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5 0.0 1.0 1 0");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    inputStringOfCoef(&trigPoly2, "-3.5 0.0 1.0 0 1");
    printf("Second polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("\np1 *= p2");
    unmul(&trigPoly1, trigPoly2);
    printf("\np1 = ");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("\n------------------------------------------------");
    i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);

    /*no need to call this func with arguments:
    polynomials with different sizes, because this function with call
    func mul and printf("Error") and exit
    */


    /*test 1 TrigPoly mul_const(TrigPoly p, Dtype C);
             TrigPoly div_const(TrigPoly p, Dtype C);
    const != 0
    */

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 -4.0");
    printf("\nPolynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Polynomial * 5 = ");
    trigPoly2 = mul_const(trigPoly1, 5);
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Polynomial / 2 = ");
    trigPoly3 = div_const(trigPoly1, 5);
    coolOutput(trigPoly3, 0, 4, 2);
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    destroy(&trigPoly3);
    printf("\n------------------------------------------------");

    /*test 2 TrigPoly mul_const(TrigPoly p, Dtype C);
             TrigPoly div_const(TrigPoly p, Dtype C);
    const == 0
    */

    printf("\ntest %i-%i", i, i+1);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 -4.0");
    printf("\nPolynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Polynomial * 0 = ");
    trigPoly2 = mul_const(trigPoly1, 5);
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Polynomial / 0 = ");
    trigPoly3 = div_const(trigPoly1, 5);
    i++; i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    printf("\n------------------------------------------------");

    /*test 1 int div_(TrigPoly p, TrigPoly p1);
             Dtype mod(TrigPoly p, TrigPoly p1);
             Dtype value(TrigPoly p);
             different sizes of polynomials
    */

    printf("\ntest %i-%i", i, i+2);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 10.0");
    trigPoly1.alpha = M_PI / 2;
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Value of this polynomial: %lf", value(trigPoly1));
    inputStringOfCoef(&trigPoly2, "-3.5 0.0 1.0 0 1");
    trigPoly2.alpha = M_PI / 2;
    printf("\nSecond polynomial is equal:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Value of this polynomial: %lf", value(trigPoly2));
    printf("\ndiv (p1/p2) of polynomials' values without remaining: %i", div_(trigPoly1, trigPoly2));
    printf("\nmod (p1/p2) of polynomials' values with remaining: %lf", mod(trigPoly1, trigPoly2));
    coolOutput(trigPoly1, 0, 4, 2);
    i +=3;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    printf("\n------------------------------------------------");

    /*test 2 int div_(TrigPoly p, TrigPoly p1);
             Dtype mod(TrigPoly p, TrigPoly p1);
             Dtype value(TrigPoly p);
             different sizes of polynomials, but second one = 0
    */

    printf("\ntest %i-%i", i, i+2);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 10.0");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Value of this polynomial: %lf", value(trigPoly1));
    inputStringOfCoef(&trigPoly2, "-3.5");
    printf("\nSecond polynomial is equal to zero:");
    coolOutput(trigPoly2, 0, 4, 2);
    printf("Value of this polynomial: %lf", value(trigPoly2));
    printf("\ndiv (p1/p2) of polynomials' values without remaining: %i", div_(trigPoly1, trigPoly2));
    printf("\nmod (p1/p2) of polynomials' values with remaining: %lf", mod(trigPoly1, trigPoly2));
    i +=3;

    destroy(&trigPoly1);
    destroy(&trigPoly2);
    printf("\n------------------------------------------------");

    /*test 1 TrigPoly derivative(TrigPoly p);
    polynomial with lenght = 1
    */

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 10.0");
    printf("\nFirst polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Derivative is: ");
    trigPoly2 = derivative(trigPoly1);
    coolOutput(trigPoly2, 0, 4, 2);
    i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);

    printf("\n------------------------------------------------");

    /*test 2 TrigPoly derivative(TrigPoly p);
    polynomial with lenght = 2
    */

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 10.0 1.0 1.0 2.0 -4.0");
    printf("Polynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Derivative is: ");
    trigPoly2 = derivative(trigPoly1);
    coolOutput(trigPoly2, 0, 4, 2);
    i++;

    printf("\n------------------------------------------------");

    destroy(&trigPoly1);
    destroy(&trigPoly2);

    /*test 1 integral(TrigPoly p, Dtype C);
    polynomial with b0 == 0
    */

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 0 -5 7");
    printf("\nPolynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Constant = 1:");
    printf("\nIntegral is: ");
    trigPoly2 = integral(trigPoly1, 1);
    coolOutput(trigPoly2, 0, 4, 2);
    i++;

    destroy(&trigPoly1);
    destroy(&trigPoly2);

    printf("\n------------------------------------------------");

    /*test 2 integral(TrigPoly p, Dtype C);
    polynomial with b0 != 0, so integral from b0 = b0*x, which is not a TrigPoly
    */

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 10.0");
    printf("\nPolynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("Constant = 1:");
    printf("\nIntegral is: ");
    trigPoly2 = integral(trigPoly1, 1);
    i++;

    printf("\n------------------------------------------------");

    destroy(&trigPoly1);


    /*test 1 Dtype integrate(TrigPoly p, Dtype a, Dtype b);
    polynomial with length = 0
    */

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5");
    printf("\nPolynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("[a, b] = [0, M_PI]");
    printf("\nRieman's Integral = %lf", integrate(trigPoly1, 0, M_PI));
    coolOutput(trigPoly2, 0, 4, 2);
    i++;

    destroy(&trigPoly1);

    printf("\n------------------------------------------------");

    /*test 2 integrate(TrigPoly p, Dtype a, Dtype b);
    polynomial with length > 0
    */

    printf("\ntest %i", i);
    inputStringOfCoef(&trigPoly1, "-3.5 2.0 10.0 14 11 -22 12");
    printf("\nPolynomial is equal:");
    coolOutput(trigPoly1, 0, 4, 2);
    printf("[a, b] = [0, M_PI]");
    printf("\nRieman's Integral = %lf", integrate(trigPoly1, 0, M_PI));
    i++;

    printf("\n------------------------------------------------");

    destroy(&trigPoly1);


}
