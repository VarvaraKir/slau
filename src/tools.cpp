#include "tools.hpp"

DenseMatrix I(size_t n)
{
    std::vector<double> data(n * n);
    for (size_t i = 0; i < n; i++)
    {
        data[i + i * n] = 1;
    }
    return DenseMatrix(data, n);
}

DenseMatrix transpose(const DenseMatrix &A)
{
    size_t rows = A.GetRows();
    size_t cols = A.GetCols();

    std::vector<double> data(rows * cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            data[j * rows + i] = A(i, j);
        }
    }
    return DenseMatrix(data, rows);
}

DenseMatrix operator*(double a, const DenseMatrix &A)
{
    std::vector<double> data(A.GetData());
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = data[i] * a;
    }
    return DenseMatrix(data, A.GetCols());
}

DenseMatrix operator*(const DenseMatrix &A, double a)
{
    return A * a;
}

DenseMatrix operator/(const DenseMatrix &mat, double a)
{
    std::vector<double> data(mat.GetData());
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = data[i] / a;
    }
    return DenseMatrix(data, mat.GetCols());
}

DenseMatrix operator-(const DenseMatrix &A, const DenseMatrix &B)
{
    std::vector<double> data(A.GetData().size());
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = A.GetData()[i] - B.GetData()[i];
    }
    return DenseMatrix(data, A.GetCols());
}

DenseMatrix vector_matrix(const std::vector<double> &v, const std::vector<double> &v_T)
{
    std::vector<double> data(v.size() * v.size());
    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = 0; j < v_T.size(); j++)
        {
            data[i * v.size() + j] = v[i] * v_T[j];
        }
    }
    return DenseMatrix(data, v.size());
}
std::vector<double> operator+(const std::vector<double> &v, const std::vector<double> &x)
{
    std::vector<double> y(v.size());

    for (size_t i = 0; i < v.size(); i++)
    {
        y[i] = v[i] + x[i];
    }
    return y;
}

double dot(const std::vector<double> &v, const std::vector<double> &x)
{
    double s = 0;
    for (size_t i = 0; i < v.size(); i++)
    {
        s += v[i] * x[i];
    }
    return s;
}

std::vector<double> operator*(const std::vector<double> &v, double a)
{
    std::vector<double> y(v.size());

    for (size_t i = 0; i < v.size(); i++)
    {
        y[i] = v[i] * a;
    }
    return y;
}

std::vector<double> operator*(double a, const std::vector<double> &v)
{
    std::vector<double> y(v.size());

    for (size_t i = 0; i < v.size(); i++)
    {
        y[i] = a * v[i];
    }
    return y;
}

std::vector<double> operator-(const std::vector<double> &v, const std::vector<double> &x)
{
    std::vector<double> y(v.size());

    for (size_t i = 0; i < v.size(); i++)
    {
        y[i] = v[i] - x[i];
    }
    return y;
}

bool operator==(const std::vector<double> &v, const std::vector<double> &x)
{
    return (norm2(v - x) < 1e-6);
}

double norm2(const std::vector<double> &v)
{
    return sqrt(dot(v, v));
}

std::vector<double> normalize(const std::vector<double> &v)
{
    double n = norm2(v);
    if (n > 0)
    {
        return v * (1.0 / n);
    }
    return v;
}

std::ostream &operator<<(std::ostream &os, const std::vector<double> &vec)
{
    double eps = 1e-100, el;

    for (unsigned i = 0; i < vec.size(); i++)
    {
        el = fabs(vec[i]) > eps ? vec[i] : 0;
        os << el << ' ';
    }

    return os;
}
