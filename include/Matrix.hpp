#pragma once

#include <iostream>
#include <stdexcept>
#include <tuple>

#ifndef MATRIX_HEADER_CLASS_METHOD_DECLARATIONS
#define MATRIX_HEADER_CLASS_METHOD_DECLARATIONS

namespace linalg
{
    template <typename T>
    class Matrix
    {
    public:
        // MatrixConstructors.tpp
        Matrix(const size_t &x, const size_t &y);
        Matrix(const size_t &x);
        Matrix(const Matrix &other);
        Matrix(Matrix &&other) noexcept;
        Matrix();
        ~Matrix();

        // MatrixOperators.tpp
        T &operator()(size_t i, size_t j);
        T operator()(size_t i, size_t j) const;
        T &operator()(size_t i);
        T operator()(size_t i) const;
        Matrix &operator=(const Matrix &other);
        Matrix &operator=(Matrix &&other) noexcept;
        bool operator==(const Matrix &other) const;
        bool operator!=(const Matrix &other) const;
        Matrix operator+(const Matrix &other) const;
        void operator+=(const Matrix &other);
        Matrix operator+(const T &n) const;
        void operator+=(const T &n);
        Matrix operator-(const Matrix &other) const;
        void operator-=(const Matrix &other);
        Matrix operator-(const T &n) const;
        void operator-=(const T &n);
        Matrix operator*(const Matrix &other) const;
        Matrix operator*(const T &n) const;
        void operator*=(const T &n);
        Matrix operator/(const T &n) const;
        void operator/=(const T &n);

        // MatrixMathematics.tpp
        T trace() const;
        std::tuple<Matrix, Matrix> LU_decomp();
        T determinant();
        Matrix Cramer_rule(const Matrix &other);
        double norm() const;
        double magnitude() const;

        // MatrixUtility.tpp
        void display() const;
        void pivot(const size_t &row1, const size_t &row2);
        std::tuple<size_t, size_t> shape() const;
        Matrix reshape(const size_t &new_rows, const size_t &new_cols) const;
        Matrix transpose() const;
        T diagonal_product() const;
        Matrix conjugate() const;
        bool is_self_adjoint() const;
        Matrix replace_column(const size_t &column1, const Matrix<T> &new_column) const;
        void vstack(const Matrix &other);

    private:
        size_t rows, cols;
        T *data;

        // MatrixPrivateMethods.tpp
        std::tuple<Matrix, Matrix, int> _LU_det();
        void pivot_system(const size_t &row1, const size_t &row2, Matrix &other);
    };

    // MatrixExtraOperators.tpp
    template <typename T>
    Matrix<T> operator+(const T &n, const Matrix<T> &A);
    template <typename T>
    Matrix<T> operator-(const T &n, const Matrix<T> &A);
    template <typename T>
    Matrix<T> operator*(const T &n, const Matrix<T> &A);

    // MatrixExtraFunctions.tpp
    template <typename T>
    Matrix<T> eye(const size_t &n);
}

#include "MatrixConstructors.tpp"
#include "MatrixMathematics.tpp"
#include "MatrixOperators.tpp"
#include "MatrixUtility.tpp"
#include "MatrixExtraOperators.tpp"
#include "MatrixExtraFunctions.tpp"
#include "MatrixPrivateMethods.tpp"


#endif
