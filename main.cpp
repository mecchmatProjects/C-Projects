#include "src/tensor.hxx"
#include <iostream>
#include <fstream>

using namespace std;

typedef int TEST_TYPE;


void readTensor(Tensor<TEST_TYPE> &tensor, istream &file){
    if (tensor.dimension() == 1){
        TEST_TYPE tmp;
        for (ARRAY_SIZE itr = 0; itr < tensor.shape()[0] && file >> tmp; ++itr){
            tensor[itr] = Tensor<TEST_TYPE >(tmp);
        }
    } else {
        for (ARRAY_SIZE itr = 0; itr < tensor.shape()[0]; ++itr){
            readTensor(tensor[itr], file);
        }
    }
    if (file.fail() && !file.eof()) throw domain_error("Couldn't read information from file");
}

Tensor<TEST_TYPE > &loadFromFile(istream &file){
    ARRAY_SIZE dim;
    if (file >> dim && dim > 0){
        auto *shape = new ARRAY_SIZE[dim];
        for (ARRAY_SIZE itr = 0; itr < dim && file >> shape[itr]; ++itr);
        if (file.fail() && !file.eof()) throw domain_error("Couldn't read information from file");

        auto res = new Tensor<TEST_TYPE >(dim, shape);
        readTensor(*res, file);
        return *res;
    } else {
        throw domain_error("Bad file");
    }
}



int main() {
    char mod;

    ofstream outFile("output.txt", ios::out);
    bool flag = true;
    if (!outFile.is_open()){
        cout << "Could not open the output file, output will be written only in console." << endl;
        flag = false;
    }

    cout << "Do you want to input arrays from file?(y/n)\n--> ";
    cin >> mod;
    auto *testTensor1_p = new Tensor<TEST_TYPE >();
    auto *testTensor2_p = new Tensor<TEST_TYPE >();
    if (mod == 'y' || mod == 'Y'){
        ifstream inputFile("../input.txt", ios::in);     // read from file
        if (!inputFile.is_open()){
            cout << "Could not open the file";
            return 0;
        }

        testTensor1_p = &loadFromFile(inputFile);
        testTensor2_p = &loadFromFile(inputFile);
        cout << "tensor1:" << endl;
        testTensor1_p->print();
        cout << "tensor2:" << endl;
        testTensor2_p->print();

        if (flag){
            outFile << "tensor1:" << endl;
            testTensor1_p->write(outFile);
            outFile << "tensor2:" << endl;
            testTensor2_p->write(outFile);
        }

    } else {
        ARRAY_SIZE dim;
        cout << "Please, enter 2 tensors with same shapes." << endl;   // read from console
        cout << "Tensor1" << endl << "Dim:\n--> ";
        cin >> dim;
        auto shape = new ARRAY_SIZE[dim];
        ARRAY_SIZE amount = 1;
        for (ARRAY_SIZE itr = 0; itr < dim; ++itr){
            cout << endl << "shape[" << itr << "]: ";
            cin >> shape[itr];
            amount *= shape[itr];
        }
        cout << endl << "Please, enter the " << amount << " numbers:" << endl;
        auto tmp = Tensor<TEST_TYPE >(dim, shape);
        testTensor1_p = &tmp;
        readTensor(*testTensor1_p, cin);

        cout << "Tensor2" << endl << "Dim:\n--> ";
        cin >> dim;
        auto shape2 = new ARRAY_SIZE[dim];
        ARRAY_SIZE amount2 = 1;
        for (ARRAY_SIZE itr = 0; itr < dim; ++itr){
            cout << endl << "shape[" << itr << "]: ";
            cin >> shape2[itr];
            amount2 *= shape2[itr];
        }
        cout << endl << "Please, enter the " << amount2 << " numbers:" << endl;
        auto tmp2 = Tensor<TEST_TYPE >(dim, shape);
        testTensor2_p = &tmp2;
        readTensor(*testTensor2_p, cin);

    }

    auto testTensor1 = *testTensor1_p;
    auto testTensor2 = *testTensor2_p;

    while (true){
        int workMod;
        cout << "Please, enter what do you want to do with tensors:" << endl;
        cout << "1 - do operation between the both of tensors" << endl;
        cout << "2 - do operation between the 1-st tensor and number" << endl;
        cout << "3 - do operation between the 2-nd tensor and number" << endl;
        cout << "0 - exit" << endl << "--> ";

        cin >> workMod;
        if (workMod == 1){
            cout << "Please, enter the operation (+, -, *, /)" << endl << "--> ";
            cin >> mod;
            if (mod == '+') (testTensor1 + testTensor2).print();
            else if (mod == '-') (testTensor1 - testTensor2).print();
            else if (mod == '*') (testTensor1 * testTensor2).print();
            else (testTensor1 / testTensor2).print();
        } else if (workMod == 2){

            cout << "Please, enter the operation (+, -, *, /)" << endl << "--> ";
            cin >> mod;
            cout << "Please, enter the number" << endl << "--> ";
            TEST_TYPE number;
            cin >> number;
            if (mod == '+') (testTensor1 + number).print();
            else if (mod == '-') (testTensor1 - number).print();
            else if (mod == '*') (testTensor1 * number).print();
            else (testTensor1 / number).print();
        } else if (workMod == 3){

            cout << "Please, enter the operation (+, -, *, /)" << endl << "--> ";
            cin >> mod;
            cout << "Please, enter the number" << endl << "--> ";
            TEST_TYPE number;
            cin >> number;
            if (mod == '+') (testTensor2 + number).print();
            else if (mod == '-') (testTensor2 - number).print();
            else if (mod == '*') (testTensor2 * number).print();
            else (testTensor2 / number).print();
        } else
            break;
    }
}