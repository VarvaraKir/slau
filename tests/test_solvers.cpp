#include <gtest/gtest.h>

#include "tools.hpp"
#include "CSRMatrix.hpp"
#include "solvers.hpp"

TEST(solve, Jacobi)
{
    std::vector<double> x = {1, 5, 3};
    CSRMatrix A = CSRMatrix({1, 2, 4, 2, 6}, {0, 1, 1, 1, 2}, {0, 2, 3, 5});

    std::vector<double> b = A * x;
    std::vector<double> f = solvers::Jacobi(A, b);

    EXPECT_TRUE(x == f);
}