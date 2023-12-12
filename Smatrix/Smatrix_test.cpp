/* Task 1: Smatrix
* Group: compmat 1
* Name: Yaremchuk Igor
* Time: 11.12.2023
*
* file for testing the program
*/

#include "Smatrix.h"

int main() {
    // Creating a sparse vector
    SVector vector;
    input(vector, "1: 2.5, 3: -1.5", "");
    std::cout << "Sparse Vector:\n";
    print(vector, std::cout);

    // Creating a sparse matrix
    SMatyrix matrix(3, 3);
    input(matrix, "1 0 0, 0 2 0, 0 0 3", "");
    std::cout << "\nSparse Matrix:\n";
    print(matrix);

    // Calculation and derivation of the matrix determinant
    Dtype determinant = det(matrix);
    std::cout << "\nDeterminant of the Matrix: " << determinant << "\n";

    // Calculation and derivation of the inverse matrix
    SMatyrix inverseMatrix = inverse(matrix);
    std::cout << "\nInverse Matrix:\n";
    print(inverseMatrix);

    // Solving a system of linear equations
    SVector solution = solve(matrix, vector);
    std::cout << "\nSolution to Ax = b:\n";
    print(solution, std::cout);

    return 0;
}
