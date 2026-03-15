#pragma once

#include <vector>
#include "DenseMatrix.hpp"

DenseMatrix I(size_t n);
DenseMatrix vector_matrix(const std::vector<double> &v,const std::vector<double> &v_T);
DenseMatrix operator*(double a, const DenseMatrix& mat);
DenseMatrix operator*(const DenseMatrix& mat, double a);
DenseMatrix operator/(const DenseMatrix& mat, double a);
DenseMatrix operator-(const DenseMatrix& A, const DenseMatrix& B);
std::vector<double> operator+(const std::vector<double> &v, const std::vector<double> &x);
double dot(const std::vector<double> &v, const std::vector<double> &x);
std::vector<double> operator*(const std::vector<double> &v, double a);
std::vector<double> operator*(double a, const std::vector<double> &v);
std::vector<double> operator-(const std::vector<double> &v, const std::vector<double> &x);