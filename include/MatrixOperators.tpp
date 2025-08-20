#include <iostream>
#include <stdexcept>

namespace linalg
{
    template <typename T>
    T &Matrix<T>::operator()(size_t i, size_t j)
    {
        if (data == nullptr)
        {
            throw std::logic_error("Cannot access elements of empty Matrix.");
        }
        if ((i > rows) || (j > cols))
        {
            throw std::logic_error("Requested index out of range.");
        }

        return data[i * cols + j];
    }
    template <typename T>
    T Matrix<T>::operator()(size_t i, size_t j) const
    {
        if (data == nullptr)
        {
            throw std::logic_error("Cannot access elements of empty Matrix.");
        }
        if ((i > rows) || (j > cols))
        {
            throw std::logic_error("Requested index out of range.");
        }

        return data[i * cols + j];
    }
    template <typename T>
    T &Matrix<T>::operator()(size_t i)
    {
        if (data == nullptr)
        {
            throw std::logic_error("Cannot access elements of empty Matrix.");
        }
        if ((rows != 1) && (cols != 1))
        {
            throw std::logic_error("Cannot get element of 2D matrix with only one input.");
        }

        return data[i];
    }
    template <typename T>
    T Matrix<T>::operator()(size_t i) const
    {
        if (data == nullptr)
        {
            throw std::logic_error("Cannot access elements of empty Matrix.");
        }
        if ((rows != 1) && (cols != 1))
        {
            throw std::logic_error("Cannot get element of 2D matrix with only one input.");
        }

        return data[i];
    }
    template <typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
    {
        if (this != &other)
        {
            Matrix<T> temp{other};

            std::swap(rows, temp.rows);
            std::swap(cols, temp.cols);
            std::swap(data, temp.data);
        }

        return *this;
    }
    template <typename T>
    Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = other.data;

            other.rows = 0;
            other.cols = 0;
            other.data = nullptr;
        }
        return *this;
    }
    template <typename T>
    bool Matrix<T>::operator==(const Matrix<T> &other) const
    {
        if ((rows != other.rows) || (cols != other.cols))
        {
            return false;
        }

        for (size_t i{0}; i < rows * cols; ++i)
        {
            if (data[i] != other.data[i])
            {
                return false;
            }
        }

        return true;
    }
    template <typename T>
    bool Matrix<T>::operator!=(const Matrix<T> &other) const
    {
        return !((*this) == other);
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix &other) const
    {
        if ((rows != other.rows) || (cols != other.cols))
        {
            throw std::logic_error("Cannot add matrices with different dimensions");
        }

        Matrix<T> addition{(*this)};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            addition.data[i] += other.data[i];
        }

        return addition;
    }
    template <typename T>
    void Matrix<T>::operator+=(const Matrix &other)
    {
        if ((rows != other.rows) || (cols != other.cols))
        {
            throw std::logic_error("Cannot add matrices with different dimensions");
        }

        for (size_t i{0}; i < rows * cols; ++i)
        {
            data[i] += other.data[i];
        }
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator+(const T &n) const
    {
        Matrix<T> addition{(*this)};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            addition.data[i] += n;
        }

        return addition;
    }
    template <typename T>
    void Matrix<T>::operator+=(const T &n)
    {
        for (size_t i{0}; i < rows * cols; ++i)
        {
            data[i] += n;
        }
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator-(const Matrix &other) const
    {
        if ((rows != other.rows) || (cols != other.cols))
        {
            throw std::logic_error("Cannot subtract matrices with different dimensions");
        }

        Matrix<T> addition{(*this)};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            addition.data[i] -= other.data[i];
        }

        return addition;
    }
    template <typename T>
    void Matrix<T>::operator-=(const Matrix &other)
    {
        if ((rows != other.rows) || (cols != other.cols))
        {
            throw std::logic_error("Cannot subtract matrices with different dimensions");
        }

        for (size_t i{0}; i < rows * cols; ++i)
        {
            data[i] -= other.data[i];
        }
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator-(const T &n) const
    {
        Matrix<T> addition{(*this)};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            addition.data[i] -= n;
        }

        return addition;
    }
    template <typename T>
    void Matrix<T>::operator-=(const T &n)
    {
        for (size_t i{0}; i < rows * cols; ++i)
        {
            data[i] -= n;
        }
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
    {
        if (cols != other.rows)
        {
            throw std::logic_error("Invalid dimensions for matrix multiplication.");
        }

        Matrix<T> multiplication{rows, other.cols};

        for (size_t i{0}; i < rows; ++i)
        {
            for (size_t j{0}; j < other.cols; ++j)
            {
                for (size_t k{0}; k < cols; ++k)
                {
                    multiplication(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }

        return multiplication;
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator*(const T &n) const
    {
        Matrix<T> multiplication{(*this)};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            multiplication.data[i] *= n;
        }

        return multiplication;
    }
    template <typename T>
    void Matrix<T>::operator*=(const T &n)
    {
        for (size_t i{0}; i < rows * cols; ++i)
        {
            data[i] *= n;
        }
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator/(const T &n) const
    {
        Matrix<T> division{(*this)};

        for (size_t i{0}; i < rows * cols; ++i)
        {
            division.data[i] /= n;
        }

        return division;
    }
    template <typename T>
    void Matrix<T>::operator/=(const T &n)
    {
        for (size_t i{0}; i < rows * cols; ++i)
        {
            data[i] /= n;
        }
    }
}