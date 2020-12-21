/* File Random2D_Muzychina_test.cpp
Realization of tests for Random2D class (32) (C++)
Done by Anna Muzychina (group comp. mat. 2)
Date 09.12.2020 */

#include "../headers/Random2D_Muzychina.h"

// g++ Random2D_Muzychina_test.cpp ../src/Random2D_Muzychina.cpp -o test
// test.exe

int main() {
    // srand(time(NULL));
    Random2D test;
    char c;
    NType n = 0, m = 0;

    cout << "Select data entry method (console/file .txt)\nc/f: ";
    cin >> c;
    if (c == 'f') {
        string filename = "Random2D_Muzychina_test.txt";
        ifstream finp(filename);
        finp >> n >> m;
        finp.close();
    }

    FILE* fout = fopen("output.txt", "w");
    test.print_Random2D(fout, "Next s_n: %u\n", test.next_s_n_Random2D());
    test.print_Random2D(fout, "Next r_n: %lf\n", test.next_r_n_Random2D());
    test.print_Random2D(fout, "Random integer: %i\n", test.generate_integer_Random2D());
    test.print_Random2D(fout, "Random real: %lf\n", test.generate_real_Random2D());
    vector<DType> v1_large = test.generate_vector_Random2D();
    vector<DType> v2_large = test.generate_vector_Random2D();
    test.correlationCoefficient(v1_large, v2_large, fout);

    if (!n) {
        cout << "Enter dimension of vectors: ";
        cin >> n;
    }
    vector<DType> v1 = test.generate_vector_Random2D(n);
    vector<DType> v2 = test.generate_vector_Random2D(n);
    test.correlationCoefficient(v1, v2, fout);

    if (!m) {
        cout << "Enter dimension of sphere: ";
        cin >> m;
    }
    test.sphere_volume_Monte_Carlo_Random2D(m, fout);
    
    fclose(fout);
    return 0;
}
