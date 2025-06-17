#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева из префиксного выражения
Node* buildTreeFromPrefix(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) return nullptr;

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
        return new Node(value);
    }

    Node* node = new Node(value);
    node->left = buildTreeFromPrefix(tokens, index);
    node->right = buildTreeFromPrefix(tokens, index);
    return node;
}

// Функция для вычисления значения поддерева
int evaluate(Node* root) {
    if (!root) return 0;
    if (root->value >= 0) return root->value;

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    switch (root->value) {
        case -1: return leftVal + rightVal;
        case -2: return leftVal - rightVal;
        case -3: return leftVal * rightVal;
        case -4: return leftVal / rightVal;
        default: return 0;
    }
}

// Функция для преобразования дерева (заменяет + и - на их значения)
Node* transformTree(Node* root) {
    if (!root) return nullptr;

    if (root->value == -1 || root->value == -2) {
        int val = evaluate(root);
        return new Node(val);
    }

    root->left = transformTree(root->left);
    root->right = transformTree(root->right);
    return root;
}

// Функция для чтения файла и получения префиксного выражения
vector<string> readPrefixExpression(const string& filename) {
    ifstream file(filename);
    vector<string> tokens;
    string token;

    while (file >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int main() {
    string filename = "filename.txt"; // Имя файла с выражением
    vector<string> tokens = readPrefixExpression(filename);

    int index = 0;
    Node* root = buildTreeFromPrefix(tokens, index);

    cout << "Исходное дерево построено" << endl;

    root = transformTree(root);

    cout << "Указатель на корень преобразованного дерева: " << root << endl;
    if (root) {
        cout << "Значение корня: " << root->value << endl;
    }

    return 0;
}
