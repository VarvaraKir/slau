#include "HouseholderQR.hpp"

HouseholderQR::HouseholderQR(DenseMatrix dm) : A(dm)
{
    computeQR();
}

DenseMatrix &HouseholderQR::GetQ()
{
    return Q;
}

DenseMatrix &HouseholderQR::GetR()
{
    return R;
}

DenseMatrix HouseholderQR::rho(const std::vector<double> v) const
{
    DenseMatrix H = I(v.size());
    return H - (2 * vector_matrix(v, v) / dot(v, v));
}

void HouseholderQR::computeQR()
{
    size_t n = A.GetRows();
    Q = I(n);

    for (size_t k = 0; k < n - 1; k++)
    {
        size_t m = n - k;
        std::vector<double> x(m);
        for (size_t i = 0; i < m; i++)
        {
            x[i] = A(k + i, k);
        }
        double norm = 0.0;
        for (size_t i = 0; i < m; i++)
        {
            norm += x[i] * x[i];
        }
        norm = sqrt(norm);
        if (norm < 1e-14)
            continue;

        std::vector<double> v = x;
        double sign = (x[0] >= 0.0) ? 1.0 : -1.0;
        v[0] += sign * norm;

        for (size_t j = k; j < n; j++)
        {
            std::vector<double> y(m);

            for (size_t i = 0; i < m; i++)
            {
                y[i] = A(k + i, j);
            }
            DenseMatrix Pk = P(v);
            std::vector<double> new_y = Pk * y;

            for (size_t i = 0; i < m; i++)
            {
                A.at(k + i, j) = new_y[i];
            }
        }

        for (size_t j = 0; j < n; j++)
        {
            std::vector<double> y(m);
            for (size_t i = 0; i < m; i++)
            {
                y[i] = Q(k + i, j);
            }
            DenseMatrix Pk = P(v);
            std::vector<double> new_y = Pk * y;

            for (size_t i = 0; i < m; i++)
            {
                Q.at(k + i, j) = y[i];
            }
        }
        R = A;
    }
