#include "solvers.hpp"

DenseMatrix solvers::QR(const DenseMatrix &Q, const DenseMatrix &R, const DenseMatrix &b)
{
    std::vector<double> b_v = b.GetCol(0);
    std::vector<double> y_v = transpose(Q) * b_v;
    DenseMatrix y(y_v, 1);

    size_t n = R.GetRows();
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for (size_t j = i + 1; j < n; j++)
        {
            sum += R(i, j) * x[j];
        }
            x[i] = (y(i, 0) - sum)/R(i,i);
    }
    return DenseMatrix(x, 1);
}