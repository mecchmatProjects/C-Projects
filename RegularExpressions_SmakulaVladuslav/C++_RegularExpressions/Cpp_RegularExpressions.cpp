/* File Cpp_RegularExpressions.cpp
Realization of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile in C++
and help functions
Done by Smakula Vladuslav (group: computer methematics 1)
Date 03.12.2023
Implementations of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile and
additional functions: parseInlineLink, parseInlineDate, parseInlineNumber
*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

const size_t MAX_LINE_SIZE = 1000;
const size_t MAX_WORD_SIZE = 256;

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
static bool parseInlineLinkCpp(const char* word, char* text, char* link, size_t text_size, size_t link_size) {
    // Initialize the output parameters
    text[0] = '\0';
    link[0] = '\0';

    // Find the opening square bracket '['
    const char* start_bracket = strchr(word, '[');
    if (start_bracket == nullptr) {
        return false; // '[' not found, invalid format
    }

    // Find the closing square bracket ']'
    const char* end_bracket = strchr(start_bracket, ']');
    if (end_bracket == nullptr) {
        return false; // ']' not found, invalid format
    }

    // Calculate the length of the text inside the square brackets
    size_t text_length = end_bracket - start_bracket - 1;

    // Copy the text inside the square brackets to the 'text' parameter
    strncpy(text, start_bracket + 1, text_length);
    text[text_length] = '\0';

    // Find the opening parenthesis '(' after the closing square bracket
    const char* start_parenthesis = strchr(end_bracket, '(');
    if (start_parenthesis == nullptr) {
        return false; // '(' not found, invalid format
    }

    // Find the closing parenthesis ')' after the opening parenthesis
    const char* end_parenthesis = strchr(start_parenthesis, ')');
    if (end_parenthesis == nullptr) {
        return false; // ')' not found, invalid format
    }

    // Calculate the length of the link inside the parentheses
    size_t link_length = end_parenthesis - start_parenthesis - 1;

    // Copy the link inside the parentheses to the 'link' parameter
    strncpy(link, start_parenthesis + 1, link_length);
    link[link_length] = '\0';

    return true;
}

/**
 * Parses a string to check if it contains a date in various formats and converts it to a specified format.
 *
 * @param word The input string to be parsed for a date.
 * @return A formatted date string in the format "%Y %B %d" if the input is a valid date, or nullptr otherwise.
 * 
 * @note This function supports date formats like "DD/MM/YYYY", "DD.MM.YYYY", "DD/MM/YY", "DD.MM.YY",
 * "YYYY/MM/DD", "YYYY.MM.DD".
 */
static char* parseInlineDateCpp(const char* word) {
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

        // Handling dates like 23.23.23
        std::mktime(&timeinfo);

        char* buffer = new char[MAX_WORD_SIZE];
        if (std::strftime(buffer, MAX_WORD_SIZE, "%Y %B %d", &timeinfo) == 0) {
            // Handle formatting error
            std::cerr << "Error formatting date." << std::endl;
            delete[] buffer;
            return nullptr;
        }

        return buffer;
    }

    return nullptr;
}

/**
 * Parses a string to check if it represents a valid number, converts it to a fixed-point format with 4 digits after the decimal point,
 * and returns the result enclosed in parentheses. If the input is not a valid number, returns NULL.
 *
 * @param word The input string to be parsed.
 * @return A dynamically allocated string containing the formatted number or NULL if the input is not a valid number.
 */
static char* parseInlineNumberCpp(const char* word) {
    // Replace commas with dots
    std::string modifiedWord = word;
    for (size_t i = 0; i < modifiedWord.length(); ++i) {
        if (modifiedWord[i] == ',') {
            modifiedWord[i] = '.';
        }
    }

    char* endptr;
    // Converting doesn't work without #include <cstdlib>
    double value = strtod(modifiedWord.c_str(), &endptr);

    // Check if the entire string is a valid number
    if (endptr != NULL && *endptr == '\0') {
        // Format the number to have 4 digits after the decimal point
        char formattedNumber[MAX_WORD_SIZE];
        snprintf(formattedNumber, sizeof(formattedNumber), "(%.4f)", value);
        char* result = new char[strlen(formattedNumber) + 1];
        std::strcpy(result, formattedNumber);
        return result;
    }
    else {
        // If the input is not a number, return NULL
        return nullptr;
    }
}

/**
 * Processes a file, extracts and replaces valid dates with a specified format,
   and saves the matches to another file and writes them on console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 * @param outputFilename The name of the output file where processed text with formatted dates will be saved.
 */
int getDatesFromFileCpp(const char* inputFilename, const char* outputFilename) {
    std::ifstream inputFile(inputFilename);
    std::ofstream tempFile("temp.txt");
    std::ofstream outputFile(outputFilename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return -1;
    }

    if (!tempFile.is_open()) {
        std::cerr << "Error opening temp file" << std::endl;
        inputFile.close();
        return -1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        inputFile.close();
        tempFile.close();
        return -1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            // Get parsed date
            char* date = parseInlineDateCpp(word.c_str());
            if (date != nullptr) {
                std::cout << date << std::endl;
                tempFile << date << ' ';
                outputFile << date << std::endl;
                delete[] date;
            }
            else {
                tempFile << word << ' ';
            }
        }

        tempFile << '\n';
    }

    // Close the files
    inputFile.close();
    outputFile.close();
    tempFile.close();

    // Rename files
    std::remove(inputFilename);
    std::rename("temp.txt", inputFilename);
    return 0;
}

/**
 * Reads a file, replaces all valid date strings with the current date, and saves the result to the same file
 * and writes replaces matches to console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 */
int replaceAllDatesToCurrentCpp(const char* inputFilename) {
    std::ifstream inputFile(inputFilename);
    std::ofstream tempFile("temp.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return -1;
    }

    if (!tempFile.is_open()) {
        std::cerr << "Error opening temp file" << std::endl;
        inputFile.close();
        return -1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            // Get parsed date
            char* date = parseInlineDateCpp(word.c_str());
            if (date != nullptr) {
                // If the current word is a date, get the current time to replace it
                std::cout << date;
                delete[] date;

                time_t currentTime;
                time(&currentTime);
                struct tm timeInfo;
                localtime_s(&timeInfo, &currentTime);

                // Format the date string
                char dateString[MAX_WORD_SIZE];
                if (strftime(dateString, sizeof(dateString), "%Y %B %d", &timeInfo) == 0) {
                    // Handle error
                    std::cerr << "Error formatting date." << std::endl;
                    return 1;
                }

                std::cout << " -> " << dateString << std::endl;
                tempFile << dateString << ' ';
            }
            else {
                tempFile << word << ' ';
            }
        }

        tempFile << '\n';
    }

    // Close the files
    inputFile.close();
    tempFile.close();

    // Rename files
    std::remove(inputFilename);
    std::rename("temp.txt", inputFilename);
    return 0;
}

/**
 * Reads a file, extracts inline hyperlinks, and writes the extracted data to an output file and console.
 *
 * @param inputFilename The name of the input file to read.
 * @param outputFilename The name of the output file to write the extracted data.
 */
int getHyperlinksFromFileCpp(const char* inputFilename, const char* outputFilename) {
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return -1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        char* saveptr;
        char* word = strtok_s(const_cast<char*>(line.c_str()), " \t\n", &saveptr);

        while (word != nullptr) {
            char text[MAX_WORD_SIZE];
            char link[MAX_WORD_SIZE];

            // Check if parsing was successful
            if (parseInlineLinkCpp(word, text, link, sizeof(text), sizeof(link))) {
                std::cout << text << ' ' << link << std::endl;
                outputFile << text << ' ' << link << std::endl;
            }

            // Get the next word
            word = strtok_s(nullptr, " \t\n", &saveptr);
        }
    }
    return 0;
}

/**
 * Reads a file, tokenizes each line into words, and replaces valid numbers with a formatted version having 4 digits after the decimal point.
 * Writes the modified content to a temporary file and replaces the original file with the temporary one.
 *
 * @param inputFilename The name of the file to process.
 * @note The function prints each unified number to the console during processing.
 */
int unifyAllNumbersInFileCpp(const char* inputFilename) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        perror("Error opening file");
        return -1;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        perror("Error opening temp file");
        inputFile.close();
        return -1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            // Get current number
            char* number = parseInlineNumberCpp(word.c_str());
            if (number != nullptr) {
                std::cout << number << std::endl;
                tempFile << number << ' ';
                delete[] number;
            }
            else {
                tempFile << word << ' ';
            }
        }
        tempFile << '\n';
    }

    // Close the files
    inputFile.close();
    tempFile.close();

    // Replace the original file with the temporary one
    std::remove(inputFilename);
    std::rename("temp.txt", inputFilename);
    return 0;
}