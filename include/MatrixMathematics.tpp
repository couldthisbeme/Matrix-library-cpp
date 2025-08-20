#include <cmath>
#include <complex>
#include <stdexcept>

namespace linalg
{
    template <typename T>
    T Matrix<T>::trace() const
    {
        if ((rows == 1) || (cols == 1))
        {
            throw std::logic_error("Cannot calculate trace of 1D matrix");
        }

        if (rows != cols)
        {
            throw std::logic_error("Cannot calculate trace of non square matrix");
        }

        T tr{0};

        for (size_t i{0}; i < rows; ++i)
        {
            tr += (*this)(i, i);
        }

        return tr;
    }
    template <typename T>
    std::tuple<Matrix<T>, Matrix<T>> Matrix<T>::LU_decomp()
    {
        if (rows != cols)
        {
            throw std::logic_error("Cannot perform LU decomposition on non square matrices.");
        }

        Matrix<T> L{rows, cols};
        Matrix<T> U{eye<T>(rows)};

        // Step 2
        for (size_t j{0}; j < cols; ++j)
        {
            for (size_t i{j}; i < rows; ++i)
            {
                T term2{0};
                for (size_t k{0}; k < j; ++k)
                {
                    term2 += L(i, k) * U(k, j);
                }

                L(i, j) = (*this)(i, j) - term2;
            }

            if (L(j, j) == 0.0)
            {
                auto max_abs_val = std::abs(L(j, j));
                size_t pivot_row{j};
                // Search for line to switch
                for (size_t i2{j}; i2 < rows; ++i2)
                {
                    if (std::abs(L(i2, j)) > max_abs_val)
                    {
                        max_abs_val = std::abs(L(i2, j));
                        pivot_row = i2;
                    }
                }

                if (max_abs_val == 0.0)
                {
                    throw std::runtime_error("Matrix is singular.");
                }

                pivot(j, pivot_row);
                L.pivot(j, pivot_row);
            }

            for (size_t i{j + 1}; i < rows; ++i)
            {
                T term2{0};
                for (size_t k{0}; k < j; ++k)
                {
                    term2 += L(j, k) * U(k, i);
                }

                U(j, i) = ((*this)(j, i) - term2) / L(j, j);
            }
        }

        return std::make_tuple(L, U);
    }
    template <typename T>
    T Matrix<T>::determinant()
    {
        if (rows != cols)
        {
            throw std::logic_error("Cannot compute determinant of non square matrix.");
        }
        auto [L, U, pivot_num] = _LU_det();

        return L.diagonal_product() * U.diagonal_product() * std::pow(-1, pivot_num);
    }
    template <typename T>
    Matrix<T> Matrix<T>::Cramer_rule(const Matrix<T> &other)
    {
        if (rows > cols)
        {
            throw std::logic_error("System is overdefined.");
        }
        else if (rows < cols)
        {
            throw std::logic_error("System doesn't have an exact solution.");
        }

        if (other.cols != 1)
        {
            throw std::logic_error("Can only solve system when passing a 1D Matrix object to the method.");
        }

        if (other.rows != cols)
        {
            throw std::logic_error("Incompatible number of dimensions for system.");
        }

        Matrix<T> solution{other.rows};

        T denominator{determinant()};

        for (size_t i{0}; i < other.rows; ++i)
        {
            Matrix<T> temp{replace_column(i, other)};
            solution(i) = temp.determinant() / denominator;
        }

        return solution;
    }
    template <typename T>
    double Matrix<T>::norm() const
    {
        if ((rows != 1) && (cols != 1))
        {
            throw std::logic_error("Norm is defined only for vectors, not matrices.");
        }

        double solution{0};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            solution += std::pow(std::abs(data[i]), 2);
        }

        return solution;
    }
    template <typename T>
    double Matrix<T>::magnitude() const
    {
        return std::sqrt(norm());
    }
}