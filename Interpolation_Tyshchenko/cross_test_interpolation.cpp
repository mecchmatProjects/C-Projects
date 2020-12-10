#include<iostream>
#include<fstream>

using namespace std;

int main(){
    ifstream Cfile;
    ifstream Cppfile;
    Cfile.open("../Interpolation_Tyshchenko/Interpolation_Tyshchenko_C/tests/out.txt");
    Cppfile.open("../Interpolation_Tyshchenko/Interpolation_Tyshchenko_CPP/tests/out.txt");
    string Cstr, Cppstr;
    getline(Cfile, Cstr);
    getline(Cppfile, Cppstr);
    Cfile.close();
    Cppfile.close();
    cout << "Answer from C program: ";
    cout << Cstr << endl;
    cout << "Answer from C++ program: ";
    cout << Cppstr << endl;
    cout << "If results are different, maybe you didnt run both c and cpp projects or your data was different in these projects" << endl;
    return 0;
}
