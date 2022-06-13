#include "Matrix.h"

#include <algorithm>
#include <exception>
#include <iostream>

Matrix::Matrix(size_t h, size_t w):
    rows(h), cols(w), matrix(new double[h * w])
{
    std::fill(matrix, matrix + size(), 0);
}

Matrix::Matrix(const Matrix& rhs):
    rows(rhs.rows), cols(rhs.cols),
    matrix(new double[rhs.size()])
{
    std::copy(rhs.matrix, rhs.matrix + size(), matrix);
}

Matrix::Matrix(Matrix&& rhs) noexcept:
    rows(rhs.rows), cols(rhs.cols),
    matrix(rhs.matrix)
{
    rhs.matrix = nullptr;
}

Matrix::~Matrix() {
    delete [] matrix;
}

Matrix& Matrix::operator=(const Matrix& rhs) {
    if (this != &rhs) {
        double* data = new double[rhs.size()];
        std::copy(rhs.matrix, rhs.matrix + rhs.size(), data);
        delete [] matrix;
        rows = rhs.rows;
        cols = rhs.cols;
        matrix = data;
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& rhs) noexcept {
    if (this != &rhs) {
        rows = rhs.rows;
        cols = rhs.cols;
        delete [] matrix;
        matrix = rhs.matrix;
        rhs.matrix = nullptr;
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
    if (rows != rhs.rows || cols != rhs.cols) {
        throw std::invalid_argument("Incompatible dimensions");
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            at(i, j) += rhs(i, j);
        }
    }
    return *this;
}

double& Matrix::operator()(size_t r, size_t c) {
    return matrix[r * cols + c];
}

const double& Matrix::operator()(size_t r, size_t c) const{
    return matrix[r * cols + c];
}

double& Matrix::at(size_t r, size_t c) {
    if (r >= rows || c >= cols) {
        throw std::out_of_range("Out of matrix bounds");
    }
    return matrix[r * cols + c];
}

const double& Matrix::at(size_t r, size_t c) const {
    if (r >= rows || c >= cols) {
        throw std::out_of_range("Out of matrix bounds");
    }
    return matrix[r * cols + c];
}

double* Matrix::operator[](size_t r) {
    return &matrix[r * cols];
}

const double* Matrix::operator[](size_t r) const {
    return &matrix[r * cols];
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.height() != rhs.height() || lhs.width() != rhs.width()) {
        throw std::invalid_argument("Incompatible dimensions");
    }
    Matrix result(lhs.height(), lhs.width());

    for (size_t i = 0; i < result.height(); i++) {
        for (size_t j = 0; j < result.width(); j++) {
            result(i, j) = lhs(i, j) + rhs(i, j);
        }
    }

    return result;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.width() != rhs.height()) {
        throw std::invalid_argument("Incompatible dimensions");
    }
    Matrix result(lhs.height(), rhs.width());

    for (size_t i = 0; i < result.height(); i++) {
        for (size_t j = 0; j < result.width(); j++) {
            // Dot-product of left-row and right-col
            for (size_t k = 0; k < lhs.width(); k++) {
                result(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }

    return result;
}

// int main() {
//     size_t h = 4, w = 3;
//     Matrix m(h, w);
//     m[2][2] = 4;
//     for (size_t i = 0; i < h; i++) {
//         for (size_t j = 0; j < w; j++) {
//             std::cout << m[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }