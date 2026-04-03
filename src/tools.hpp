#pragma once

#include <vector>
#include <cmath>
#include "DenseMatrix.hpp"

DenseMatrix I(size_t n);
DenseMatrix transpose(const DenseMatrix &A);
DenseMatrix vector_matrix(const std::vector<double> &v, const std::vector<double> &v_T);
DenseMatrix operator*(double a, const DenseMatrix &A);
DenseMatrix operator*(const DenseMatrix &mat, double a);
DenseMatrix operator/(const DenseMatrix &mat, double a);
DenseMatrix operator-(const DenseMatrix &A, const DenseMatrix &B);
std::vector<double> operator+(const std::vector<double> &v, const std::vector<double> &x);
double dot(const std::vector<double> &v, const std::vector<double> &x);
std::vector<double> operator*(const std::vector<double> &v, double a);
std::vector<double> operator*(double a, const std::vector<double> &v);
std::vector<double> operator-(const std::vector<double> &v, const std::vector<double> &x);
bool operator==(const std::vector<double> &v, const std::vector<double> &x);
double norm2(const std::vector<double> &v);
std::vector<double> normalize(const std::vector<double> &v);
std::ostream &operator<<(std::ostream &os, const std::vector<double> &vec);