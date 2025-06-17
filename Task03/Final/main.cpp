#include <iostream>
#include "graph_operations.h"

using namespace std;

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы (0 - успех)</returns>
int main() {
    string FileName;
    int K, L;

    cout << "Введите имя файла: ";
    cin >> FileName;
    cout << "Введите номер начального города (K): ";
    cin >> K;
    cout << "Введите количество пересадок (L): ";
    cin >> L;

    /// Получение списка городов
    vector<int> cities = findCities(FileName, K, L);

    /// Вывод результата
    cout << "Результат: ";
    for (int city : cities) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
