#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

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
    template <typename T>
    void Matrix<T>::read_csv(std::string csv_path, char delimiter)
    {
        // Check whether the file has the correct extension
        if (csv_path.substr(csv_path.length() - 4, csv_path.length()) != ".csv")
        {
            std::cerr << "Invalid file type (must be .csv).";
        }

        std::ifstream csv(csv_path);
        std::string line;

        size_t file_rows{0};
        size_t file_cols{0};

        // Read file once to get the number of rows and columns
        while (std::getline(csv, line))
        {
            std::stringstream partial_line(line);
            std::string file_component;

            size_t file_columns{0};

            ++file_rows;

            while (std::getline(partial_line, file_component, delimiter))
            {
                ++file_columns;
            }
            file_cols = file_columns;
        }

        // Initialize the data
        rows = file_rows;
        cols = file_cols;

        delete[] data;
        data = new T[rows * cols];

        // Read the file again to get the values
        csv.clear();
        csv.seekg(0, std::ios::beg);

        size_t current_index = 0;

        while (std::getline(csv, line))
        {
            std::stringstream partial_line(line);
            std::string file_component;

            while (std::getline(partial_line, file_component, delimiter))
            {
                // Convert type and add to data here
                data[current_index++] = static_cast<T>(std::stod(file_component));
            }
        }
    }
}
