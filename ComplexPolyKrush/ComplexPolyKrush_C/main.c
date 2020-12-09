#include "ComplexPoly.c"

int main(){
    complex number1;
    number1.image = 10.3;
    number1.real = 5.1;
    printf("(%g+%gI)\n", number1.real, number1.image);

    complex number2;
    printf("image part:\n");
    scanf("%lf", &number2.image);
    printf("real part:\n");
    scanf("%lf", &number2.real);
    printf("(%g+(%g)I)\n", number2.real, number2.image);
    complex number3 = plus(number1, number2);
    printf("(%g+(%g)I)\n", number3.real, number3.image);
    complex number4, number5, number6;
    number4.real = 2;
    number4.image = 2.5;
    number5.real = -1;
    number5.image = 1.5;
    number6 = multiply(number4, number5);
    printf("(%g+(%g)I)\n", number6.real, number6.image);
    complex number7 = division(number4, number5);
    printf("(%g+(%g)I)\n", number7.real, number7.image);

    int n1, n2;
    complex * arr1 = Init_coplex_Array(&n1);
    complex * arr2 = Init_coplex_Array(&n2);
    printf("n1=%d\n", n1);

    ShowArray(arr1, n1);
    ShowArray(arr2, n2);

    int n3;
    complex *arr3 = add_arrays(arr1, arr2,n1,n2,&n3);
    printf("n3=%d\n", n3);
    ShowArray(arr3, n3);

    int n4;
    complex *arr4 = subtraction_arrays(arr1, arr2, n1, n2, &n4);
    printf("n3=%d\n", n4);
    ShowArray(arr4, n4);

    complex result;
    result = value(arr1, n1);
    printf("(%g+(%g)I) ", result.real, result.image);
    printf("\n");

    int SIZE;
    complex *arr5=generate(&SIZE);
    ShowArray(arr5, SIZE);


    complex *arr6;
    int n6;
    arr6 = derivative(arr1, n1, &n6);
    ShowArray(arr6, n6);
    write_into_file(arr6,n6);
}
