/* File CppRe_RegularExpressions_test.cpp
Realization of test funcs in C++ with regex
Done by Smakula Vladuslav (group: computer methematics 1)
Date 05.12.2023
*/
#include "CppRe_RegularExpressions.h"
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
void autoFileTestRe();

/**
 * Performs a manual test involving file operations.
 * - Accepts user input for input and output filenames.
 * - Processes each file with specific functions and prints the results.
 * - Provides warnings about potential overwriting of input file content.
 */
void manualFileTestRe();

/**
 * Performs regular expression tests for C++ with regex.
 *
 * @param bypass_check Flag to bypass user input for test mode selection (1 for automatic).
 * @return 0 on successful execution.
 *
 * If bypass_check is set to 1, the function automatically runs automated tests; otherwise,
 * it prompts the user to choose between manual and automatic test modes.
 */
int RegularExpressionsTestRe(int bypass_check = 0) {
    if (bypass_check = 1) {
        autoFileTestRe();
        return 0;
    }
    char test_mode;
    std::cout << "Please enter test mode: manual or automatic (M/A): ";

    if (std::cin >> test_mode) {
        if (test_mode == 'A' || test_mode == 'a') {
            autoFileTestRe();
        }
        else {
            manualFileTestRe();
        }
    }
    else {
        std::cerr << "Error reading test mode." << std::endl;
    }
    return 0;
}

void autoFileTestRe() {
    const std::string folderName = "test";
    _mkdir(folderName.c_str());

    copyFile("C++Re_RegularExpressions/CppRe_RegularExpressions_test.txt", "test/getHyperlinksFromFileRe.txt");
    copyFile("C++Re_RegularExpressions/CppRe_RegularExpressions_test.txt", "test/getDatesFromFileRe.txt");
    copyFile("C++Re_RegularExpressions/CppRe_RegularExpressions_test.txt", "test/unifyAllNumbersInFileRe.txt");
    copyFile("C++Re_RegularExpressions/CppRe_RegularExpressions_test.txt", "test/replaceAllDatesToCurrentRe.txt");

    std::cout << "After tests you could find all output data in 'test/' folder" << std::endl;
    std::cout << "Processing getHyperlinksFromFileRe..." << std::endl;
    int resp = getHyperlinksFromFileRe("test/getHyperlinksFromFileRe.txt", "test/getHyperlinksFromFile_outputRe.txt");
    if (resp == 0) {
        processTest("test/getHyperlinksFromFileRe.txt", "ValidResponses/getHyperlinksFromFile.valid_resp",
            "test/getHyperlinksFromFile_outputRe.txt", "ValidResponses/getHyperlinksFromFile_output.valid_resp",
            "1");
    }
    else {
        printf("Test 1 failed, got error");
    }
    std::cout << "Processing getDatesFromFileRe..." << std::endl;
    resp=getDatesFromFileRe("test/getDatesFromFileRe.txt", "test/getDatesFromFile_outputRe.txt");
    if (resp == 0) {
        processTest("test/getDatesFromFileRe.txt", "ValidResponses/getDatesFromFile.valid_resp",
            "test/getDatesFromFile_outputRe.txt", "ValidResponses/getDatesFromFile_output.valid_resp",
            "2");
    }
    else {
        printf("Test 2 failed, got error");
    }
    std::cout << "Processing unifyAllNumbersInFileRe..." << std::endl;
    resp=unifyAllNumbersInFileRe("test/unifyAllNumbersInFileRe.txt");
    if (resp == 0) {
        processTest("test/unifyAllNumbersInFileRe.txt", "ValidResponses/unifyAllNumbersInFile.valid_resp", NULL, NULL, "3");
    }
    else {
        printf("Test 3 failed, got error");
    }
    std::cout << "Processing replaceAllDatesToCurrentRe..." << std::endl;
    printf("WARNING: We cant properly test this function because current date is dunamic\nso in any case we need func to create test file with current date\nbut logic in ths func is the same as in getDatesFromFile func\n");
    replaceAllDatesToCurrentRe("test/replaceAllDatesToCurrentRe.txt");
    if (resp != 0) {
        printf("Test 4 failed, got error");
    }
}

void manualFileTestRe() {
    char getHyperlinksInput[MAX_FILENAME_SIZE];
    char getHyperlinksOutput[MAX_FILENAME_SIZE];
    char getDatesInput[MAX_FILENAME_SIZE];
    char getDatesOutput[MAX_FILENAME_SIZE];
    char unifyNumbersInput[MAX_FILENAME_SIZE];
    char replaceDatesInput[MAX_FILENAME_SIZE];

    std::cout << "WARNING: you entered manual testing mode\nplease consider that content of some input files would be overwritten\n";

    std::cout << "Enter the input filename for getHyperlinksFromFileRe: ";
    std::cin >> getHyperlinksInput;
    if (!fileExists(getHyperlinksInput)) {
        getUserInputAndWriteToFile(getHyperlinksInput);
    }

    std::cout << "Enter the output filename for getHyperlinksFromFileRe: ";
    std::cin >> getHyperlinksOutput;

    std::cout << "Processing getHyperlinksFromFileRe..." << std::endl;
    getHyperlinksFromFileRe(getHyperlinksInput, getHyperlinksOutput);

    std::cout << "Enter the input filename for getDatesFromFileRe: ";
    std::cin >> getDatesInput;
    if (!fileExists(getDatesInput)) {
        getUserInputAndWriteToFile(getDatesInput);
    }

    std::cout << "Enter the output filename for getDatesFromFileRe: ";
    std::cin >> getDatesOutput;

    std::cout << "Processing getDatesFromFileRe..." << std::endl;
    getDatesFromFileRe(getDatesInput, getDatesOutput);

    std::cout << "Enter the input filename for unifyAllNumbersInFileRe: ";
    std::cin >> unifyNumbersInput;
    if (!fileExists(unifyNumbersInput)) {
        getUserInputAndWriteToFile(unifyNumbersInput);
    }

    std::cout << "Processing unifyAllNumbersInFileRe..." << std::endl;
    unifyAllNumbersInFileRe(unifyNumbersInput);

    std::cout << "Enter the input filename for replaceAllDatesToCurrentRe: ";
    std::cin >> replaceDatesInput;
    if (!fileExists(replaceDatesInput)) {
        getUserInputAndWriteToFile(replaceDatesInput);
    }

    std::cout << "Processing replaceAllDatesToCurrentRe..." << std::endl;
    replaceAllDatesToCurrentRe(replaceDatesInput);
}