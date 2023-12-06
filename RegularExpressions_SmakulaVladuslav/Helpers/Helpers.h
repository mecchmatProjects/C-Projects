/* File Helpers.h
Realization of headers for help funcs in C
Done by Smakula Vladuslav (group: computer methematics 1)
Date 04.12.2023
*/
#ifndef HELPERS_F
#define HELPERS_F
#ifdef __cplusplus
extern "C" {
#endif

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
    const char* testName);

/**
 * @brief Compares two text files to check if their content is identical.
 *
 * @param filename1 The path to the first file.
 * @param filename2 The path to the second file.
 * @return Returns 1 if the files are similar (content is identical), 0 otherwise.
 *         Returns 0 in case of an error (e.g., unable to open files).
 */
int compareFiles(const char* filename1, const char* filename2);

/**
 * Checks if a file exists at the specified path.
 *
 * @param filename The path to the file.
 * @return Returns 1 if the file exists, 0 otherwise.
 */
int fileExists(const char* filename);

/**
 * Checks if the specified file exists and prompts the user to create it manually from the console.
 *
 * @param filename The path to the file.
 *
 * @note If the file does not exist, the function asks the user if they want to create it manually.
 * If the user agrees ('y' or 'Y'), the function calls the WriteToFileFromConsole function to get
 * user input and write it to the file.
 */
void getUserInputAndWriteToFile(const char* filename);

/**
 * Copies the content of one file to another.
 *
 * @param filename_i The name of the source file to copy from.
 * @param filename_o The name of the destination file to copy to.
 * @note The function overwrites the destination file if it already exists.
 */
void copyFile(const char* filename_i, const char* filename_o);
#ifdef __cplusplus
}
#endif

#endif // HELPERS_F
