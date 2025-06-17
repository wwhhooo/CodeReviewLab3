#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream file("FileName.txt");
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    int n, K, L;
    file >> n; // Читаем количество городов

    vector<vector<int>> m(n, vector<int>(n)); // Матрица смежности

    // Читаем матрицу смежности
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> m[i][j];
        }
    }

    file.close();

    cout << "Введите номер города K: ";
    cin >> K;
    cout << "Введите количество пересадок L: ";
    cin >> L;

    K--; // Преобразуем в индекс (начинается с 0)

    vector<int> distances(n, -1); // Инициализируем расстояния как -1 (недостижимо)
    queue<int> q;
    q.push(K);
    distances[K] = 0; // Расстояние до самого себя равно 0

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (m[current][neighbor] == 1 && distances[neighbor] == -1) {
                distances[neighbor] = distances[current] + 1;
                q.push(neighbor);
            }
        }
    }

    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (distances[i] == L + 1) { // L пересадок означает L+1 шагов
            cout << i + 1 << " ";
            found = true;
        }
    }

    if (!found) {
        cout << -1;
    }

    return 0;
}
