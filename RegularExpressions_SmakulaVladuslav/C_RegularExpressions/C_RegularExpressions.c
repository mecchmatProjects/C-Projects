/* File C_RegularExpressions.c
Realization of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile in C
and help functions
Done by Smakula Vladuslav (group: computer methematics 1)
Date 03.12.2023
Implementations of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile and
additional functions: parseInlineLink, parseInlineDate, parseInlineNumber
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#define MAX_LINE_SIZE 1000
#define MAX_WORD_SIZE 256


/**
 * Parses an inline link in the given word and extracts the text and link of hypertext.
 *
 * @param word The input word containing the inline link.
 * @param text Output parameter to store the extracted text from the link.
 * @param link Output parameter to store the extracted link.
 * @param text_size Size of the 'text' buffer.
 * @param link_size Size of the 'link' buffer.
 * @return True if the parsing is successful, false otherwise (invalid format).
 */
static bool parseInlineLink(const char* word, char* text, char* link, size_t text_size, size_t link_size) {
    // Initialize the output parameters
    text[0] = '\0';
    link[0] = '\0';

    // Find the opening square bracket '['
    const char* start_bracket = strchr(word, '[');
    if (start_bracket == NULL) {
        return false; // '[' not found, invalid format
    }

    // Find the closing square bracket ']'
    const char* end_bracket = strchr(start_bracket, ']');
    if (end_bracket == NULL) {
        return false; // ']' not found, invalid format
    }

    // Calculate the length of the text inside the square brackets
    size_t text_length = end_bracket - start_bracket - 1;

    // Copy the text inside the square brackets to the 'text' parameter
    strncpy_s(text, text_size, start_bracket + 1, text_length);
    text[text_length] = '\0';

    // Find the opening parenthesis '(' after the closing square bracket
    const char* start_parenthesis = strchr(end_bracket, '(');
    if (start_parenthesis == NULL) {
        return false; // '(' not found, invalid format
    }

    // Find the closing parenthesis ')' after the opening parenthesis
    const char* end_parenthesis = strchr(start_parenthesis, ')');
    if (end_parenthesis == NULL) {
        return false; // ')' not found, invalid format
    }

    // Calculate the length of the link inside the parentheses
    size_t link_length = end_parenthesis - start_parenthesis - 1;

    // Copy the link inside the parentheses to the 'link' parameter
    strncpy_s(link, link_size, start_parenthesis + 1, link_length);
    link[link_length] = '\0';

    return true;
}

/**
 * Parses a string to check if it contains a date in various formats and converts it to a specified format.
 *
 * @param word The input string to be parsed for a date.
 * @return A formatted date string in the format "%Y %B %d" if the input is a valid date, or NULL otherwise.
 * 
 * @note This function supports date formats like "DD/MM/YYYY", "DD.MM.YYYY", "DD/MM/YY", "DD.MM.YY",
 * "YYYY/MM/DD", "YYYY.MM.DD".
 */
static char* parseInlineDate(const char* word) {
    // Check if the word contains a date in the specified formats
    int day, month, year;
    if (
        sscanf_s(word, "%02d.%02d.%04d", &day, &month, &year) == 3 ||
        sscanf_s(word, "%02d/%02d/%04d", &day, &month, &year) == 3 ||
        sscanf_s(word, "%04d.%02d.%02d", &year, &month, &day) == 3 ||
        sscanf_s(word, "%04d/%02d/%02d", &year, &month, &day) == 3 ||
        sscanf_s(word, "%02d.%02d.%02d", &day, &month, &year) == 3 ||
        sscanf_s(word, "%02d/%02d/%02d", &day, &month, &year) == 3
        ) {
        struct tm timeinfo = { 0 };
        //if year in 12.12.23 format
        if (year < 100) {
            year += 2000;
        }
        timeinfo.tm_year = year - 1900; // Year since 1900
        timeinfo.tm_mon = month - 1;    // Month is 0-based in tm struct
        timeinfo.tm_mday = day;
        //Handling dates like 23.23.23
        mktime(&timeinfo);
        char buffer[MAX_WORD_SIZE];
        if (strftime(buffer, sizeof(buffer), "%Y %B %d", &timeinfo) == 0) {
            // Handle formatting error
            printf("Error formatting date.\n");
            return NULL;
        }
        return buffer;
    }

    return NULL;
}

/**
 * Parses a string to check if it represents a valid number, converts it to a fixed-point format with 4 digits after the decimal point,
 * and returns the result enclosed in parentheses. If the input is not a valid number, returns NULL.
 *
 * @param word The input string to be parsed.
 * @return A dynamically allocated string containing the formatted number or NULL if the input is not a valid number.
 */
static char* parseInlineNumber(const char* word) {
    // Replace commas with dots
    char* modifiedWord = _strdup(word);  // Duplicate the input string
    for (size_t i = 0; i < strlen(modifiedWord); ++i) {
        if (modifiedWord[i] == ',') {
            modifiedWord[i] = '.';
        }
    }
    char* endptr;
    //Converting dont work without #include <stdlib.h>
    double value = strtod(modifiedWord, &endptr);

    // Check if the entire string is a valid number
    if (endptr != NULL && *endptr == '\0') {
        // Format the number to have 4 digits after the decimal point
        char formattedNumber[MAX_WORD_SIZE];
        snprintf(formattedNumber, sizeof(formattedNumber), "(%.4f)", value);
        char* result = (char*)malloc(strlen(formattedNumber) + 1);
        if (result != NULL) {
            strcpy_s(result, strlen(formattedNumber) + 1, formattedNumber);
        }
        free(modifiedWord);
        return result;
    }
    else {
        // If the input is not a number, return NULL
        free(modifiedWord);
        return NULL;
    }
}

/**
 * Reads a file, extracts inline hyperlinks, and writes the extracted data to an output file and console.
 *
 * @param inputFilename The name of the input file to read.
 * @param outputFilename The name of the output file to write the extracted data.
 */
int getHyperlinksFromFile(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile;
    FILE* outputFile;
    char line[MAX_LINE_SIZE];
    char* word, * saveptr;

    errno_t err = fopen_s(&inputFile, inputFilename, "r");
    if (err != 0) {
        perror("Error opening file");
        return -1;
    }
    err = fopen_s(&outputFile, outputFilename, "w");
    if (err != 0) {
        perror("Error opening output file");
        fclose(inputFile);
        return -1;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Tokenize the line into words
        word = strtok_s(line, " \t\n", &saveptr);
        while (word != NULL) {
            char text[MAX_WORD_SIZE];
            char link[MAX_WORD_SIZE];
            //Check if parsing was succesful
            if (parseInlineLink(word, text, link, sizeof(text), sizeof(link))) {
                printf("%s %s\n", text, link);
                fprintf(outputFile, "%s %s\n", text, link);
            }

            // Get the next word
            word = strtok_s(NULL, " \t\n", &saveptr);
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

/**
 * Processes a file, extracts and replaces valid dates with a specified format, 
   and saves the matches to another file and writes them on console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 * @param outputFilename The name of the output file where processed text with formatted dates will be saved.
 */
int getDatesFromFile(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile;
    FILE* tempFile;
    FILE* outputFile;
    char line[MAX_LINE_SIZE];
    char* word, * saveptr;

    errno_t err = fopen_s(&inputFile, inputFilename, "r");
    if (err != 0) {
        perror("Error opening file");
        return -1;
    }
    err = fopen_s(&tempFile, "temp.txt", "w");
    if (err != 0) {
        perror("Error opening temp file");
        fclose(inputFile);
        return -1;
    }
    err = fopen_s(&outputFile, outputFilename, "w");
    if (err != 0) {
        perror("Error opening output file");
        fclose(inputFile);
        return -1;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Tokenize the line into words
        word = strtok_s(line, " \t\n", &saveptr);
        while (word != NULL) {
            //Get parsed date
            char* date = parseInlineDate(word);
            if (date != NULL) {
                printf("%s\n", date);
                fprintf(tempFile, "%s ", date);
                fprintf(outputFile, "%s\n", date);
            }
            else {
                fprintf(tempFile, "%s ", word);
            }
            

            // Get the next word
            word = strtok_s(NULL, " \t\n", &saveptr);
        }
        fprintf(tempFile, "\n");
    }

    // Close the files
    fclose(outputFile);
    fclose(inputFile);
    fclose(tempFile);
    remove(inputFilename);
    rename("temp.txt", inputFilename);
    return 0;
}

/**
 * Reads a file, replaces all valid date strings with the current date, and saves the result to the same file 
   and writes replaces matches to console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 */
int replaceAllDatesToCurrent(const char* inputFilename) {
    FILE* inputFile;
    FILE* tempFile;
    char line[MAX_LINE_SIZE];
    char* word, * saveptr;

    errno_t err = fopen_s(&inputFile, inputFilename, "r");
    if (err != 0) {
        perror("Error opening file");
        return -1;
    }
    err = fopen_s(&tempFile, "temp.txt", "w");
    if (err != 0) {
        perror("Error opening temp file");
        fclose(inputFile);
        return -1;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Tokenize the line into words
        word = strtok_s(line, " \t\n", &saveptr);
        while (word != NULL) {
            //Get parsed date
            char* date = parseInlineDate(word);
            if (date != NULL) {
                //If current word is date then we get current time to repace it
                printf("%s", date);
                time_t currentTime;
                time(&currentTime);
                struct tm timeInfo;
                if (localtime_s(&timeInfo, &currentTime) != 0) {
                    // Handle error
                    printf("Error getting local time.\n");
                    return 1;
                }

                // Format the date string
                char dateString[MAX_WORD_SIZE];  // Adjust as needed
                if (strftime(dateString, sizeof(dateString), "%Y %B %d", &timeInfo) == 0) {
                    // Handle error
                    printf("Error formatting date.\n");
                    return 1;
                }
                printf(" -> %s\n", dateString);
                fprintf(tempFile, "%s ", dateString);
            }
            else {
                fprintf(tempFile, "%s ", word);
            }


            // Get the next word
            word = strtok_s(NULL, " \t\n", &saveptr);
        }
        fprintf(tempFile, "\n");
    }

    // Close the files
    fclose(inputFile);
    fclose(tempFile);
    remove(inputFilename);
    rename("temp.txt", inputFilename);
    return 0;
}

/**
 * Reads a file, tokenizes each line into words, and replaces valid numbers with a formatted version having 4 digits after the decimal point.
 * Writes the modified content to a temporary file and replaces the original file with the temporary one.
 *
 * @param inputFilename The name of the file to process.
 * @note The function prints each unified number to the console during processing.
 */
int unifyAllNumbersInFile(const char* inputFilename) {
    FILE* inputFile;
    FILE* tempFile;
    char line[MAX_LINE_SIZE];
    char* word, * saveptr;

    errno_t err = fopen_s(&inputFile, inputFilename, "r");
    if (err != 0) {
        perror("Error opening file");
        return -1;
    }
    err = fopen_s(&tempFile, "temp.txt", "w");
    if (err != 0) {
        perror("Error opening temp file");
        fclose(inputFile);
        return -1;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Tokenize the line into words
        word = strtok_s(line, " \t\n", &saveptr);
        while (word != NULL) {
            //Get current number
            char* number = parseInlineNumber(word);
            if (number != NULL) {
                printf("%s\n", number);
                fprintf(tempFile, "%s ", number);
            }
            else {
                fprintf(tempFile, "%s ", word);
            }
            // Get the next word
            word = strtok_s(NULL, " \t\n", &saveptr);
        }
        fprintf(tempFile, "\n");
    }

    // Close the files
    fclose(inputFile);
    fclose(tempFile);
    remove(inputFilename);
    rename("temp.txt", inputFilename);
    return 0;
}