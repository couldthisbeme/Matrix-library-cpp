/*This is an example file meant to demonstrate a few basic applications of the Matrix.hpp header*/

#include <iostream>
// Including the Matrix.hpp header
#include "Matrix.hpp"

int main()
{
    // Constructing objects
    linalg::Matrix<double> A{3, 3}, B{3}, X;

    // Setting the values of A and B
    A(0, 0) = 4;    A(0, 1) = 0;    A(0, 2) = 1;
    A(1, 0) = 2;    A(1, 1) = 1;    A(1, 2) = 0;
    A(2, 0) = 2;    A(2, 1) = 2;    A(2, 2) = 3;

    B(0) = 3;
    B(1) = 4;
    B(2) = 6;

    // Displaying A and B
    std::cout << "A:\n";
    A.display();
    std::cout << "\nB:\n";
    B.display();

    // Calculating the solution
    X = A.Cramer_rule(B);

    // Displaying results
    std::cout << "\nThe calculated solution:\n";
    X.display();

    std::cout << "\nDifference between A * X and B:\n";
    (A * X - B).display();

    return 0;

}
