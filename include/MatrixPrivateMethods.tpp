#include <tuple>

namespace linalg
{

    template <typename T>
    std::tuple<Matrix<T>, Matrix<T>, int> Matrix<T>::_LU_det()
    {
        if (rows != cols)
        {
            throw std::logic_error("Cannot perform LU decomposition on non square matrices.");
        }

        Matrix<T> L{rows, cols};
        Matrix<T> U{eye<T>(rows)};

        // Step 2
        size_t pivot_num{0};
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
                ++pivot_num;
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

        return std::make_tuple(L, U, pivot_num);
    }
    template <typename T>
    void Matrix<T>::pivot_system(const size_t &row1, const size_t &row2, Matrix<T> &other)
    {
        if (row1 == row2)
        {
            throw std::logic_error("Cannot swap a row with itself.");
        }

        if ((other.rows != 1) && (other.cols != 1))
        {
            throw std::logic_error("The matrix object passed to pivot_system must be a vector.");
        }

        std::swap(other.data[row1], other.data[row2]);

        for (size_t i{0}; i < cols; ++i)
        {
            std::swap((*this)(row1, i), (*this)(row2, i));
        }
    }
}