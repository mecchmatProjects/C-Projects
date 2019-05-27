/*** File  TrigPoly.c
Realization of TrigPoly's functions (Task 7)
Done by Valentina Pryhodiuk (group statistic 2.2)
Email: shevacharmeleon@gmail.com
Date 19.05.2019 ***/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SI sizeof(double)
#include "../headers/TrigPoly.h"
Dtype doubleFromFile(FILE * f1);


    /*1. function value
    @ Gives a value of polynomial p for angle alpha */
    Dtype value(TrigPoly p){
        Dtype value = 0;
        for (int i = 0; i < (int) (p.n / SI); i++)
            value += p.b[i]*cos(i*p.alpha) + p.a[i]*sin(i*p.alpha);
        return value;
    }

    /*2. function derives TrigPoly
    @ Returns polynomial, which is a derivative of the given polynomial */
    TrigPoly derivative(TrigPoly p){
        TrigPoly x;
        x.alpha = p.alpha;
        x.n = p.n;
        x.a = (Dtype *) malloc(x.n);
        x.b = (Dtype *) malloc(x.n);
        x.a[0] = 0;
        x.b[0] = 0;
        for (int i = 0; i < x.n / SI; i++){
            x.a[i] = i * p.b[i];
            x.b[i] = -i * p.a[i];
        }
        return x;
    }

    /*3. function set an angle alpha
    This function will help us to implement func such as +, -, and etc. for
    polynomials, which have different angles.
    @ returns an angle, which user has set from console.
    */
    Dtype setAlpha(){
            Dtype alpha;
            printf("\nInput alpha as lf = ");
            scanf("%lf", &alpha);
            return alpha;
        }

    /*4. function summarizes TrigPolies
    @ Returns a poly = p1 + p2*/
    TrigPoly add(TrigPoly p1, TrigPoly p2){
        int n1 = p1.n / SI;
        int n2 = p2.n / SI;
        TrigPoly p3;

        if (n1 >= n2){
            p3.n = p1.n;
            p3.a = (double *) malloc(p3.n);
            p3.b = (double *) malloc(p3.n);

            for (int i = 0; i < n2; i ++){
                p3.a[i] = p1.a[i] + p2.a[i];
                p3.b[i] = p1.b[i] + p2.b[i];
            }
            for (int i = n2; i < n1; i ++){
                p3.a[i] = p1.a[i];
                p3.b[i] = p1.b[i];
            }
        }

        else{
            p3.n = p2.n;
            p3.a = (double *) malloc(p3.n);
            p3.b = (double *) malloc(p3.n);

            for (int i = 0; i < n1; i ++){
                p3.a[i] = p1.a[i] + p2.a[i];
                p3.b[i] = p1.b[i] + p2.b[i];
            }
            for (int i = n1; i < n2; i ++){
                p3.b[i] = p2.b[i];
                p3.a[i] = p2.a[i];
            }
        }
        //because we need to put an angle into our new polynomial
        if (p1.alpha == p2.alpha)
            p3.alpha = p2.alpha;
        else
            p3.alpha = setAlpha();
        return p3;
    }

    /*5. function minus
    @ Returns a poly = p1 - p2 */
    TrigPoly sub(TrigPoly p1, TrigPoly p2){
        int n1 = p1.n / SI;
        int n2 = p2.n / SI;
        TrigPoly p3;

        if (n1 >= n2){
            p3.n = p1.n;
            p3.a = (double *) malloc(p3.n);
            p3.b = (double *) malloc(p3.n);

            for (int i = 0; i < n2; i ++){
                p3.a[i] = p1.a[i] - p2.a[i];
                p3.b[i] = p1.b[i] - p2.b[i];
            }

            for (int i = n2; i < n1; i ++){
                p3.a[i] = p1.a[i];
                p3.b[i] = p1.b[i];
            }
        }

        else{
            p3.n = p2.n;
            p3.a = (double *) malloc(p3.n);
            p3.b = (double *) malloc(p3.n);

            for (int i = 0; i < n1; i ++){
                p3.a[i] = p1.a[i] - p2.a[i];
                p3.b[i] = p1.b[i] - p2.b[i];
            }

            for (int i = n1; i < n2; i ++){
                p3.b[i] = -p2.b[i];
                p3.a[i] = -p2.a[i];
            }
        }
        //because we need to put an angle into our new polynomial
        if (p1.alpha == p2.alpha)
            p3.alpha = p2.alpha;
        else
            p3.alpha = setAlpha();
        return p3;
    }

    /*6. function multiplies TrigPolies
    @ Returns a poly = p1 * p2*/

    TrigPoly mul(TrigPoly p1, TrigPoly p2){
        int n1 = p1.n / SI;
        int n2 = p2.n / SI;
        int k;
        TrigPoly p3;
        if (p1.n == 0 | p2.n == 0){
            printf("\nYou can`t multiply pol-ms, if one of them has a length = 0");
            exit(1);
        }
        p3.n = p1.n + p2.n - SI;
        p3.a = (double *) malloc(p3.n);
        p3.b = (double *) malloc(p3.n);
        for (int i = 0; i < p3.n / SI; i ++){
            p3.a[i] = 0;
            p3.b[i] = 0;
        }
        p3.b[0] = p1.b[0] * p2.b[0];
        for (int i = 1; i < n1; i++){
            p3.a[i] += p1.a[i] * p2.b[0];
            p3.b[i] += p1.b[i] * p2.b[0];
        }
        for (int i = 1; i < n2; i++){
            p3.a[i] += p2.a[i] * p1.b[0];
            p3.b[i] += p2.b[i] * p1.b[0];
        }
        for (int i = 1; i < n1; i++)
            for (int j = 1; j < n2; j++){
                // sin(a + b) + sin(a - b) = 2sin(a)cos(b);
                p3.a[i + j] += p1.a[i] * p2.b[j] * 1/2;
                k = abs(i - j);
                p3.a[k] += p1.a[i] * p2.b[j] * 1/2;

                // cos(a + b) + cos(a - b) = 2cos(a)cos(b);
                p3.b[i + j] += p1.b[i] * p2.b[j] * 1/2;
                p3.b[k] += p1.b[i] * p2.b[j] * 1/2;

                // -cos(a + b) + cos(a - b) = 2sin(a)sin(b);
                p3.b[i + j] -= p1.a[i] * p2.a[j] * 1/2;
                p3.b[k] += p1.a[i] * p2.a[j] * 1/2;

                // sin(a + b) + sin(a - b) = 2cos(a)sin(b);
                p3.a[i + j] += p1.b[i] * p2.a[j] * 1/2;
                p3.a[k] += p1.b[i] * p2.a[j] * 1/2;

            }
        //because we need to put an angle into our new polynomial
        if (p1.alpha == p2.alpha)
            p3.alpha = p1.alpha;
        else
            p3.alpha = setAlpha();
        return p3;
    }

    /*7.  function multiplies TrigPoly's coef by a const
    @ Returns a poly = constant * p1*/
    TrigPoly mul_const(TrigPoly p, Dtype C){
        TrigPoly p3;
        p3.n = p.n;
        p3.a = (double *) malloc(p3.n);
        p3.b = (double *) malloc(p3.n);
        for (int i = 0; i < p3.n / SI; i ++){
            p3.a[i] = p.a[i] * C;
            p3.b[i] = p.b[i] * C;
        }
        p3.alpha = p.alpha;
        return p3;
    }

    /*8. function divides TrigPoly's coef by a const
    @ Returns a poly
    @ C != 0*/
    ///the same as mod, because double can't be divided without a remainder (остачі)
    TrigPoly div_const(TrigPoly p, Dtype C){
        if (C == 0){
            printf("\nZeroDivisionError");
            exit(1);
        }
        TrigPoly p3 = mul_const(p, 1/C);
        /*p3.n = p.n;
        p3.a = (double *) malloc(p3.n);
        p3.b = (double *) malloc(p3.n);
        for (int i = 0; i < p3.n / SI; i ++){
            p3.a[i] = p.a[i] / C;
            p3.b[i] = p.b[i] / C;
        }
        p3.alpha = p.alpha;*/
        return p3;
    }
    /*9. function divides TrigPoly's coef without a remainder
    @ Returns an int value / value
    @ Function can't be implemented in different way, because
    trigonometric polynomials won't give us a TrigPoly as a result */
    int div_(TrigPoly p1, TrigPoly p2){
        if (value(p2) == 0){
            printf("\nZeroDivisionError");
            return 0;
        }
        return (int) value(p1) / value(p2);
    }
    /*10. function divides TrigPoly's coef with remainder
    @ Returns a value / value
    @ Function can't be implemented in different way, because
    trigonometric polynomials won't give us a TrigPoly as a result */
    Dtype mod(TrigPoly p1, TrigPoly p2){
        if (value(p2) == 0){
            printf("\nZeroDivisionError");
            return 0;
        }
        return value(p1) / value(p2);
    }

    /*11. function integral
    @ Returns a poly, which is an integral of a given
    @ You have to give a polynomial with b[0] = 0,
    because integral of b[0] = x * b[0], so
    it won't be a TrigPoly*/
    TrigPoly integral(TrigPoly p, Dtype C){
        if (p.b[0] != 0){
            printf("\nIntegral of this polynomial is not a TrigPoly. Sorry :(");
            return p;
        }
        TrigPoly res;
        res.alpha = p.alpha;
        res.n = p.n;
        res.a = (Dtype *) malloc(p.n);
        res.b = (Dtype *) malloc(p.n);

        /*does't matter which number is a0, because
        a0*sin0 = 0; b0 = C, because it is simple math
        */
        res.a[0] = 0; res.b[0] = C;
        for(int i = 1; i < (int) (p.n / SI); i++){
            res.a[i] = p.b[i] / i;
            res.b[i] = -p.a[i] / i;
            //here we go with minus, because d(cosx) = -sinxdx
        }
        return res;
    }


    /* 12. function rieman's integral
    @ Returns a value of rieman's integral of the polynomial on [A, B]
    @ firstly I created a new polynomial and put b0 = 0, so
    previous func will give us a result. Then I used func value for alpha=b & alpha = a*/
    Dtype integrate(TrigPoly p, Dtype A, Dtype B){
        Dtype b0 = p.b[0];
        p.b[0] = 0;
        TrigPoly res = integral(p, 0);
        res.alpha = A;
        Dtype integral = b0*(B - A) - value(res);
        res.alpha = B;
        integral += value(res);
        free(res.a);
        free(res.b);
        return integral;
        }

    ///unary operations
    /*13. function p1 += p2
    @ param - *poly1 and poly2
    @ returns 0, if p1=p2=0 */
    int unadd(TrigPoly * p1, const TrigPoly p2){
        if (p1->n == 0 && p2.n == 0)
            return 0;
        TrigPoly p3 = add(*p1, p2);
        p1->n = p3.n;
        p1->a = (double *) realloc(p3.a, p1->n);
        p1->b = (double *) realloc(p3.b, p1->n);
        p1->alpha = p3.alpha;
        return 1;
    }

    /*14. function p1 -= p2
    @ param - *poly1 and poly2
    @ returns 0, if p1=p2=0 */
    int unsub(TrigPoly * p1, const TrigPoly p2){
        if (p1->n == 0 && p2.n == 0)
            return 0;
        TrigPoly p3 = sub(*p1, p2);
        p1->n = p3.n;
        p1->a = (double *) realloc(p3.a, p1->n);
        p1->b = (double *) realloc(p3.b, p1->n);
        p1->alpha = p3.alpha;
        return 1;
    }

    /*15. function p1 *= p2
    @ param - *poly1 and poly2
    @ returns 0, if p1=p2=0 */
    int unmul(TrigPoly * p1, const TrigPoly p2){
        if (p1->n == 0 && p2.n == 0)
            return 0;
        TrigPoly p3 = mul(*p1, p2);
        p1->n = p3.n;
        p1->a = (double *) realloc(p3.a, p1->n);
        p1->b = (double *) realloc(p3.b, p1->n);
        p1->alpha = p3.alpha;
        return 1;
    }

    /*16. function - output into the binary file
    @ param - filename and poly
    @ returns 0, if file can't be created, wrong path */
    int outputBinaryFile(char * filename, TrigPoly p){
        FILE * f1 = fopen(filename, "wb+");
        if (f1 == NULL){
            printf("\nFileNotFoundError");
            return 0;
        }
        fwrite(&p.alpha, SI, 1, f1);
        for(int i = 0; i < (int) (p.n / SI); i++){
            fwrite(&p.a[i], SI, 1, f1);
            fwrite(&p.b[i], SI, 1, f1);
        }
        fclose(f1);
        return 1;
    }

    /*17. function - intput from the binary file
    @ param - file and *poly
    @ returns 0, if file doesn't exist*/
    int inputBinaryFile(char * filename, TrigPoly *p){
        FILE * f1 = fopen(filename, "rb");
        if (f1 == NULL){
            printf("\nFileNotFoundError");
            return 0;
        }
        fseek(f1, 0, SEEK_END);

        //alpha a0 b0 a1 b1...
        int n = (ftell(f1) - SI) / (SI * 2);
        p->n = n * SI;
        p->a = (double *) malloc(p->n);
        p->b = (double *) malloc(p->n);

        fseek(f1, SEEK_SET, 0);
        fread(&p->alpha, SI, 1, f1);
        for (int i = 0; i < n; i ++){
            fread(&p->a[i], SI, 1, f1);
            fread(&p->b[i], SI, 1, f1);
        }
        fclose(f1);
        return 1;
    }

    /*18. function - intput from console as a table of coef
    @ param - *poly
    @ returns 1, if func has finished it's work*/
    int inputAsTable(TrigPoly * x){
        unsigned int n;
        printf("\nEnter polynom's degree: ");
        scanf("%i", &n);
        // because number of coef = degree + 1
        n = abs(n) + 1;
        x->n = n * SI;
        x->a = (Dtype *) malloc(x->n);
        x->b = (Dtype *) malloc(x->n);
        printf("\nEnter angle: ");
        scanf("%lf", &x->alpha);

        printf("\n Enter coef of sin");

        for (int i = 0; i < n; i ++)
            scanf("%lf", &x->a[i]);

        printf("\n Enter coef of cos");
        for (int i = 0; i < n; i ++)
            scanf("%lf", &x->b[i]);
        return 1;
    }

    /*19. function - input from the string with coef and alpha
    with fixed size of coeficients
    @ param - *poly, string
    @ returns 0, if string is empty or odd length*/
    int inputStringOfCoef(TrigPoly * x, char * str){
        char symbol;
        // sign - to add a sign, k - a variable to parse through the str
        // i - a variable to write into the arrays
        int i = 0, k = 0, sign = 1;
        int counter = 0; //counts length of str
        double data = 0; //a number, which we converted from char
        double integer = 0; //before the dot
        double floating = 0; //after the dot
        int exDot = 0; //flag for the dot
        double z = 10; //helps to convert char into a fraction

        while((symbol = str[i])&&(symbol != '\0')){
            i ++;
            if (symbol == ' ')
                counter ++;
        }
        if (str[0] == '\0'){
            printf("\nEmptyStringError");
            return 0;
        }
        else if (counter % 2 != 0){
            //I invented this error. It means z you missed coef
            // and string became non simetric
            printf("\nNonSimetricStringError");
            return 0;
        }
        symbol = str[0];
        x->n = counter * SI / 2;
        x->a = malloc(x->n);
        x->b = malloc(x->n);

        //here we start to convert 'number' into a (double) number
        for (i = 0; i <= counter; i++){
            data = 0;
            integer = 0;
            floating = 0;
            exDot = 0;
            sign = 1;
            z = 10;

            //while it's not an ending for the number or for the str
            while (symbol != ' ' && symbol != '\0' && symbol){

                if (symbol == '-'){
                    sign = -1;
                    k++;
                    symbol = str[k];
                    continue;
                }

                else if (symbol == '.'){
                    exDot = 1;
                    k++;
                    symbol = str[k];
                    continue;
                }

                symbol = symbol - '0';

                if (!exDot)
                    integer = 10 * integer + symbol;
                else {
                    floating = floating + (double) (symbol)/z;
                    z *= 10;
                }
                data = integer + floating;
                k++;
                symbol = str[k];
            }
            k++;
            symbol = str[k];
            data *= sign; //we take into account the sign

            //writes the number into an array or alpha
            if (i == 0)
                x->alpha = data;
            else if (i%2 == 0)
                x->b[(i-1)/2] = data;
            else
                x->a[(i-1)/2] = data;
        }
        return 1;
    }

    /*20. function - output on screen coef and angle
    with fixed size of coeficients
    @ param - *poly
    @ returns 1, if func has finished it's work*/
    void output(TrigPoly poly, int type, int width, int precision){
        if((type < 0) || (type > 2)) type = 0;
        width = abs(width);
        precision = abs(precision);
        char modes[3][4] = {"f ", "g ", "e "};
        char out[96] = "%", buf[64];
        sprintf(buf, "%d.%d", width, precision);
        strcat(out, buf);
        strcat(out, modes[type]);
        printf("\nalpha: ");
        printf(out, poly.alpha);

        printf("\ncoeficients of sin: ");
        for (int i = 0; i < poly.n / SI; i++)
            printf(out, poly.a[i]);

        printf("\ncoeficients of cos: ");
        for (int i = 0; i < poly.n / SI; i++)
            printf(out, poly.b[i]);
        printf("\n\n");
    }

    /*21. function - intput from the text file
    @ param - filename and *poly */
    int inputTextFile(char * filename, TrigPoly * x){

        FILE * f = fopen(filename, "rt");
        char * txt = ".txt";
        int len = strlen(filename);

        if (strcmp((filename + len - 4), txt) | f == NULL){
            printf("\nFileNotFoundError");
            return 0;
        }

        int n = spaceCounter(f);
        if (n % 2 != 0){
            printf("\nNonSimetricStringError");
            return 0;
        }
        fclose(f);
        f = fopen(filename, "rt");
        n = n / 2;

        x->n = n * SI;
        x->alpha = doubleFromFile(f);

        x->a = (double *) calloc(n, sizeof(double));
        x->b = (double *) calloc(n, sizeof(double));

        for (int i = 0; i < n; i ++){
            x->a[i] = doubleFromFile(f);
            x->b[i] = doubleFromFile(f);
        }
        fclose(f);
        return 1;
    }

    /*22. function - output to the text file
    @ param - filename, poly, width and size of coef
    @ returns 0, if file can't be created*/
    int outputTextFile(char * File, TrigPoly poly, int type, int width, int precision){
        FILE * f = fopen(File, "at");
        char * txt = ".txt";
        int len = strlen(File);
        //printf("%s", (File + len - 4));
        if (strcmp((File + len - 4), txt) | f == NULL){
            printf("\nFileNotFoundError");
            return 0;
        }
        if((type < 0) || (type > 2)) type = 0;
        char modes[3][4] = {"f ", "g ", "e "};
        char out[96] = "%", buf[64];
        sprintf(buf, "%d.%d", width, precision);
        strcat(out, buf);
        strcat(out, modes[type]);
        fprintf(f, out, poly.alpha);

        fprintf(f, " ");
        for (int i = 0; i < poly.n / SI; i++){
            fprintf(f, out, poly.a[i]);
            fprintf(f, out, poly.b[i]);
        }
        fprintf(f, "\n");
        fclose(f);
        return 1;
    }

    /*23. function - output to console
    @ param - poly, width and size of coef
    @ returns void*/
    void coolOutput(TrigPoly poly, int type, int width, int precision){
        if((type < 0) || (type > 2)) type = 0;
        int i = 1;
        width = abs(width);
        precision = abs(precision);
        char modes[3][4] = {"f ", "g ", "e "};
        char out[96] = "%", buf[64];
        sprintf(buf, "%+d.%d", width, precision);
        strcat(out, buf);
        strcat(out, modes[type]);
        printf("\nalpha: ");
        printf(out, poly.alpha);

        printf("\n");
        printf(out, poly.b[0]);
        printf(" ");
        for (i = 1; i < poly.n / SI; i++){
            printf(out, poly.a[i]);
            printf("sin(%ix) ", i);
            printf(out, poly.b[i]);
            printf("cos(%ix) ", i);
        }
        printf("\n\n");
    }

    /***
    I used <time.h> and found a solution for the
    similar problem here: http://www.c-cpp.ru/content/srand
    so I used time to change seed in random. To turn int into a double
    I divide sometimes and randomly put '-'
    ***/
    /*24. function - generate random poly with length n
    @ param - int n
    @ returns poly*/
    TrigPoly generate(int n){
        int i, stime;
        long ltime;
        TrigPoly x;

        ltime = time (NULL);
        stime = (unsigned int) ltime/2;
        srand(stime);
        if (n < 0){
            n = abs(n);
            printf("\nLength was converted to %i", n);
        }
        x.n = n * SI;
        x.a = (Dtype *) malloc(x.n);
        x.b = (Dtype *) malloc(x.n);
        x.alpha = (Dtype) rand() / (17 * 133);

        if (n == 0){
            printf("\nlength = 0, no coefs");
        }
        for (int i = 0; i < n; i++){
            if (rand() % 7 == 0)
                x.a[i] = (Dtype) - rand() / (17 * 84);
            else
                x.a[i] = (Dtype) rand() / (17 * 84);

            if (rand() % 4 == 0)
                x.b[i] = (Dtype) -rand() / (19 * 68);
            else
                x.b[i] = (Dtype) rand() / (19 * 68);
        }
        return x;
    }


    /*25. function - transforms char into double
    @ param - *file
    @ returns double */
    Dtype doubleFromFile(FILE * f1){

        char symbol;
        double data = 0;
        double integer = 0;
        double floating = 0;
        int sign = 1;

        int exDot = 0;

        double z = 10;

        while (1){
            symbol = fgetc(f1);
            if (symbol == ' ' | symbol == -1 | symbol == '\n')
                break;
            if (symbol == '.'){
                exDot = 1;
                continue;
            }
            else if (symbol == '-1')
                sign = -1;

            symbol = symbol - '0';

            if (!exDot)
                integer = 10 * integer + symbol;
            else {
                floating = floating + (double) (symbol)/z;
                z *= 10;
            }
            data = integer + floating;
        }
        return data * sign;
    }

    /*26. function - counts spaces in the line
    @ param - *file
    @ returns length */
    int spaceCounter(FILE * f){

        int counter = 0, len = 0;
        char s;

        while((s = fgetc(f))&&(s != -1)&&(s != '\n')){
            len ++;
            if (s == ' ')
                counter ++;
        }
        //len = len * sizeof(char);
        //fseek(f, -len, SEEK_CUR);

        return counter;

    }

    /*27. function - transforms char into double
    @ param - *str like "44, 87.9, -0.76"
    @ returns double */
    Dtype doubleFromStr(char * str){

        char symbol;
        int sign = 1;
        int len = 0; //counts length of str
        double data = 0; //a number, which we converted from char
        double integer = 0; //before the dot
        double floating = 0; //after the dot
        int exDot = 0; //flag for the dot
        double z = 10; //helps to convert char into a fraction
        while (str[len] != ',' && str[len] != ' ' && str[len] != '\0' &&  str[len] != '\n'){
            len++;
            symbol = str[len];
        }

        for (int i = 0; i < len; i++){
            symbol = str[i];
            if (symbol == '-'){
                sign = -1;
                continue;
            }
            else if (symbol == '.'){
                exDot = 1;
                continue;
            }
            symbol = symbol - '0';

            if (!exDot)
                integer = 10 * integer + symbol;
            else {
                floating = floating + (double) (symbol)/z;
                z *= 10;
            }
            data = integer + floating;
        }
        return data*sign;
    }

    /*28. function - destroy a struct
    Unfortunately, C doesn't have exceptions,
    so you have to
    @ create poly firstly or input it somehow
    */
    int destroy(TrigPoly * x){
        x->n = 0;
        x->alpha = 0;
        free(x->a);
        free(x->b);
        return 1;
     }
