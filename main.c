#include <stdio.h>
#include "headers/BigNumbers.h"


int main() {

    SYMBOL *ans = (SYMBOL*) malloc(sizeof(SYMBOL));
    printf("Do you want to load numbers from the input file?(y/n)\n--> ");
    fgets(ans, 10, stdin);
    BigInteger *num1;
    BigInteger *num2;

    if (ans[0] == 'y' || ans[0] == 'Y'){
        FILE *file = fopen("../input.txt", "r");
        if (file == NULL){
            printf("Couldn't open the file. Exiting..");
            exit(1);
        }
        num1 = readBigInt(file);
        num2 = readBigInt(file);
        fclose(file);
    } else {
        printf("please, enter 2 big numbers each at the new line:\n--> ");
        num1 = inputBigInt();
        printf("--> ");
        num2 = inputBigInt();
    }

    BigInteger *res_add = add(num1, num2);

    print(num1);
    print(num2);
    printf("addition:\n");
    print(res_add);

    BigInteger *res_sub = sub(num1, num2);
    printf("subtraction:\n");
    print(res_sub);

    BigInteger *res_mul = mul(num1, num2);
    printf("multiplication:\n");
    print(res_mul);

    BigInteger *res_div = divide(num1, num2);
    printf("division:\n");
    print(res_div);

    BigInteger *tmp = mul(res_div, num2);
    BigInteger *remainder = sub(num1, tmp);
    printf("remainder:\n");
    print(remainder);

    BigInteger **res_xgcd = xgcd(num1, num2);
    printf("gcd(a, b) = xa + yb\n");

    printf("gcd(a, b):\n");
    print(gcd(num1, num2));
    printf("x:\n");
    print(res_xgcd[0]);
    printf("y\n");
    print(res_xgcd[1]);

    printf("lcm(a, b):\n");
    print(lcm(num1, num2));

    printf("please, enter the number in binary system:\n--> ");
    BigInteger *num3 = inputAnyBigInt(2);
    print(num3);

    printf("please, enter the number in hexadecimal system:\n--> ");
    BigInteger *num4 = inputAnyBigInt(16);
    print(num4);

    FILE *ofile = fopen("../output.txt", "w");
    if (ofile == NULL){
        printf("Couldn't open output file");
        return 0;
    } else {
        printf("please, wait, saving the output to the outfile...");
        fprint(ofile, num1);
        fprint(ofile, num2);
        fprintf(ofile, "addition:\n");
        fprint(ofile, res_add);
        fprintf(ofile, "subtraction:\n");
        fprint(ofile, res_sub);
        fprintf(ofile, "multiplication:\n");
        fprint(ofile, res_mul);
        fprintf(ofile, "division:\n");
        fprint(ofile, res_div);

        fprintf(ofile, "gcd(a, b) = xa + yb\n");

        fprintf(ofile, "gcd(a, b):\n");
        fprint(ofile, gcd(num1, num2));
        fprintf(ofile, "x:\n");
        fprint(ofile, res_xgcd[0]);
        fprintf(ofile, "y\n");
        fprint(ofile, res_xgcd[1]);

        fprintf(ofile, "lcm(a, b):\n");
        fprint(ofile, lcm(num1, num2));
        fclose(ofile);
    }
    return 0;
}