#include "tools.hpp"
#include <cmath>

DenseMatrix I(size_t n)
{
    std::vector<double> data(n * n);
    for (size_t i = 0; i < n; i++)
    {
        data[i + i * n] = 1;
    }
    return DenseMatrix(data, n);
}

DenseMatrix operator*(double a, const DenseMatrix& mat)
{
    std::vector<double> data(mat.GetData());
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = data[i] * a;
    }
    return DenseMatrix(data, mat.GetCols());
}

DenseMatrix operator*(const DenseMatrix& mat, double a)
{
    return a * mat;
}

DenseMatrix operator/(const DenseMatrix& mat, double a)
{
    std::vector<double> data(mat.GetData());
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = data[i] / a;
    }
    return DenseMatrix(data, mat.GetCols());
}

DenseMatrix operator-(const DenseMatrix& A, const DenseMatrix& B)
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
           data[i*v.size()+j] = v[i] * v_T[j];
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
