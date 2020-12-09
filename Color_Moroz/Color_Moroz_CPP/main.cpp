#include <iostream>

#include "test/test.hpp"

using namespace std;

void runTests();

int main()
{
    runTests();
    return 0;
}

void runTests(){
    try {
        cout << "\n--RGBA TEST--\n" << endl;
        testRGBA();
        cout << "\n--CMYK TEST--\n" << endl;
        testCMYK();
        cout << "\n--HSB TEST--\n" << endl;
        testHSB();
        cout << "\n--CONVERT TEST--\n" << endl;
        testConvert();
        cout << "\n--IMAGE LOAD AND SAVE TEST--\n" << endl;
        testImageLoadSave();
        cout << "\n--IMAGE FILTER TEST--\n" << endl;
        testImageMask();
        cout << "\n--TESTS PASSED--\n" << endl;
    } catch (...) {
        cout << "\n--TESTS NOT PASSED--\n" << endl;
    }
}
