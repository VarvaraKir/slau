#include <iostream>
#include <vector>
// #include "matrix.h"

int main()
{
    size_t n = 4;
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(n);
    std::vector<double> d(n);
    std::vector<double> p(n);
    std::vector<double> q(n);
    std::vector<double> x(n);

    for (size_t i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> b[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> c[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> d[i];
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        if (i == 0)
        {
            p[i] = -c[i] / b[i];
            q[i] = d[i] / b[i];
        }
        else
        {
            p[i] = -c[i] / (a[i] * p[i - 1] + b[i]);
            q[i] = (d[i] - a[i] * q[i - 1]) / (a[i] * p[i - 1] + b[i]);
        }
    }
    x[n - 1] = (d[n - 1] - a[n - 1] * q[n - 2]) / (a[n - 1] * p[n - 2] + b[n - 1]);
    for (size_t i = n - 1; i > 0; i--)
    {
        x[i - 1] = p[i - 1] * x[i] + q[i - 1];
    };

    for (size_t i = 0; i < n; i++)
    {
        std::cout << x[i] << ' ';
    }
    return 0;
}