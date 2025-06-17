#include <iostream>
#include "tree_operations.h"

using namespace std;

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы</returns>
int main() {
    string filename = "filename.txt"; // Имя файла с выражением

    try {
        vector<string> tokens = readPrefixExpression(filename);

        int index = 0;
        Node* root = buildTreeFromPrefix(tokens, index);

        cout << "Исходное дерево построено" << endl;

        root = transformTree(root);

        cout << "Указатель на корень преобразованного дерева: " << root << endl;
        if (root) {
            cout << "Значение корня: " << root->value << endl;
        } else {
            cout << "Файл пуст" << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
