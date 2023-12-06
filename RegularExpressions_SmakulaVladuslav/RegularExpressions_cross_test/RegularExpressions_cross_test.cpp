/* File RegularExpressions_cross_test.cpp
Realization of cross-test functional
Done by Smakula Vladuslav (group: computer methematics 1)
Date 05.12.2023
*/
#include "../C_RegularExpressions/C_RegularExpressions_test.h"
#include "../C++_RegularExpressions/Cpp_RegularExpressions_test.h"
#include "../C++Re_RegularExpressions/CppRe_RegularExpressions_test.h"
#include "../Helpers/Helpers.h"
#include <stdio.h>

/**
 * Performs a cross-test to check if functions implemented in different languages produce the same results.
 *
 * This function performs automated tests for functions implemented in C, C++, and using regular expressions.
 * It compares the output of corresponding functions across languages to ensure consistency.
 * Results are saved for further analysis.
 */
void CrossTest();


//int main() {
//    CrossTest();
//}


void CrossTest() {
    int resp1, resp2, resp3;
	printf("Perfirming cross test to check if funcs realized in different languages perform the same\n");
    RegularExpressionsTestC(1);
    RegularExpressionsTestCpp(1);
    RegularExpressionsTestRe(1);

    printf("All func results are saved so now we can perform cross test\n");
    printf("getHyperlinksFromFile\n");
    processTest("test/getHyperlinksFromFile.txt", "test/getHyperlinksFromFileCpp.txt", 
        "test/getHyperlinksFromFile_output.txt", "test/getHyperlinksFromFile_outputCpp.txt",
            "getHyperlinksFromFile on C and C++");
    processTest("test/getHyperlinksFromFile.txt", "test/getHyperlinksFromFileRe.txt",
        "test/getHyperlinksFromFile_output.txt", "test/getHyperlinksFromFile_outputRe.txt",
        "getHyperlinksFromFile on C and C++ regex");

    printf("getDatesFromFile\n");
    processTest("test/getDatesFromFile.txt", "test/getDatesFromFile.txt",
        "test/getDatesFromFile_output.txt", "test/getDatesFromFile_outputCpp.txt",
        "getDatesFromFile on C and C++");
    processTest("test/getDatesFromFile.txt", "test/getDatesFromFileRe.txt",
        "test/getDatesFromFile_output.txt", "test/getDatesFromFile_outputRe.txt",
        "getDatesFromFile on C and C++ regex");

    printf("unifyAllNumbersInFile\n");
    processTest("test/unifyAllNumbersInFile.txt", "test/unifyAllNumbersInFileCpp.txt",
        NULL, NULL,
        "unifyAllNumbersInFile on C and C++");
    processTest("test/unifyAllNumbersInFile.txt", "test/unifyAllNumbersInFileRe.txt",
        NULL, NULL,
        "unifyAllNumbersInFile on C and C++ regex");

    printf("replaceAllDatesToCurrent\n");
    processTest("test/replaceAllDatesToCurrent.txt", "test/replaceAllDatesToCurrentCpp.txt",
        NULL, NULL,
        "replaceAllDatesToCurrent on C and C++");
    processTest("test/replaceAllDatesToCurrent.txt", "test/replaceAllDatesToCurrentRe.txt",
        NULL, NULL,
        "replaceAllDatesToCurrent on C and C++ regex");

}