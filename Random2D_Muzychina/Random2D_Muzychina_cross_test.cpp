/* File Random2D_Muzychina_cross_test.cpp
Realization of cross test for Random2D (32) (C++)
Done by Anna Muzychina (group comp. mat. 2)
Date 09.12.2020 */

#include <iostream>
#include <fstream>

using namespace std;


// Запустите тестовые файлы программ на С и С++ перед этим тестом
int main() {
    ifstream cpp_output;
    ifstream c_output;
    cpp_output.open("Random2D_Muzychina_CPP/tests/output.txt");
    c_output.open("Random2D_Muzychina_C/tests/output.txt");
    string cpp_line, c_line;
    cout << "Result of the C++ program:" << endl;
    for (int i = 0; i < 9; i++) {
        getline(cpp_output, cpp_line);
        cout << cpp_line << endl;
    }
    cout << "\nResult of the C program:" << endl;
    for (int i = 0; i < 9; i++) {
        getline(c_output, c_line);
        cout << c_line << endl;
    }
    cpp_output.close();
    c_output.close();
    return 0;
}
