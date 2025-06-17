#include "graph_operations.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<int> findCities(const string& FileName, int K, int L) {
    ifstream file(FileName);
    vector<int> result;

    /// Проверка на пустоту файла
    if (file.peek() == ifstream::traits_type::eof()) {
        result.push_back(-1);
        return result;
    }

    int n;
    file >> n;

    /// Проверка корректности количества городов
    if (n <= 0 || n > 25) {
        result.push_back(-1);
        return result;
    }

    /// Проверка корректности K
    if (K < 1 || K > n) {
        result.push_back(-1);
        return result;
    }

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> matrix[i][j])) {
                /// Проверка на корректность данных матрицы
                result.push_back(-1);
                return result;
            }
            /// Проверка что значения только 0 или 1
            if (matrix[i][j] != 0 && matrix[i][j] != 1) {
                result.push_back(-1);
                return result;
            }
        }
    }

    /// BFS для поиска городов на расстоянии L пересадок
    queue<pair<int, int>> q; /// {город, текущее количество пересадок}
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    set<int> cities;

    q.push({K-1, 0});
    visited[K-1] = true;
    distance[K-1] = 0;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        int city = current.first;
        int steps = current.second;

        if (steps == L) {
            cities.insert(city + 1); /// +1 так как нумерация с 1
            continue;
        }

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (matrix[city][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = steps + 1;
                q.push({neighbor, steps + 1});
            }
        }
    }

    if (cities.empty()) {
        result.push_back(-1);
    } else {
        result.assign(cities.begin(), cities.end());
    }

    return result;
}
