#pragma once

#include <iostream>
#include <vector>

class DenseMatrix
{
private:
    size_t rows, cols;
    std::vector<double> data;

public:
    DenseMatrix();
    DenseMatrix(const std::vector<double> &data, size_t cols);

    double operator()(size_t i, size_t j) const;
    double &at(size_t i, size_t j);

    size_t GetRows() const;
    size_t GetCols() const;
    const std::vector<double> &GetData() const;
    const std::vector<double> GetRow(size_t k) const;
    const std::vector<double> GetCol(size_t k) const;

    std::vector<double> operator*(const std::vector<double> &v) const;
};

std::vector<double> operator+(const std::vector<double> &v, const std::vector<double> &x);
double operator*(const std::vector<double> &v, const std::vector<double> &x);
std::vector<double> operator*(std::vector<double> &v, double a);
