// random.cpp
#include "CSRMatrix.hpp"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

class Random
{
private:
    static std::mt19937& engine()
    {
        static std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
        return eng;
    }

public:
    static double getDouble(double min = 0.0, double max = 1.0)
    {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(engine());
    }

    static unsigned getUnsigned(unsigned min = 0, unsigned max = 4294967295U)
    {
        std::uniform_int_distribution<unsigned> dist(min, max);
        return dist(engine());
    }

    static CSRMatrix getCSRMatrix(unsigned rows, unsigned cols = 0,
                                  double density = 0.05,
                                  double min_val = -1.0,
                                  double max_val = 1.0,
                                  bool diagonallyDominant = true)
    {
        if (cols == 0) cols = rows;  // квадратная матрица по умолчанию

        std::vector<std::vector<std::pair<unsigned, double>>> temp(rows);

        for (unsigned i = 0; i < rows; ++i)
        {
            double off_diag_sum = 0.0;

            for (unsigned j = 0; j < cols; ++j)
            {
                bool is_diag = (i == j);
                if (is_diag || getDouble(0.0, 1.0) < density)
                {
                    double val = getDouble(min_val, max_val);

                    if (is_diag && diagonallyDominant)
                        val = std::abs(val) + 1.0 + off_diag_sum * 1.5;

                    temp[i].emplace_back(j, val);
                    if (!is_diag) off_diag_sum += std::abs(val);
                }
            }
            std::sort(temp[i].begin(), temp[i].end());
        }

        // Сборка CSR
        std::vector<double> values;
        std::vector<double> col_idx;
        std::vector<double> row_ptr(rows + 1, 0);

        size_t nnz = 0;
        for (unsigned i = 0; i < rows; ++i)
        {
            row_ptr[i] = nnz;
            for (const auto& p : temp[i])
            {
                col_idx.push_back(p.first);
                values.push_back(p.second);
                nnz++;
            }
        }
        row_ptr[rows] = nnz;

        return CSRMatrix(values, col_idx, row_ptr);
    }

    static std::vector<double> getVector(unsigned size, double min_val = -10.0, double max_val = 10.0)
    {
        std::vector<double> v(size);
        for (auto& x : v)
            x = getDouble(min_val, max_val);
        return v;
    }
};