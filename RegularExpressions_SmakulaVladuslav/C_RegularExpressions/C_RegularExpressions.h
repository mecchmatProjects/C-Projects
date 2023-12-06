/* File C_RegularExpressions.h
Realization of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile in C
Done by Smakula Vladuslav (group: computer methematics 1)
Date 03.12.2023
Headers of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile
*/
#ifndef C_REGULAREXPRESSIONS_H
#define C_REGULAREXPRESSIONS_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Reads a file, extracts inline hyperlinks, and writes the extracted data to an output file and console.
 *
 * @param inputFilename The name of the input file to read.
 * @param outputFilename The name of the output file to write the extracted data.
 */
int getHyperlinksFromFile(const char* inputFilename, const char* outputFilename);

/**
 * Processes a file, extracts and replaces valid dates with a specified format,
   and saves the matches to another file and writes them on console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 * @param outputFilename The name of the output file where processed text with formatted dates will be saved.
 */
int getDatesFromFile(const char* inputFilename, const char* outputFilename);

/**
 * Reads a file, replaces all valid date strings with the current date, and saves the result to the same file
   and writes replaces matches to console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 */
int replaceAllDatesToCurrent(const char* inputFilename);

/**
 * Reads a file, tokenizes each line into words, and replaces valid numbers with a formatted version having 4 digits after the decimal point.
 * Writes the modified content to a temporary file and replaces the original file with the temporary one.
 *
 * @param inputFilename The name of the file to process.
 * @note The function prints each unified number to the console during processing.
 */
int unifyAllNumbersInFile(const char* inputFilename);
#ifdef __cplusplus
}
#endif

#endif // C_REGULAREXPRESSIONS_H