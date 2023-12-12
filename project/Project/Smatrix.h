/* Task 1: Smatrix
* Group: compmat 1
* Name: Yaremchuk Igor
* Time: 11.12.2023
*
* header file with functions
*/


#pragma once

// Header file for working with sparse matrices and vectors

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include  <utility>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>

// A data type for representing vector and matrix elements
typedef double Dtype;

// Structure for a sparse vector
struct SVector {
    std::map<int, Dtype> elements;
};

// Structure for a sparse matrix
struct SMatyrix {
    int rows;
    int cols;

    // Adding a constructor to initialize fields
    SMatyrix(int numRows, int numCols) : rows(numRows), cols(numCols) {}

    std::map<std::pair<int, int>, Dtype> elements;
};

// Function declarations for working with sparse vectors and matrices
int input(SVector& x, const std::string& inputString, const std::string& filename = "");

int input(SMatyrix& x, const std::string& inputString, const std::string& filename = "");

void print(const SMatyrix& x, std::ostream& output = std::cout);

void print(const SVector& x, std::ostream& output = std::cout);

SVector solve(const SMatyrix& A, const SVector& y, std::ostream& output = std::cout);

Dtype det(const SMatyrix& x);

SMatyrix inverse(const SMatyrix& x);

