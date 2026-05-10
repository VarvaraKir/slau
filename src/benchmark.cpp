// benchmark.cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

#include "CSRMatrix.hpp"
#include "solvers.hpp"
#include "random.cpp"

struct IterationHistory
{
    std::vector<int> iterations;
    std::vector<double> residuals;
    std::vector<double> times; // кумулятивное время в секундах
    std::string method_name;
};

IterationHistory runFixedPoint(const CSRMatrix &A, const std::vector<double> &b,
                               const std::vector<double> &x0, double tau, double tol, int maxIter = 30000)
{
    IterationHistory hist;
    hist.method_name = "FixedPoint_tau_" + std::to_string(tau);

    std::vector<double> x = x0;
    std::vector<double> r = A * x - b;

    hist.iterations.push_back(0);
    hist.residuals.push_back(norm2(r));
    hist.times.push_back(0.0);

    for (int iter = 1; iter <= maxIter; ++iter)
    {
        auto start = std::chrono::high_resolution_clock::now();

        x = x - tau * r;
        r = A * x - b;

        auto end = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(end - start).count();

        hist.iterations.push_back(iter);
        hist.residuals.push_back(norm2(r));
        hist.times.push_back(hist.times.back() + dt);

        if (hist.residuals.back() < tol)
            break;
    }
    return hist;
}

IterationHistory runJacobi(const CSRMatrix &A, const std::vector<double> &b, double tol = 1e-8, int maxIter = 10000)
{
    IterationHistory hist;
    hist.method_name = "Jacobi";

    std::vector<double> x(b.size(), 0.0);

    hist.iterations.push_back(0);
    hist.residuals.push_back(1e10);
    hist.times.push_back(0.0);

    for (int iter = 1; iter <= maxIter; ++iter)
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<double> y = b - solvers::wthD(A, x);
        std::vector<double> x_new(b.size());

        for (size_t i = 0; i < b.size(); ++i)
        {
            x_new[i] = y[i] / A(i, i);
        }

        x = std::move(x_new);

        auto end = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(end - start).count();

        double residual = norm2(A * x - b);

        hist.iterations.push_back(iter);
        hist.residuals.push_back(residual);
        hist.times.push_back(hist.times.back() + dt);

        if (residual < tol)
            break;
    }
    return hist;
}

IterationHistory runGaussSeidel(const CSRMatrix &A, const std::vector<double> &b, double tol = 1e-8, int maxIter = 10000)
{
    IterationHistory hist;
    hist.method_name = "GaussSeidel";

    std::vector<double> x(b.size(), 0.0);

    hist.iterations.push_back(0);
    hist.residuals.push_back(1e10);
    hist.times.push_back(0.0);

    for (int iter = 1; iter <= maxIter; ++iter)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < b.size(); ++i)
        {
            double sum = b[i];
            double diag = 0.0;

            for (size_t k = A.rows[i]; k < A.rows[i + 1]; ++k)
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

            if (std::abs(diag) < 1e-14)
            {
                throw std::runtime_error("Zero diagonal element at row " + std::to_string(i));
            }
            x[i] = sum / diag;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(end - start).count();

        double residual = norm2(A * x - b);

        hist.iterations.push_back(iter);
        hist.residuals.push_back(residual);
        hist.times.push_back(hist.times.back() + dt);

        if (residual < tol)
            break;
    }
    return hist;
}

void saveToCSV(const IterationHistory &hist, const std::string &filename)
{
    std::ofstream file(filename);

    file << "iteration,residual,time_seconds\n";
    for (size_t i = 0; i < hist.iterations.size(); ++i)
    {
        file << hist.iterations[i] << ","
             << std::scientific << std::setprecision(12) << hist.residuals[i] << ","
             << std::fixed << std::setprecision(6) << hist.times[i] << "\n";
    }
}

int main()
{
    unsigned n = 500; // размер матрицы

    CSRMatrix A = Random::getCSRMatrix(n, n, 0.05, -1.0, 1.0, true); // diagonally dominant
    std::vector<double> b = Random::getVector(n, -10.0, 10.0);
    std::vector<double> x0(n, 0.0);

    double tol = 1e-8;
    double tau = 0.01;

    auto histFP = runFixedPoint(A, b, x0, tau, tol);
    auto histJac = runJacobi(A, b, tol);
    auto histGS = runGaussSeidel(A, b, tol);

    saveToCSV(histFP, "fixedpoint_tau_" + std::to_string(tau) + ".csv");
    saveToCSV(histJac, "jacobi.csv");
    saveToCSV(histGS, "gauss_seidel.csv");

    return 0;
}