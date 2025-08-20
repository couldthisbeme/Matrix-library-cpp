namespace linalg
{
    template <typename T>
    Matrix<T> operator+(const T &n, const Matrix<T> &A)
    {
        auto [rows, cols] = A.shape();
        Matrix<T> addition{rows, cols};

        for (size_t i{0}; i < rows; ++i)
        {
            for (size_t j{0}; j < cols; ++j)
            {
                addition(i, j) = A(i, j) + n;
            }
        }

        return addition;
    }
    template <typename T>
    Matrix<T> operator-(const T &n, const Matrix<T> &A)
    {
        auto [rows, cols] = A.shape();
        Matrix<T> addition{rows, cols};

        for (size_t i{0}; i < rows; ++i)
        {
            for (size_t j{0}; j < cols; ++j)
            {
                addition(i, j) = A(i, j) - n;
            }
        }

        return addition;
    }
    template <typename T>
    Matrix<T> operator*(const T &n, const Matrix<T> &A)
    {
        return A * n;
    }
}