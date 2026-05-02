#include <iostream>
#include "DenseMatrix.hpp"

#include <vector>
#include <queue>

size_t shortestDistance(const std::vector<std::vector<size_t>> &graph, size_t start, size_t end)
{
    if (start == end)
        return 0;

    size_t n = graph.size();
    std::vector<bool> visited(n, false);
    std::vector<size_t> dist(n, 0);

    std::queue<size_t> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        size_t node = q.front();
        q.pop();

        for (size_t neighbor : graph[node])
        {
            if (neighbor == node)
                continue;

            if ((neighbor <= node || neighbor == end) && !visited[neighbor])
            {
                visited[neighbor] = true;
                dist[neighbor] = dist[node] + 1;

                if (neighbor == end)
                {
                    return dist[neighbor] > 0 ? dist[neighbor] - 1 : 0;
                }

                q.push(neighbor);
            }
        }
    }

    return n - 1;
}

int main()
{
    size_t n = 3;
    size_t m = 3;
    DenseMatrix dense = {{2, 1, 1,             (2*10^-32, 10^-301
                          0, 2, 0,             10^-301, 10^-32)
                          2, 0, 4},
                         m};

    std::vector<std::vector<size_t>> links(5);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (abs(dense(i, j)) > 0)
            {
                links[i].push_back(j);
            }
        }
    }

    DenseMatrix level(std::vector<double>(n * m), m);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            level.at(i, j) = shortestDistance(links, i, j);
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            std::cout << level(i, j) << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}