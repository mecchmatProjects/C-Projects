/* File Random2D_Muzychina_test.c
Realization of tests for Random2D class (32) (C)
Done by Anna Muzychina (group comp. mat. 2)
Date 09.12.2020 */

#include "../headers/Random2D_Muzychina.h"

// g++ Random2D_Muzychina_test.c ../src/Random2D_Muzychina.c -o test
// test.exe

int main() {
    // srand(time(NULL));
    Random2D test;
    generate_numbers_Random2D(&test);
    char c;
    NType n = 0, m = 0;

    printf("Select data entry method (console/file .txt)\nc/f: ");
    scanf("%c", &c);
    if (c == 'f') {
        const char* filename = "Random2D_Muzychina_test.txt";
        FILE* finp = fopen(filename, "r");
        fscanf(finp, "%u%u", &n, &m);
        fclose(finp);
    }

    FILE* fout = fopen("output.txt", "w");
    print_integer_Random2D(fout, "Next s_n: %u\n", next_s_n_Random2D(&test));
    print_double_Random2D(fout, "Next r_n: %lf\n", next_r_n_Random2D(&test));
    print_integer_Random2D(fout, "Random integer: %i\n", generate_integer_Random2D(&test));
    print_double_Random2D(fout, "Random real: %lf\n", generate_real_Random2D(&test));
    DType* v1_large = generate_vector_Random2D(&test, 1000);
    DType* v2_large = generate_vector_Random2D(&test, 1000);
    correlationCoefficient(v1_large, v2_large, 1000, fout);

    if (!n) {
        printf("Enter dimension of vectors: ");
        scanf("%u", &n);
    }
    DType* v1 = generate_vector_Random2D(&test, n);
    DType* v2 = generate_vector_Random2D(&test, n);
    correlationCoefficient(v1, v2, n, fout);

    if (!m) {
        printf("Enter dimension of sphere: ");
        scanf("%u", &m);
    }
    sphere_volume_Monte_Carlo_Random2D(&test, m, fout);
    
    fclose(fout);
    free(v1_large);
    free(v2_large);
    free(v1);
    free(v1);
    return 0;
}
