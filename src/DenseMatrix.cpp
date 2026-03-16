#include "DenseMatrix.hpp"

DenseMatrix::DenseMatrix() : rows(0), cols(0), data({}) {}
DenseMatrix::DenseMatrix(const std::vector<double> &data, size_t cols) : rows(data.size() / cols), cols(cols), data(data) {}

double DenseMatrix::operator()(size_t i, size_t j) const
{
    return data[i * cols + j];
}

double &DenseMatrix::at(size_t i, size_t j)
{
    return data[i * cols + j];
}

size_t DenseMatrix::GetRows() const
{
    return rows;
}

size_t DenseMatrix::GetCols() const
{
    return cols;
}

const std::vector<double> &DenseMatrix::GetData() const
{
    return data;
}

const std::vector<double> DenseMatrix::GetRow(size_t k) const
{
    std::vector<double> v(cols);

    for (size_t i = 0; i < cols; i++)
    {
        v[i] = operator()(k, i);
    }

    return v;
}

const std::vector<double> DenseMatrix::GetCol(size_t k) const
{
    std::vector<double> v(rows);

    for (size_t i = 0; i < rows; i++)
    {
        v[i] = operator()(i, k);
    }

    return v;
}

std::vector<double> DenseMatrix::operator*(const std::vector<double> &v) const
{
    std::vector<double> k(rows);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            k[i] += operator()(i, j) * v[j];
        }
    }

    return k;
}

DenseMatrix DenseMatrix::operator*(const DenseMatrix& other) const {
    size_t n = rows, m = other.cols;
    std::vector<double> v(n * m);
    for (size_t i = 0; i < n; i++) {
        for (size_t k = 0; k < cols; k++) {
            for (size_t j = 0; j < m; j++) {
                v[m * i + j] += operator()(i, k) * other(k, j);
            }
        }
    }
    return DenseMatrix(v, m);
}

bool DenseMatrix::operator==(const DenseMatrix& other) const {
    double eps = 1e-13;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (fabs(operator()(i, j) - other(i, j)) > eps) {
                return false;
            } 
        }
    }
    return true;
}