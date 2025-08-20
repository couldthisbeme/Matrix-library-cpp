#include <cmath>
#include <iostream>

namespace linalg
{
    template <typename T>
    void Matrix<T>::display() const
    {
        for (size_t i{0}; i < rows; ++i)
        {
            for (size_t j{0}; j < cols; ++j)
            {
                std::cout << (*this)(i, j) << '\t';
            }
            std::cout << '\n';
        }
    }
    template <typename T>
    void Matrix<T>::pivot(const size_t &row1, const size_t &row2)
    {
        if (row1 == row2)
        {
            throw std::logic_error("Cannot swap a row with itself.");
        }

        for (size_t j{0}; j < cols; ++j)
        {
            std::swap((*this)(row1, j), (*this)(row2, j));
        }
    }
    template <typename T>
    std::tuple<size_t, size_t> Matrix<T>::shape() const
    {
        return std::make_tuple(rows, cols);
    }
    template <typename T>
    Matrix<T> Matrix<T>::reshape(const size_t &new_rows, const size_t &new_cols) const
    {
        if ((new_rows * new_cols) != (rows * cols))
        {
            throw std::logic_error("Invalid dimensions for reshaping.");
        }

        Matrix<T> reshaped{new_rows, new_cols};

        std::copy(data, data + (rows * cols), reshaped.data);

        return reshaped;
    }
    template <typename T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Matrix<T> transposition{cols, rows};

        for (size_t i{0}; i < cols; ++i)
        {
            for (size_t j{0}; j < rows; ++j)
            {
                transposition(i, j) = (*this)(j, i);
            }
        }

        return transposition;
    }
    template <typename T>
    T Matrix<T>::diagonal_product() const
    {
        if (rows != cols)
        {
            throw std::logic_error("Cannot compute diagonal product of non square matrix.");
        }
        T dp{1};

        for (size_t i{0}; i < rows; ++i)
        {
            dp *= (*this)(i, i);
        }

        return dp;
    }
    template <typename T>
    Matrix<T> Matrix<T>::conjugate() const
    {
        Matrix<T> conj{rows, cols};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            conj.data[i] = std::conj(data[i]);
        }

        return conj;
    }
    template <typename T>
    bool Matrix<T>::is_self_adjoint() const
    {
        if (rows != cols)
        {
            return false;
        }

        Matrix<T> sa{conjugate()};
        sa = sa.transpose();

        return ((*this) == sa);
    }
    template <typename T>
    Matrix<T> Matrix<T>::replace_column(const size_t &column1, const Matrix<T> &new_column) const
    {
        if ((new_column.rows != 1) && (new_column.cols != 1))
        {
            throw std::logic_error("Cannot replace singular row with non vector.");
        }

        if ((new_column.rows != rows) && (new_column.cols != rows))
        {
            throw std::logic_error("Incompatible number of elements for replacement.");
        }

        Matrix<T> column_replaced{(*this)};

        for (size_t i{0}; i < rows; ++i)
        {
            column_replaced(i, column1) = new_column(i);
        }

        return column_replaced;
    }
}