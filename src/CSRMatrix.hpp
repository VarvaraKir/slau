#pragma once

#include <iostream>
#include <vector>

class CSRMatrix
{
private:
    size_t N;
    size_t M;

    std::vector<double> values;
    std::vector<double> cols;
    std::vector<double> rows;

public:
    CSRMatrix();
    CSRMatrix(const std::vector<double> &values, std::vector<double> &cols, std::vector<double> &rows);

    double operator()(size_t i, size_t j) const;
    std::vector<double> operator*(const std::vector<double> &v) const;
};
