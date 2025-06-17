#include "tree_operations.h"
#include <fstream>
#include <stdexcept>

using namespace std;

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

vector<string> readPrefixExpression(const string& filename) {
    ifstream file(filename);
    vector<string> tokens;
    string token;

    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    while (file >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
