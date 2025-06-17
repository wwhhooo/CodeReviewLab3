#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <memory>

using namespace std;

// Структура узла дерева
struct TreeNode {
    int value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева из префиксного выражения
shared_ptr<TreeNode> buildTree(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) {
        return nullptr;
    }

    string token = tokens[index++];
    int value;

    if (token == "+") {
        value = -1;
    } else if (token == "-") {
        value = -2;
    } else if (token == "*") {
        value = -3;
    } else if (token == "/") {
        value = -4;
    } else {
        value = stoi(token);
    }

    auto node = make_shared<TreeNode>(value);

    if (value < 0) { // Если это оператор
        node->left = buildTree(tokens, index);
        node->right = buildTree(tokens, index);
    }

    return node;
}

// Функция для вычисления значения поддерева
int evaluateSubtree(shared_ptr<TreeNode> node) {
    if (node == nullptr) {
        return 0;
    }

    if (node->value >= 0) { // Если это операнд
        return node->value;
    }

    int leftValue = evaluateSubtree(node->left);
    int rightValue = evaluateSubtree(node->right);

    switch (node->value) {
        case -1: // Сложение
            return leftValue + rightValue;
        case -2: // Вычитание
            return leftValue - rightValue;
        case -3: // Умножение
            return leftValue * rightValue;
        case -4: // Деление
            return leftValue / rightValue;
        default:
            return 0;
    }
}

// Функция для преобразования дерева
shared_ptr<TreeNode> transformTree(shared_ptr<TreeNode> node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->value == -1 || node->value == -2) { // Если это сложение или вычитание
        int value = evaluateSubtree(node);
        return make_shared<TreeNode>(value);
    }

    node->left = transformTree(node->left);
    node->right = transformTree(node->right);

    return node;
}

// Функция для вывода дерева (для проверки)
void printTree(shared_ptr<TreeNode> node) {
    if (node == nullptr) {
        return;
    }

    cout << node->value << " ";
    printTree(node->left);
    printTree(node->right);
}

int main() {
    ifstream file("filename.txt");
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    string line;
    getline(file, line);
    file.close();

    istringstream iss(line);
    vector<string> tokens;
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    int index = 0;
    shared_ptr<TreeNode> root = buildTree(tokens, index);

    root = transformTree(root);

    cout << "Указатель на корень полученного дерева: " << root << endl;
    if (root) {
        cout << "Значение корня: " << root->value << endl;
    }

    return 0;
}
