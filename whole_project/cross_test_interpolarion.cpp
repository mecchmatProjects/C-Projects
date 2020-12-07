#include<iostream>
#include<fstream>

using namespace std;

int main(){
    ifstream Cfile;
    ifstream Cppfile;
    Cfile.open("../whole_project/c_project_interpolation/tests/out.txt");
    Cppfile.open("../whole_project/c++_project_interpolation/tests/out.txt");
    string Cstr, Cppstr;
    getline(Cfile, Cstr);
    getline(Cppfile, Cppstr);
    cout << "Answer from C program: ";
    cout << Cstr << endl;
    cout << "Answer from C++ program: ";
    cout << Cppstr << endl;
    return 0;
}