#pragma once

#include "DenseMatrix.hpp"
#include "CSRMatrix.hpp"
#include "tools.hpp"

namespace solvers
{
    DenseMatrix QR(const DenseMatrix &Q, const DenseMatrix &R, const DenseMatrix &b);

    std::vector<double> wthD(const CSRMatrix &A, std::vector<double> &v);

    std::vector<double> Jacobi(const CSRMatrix &A, const std::vector<double> &b);

    std::vector<double> GaussSeidel(const CSRMatrix &A, const std::vector<double> &b);
    

}