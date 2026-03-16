#include <gtest/gtest.h>

#include "DenseMatrix.hpp"
#include "tools.hpp"
#include "HouseholderQR.hpp"
#include "solvers.hpp"

TEST(Householder, main) {
    std::vector<double> data(20*20);
    for (size_t i =0; i < 20 * 20; i++){
        data[i] = (rand()% 200 - 100) / 10.0;
    }
    DenseMatrix A(data, 20);
    HouseholderQR hhqr = HouseholderQR(A);
    DenseMatrix Q = hhqr.GetQ();
    DenseMatrix R = hhqr.GetR();
	
	EXPECT_TRUE(Q * R == A);
}

TEST(HouseholderQR, SolveLinearSystem) {
    std::vector<double> A_data = {
        4, 1, 1,
        1, 4, 1,
        1, 1, 4
    };
    DenseMatrix A(A_data, 3);
    
    std::vector<double> b_data = {6, 6, 6};  
    DenseMatrix b(b_data, 1);
    
    HouseholderQR hhqr(A);
    
    DenseMatrix x = solvers::QR(hhqr.GetQ(), hhqr.GetR(), b);
    
    EXPECT_NEAR(x(0, 0), 1.0, 1e-10);
    EXPECT_NEAR(x(1, 0), 1.0, 1e-10);
    EXPECT_NEAR(x(2, 0), 1.0, 1e-10);
    
    std::vector<double> Ax = A * x.GetCol(0);
    for (size_t i = 0; i < 3; i++) {
        EXPECT_NEAR(Ax[i], b_data[i], 1e-10);
    }
}