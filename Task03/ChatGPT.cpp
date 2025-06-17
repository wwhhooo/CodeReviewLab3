#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

int main() {
    std::ifstream file("FileName.txt");
    if (!file) {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return 1;
    }

    int n;
    file >> n;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            file >> graph[i][j];

    int K, L;
    std::cout << "Введите номер города K (от 1 до " << n << "): ";
    std::cin >> K;
    std::cout << "Введите количество пересадок L: ";
    std::cin >> L;

    K--; // переходим к нумерации с 0

    std::queue<std::pair<int, int>> q; // (текущий город, уровень)
    q.push({K, 0});

    std::set<int> visited_at_level_L;

    while (!q.empty()) {
        auto [city, level] = q.front();
        q.pop();

        if (level == L) {
            visited_at_level_L.insert(city);
            continue; // не продолжаем дальше
        }

        for (int next = 0; next < n; ++next) {
            if (graph[city][next] == 1) {
                q.push({next, level + 1});
            }
        }
    }

    if (visited_at_level_L.empty()) {
        std::cout << -1 << std::endl;
    } else {
        std::vector<int> result(visited_at_level_L.begin(), visited_at_level_L.end());
        std::sort(result.begin(), result.end());
        for (int city : result) {
            std::cout << (city + 1) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
