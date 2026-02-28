#include <CSRMatrix.hpp>

CSRMatrix::CSRMatrix() : N(0), M(0), values({}), cols({}), rows({}) {}
CSRMatrix::CSRMatrix(const std::vector<double> &values, std::vector<double> &cols, std::vector<double> &rows) : N(cols.size()), M(rows.size() - 1), values(values), cols(cols), rows(rows) {}

double CSRMatrix::operator()(size_t i, size_t j) const
{
    for (size_t k = rows[i]; k < rows[i + 1]; k++)
    {
        if (j == cols[k])
        {
            return values[k];
        }
    }
    return 0;
}

std::vector<double> CSRMatrix::operator*(const std::vector<double> &v) const
{
    std::vector<double> y(cols);

    for (size_t i = 0; i < M; i++)
    {
        for (size_t k = rows[i]; k < rows[i + 1]; k++)
        {
            y[i] += values[k] * v[cols[k]];
        }
    }
    return y;
}