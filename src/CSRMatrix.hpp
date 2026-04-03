#pragma once

#include <iostream>
#include <vector>

class CSRMatrix
{
public:
    size_t N;
    size_t M;

    std::vector<double> values;
    std::vector<double> cols;
    std::vector<double> rows;

    CSRMatrix();
    CSRMatrix(const std::vector<double> &values, const std::vector<double> &cols, const std::vector<double> &rows);

    double operator()(size_t i, size_t j) const;
    std::vector<double> operator*(const std::vector<double> &v) const;
};
