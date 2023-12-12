/* Task 1: Smatrix
* Group: compmat 1
* Name: Yaremchuk Igor
* Time: 11.12.2023
*
* header file with functions
*/
#ifndef SMATRIX_H
#define SMATRIX_H

// Header file for working with sparse matrices and vectors

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <utility>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>

// A data type for representing vector and matrix elements
typedef double Dtype;

// Structure for a sparse vector
struct SVector {
    std::map<int, Dtype> elements;  // The key is an index, the value is an element
};

// Structure for a sparse matrix
struct SMatyrix {
    int rows;  // Number of lines
    int cols;  // Number of columns
    std::map<std::pair<int, int>, Dtype> elements;  // The key is a pair (row, column), the value is an element

    SMatyrix() : rows(0), cols(0) {
    }
    SMatyrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
    }
};

// Function declarations for working with sparse vectors and matrices
int input(SVector& x, const std::string& inputString, const std::string& filename);

int input(SMatyrix& x, const std::string& inputString, const std::string& filename);

void print(const SMatyrix& x, std::ostream& output = std::cout);

void print(const SVector& x, std::ostream& output);

SVector solve(const SMatyrix& A, const SVector& y);

Dtype det(const SMatyrix& x);

SMatyrix inverse(const SMatyrix& x);

#endif // SMATRIX_H
