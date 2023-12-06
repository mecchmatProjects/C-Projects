/* File Cpp_RegularExpressions_test.cpp
Realization of test funcs in C++
Done by Smakula Vladuslav (group: computer methematics 1)
Date 03.12.2023
*/
#include "Cpp_RegularExpressions.h"
#include "../Helpers/Helpers.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>

const size_t MAX_FILENAME_SIZE = 256;

/**
 * Performs an automated test involving file operations.
 * - Creates a 'test' folder if it doesn't exist.
 * - Copies a source file to destination folder.
 * - Processes each destination file with specific functions and prints the results.
 * - Displays information about where to find the output data.
 */
void autoFileTestCpp();

/**
 * Performs a manual test involving file operations.
 * - Accepts user input for input and output filenames.
 * - Processes each file with specific functions and prints the results.
 * - Provides warnings about potential overwriting of input file content.
 */
void manualFileTestCpp();

/**
 * Performs regular expression tests for C++.
 *
 * @param bypass_check Flag to bypass user input for test mode selection (1 for automatic).
 * @return 0 on successful execution.
 *
 * If bypass_check is set to 1, the function automatically runs automated tests; otherwise,
 * it prompts the user to choose between manual and automatic test modes.
 */
int RegularExpressionsTestCpp(int bypass_check=0) {
    if (bypass_check = 1) {
        autoFileTestCpp();
        return 0;
    }
    char test_mode;
    std::cout << "Please enter test mode: manual or automatic (M/A): ";

    if (std::cin >> test_mode) {
        if (test_mode == 'A' || test_mode == 'a') {
            autoFileTestCpp();
        }
        else {
            manualFileTestCpp();
        }
    }
    else {
        std::cerr << "Error reading test mode." << std::endl;
    }
    return 0;
}

void autoFileTestCpp() {
    const std::string folderName = "test";
    _mkdir(folderName.c_str());

    copyFile("C++_RegularExpressions/Cpp_RegularExpressions_test.txt", "test/getHyperlinksFromFileCpp.txt");
    copyFile("C++_RegularExpressions/Cpp_RegularExpressions_test.txt", "test/getDatesFromFileCpp.txt");
    copyFile("C++_RegularExpressions/Cpp_RegularExpressions_test.txt", "test/unifyAllNumbersInFileCpp.txt");
    copyFile("C++_RegularExpressions/Cpp_RegularExpressions_test.txt", "test/replaceAllDatesToCurrentCpp.txt");

    std::cout << "After tests you could find all output data in 'test/' folder" << std::endl;
    std::cout << "Processing getHyperlinksFromFileCpp..." << std::endl;
    int resp = getHyperlinksFromFileCpp("test/getHyperlinksFromFileCpp.txt", "test/getHyperlinksFromFile_outputCpp.txt");
    if (resp == 0) {
        processTest("test/getHyperlinksFromFileCpp.txt", "ValidResponses/getHyperlinksFromFile.valid_resp",
            "test/getHyperlinksFromFile_outputCpp.txt", "ValidResponses/getHyperlinksFromFile_output.valid_resp",
            "1");
    }
    else {
        printf("Test 1 failed, got error");
    }
    std::cout << "Processing getDatesFromFileCpp..." << std::endl;
    resp=getDatesFromFileCpp("test/getDatesFromFileCpp.txt", "test/getDatesFromFile_outputCpp.txt");
    if (resp == 0) {
        processTest("test/getDatesFromFileCpp.txt", "ValidResponses/getDatesFromFile.valid_resp",
            "test/getDatesFromFile_outputCpp.txt", "ValidResponses/getDatesFromFile_output.valid_resp",
            "2");
    }
    else {
        printf("Test 2 failed, got error");
    }
    std::cout << "Processing unifyAllNumbersInFileCpp..." << std::endl;
    resp=unifyAllNumbersInFileCpp("test/unifyAllNumbersInFileCpp.txt");
    if (resp == 0) {
        processTest("test/unifyAllNumbersInFileCpp.txt", "ValidResponses/unifyAllNumbersInFile.valid_resp", NULL, NULL, "3");
    }
    else {
        printf("Test 3 failed, got error");
    }
    std::cout << "Processing replaceAllDatesToCurrentCpp..." << std::endl;
    printf("WARNING: We cant properly test this function because current date is dunamic\nso in any case we need func to create test file with current date\nbut logic in ths func is the same as in getDatesFromFile func\n");
    replaceAllDatesToCurrentCpp("test/replaceAllDatesToCurrentCpp.txt");
    if (resp != 0) {
        printf("Test 4 failed, got error");
    }
}

void manualFileTestCpp() {
    char getHyperlinksInput[MAX_FILENAME_SIZE];
    char getHyperlinksOutput[MAX_FILENAME_SIZE];
    char getDatesInput[MAX_FILENAME_SIZE];
    char getDatesOutput[MAX_FILENAME_SIZE];
    char unifyNumbersInput[MAX_FILENAME_SIZE];
    char replaceDatesInput[MAX_FILENAME_SIZE];

    std::cout << "WARNING: you entered manual testing mode\nplease consider that content of some input files would be overwritten\n";

    std::cout << "Enter the input filename for getHyperlinksFromFileCpp: ";
    std::cin >> getHyperlinksInput;
    if (!fileExists(getHyperlinksInput)) {
        getUserInputAndWriteToFile(getHyperlinksInput);
    }

    std::cout << "Enter the output filename for getHyperlinksFromFileCpp: ";
    std::cin >> getHyperlinksOutput;

    std::cout << "Processing getHyperlinksFromFileCpp..." << std::endl;
    getHyperlinksFromFileCpp(getHyperlinksInput, getHyperlinksOutput);

    std::cout << "Enter the input filename for getDatesFromFileCpp: ";
    std::cin >> getDatesInput;
    if (!fileExists(getDatesInput)) {
        getUserInputAndWriteToFile(getDatesInput);
    }

    std::cout << "Enter the output filename for getDatesFromFileCpp: ";
    std::cin >> getDatesOutput;

    std::cout << "Processing getDatesFromFileCpp..." << std::endl;
    getDatesFromFileCpp(getDatesInput, getDatesOutput);

    std::cout << "Enter the input filename for unifyAllNumbersInFileCpp: ";
    std::cin >> unifyNumbersInput;
    if (!fileExists(unifyNumbersInput)) {
        getUserInputAndWriteToFile(unifyNumbersInput);
    }

    std::cout << "Processing unifyAllNumbersInFileCpp..." << std::endl;
    unifyAllNumbersInFileCpp(unifyNumbersInput);

    std::cout << "Enter the input filename for replaceAllDatesToCurrentCpp: ";
    std::cin >> replaceDatesInput;
    if (!fileExists(replaceDatesInput)) {
        getUserInputAndWriteToFile(replaceDatesInput);
    }

    std::cout << "Processing replaceAllDatesToCurrentCpp..." << std::endl;
    replaceAllDatesToCurrentCpp(replaceDatesInput);
}