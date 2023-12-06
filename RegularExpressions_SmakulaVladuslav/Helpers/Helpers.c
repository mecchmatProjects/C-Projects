/* File Helpers.c
Realization of help funcs in C
Done by Smakula Vladuslav (group: computer methematics 1)
Date 04.12.2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 this func is depricated
 */
//void processTest(const char* filename1, const char* filename2, const char* testName) {
//    int response = compareFiles(filename1, filename2);
//    if (response == 1) {
//        printf("Test %s passed\n",testName);
//    }
//    else {
//        printf("Test %s failed\noutput files and valid responses are not identical\n", testName);
//    }
//}

/**
 * @brief Processes a test case by comparing the content of two pairs of files.
 *
 * @param filename1 The path to the first input file.
 * @param filename2 The path to the second input file.
 * @param filename1_outp The path to the first output file.
 * @param filename2_outp The path to the second output file.
 * @param testName The name of the test case.
 *
 * @note This function compares the content of the two pairs of input and output files
 * and prints a message indicating whether the test passed or failed based on the file content.
 */
void processTest(const char* filename1, const char* filename2, 
                 const char* filename1_outp, const char* filename2_outp,
                 const char* testName) {
    int response1 = compareFiles(filename1, filename2);
    int response2=0;
    //this done because func overloading dont work properly
    if (filename1_outp == NULL) {
        response2 = 1;
    }
    else {
        response2 = compareFiles(filename1_outp, filename2_outp);
    }
    if (response1 == 1 && response2==1) {
        printf("Test %s passed\n", testName);
    }
    else {
        printf("Test %s failed\noutput files and valid responses are not identical\n", testName);
    }
}

/**
 * @brief Compares two text files to check if their content is identical.
 *
 * @param filename1 The path to the first file.
 * @param filename2 The path to the second file.
 * @return Returns 1 if the files are similar (content is identical), 0 otherwise.
 *         Returns 0 in case of an error (e.g., unable to open files).
 */
int compareFiles(const char* filename1, const char* filename2) {
    FILE* file1, * file2;
    char ch1, ch2;

    // Open the files for comparison
    if (fopen_s(&file1, filename1, "r") != 0 || fopen_s(&file2, filename2, "r") != 0) {
        perror("Error opening files");
        return 0; // Consider files as not similar in case of an error
    }

    // Compare files
    do {
        ch1 = fgetc(file1);
        ch2 = fgetc(file2);

        if (ch1 != ch2) {
            fclose(file1);
            fclose(file2);
            return 0; // Files are not similar
        }

    } while (ch1 != EOF && ch2 != EOF);

    // If one file is longer than the other, they are not similar
    if (ch1 == EOF && ch2 != EOF) {
        fclose(file1);
        fclose(file2);
        return 0;
    }

    if (ch1 != EOF && ch2 == EOF) {
        fclose(file1);
        fclose(file2);
        return 0;
    }
    fclose(file1);
    fclose(file2);

    return 1;
}

/**
 * Checks if a file exists at the specified path.
 *
 * @param filename The path to the file.
 * @return Returns 1 if the file exists, 0 otherwise.
 */
int fileExists(const char* filename) {
    return _access(filename, 0) == 0;
}

/**
 * Writes user input from the console to a file until the user enters "~stop".
 *
 * @param filename The path to the file where user input will be written.
 *
 * @note The user is prompted to enter data until the input "~stop" is encountered.
 * Each user input line is written to the file, terminated by a newline character.
 * After user input is complete, the file is closed, and a success message is printed.
 */
void WriteToFileFromConsole(const char* filename) {
    FILE* outputFile;
    char userInput[1000];

    fopen_s(&outputFile, filename, "w");
    if (outputFile == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter data (enter '~stop' to finish):\n");
    // Consume the newline character
    getchar();
    // Continue getting input until the user enters "~stop"
    while (1) {
        printf("> ");
        if (scanf_s("%[^\n]", userInput, sizeof(userInput)) == 1) {
            getchar();

            if (strcmp(userInput, "~stop") == 0) {
                break;
            }

            fprintf(outputFile, "%s\n", userInput);
        }
        else {
            printf("Error reading input.\n");
            break;
        }
    }

    fclose(outputFile);
    printf("Data successfully written to '%s'.\n", filename);
}

/**
 * Checks if the specified file exists and prompts the user to create it manually from the console.
 *
 * @param filename The path to the file.
 *
 * @note If the file does not exist, the function asks the user if they want to create it manually.
 * If the user agrees ('y' or 'Y'), the function calls the WriteToFileFromConsole function to get
 * user input and write it to the file.
 */
void getUserInputAndWriteToFile(const char* filename) {
    char doesUserWantToCreateFile;
    printf("It looks like the file you entered does not exist\nDo you want to create it manually from the console?(y/n): ");
    if (scanf_s("\n%c", &doesUserWantToCreateFile, sizeof(doesUserWantToCreateFile)) == 1) {
        if (doesUserWantToCreateFile == 'y' || doesUserWantToCreateFile == 'Y') {
            WriteToFileFromConsole(filename);
        }
        else {
            printf("#%c#\n", doesUserWantToCreateFile);
            printf("Please note that funcs will give errors because this file may not exist\n");
        }
    }
    else {
        printf("Error reading char.\n");

    }
}

/**
 * Copies the content of one file to another.
 *
 * @param filename_i The name of the source file to copy from.
 * @param filename_o The name of the destination file to copy to.
 * @note The function overwrites the destination file if it already exists.
 */
void copyFile(const char* filename_i, const char* filename_o) {
    FILE* sourceFile;
    FILE* destinationFile;
    errno_t err = fopen_s(&sourceFile, filename_i, "r");
    if (err != 0) {
        perror("Error opening source file");
        return;
    }
    err = fopen_s(&destinationFile, filename_o, "w");
    if (err != 0) {
        perror("Error opening destination file");
        return;
    }

    // Copy data from source file to destination file
    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);
}