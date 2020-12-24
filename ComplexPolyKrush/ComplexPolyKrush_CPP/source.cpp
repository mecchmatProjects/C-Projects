#include <fstream>
#include "ComplexPolynomial.cpp"

int OUTPUT_MODE;

void run_tests(string sc_1, string sc_2, string sc_x){
    vector<string> sv_1;
    vector<string> sv_2;
    vector<string> sv_x;

    split(sc_1, sv_1);
    split(sc_2, sv_2);
    split(sc_x, sv_x);

    int n1, n2, nx;
    n1 = sv_1.size() / 2;
    n2 = sv_2.size() / 2;
    nx = sv_x.size() / 2;

    base * coeffs_1 = fill_from_vector(sv_1, n1);
    base * coeffs_2 = fill_from_vector(sv_2, n2);
    base * coeffs_3 = fill_from_vector(sv_x, nx);
    base comp_num_x = coeffs_3[0];

    ComplexPolynomial cpoly_1(coeffs_1, n1);
    ComplexPolynomial cpoly_2(coeffs_2, n2);

    if (OUTPUT_MODE == 1){
        ofstream FILE_OUT("output.txt");

        FILE_OUT << "Test print polynomial\n";
        FILE_OUT << cpoly_1 << endl;

        FILE_OUT << "\nTest polynomials addition\n";
        FILE_OUT << cpoly_1 + cpoly_2 << endl;

        FILE_OUT << "\nTest polynomials subtraction\n";
        FILE_OUT << cpoly_1 - cpoly_2 << endl;

        FILE_OUT << "\nTest polynomial deviation\n";
        FILE_OUT << cpoly_1.calc_derivative() << endl;

        FILE_OUT << "\nTest polynomial evaluate\n";
        FILE_OUT << cpoly_1.evaluate(comp_num_x) << endl;

        FILE_OUT << "\nTest polynomial derivation evaluate\n";
        FILE_OUT << cpoly_1.evaluate_derivative(comp_num_x) << endl;

        FILE_OUT << "\nTest random generated polynomial\n";
        cpoly_1.generate(4);
        FILE_OUT << cpoly_1 << endl;
    }
    else if (OUTPUT_MODE == 0) {
        ofstream FILE_OUT("utput.txt");

        cout << "Test print polynomial\n";
        cout << cpoly_1 << endl;

        cout << "\nTest polynomials addition\n";
        cout << cpoly_1 + cpoly_2 << endl;

        cout << "\nTest polynomials subtraction\n";
        cout << cpoly_1 - cpoly_2 << endl;

        cout << "\nTest polynomial deviation\n";
        cout << cpoly_1.calc_derivative() << endl;

        cout << "\nTest polynomial evaluate\n";
        cout << cpoly_1.evaluate(comp_num_x) << endl;

        cout << "\nTest polynomial derivation evaluate\n";
        cout << cpoly_1.evaluate_derivative(comp_num_x) << endl;

        cout << "\nTest random generated polynomial\n";
        cpoly_1.generate(4);
        cout << cpoly_1 << endl;
    }
}

void input_console() {
    cout << "\n--- CONSOLE INPUT ---\n";
    cout << "Enter polynomials real and imagine params through the space\n";

    string str_coeffs_1, str_coeffs_2, str_coeffs_x;
    cin.ignore();
    cout << "Polynomial 1: ";
    getline(cin, str_coeffs_1);
    cout << "Polynomial 2: ";
    getline(cin, str_coeffs_2);

    cout << "Polynomial x: ";
    getline(cin, str_coeffs_x);

    run_tests(str_coeffs_1, str_coeffs_2, str_coeffs_x);
}
void input_file(){
    ifstream fin("nput.txt");

    string str_coeffs_1, str_coeffs_2, str_coeffs_x;

    getline(fin, str_coeffs_1);
    getline(fin, str_coeffs_2);
    getline(fin, str_coeffs_x);

    fin.close();

    run_tests(str_coeffs_1, str_coeffs_2, str_coeffs_x);
}

void run(){
    int input_mode;

    cout << "Choose the INPUT mode\n0 - Console\n1 - File\nYour choice: ";
    cin >> input_mode;
    cout << "Choose the OUTPUT mode\n0 - Console\n1 - File\nYour choice: ";
    cin >> OUTPUT_MODE;

    if (input_mode == 0) input_console();
    if (input_mode == 1) input_file();

}



