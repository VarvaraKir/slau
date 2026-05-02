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
        x[i] = (y(i, 0) - sum) / R(i, i);
    }
    return DenseMatrix(x, 1);
}

std::vector<double> solvers::wthD(const CSRMatrix &A, std::vector<double> &v)
{
    std::vector<double> y(A.M);

    for (size_t i = 0; i < A.M; i++)
    {
        for (size_t k = A.rows[i]; k < A.rows[i + 1]; k++)
        {
            if (i != A.cols[k])
            {
                y[i] += A.values[k] * v[A.cols[k]];
            }
        }
    }
    return y;
}

std::vector<double> solvers::Jacobi(const CSRMatrix &A, const std::vector<double> &b)
{
    std::vector<double> x0(b.size());
    std::vector<double> y;
    while (true)
    {
        y = b - wthD(A, x0);

        std::vector<double> x1(b.size());
        for (size_t i = 0; i < b.size(); i++)
        {
            x1[i] = 1 / A(i, i) * y[i];
        }

        double r = norm2(A * x1 - b);
        if (r < 1e-8)
        {
            return x1;
        }

        x0 = x1;
    }
}

std::vector<double> solvers::GaussSeidel(const CSRMatrix &A, const std::vector<double> &b)
{
    std::vector<double> x(b.size(), 0.0);

    while (true)
    {
        for (size_t i = 0; i < b.size(); i++)
        {
            double sum = b[i];
            double diag = 0.0;

            for (size_t k = A.rows[i]; k < A.rows[i + 1]; k++)
            {
                size_t j = A.cols[k];

                if (i == j)
                {
                    diag = A.values[k];
                }
                else
                {
                    sum -= A.values[k] * x[j];
                }
            }
            if (std::abs(diag) < 1e-12)
            {
                throw std::runtime_error("Zero diagonal element at row " + std::to_string(i));
            }
            x[i] = sum / diag;
        }
        double r = norm2(A * x - b);
        if (r < 1e-8)
        {
            return x;
        }
    }
}
