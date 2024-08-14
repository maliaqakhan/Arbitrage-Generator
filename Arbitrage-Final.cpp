#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

std::vector<std::vector<double>> transform_matrix(std::vector<std::vector<double>>& matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            matrix[i][j] = log(matrix[i][j]);
            std::cout << "For [" << i << "][" << j << "]: " << matrix[i][j] << "\n";
        }
    }
    return matrix;
}

// This method returns true or false based on whether arbitrage exists or not
bool is_arbitrage(std::vector<std::vector<double>>& currencies)
{
    std::vector<std::vector<double>> tm = transform_matrix(currencies);

    // Bellman-Ford algorithm
    int src = 0;
    int n = tm.size(); 
    std::vector<double> min_dist(n, INFINITY);

    min_dist[src] = 0.0;

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                if (min_dist[k] > min_dist[j] + tm[j][k])
                {
                    min_dist[k] = min_dist[j] + tm[j][k];
                }
            }
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < n; ++j)
    {
        for (int k = 0; k < n; ++k)
        {
            if (min_dist[k] > min_dist[j] + tm[j][k])
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::vector<std::vector<double>> currencies = {
        {1, 0.23, 0.25, 16.43, 18.21, 4.94},
        {4.34, 1, 1.11, 71.40, 79.09, 21.44},
        {3.93, 0.90, 1, 64.52, 71.48, 19.37},
        {0.061, 0.014, 0.015, 1, 1.11, 0.30},
        {0.055, 0.013, 0.014, 0.90, 1, 0.27},
        {0.20, 0.047, 0.052, 3.33, 3.69, 1}
    };

    if (is_arbitrage(currencies))
        std::cout << "There exists an arbitrage!" << "\n";
    else
        std::cout << "There does not exist an arbitrage!" << "\n";

    return 0;
}
