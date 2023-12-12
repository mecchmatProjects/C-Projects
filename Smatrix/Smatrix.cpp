/* Task 1: Smatrix
* Group: compmat 1
* Name: Yaremchuk Igor
* Time: 11.12.2023
* 
* main file with functions
*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Smatrix.h"

// Input of a sparse vector from a string or file
int input(SVector& x, const std::string& inputString, const std::string& filename) {
    int count = 0;

    if (!filename.empty()) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
            return 0;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            count += input(x, line, "");
        }
    }
    else {
        size_t pos = 0;
        while (pos < inputString.length()) {
            int index;
            Dtype value;

            int result = sscanf(inputString.c_str() + pos, "%d: %lf", &index, &value);
            if (result == 2) {
                x.elements[index] = value;
                count++;
            }

            pos = inputString.find(',', pos);
            if (pos != std::string::npos)
                pos++;
        }
    }

    return count;
}

// Sparse matrix input from line or file
int input(SMatyrix& x, const std::string& inputString, const std::string& filename) {
    int count = 0;

    if (!filename.empty()) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
            return 0;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            count += input(x, line, "");
        }
    }
    else {
        size_t pos = 0;
        int row = 1, col = 1;

        while (pos < inputString.length()) {
            Dtype value;
            int result = sscanf(inputString.c_str() + pos, "%lf", &value);
            if (result == 1) {
                x.elements[std::make_pair(row, col)] = value;
                count++;
                col++;
            }

            pos = inputString.find_first_of(" \n", pos + 1);
            if (pos != std::string::npos) {
                if (inputString[pos] == '\n') {
                    row++;
                    col = 1;
                }
                pos++;
            }
        }

        x.rows = row;
        x.cols = col - 1;
    }

    return count;
}

// Sparse vector derivation
void print(const SVector& x, std::ostream& output = std::cout) {
    for (const auto& pair : x.elements) {
        output << pair.first << ": " << pair.second << " ";
    }
    output << std::endl;
}

// Sparse matrix derivation
void print(const SMatyrix& x, std::ostream& output) {
    for (int i = 1; i <= x.rows; ++i) {
        for (int j = 1; j <= x.cols; ++j) {
            auto it = x.elements.find(std::make_pair(i, j));
            if (it != x.elements.end()) {
                output << it->second << " ";
            }
            else {
                output << "0 ";
            }
        }
        output << std::endl;
    }
}

// Recursive function for calculating the determinant of a matrix
Dtype determinant_recursive(const SMatyrix& x, int size) {
    if (size == 1) {
        return x.elements.begin()->second;
    }
    else if (size == 2) {
        auto it = x.elements.begin();
        Dtype a = it->second;
        it++;
        Dtype b = it->second;
        it++;
        Dtype c = it->second;
        it++;
        Dtype d = it->second;

        return a * d - b * c;
    }
    else {
        Dtype determinant = 0.0;
        int sign = 1;

        for (int j = 1; j <= size; ++j) {
            SMatyrix submatrix;
            submatrix.rows = size - 1;
            submatrix.cols = size - 1;

            for (const auto& entry : x.elements) {
                int i = entry.first.first;
                int k = entry.first.second;

                if (i > 1 && k != j) {
                    int newI = (i > 1) ? i - 1 : i;
                    int newK = (k > j) ? k - 1 : k;

                    submatrix.elements[std::make_pair(newI, newK)] = entry.second;
                }
            }

            determinant += sign * x.elements.at(std::make_pair(1, j)) * determinant_recursive(submatrix, size - 1);
            sign = -sign;
        }

        return determinant;
    }
}

// A function for calculating the determinant of a matrix
Dtype det(const SMatyrix& x) {
    if (x.rows != x.cols) {
        std::cerr << "Error: Determinant is defined only for square matrices." << std::endl;
        return 0.0;
    }

    return determinant_recursive(x, x.rows);
}

// A function for calculating the algebraic complement
Dtype cofactor(const SMatyrix& x, int row, int col) {
    SMatyrix submatrix;
    submatrix.rows = x.rows - 1;
    submatrix.cols = x.cols - 1;

    for (const auto& entry : x.elements) {
        int i = entry.first.first;
        int k = entry.first.second;

        if (i != row && k != col) {
            int newI = (i > row) ? i - 1 : i;
            int newK = (k > col) ? k - 1 : k;

            submatrix.elements[std::make_pair(newI, newK)] = entry.second;
        }
    }

    int sign = ((row + col) % 2 == 0) ? 1 : -1;
    return sign * det(submatrix);
}

// Function for calculating the inverse matrix
SMatyrix inverse(const SMatyrix& x) {
    if (x.rows != x.cols) {
        std::cerr << "Error: Inverse is defined only for square matrices." << std::endl;
        return SMatyrix();
    }

    SMatyrix inverseMatrix;
    inverseMatrix.rows = x.rows;
    inverseMatrix.cols = x.cols;

    Dtype determinant = det(x);
    if (std::abs(determinant) < 1e-10) {
        std::cerr << "Error: The matrix is singular, and its inverse does not exist." << std::endl;
        return SMatyrix();
    }

    for (int i = 1; i <= x.rows; ++i) {
        for (int j = 1; j <= x.cols; ++j) {
            Dtype c = cofactor(x, i, j);
            inverseMatrix.elements[std::make_pair(j, i)] = c / determinant;
        }
    }

    return inverseMatrix;
}

// The function for finding the solution of the system of equations Ax = y
SVector solve(const SMatyrix& A, const SVector& y) {
    SMatyrix AInverse = inverse(A);

    if (AInverse.rows == 0 || AInverse.cols == 0) {
        std::cerr << "Error: Unable to find the solution. The inverse matrix does not exist." << std::endl;
        return SVector();
    }
    //print(AInverse, std::cout);
    SVector x;
    x.elements.clear();

    for (int i = 1; i <= AInverse.rows; ++i) {
        Dtype sum = 0.0;

        for (int j = 1; j <= AInverse.cols; ++j) {
            auto itAInverse = AInverse.elements.find(std::make_pair(i, j));

            if (itAInverse != AInverse.elements.end()) {
                auto itY = y.elements.find(j);
                if (itY != y.elements.end()) {
                    sum += itAInverse->second * itY->second;
                }
            }
        }

        x.elements[i] = sum;
    }

    return x;
}

