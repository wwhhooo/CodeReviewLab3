#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

vector<int> findCities(const string& fileName, int K, int L) {
    ifstream file(fileName);
    if (!file.is_open()) {
        return {-1};
    }

    int n;
    file >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }

    // Проверка корректности ввода
    if (K < 1 || K > n) {
        return {-1};
    }

    // Нумерация городов с 0 внутри программы
    int start = K - 1;
    vector<int> distances(n, -1);
    distances[start] = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (matrix[current][neighbor] == 1 && distances[neighbor] == -1) {
                distances[neighbor] = distances[current] + 1;
                q.push(neighbor);
            }
        }
    }

    set<int> result;
    for (int i = 0; i < n; ++i) {
        if (distances[i] == L) {
            result.insert(i + 1); // Возвращаем нумерацию с 1
        }
    }

    if (result.empty()) {
        return {-1};
    }

    return vector<int>(result.begin(), result.end());
}

int main() {
    string fileName = "FileName.txt"; // Имя файла с матрицей смежности
    int K, L;
    cout << "Введите номер города K (1..n): ";
    cin >> K;
    cout << "Введите количество пересадок L: ";
    cin >> L;

    vector<int> cities = findCities(fileName, K, L);

    cout << "Города, достижимые за " << L << " пересадок из города " << K << ": ";
    for (int city : cities) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
