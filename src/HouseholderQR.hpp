#pragma once

#include <cmath>
#include "DenseMatrix.hpp"
#include "tools.hpp" 

class HouseholderQR
{
public: 
    HouseholderQR(DenseMatrix dm);

    DenseMatrix& GetQ();
    DenseMatrix& GetR();

protected:
    DenseMatrix A, Q, R;
    DenseMatrix P(const std::vector<double> v) const;
    void computeQR();

};