/* File C_RegularExpressions_test.c
Realization of test funcs in C
Done by Smakula Vladuslav (group: computer methematics 1)
Date 03.12.2023
*/
#include "C_RegularExpressions.h"
#include "../Helpers/Helpers.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_SIZE 256


/**
 * Performs an automated test involving file operations.
 * - Creates a 'test' folder if it doesn't exist.
 * - Copies a source file to destination folder.
 * - Processes each destination file with specific functions and prints the results.
 * - Displays information about where to find the output data.
 */
void autoFileTest();

/**
 * Performs a manual test involving file operations.
 * - Accepts user input for input and output filenames.
 * - Processes each file with specific functions and prints the results.
 * - Provides warnings about potential overwriting of input file content.
 */
void manualFileTest();

/**
 * Entry point of the program.
 * - Prompts the user to choose between manual (M) or automatic (A) test mode.
 * - Calls the appropriate test function based on user input.
 * - Returns 0 on successful execution.
 */
 
 /**
  * Performs regular expression tests for C.
  *
  * @param bypass_check Flag to bypass user input for test mode selection (1 for automatic).
  * @return 0 on successful execution.
  *
  * If bypass_check is set to 1, the function automatically runs automated tests; otherwise,
  * it prompts the user to choose between manual and automatic test modes.
  */
int RegularExpressionsTestC(int bypass_check) {
    //C does not support default parameter values so bypass_check suposed to be passed as func var
    if (bypass_check = 1) {
        autoFileTest();
        return 0;
    }
    char test_mode;
    printf("Please enter test mode: manual or automatic (M/A):");
    if (scanf_s("%c", &test_mode, sizeof(test_mode)) == 1) {
        if (test_mode == 'A') {
            autoFileTest();
        }
        else {
            manualFileTest();
        }
    }
    else {
        printf("Error reading test mode.\n");
    }

    return 0;
}

void autoFileTest() {
    const char* folderName = "test";
    if (_access(folderName, 0) != 0) {
        if (mkdir(folderName) != 0) {
            perror("Error creating directory test/");
            return 1;
        }
    }

    copyFile("C_RegularExpressions/C_RegularExpressions_test.txt", "test/getHyperlinksFromFile.txt");
    copyFile("C_RegularExpressions/C_RegularExpressions_test.txt", "test/getDatesFromFile.txt");
    copyFile("C_RegularExpressions/C_RegularExpressions_test.txt", "test/unifyAllNumbersInFile.txt");
    copyFile("C_RegularExpressions/C_RegularExpressions_test.txt", "test/replaceAllDatesToCurrent.txt");

    printf("After tests you could find all output data in 'test/' folder\n");
    printf("Processing getHyperlinksFromFile...\n");
    int resp=getHyperlinksFromFile("test/getHyperlinksFromFile.txt", "test/getHyperlinksFromFile_output.txt");
    if (resp == 0) {
        processTest("test/getHyperlinksFromFile.txt", "ValidResponses/getHyperlinksFromFile.valid_resp",
            "test/getHyperlinksFromFile_output.txt", "ValidResponses/getHyperlinksFromFile_output.valid_resp",
            "1");
    }
    else {
        printf("Test 1 failed, got error");
    }
    printf("Processing getDatesFromFile...\n");
    resp = getDatesFromFile("test/getDatesFromFile.txt", "test/getDatesFromFile_output.txt");
    if (resp == 0) {
        processTest("test/getDatesFromFile.txt", "ValidResponses/getDatesFromFile.valid_resp",
            "test/getDatesFromFile_output.txt", "ValidResponses/getDatesFromFile_output.valid_resp",
            "2");
    }
    else {
        printf("Test 2 failed, got error");
    }
    printf("Processing unifyAllNumbersInFile...\n");
    resp = unifyAllNumbersInFile("test/unifyAllNumbersInFile.txt");
    if (resp == 0) {
        processTest("test/unifyAllNumbersInFile.txt", "ValidResponses/unifyAllNumbersInFile.valid_resp", NULL, NULL, "3");
    }
    else {
        printf("Test 3 failed, got error");
    }
    printf("Processing replaceAllDatesToCurrent...\n");
    printf("WARNING: We cant properly test this function because current date is dunamic\nso in any case we need func to create test file with current date, but logic in ths func is the same as in getDatesFromFile func\n");
    resp=replaceAllDatesToCurrent("test/replaceAllDatesToCurrent.txt");
    if (resp != 0) {
        printf("Test 4 failed, got error");
    }
}

void manualFileTest() {
    char getHyperlinksInput[MAX_FILENAME_SIZE];
    char getHyperlinksOutput[MAX_FILENAME_SIZE];
    char getDatesInput[MAX_FILENAME_SIZE];
    char getDatesOutput[MAX_FILENAME_SIZE];
    char unifyNumbersInput[MAX_FILENAME_SIZE];
    char replaceDatesInput[MAX_FILENAME_SIZE];

    printf("WARNING: you entered manual testing mode\nplease consider that content of some input files would be overwritten\n");
    printf("Enter the input filename for getHyperlinksFromFile: ");
    scanf_s("%s", getHyperlinksInput, sizeof(getHyperlinksInput));
    if (!fileExists(getHyperlinksInput)) {
        getUserInputAndWriteToFile(getHyperlinksInput);
    }

    printf("Enter the output filename for getHyperlinksFromFile: ");
    scanf_s("%s", getHyperlinksOutput, sizeof(getHyperlinksOutput));

    printf("Processing getHyperlinksFromFile...\n");
    getHyperlinksFromFile(getHyperlinksInput, getHyperlinksOutput);

    printf("Enter the input filename for getDatesFromFile: ");
    scanf_s("%s", getDatesInput, sizeof(getDatesInput));
    if (!fileExists(getDatesInput)) {
        getUserInputAndWriteToFile(getDatesInput);
    }

    printf("Enter the output filename for getDatesFromFile: ");
    scanf_s("%s", getDatesOutput, sizeof(getDatesOutput));

    printf("Processing getDatesFromFile...\n");
    getDatesFromFile(getDatesInput, getDatesOutput);

    printf("Enter the input filename for unifyAllNumbersInFile: ");
    scanf_s("%s", unifyNumbersInput, sizeof(unifyNumbersInput));
    if (!fileExists(unifyNumbersInput)) {
        getUserInputAndWriteToFile(unifyNumbersInput);
    }

    printf("Processing unifyAllNumbersInFile...\n");
    unifyAllNumbersInFile(unifyNumbersInput);

    printf("Enter the input filename for replaceAllDatesToCurrent: ");
    scanf_s("%s", replaceDatesInput, sizeof(replaceDatesInput));
    if (!fileExists(replaceDatesInput)) {
        getUserInputAndWriteToFile(replaceDatesInput);
    }

    printf("Processing replaceAllDatesToCurrent...\n");
    replaceAllDatesToCurrent(replaceDatesInput);
}