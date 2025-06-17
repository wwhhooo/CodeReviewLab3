#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

struct Node {
    int val; // -1: +, -2: -, -3: *, -4: /
    Node* left;
    Node* right;

    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Прочитать следующее значение из потока
bool nextToken(std::istringstream& iss, std::string& token) {
    //return iss >> token; //FIXME Ошибка: iss >> token возвращает istream&, а не bool
    if (iss >> token) {
        return true;
    }
    return false;
}

// Построение дерева из префиксной записи
Node* buildTree(std::istringstream& iss) {
    std::string token;
    if (!nextToken(iss, token))
        return nullptr;

    Node* node = nullptr;
    if (token == "+")      node = new Node(-1);
    else if (token == "-") node = new Node(-2);
    else if (token == "*") node = new Node(-3);
    else if (token == "/") node = new Node(-4);
    else                   node = new Node(std::stoi(token));

    if (node->val < 0) { // операция => рекурсивно строим поддеревья
        node->left = buildTree(iss);
        node->right = buildTree(iss);
    }

    return node;
}

// Вычисляет значение поддерева и удаляет его
int evaluateAndReplace(Node*& node) {
    if (!node) return 0;

    if (node->val >= 0)
        return node->val;

    int left = evaluateAndReplace(node->left);
    int right = evaluateAndReplace(node->right);
    int result = 0;

    switch (node->val) {
        case -1: result = left + right; break;
        case -2: result = left - right; break;
        case -3: result = left * right; break;
        case -4: result = right != 0 ? left / right : 0; break;
    }

    if (node->val == -1 || node->val == -2) {
        delete node->left;
        delete node->right;
        node->left = nullptr;
        node->right = nullptr;
        node->val = result;
    }

    return result;
}

// Постфиксный вывод для проверки (необязательно)
void printTree(Node* node) {
    if (!node) return;
    printTree(node->left);
    printTree(node->right);
    if (node->val < 0)
        std::cout << "(" << node->val << ") ";
    else
        std::cout << node->val << " ";
}

int main() {
    std::ifstream file("filename.txt"); //FIXME filename.txt
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::string expression;
    std::getline(file, expression);
    std::istringstream iss(expression);

    Node* root = buildTree(iss);

    evaluateAndReplace(root);

    std::cout << "Указатель на корень дерева: " << root << std::endl;

    std::cout << "Постфиксный обход дерева (для проверки): ";
    printTree(root);
    std::cout << std::endl;

    return 0;
}
