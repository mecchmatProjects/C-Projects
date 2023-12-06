/* File CppRe_RegularExpressions.cpp
Realization of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile in C++ using regex
and help functions
Done by Smakula Vladuslav (group: computer methematics 1)
Date 04.12.2023
Implementations of getHyperlinksFromFile, getDatesFromFile, replaceAllDatesToCurrent, unifyAllNumbersInFile and
additional functions: parseInlineLink, parseInlineDate, parseInlineNumber, formatingDate
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

/**
 * Parses an hyperlink from the given word using regular expressions.
 *
 * @param word The word to parse for an hyperlink.
 * @param text Output parameter to store the extracted text inside the square brackets.
 * @param link Output parameter to store the extracted link inside the parentheses.
 * @return True if parsing is successful, false otherwise.
 */
static bool parseInlineLinkRe(const std::string& word, std::string& text, std::string& link) {
    // Defining the regex pattern
    std::regex linkRegex(R"(\[(.+)\]\(([^)]+)\))");

    // Match the regex pattern
    std::smatch match;
    if (std::regex_match(word, match, linkRegex)) {
        if (match.size() == 3) {
            // Extract the matched text and link
            text = match[1].str();
            link = match[2].str();
            return true;
        }
    }

    return false;
}

/**
 * Formats a date using the provided day, month, and year components.
 *
 * @param day The day component of the date.
 * @param month The month component of the date.
 * @param year The year component of the date.
 * @return A formatted date string in the format "%Y %B %d", or an empty string in case of formatting error.
 */
static std::string formatingDate(int day, int month, int year) {
    //if year in 12.12.23 format
    if (year < 100) {
        year += 2000;
    }

    struct tm timeinfo = { 0 };
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;

    // Handling dates like 23.23.23
    std::mktime(&timeinfo);

    char buffer[100];
    if (std::strftime(buffer, sizeof(buffer), "%Y %B %d", &timeinfo) == 0) {
        // Handle formatting error
        std::cerr << "Error formatting date." << std::endl;
        return "";
    }

    return buffer;
}

/**
 * Parses an input string to check if it represents a date in various formats,
 * and returns the formatted date in the format "%Y %B %d".
 *
 * @param word The input string to be parsed.
 * @return A formatted date string or an empty string if the input does not match any supported date format.
 *
 * @note This function supports date formats like "DD/MM/YYYY", "DD.MM.YYYY", "DD/MM/YY", "DD.MM.YY",
 * "YYYY/MM/DD", "YYYY.MM.DD".
 */
static std::string parseInlineDateRe(const std::string& word) {
    // Defining the regex pattern for date formats
    std::regex dateRegexRegular(R"((\d{1,2})[./](\d{1,2})[./](\d{4}|\d{2}))");
    std::regex dateRegexRot(R"((\d{4})[./](\d{1,2})[./](\d{1,2}))");
    std::smatch match;
    //Checking regex then formating response
    if (std::regex_match(word, match, dateRegexRegular)) {
        int day = std::stoi(match[1].str());
        int month = std::stoi(match[2].str());
        int year = std::stoi(match[3].str());
        return formatingDate(day, month, year);
    }
    if (std::regex_match(word, match, dateRegexRot)) {
        int day = std::stoi(match[3].str());
        int month = std::stoi(match[2].str());
        int year = std::stoi(match[1].str());
        return formatingDate(day, month, year);
    }
    return "";
}

/**
 * Parses an input string to check if it represents a valid number,
 * converts it to a fixed-point format with 4 digits after the decimal point,
 * and returns the result enclosed in parentheses.
 *
 * @param word The input string to be parsed.
 * @return A formatted string containing the number or an empty string if the input is not a valid number.
 *
 * @note This function validates the number format using regex
 */
static std::string parseInlineNumberRe(const std::string& word) {
    // Define the regex pattern for a valid number
    std::regex numberRegex(R"([-+]?\d*[\.,]?\d+)");

    if (std::regex_match(word, numberRegex)) {
        // Convert the string to a double
        double value = std::stod(word);

        // Format the number to have 4 digits after the decimal point
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(4) << value;
        return "(" + oss.str() + ")";
    }
    else {
        // If the input is not a number, return an empty string
        return "";
    }
}

/**
 * Reads a file, extracts inline hyperlinks, and writes the extracted data to an output file and console.
 *
 * @param inputFilename The name of the input file to read.
 * @param outputFilename The name of the output file to write the extracted data.
 */
int getHyperlinksFromFileRe(const char* inputFilename, const char* outputFilename) {
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
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            std::string text;
            std::string link;
            // Check if parsing was successful
            if (parseInlineLinkRe(word, text, link)) {
                std::cout << text << ' ' << link << std::endl;
                outputFile << text << ' ' << link << std::endl;
            }
        }
    }

    return 0;
}

/**
 * Processes a file, extracts and replaces valid dates with a specified format,
   and saves the matches to another file and writes them on console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 * @param outputFilename The name of the output file where processed text with formatted dates will be saved.
 */
int getDatesFromFileRe(const char* inputFilename, const char* outputFilename) {
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
            std::string date = parseInlineDateRe(word);
            if (!date.empty()) {
                std::cout << date << std::endl;
                tempFile << date << ' ';
                outputFile << date << std::endl;
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
   and writes replaces matches to console.
 *
 * @param inputFilename The name of the input file containing text with potential date strings.
 */
int replaceAllDatesToCurrentRe(const char* inputFilename) {
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
            std::string date = parseInlineDateRe(word);
            if (!date.empty()) {
                // If the current word is a date, get the current time to replace it
                std::cout << date;

                time_t currentTime;
                time(&currentTime);
                struct tm timeInfo;
                localtime_s(&timeInfo, &currentTime);

                // Format the date string
                char dateString[100];
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
 * Reads a file, tokenizes each line into words, and replaces valid numbers with a formatted version having 4 digits after the decimal point.
 * Writes the modified content to a temporary file and replaces the original file with the temporary one.
 *
 * @param inputFilename The name of the file to process.
 * @note The function prints each unified number to the console during processing.
 */
int unifyAllNumbersInFileRe(const char* inputFilename) {
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
            std::string number = parseInlineNumberRe(word);
            if (!number.empty()) {
                std::cout << number << std::endl;
                tempFile << number << ' ';
            }
            else {
                tempFile << word << ' ';
            }
        }
        tempFile << '\n';
    }
    inputFile.close();
    tempFile.close();
    std::remove(inputFilename);
    std::rename("temp.txt", inputFilename);
    return 0;
}