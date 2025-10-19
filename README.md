# Matrix-library-cpp
A c++ library for basic linear algebra operations, along with various helpful methods. It containss a header that defines the class `Matrix`, which allows operations using mathematical matrices and vectors. It is inspired by matlab's syntax, and by the functionality of python's numpy.

## How to use
Add the contents of **include/** to your compiler's include path. In case the contents of **include/** are moved, the `.hpp` file and `.tpp` files must be placed in the same directory. A program that uses this library will look something like this:
```c++
#include "Matrix.hpp"
#include <iostream>

int main()
{
    linalg::Matrix<double> X{3};

    X.display(); // Will show a column vector full of zeros

    linalg::Matrix<double> A{3, 3};

    A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
    A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
    A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

    std::cout << A(2,1) << '\n'; 

    return 0;
}
```

## Quick start features
- Namespace: `linalg`
- Constructors: Two numbers for 2D matrix, one number for 1D matrix.
- Read .csv files.
- Accessing operator: `()`
- Assignment operator: `=`
- Logical operators `== !=`
- Basic mathematics operators: `+ += - -= * *= / /=`
- Utility functions: `display() reshape(size_t new_rows, size_t new_cols) pivot(size_t row1, size_t row2) transpose() LU_decomp() is_self_adjoint()`
- Functions: `eye<type>(size_t sidelength) norm() magnitude()`
- Solve systems: `Cramer_rule(Matrix other)`

## Explanations of operators and methods
- **Constructors**: The type of variable that is held in the object must be specified. The default constructor creates an empty object. Passing one number `x` when constructing an object creates a 1D object with `x` rows. Passing two numbers `x` and `y` when constructing an object creates a 2D object with `x` rows and `y` columns.
```c++
linalg::Matrix<float> E; // Empty object
linalg::Matrix<double> X{4}; // Object with 4 rows and 1 column. Holds values of type double
linalg::Matrix<int> A{2,6}; // Object with two rows and 6 columns. Holds values of type int
```
A csv file can be read once a Matrix object has been initialized. The type of variables held by the matrix has to be the same as the values in the csv file. A delimiter `char` must also be passed. If uncertain of what to put, `','` should work most of the time.
```c++
linalg::Matrix<double> A;
A.read_csv(R"(path\to\your\file.csv)", ',');
```
- **Accessing elements**: The elements of a 2D object can be accessed using `()` with two positional indices. The elements of a 1D object can be accessed using `()`, either with one or two positional indices. Attempting to access the elements of an empty object will result in a `std::logic_error` being thrown.
```c++
linalg::Matrix<double> A{3, 4}, B{7}, C; // Notice that B has 7 rows and 1 column

std::cout << A(2,1) << '\n'; // Displays the element of A at the 3rd row and 2nd column

std::cout << B(3) << '\n'; // Displays the 4th element of B
std::cout << B(3,1) << '\n'; // Displays the 4th element of B
std::cout << B(1,3) << '\n'; // Throws an error, B doesn't have 4 rows!

std::cout << C(0) << '\n'; // Throws an error
```

- **Assigning values**: By accessing an element as described above, its value can be changed. A `Matrix` object can also have another `Matrix` object assigned to it. This will change its dimensions and values to match the other object.
```c++
linalg::Matrix<double> A{3, 3}, B{2};

B(0) = 3.5; B(1) = 9.2;

A = B; // A now has the same values and dimensions as B

A.display(); // Will show 3.5 \n 9.2
```

- **Logical operators**: By using `==` and `!=`, the two objects are compared.
```c++
linalg::Matrix<int> A{3, 3}, B{3, 3}, C{3, 4};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

B=A;

for (size_t i{0}; i < 3; ++i)
{
    for (size_t j{0}; j <3; ++j)
    {
        C(i, j) = A(i, j);
    }
}

B==A; // True, the two matrices have the same dimensions and elements
C!=A; // True, notice that C has one more column than A
```

- **Addition, subtraction, multiplication, and division**: A `Matrix` object can have another `Matrix` object added or subtracted using the operators `+ += - -=`, as long as they have the same rows and columns. These operators also work for variables of the same type as those that are held in the `Matrix` object. The operators `*` and `*=` performs matrix multiplication of two `Matrix` objects, as long as their dimensions are compatible (the columns of the object on the left match the rows of the object on the right). The same operators perform regular multiplication when used with a type that is the same as the type held by the `Matrix` object. Division only works when using a variable of the type held within the `Matrix` object, not with other `Matrix` objects. The `Matrix` object must be on the left side of `/` and `/=`.
```c++
linalg::Matrix<int> A{3, 3}, B{3, 3}, C{3}, D{4, 3};
int number{4};

linalg::Matrix<int> test_matrix;

// Set values of matrices here

test_matrix = A + B; // Works
test_matrix = A + D; // Error
test_matrix = A + number; //Works
test_matrix = number + A; // Works
A += B; // Works
A += number; // Works
test_matrix = A - B; // Works
test_matrix = A - D; // Error
test_matrix = A - number; // Works
test_matrix = number - A; // Works
A -= B; // Works
A -= number; // Works
test_matrix = A * B; // Works
test_matrix = A * C; // Works, test_matrix now has 3 rows and 1 column
test_matrix = D * A; // Works, test_matrix now has 4 rows and 3 columns
test_matrix = A * D; // Error
A *= B; // Works
A *= C; // Works, A now has 3 rows and 1 column
C *= A; // Error
D *= A; // Works
A *= D; // Error
test_matrix = A / number; // Works
test_matrix = A / B; // Error
A /= number; // Works
test_matrix = number / A; // Error
number /= A; // Error
```

- **`void display()`**: Displays the elements of the object, in the same shape as the object.
```c++
linalg::Matrix<double> A{3, 3};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

A.display(); // Displays the matrix. Takes up three lines to do so
```

- **`std::tuple<size_t, size_t> shape()`**: Returns the shape of the object as a tuple.
```c++
linalg::Matrix<double> A{9, 4};

auto [nrows, ncols] = A.shape(); // nrows = 9 and ncols = 4, both of them are of type size_t
```

- **`Matrix reshape(size_t new_rows, size_t new_cols)`**: Reshapes the object, as long as the new dimensions don't change the number of elements that the object already holds. Can be used to flatten an object.
```c++
linalg::Matrix<double> A{4, 6}, B;

B = A.reshape(24, 1); // B now has the elements of A in 24 rows and 1 column
B = A.reshape(1, 24); // B now has the elements of A in 1 row and 24 columns
B = A.reshape(8, 3); // B now has the elements of A in 8 rows and 3 columns
B = A.reshape(3, 3); // Error, incompatible dimensions
```

- **`Matrix transpose()`**: Switches the elements of the objects along the diagonal. Can also be used to turn column vectors into row vectors, and vice versa.
```c++
linalg::Matrix<int> A{3, 4}, B;

// Set values of A here

B = A.transpose(); // B now has 4 rows and 3 columns, and B(i, j) = A(j, i)
```

- **`Matrix conjugate()`**: Calculates the conjugate of a matrix. Only works when using std::complex.
```c++
linalg::Matrix<std::complex<double>> A{3, 3}, B;
linalg::Matrix<double> C{3, 3}, D;

// Set values of A and C here

B = A.conjugate(); // B's values are now the conjugates of A's values
D = C.conjugate(); // D has the same values as C
```

- **`bool is_self_adjoint()`**: Returns true if a matrix is self adjoint, and false if it isn't. A self adjoint matrix is one that is equal to its transposed conjugate.
```c++
linalg::Matrix<int> A{3, 3};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

if (A.is_self_adjoint)
{
    std::cout<<"A is self adjoint.\n"; // Will not be printed
}
else
{
    std::cout<<"A is not self adjoint.\n"; // Will be printed
}
```

- **`T diagonal_product()`**: Returns the product of the elements of the diagonal. The type of the product is the same as the type of the elements. Only works for square `Matrix` objects (same rows and columns).
```c++
linalg::Matrix<double> A{3, 3}, B{3, 4};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

double diag = A.diagonal_product(); // diag = 12.0
diag = B.diagonal_product(); // Error
```

- **`void pivot(size_t row1, size_t row2)`**: Swaps rows row1 and row2.
```c++
linalg::Matrix<double> A{3, 3};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

A.pivot(0, 2); // Now the first and third row of A have been swapped
```

- **`Matrix replace_column(size_t column1, Matrix other)`**: Replaces column `column1` with `other`, as long as `other` has one column, and the same number of rows as the object it is called upon.
```c++
linalg::Matrix<double> A{3, 3}, B{3}, C;

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

C = A.replace_column(2, B); // Now C has the same values as A in the first and second columns, and the values of B in its third column
```

- **`T trace()`**: Returns the sum of all elements along the diagonal of a square matrix. The result is of the same type as the elements of the matrix.
```c++
linalg::Matrix<double> A{3, 3};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

double tr = A.trace(); // tr = 8
```

- **`std::tuple<Matrix, Matrix> LU_decomp();`**: Performs LU decomposition of the matrix, which expresses a given square matrix as the product of a lower triangular matrix L with an upper triangular matrix U. It uses Crout's algorithm, which involves division, therefore its results are susceptible to mistakes when the matrix holds `int` elements.
```c++
linalg::Matrix<double> A{3, 3};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

auto [L, U]= A.LU_decomp(); // L is a lower triangular matrix, U is an upper triangular matrix
```

- **`T determinant()`**: Returns the determinant of a square matrix, which is of the same type as the elements of the matrix. One of its steps is LU decomposition, therefore it is susceptible to mistakes when the matrix holds `int` elements.
```c++
linalg::Matrix<double> A{3, 3};

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

double det = A.determinant(); // det = 14
```
- **`double norm()`**: Calculates the norm of the object, as long as it has only one row or one column.
```c++
linalg::Matrix<double> X{3};

X(0) = 1; X(1) = 2; X(2) = 3;

std::cout << X.norm(); // 14
```

- **`double magnitude()`**: Calculates the magnitude of the object, as long as it has only one row or one column.
```c++
linalg::Matrix<double> X{3};

X(0) = 1; X(1) = 2; X(2) = 3;

std::cout << X.magnitude(); // 3.74166
```

- **`Matrix Cramer_rule(Matrix other)`**: Uses Cramer's rule to calculate X in the system A * X = B, where A is the object upon which the method is called, X is the solution, and B is `other`
```c++
linalg::Matrix<double> A{3, 3}, B{3}, X;

A(0, 0) = 4; A(0, 1) = 0; A(0, 2) = 1;
A(1, 0) = 2; A(1, 1) = 1; A(1, 2) = 0;
A(2, 0) = 2; A(2, 1) = 2; A(2, 2) = 3;

B(0) = 3; B(1) = 4; B(2) = 6;

X = A.Cramer_rule(B);

X.display(); // Displays the solution

(A * X).display(); // This is equal to B
```

- **`void vstack(Matrix other)`**: Adds `other` to the bottom of the object it is called upon, as long as the dimesnions are compatible.
```c++
linalg::Matrix<double> A{3, 3}, B{40, 3}, C, D{3, 12};

A.vstack(B); // Works, A now has 43 rows and 3 columns
A.vstack(C); // Works, no changes are made to A
A.vstack(D); // Error, D has more rows than A so the operation cannot happen
```
