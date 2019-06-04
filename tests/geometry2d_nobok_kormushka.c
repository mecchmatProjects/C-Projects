#define _ERROR_INVALID_INPUT 1

#include "../headers/geometry2d_nobok_kormushka.h"

#include <stdlib.h>

void TestVectorOperations()
{
    Vector2D a, b;

    printf("Vector Operations:\n");

    console_input_vector2d_data(&a);
    stream_output_vector2d_data(stdout, a, 1, 1, 1);
    console_input_vector2d_data(&b);
    stream_output_vector2d_data(stdout, b, 1, 1, 1);

    printf("Arithmetic:\n");

    printf("a + b:\n");
    stream_output_vector2d_data(stdout, binary_sum_vectors(a, b), 1, 1, 1);

    printf("a - b:\n");
    stream_output_vector2d_data(stdout, binary_sub_vectors(a, b), 1, 1, 1);

    printf("[a , b] = %.4f\n", binary_mul_vectors(a, b));
    printf("<a , b> = %.4f\n", binary_mul_scalar_vectors(a, b));

    printf("||a|| = %.4f\n", norm_of_vector(a));
    printf("||b|| = %.4f\n", norm_of_vector(b));

    printf("a || b - ? => %i\n", collinear_vectors(a, b));
    printf("a ⊥ b - ? => %i\n", orthogonal_vectors(a, b));

    printf("Normed a - ? => %i\n", normed_vector(a));
    printf("Normed b - ? => %i\n", normed_vector(b));

    printf("Unary a = a + b:\n");
    unary_sum_vectors(&a, b);
    stream_output_vector2d_data(stdout, a, 1, 1, 1);

    printf("Unary a = a - b:\n");
    unary_sub_vectors(&a, b);
    stream_output_vector2d_data(stdout, a, 1, 1, 1);
}

void TestTriangleOperations()
{}

void TestIntersectOperations()
{}

void TestTextOperations()
{}

int main()
{
    short m;
    printf("Enter your mode:\n"
           "1 - Test basic vector operations\n"
           "2 - Test basic triangle operations\n"
           "3 - Test intersection functions\n"
           "4 - Test operations with text files\n");
    scanf("%hi", &m);

    switch (m)
    {
        case 1:
        {
            TestVectorOperations();
            break;
        }
        case 2:
        {
            TestTriangleOperations();
            break;
        }
        case 3:
        {
            TestIntersectOperations();
            break;
        }
        case 4:
        {
            TestTextOperations();
            break;
        }
        default:
        {
            printf("Invalid input.\n");
            exit(_ERROR_INVALID_INPUT);
        }
    }
}