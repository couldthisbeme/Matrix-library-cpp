#include <stdexcept>

namespace linalg
{
    template <typename T>
    Matrix<T>::Matrix(const size_t &x, const size_t &y)
    {
        if ((x == 0) || (y == 0))
        {
            throw std::logic_error("Cannot create a matrix with 0 rows/columns.");
        }

        rows = x;
        cols = y;
        data = new T[rows * cols]();
    }
    template <typename T>
    Matrix<T>::Matrix(const size_t &x) : rows{x}, cols{1}
    {
        if (x == 0)
        {
            data = nullptr;
        }
        else
        {
            data = new T[x]();
        }
    }
    template <typename T>
    Matrix<T>::Matrix(const Matrix<T> &other) : rows{other.rows}, cols{other.cols}, data{new T[other.rows * other.cols]()}
    {
        std::copy(other.data, other.data + rows * cols, data);
    }
    template <typename T>
    Matrix<T>::Matrix(Matrix<T> &&other) noexcept : rows{other.rows}, cols{other.cols}, data{other.data}
    {
        other.rows = 0;
        other.cols = 0;
        other.data = nullptr;
    }
    template <typename T>
    Matrix<T>::Matrix() : rows{0}, cols{0}, data{nullptr} {}
    template <typename T>
    Matrix<T>::~Matrix() { delete[] data; }
}