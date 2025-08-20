#include <iostream>

namespace linalg
{
    template <typename T>
    Matrix<T> eye(const size_t &n)
    {
        Matrix<T> identity{n, n};

        for (size_t i{0}; i < n; ++i)
        {
            identity(i, i) = 1.0;
        }

        return identity;
    }
}