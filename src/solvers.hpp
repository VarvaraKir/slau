#pragma once

#include "DenseMatrix.hpp"
#include "CSRMatrix.hpp"
#include "tools.hpp"

namespace solvers {
    DenseMatrix QR(const DenseMatrix& Q, const DenseMatrix& R, const DenseMatrix& b);
    
}