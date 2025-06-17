#pragma once

/// <summary>
/// Структура, представляющая узел бинарного дерева
/// </summary>
struct Node {
    int value;      ///< Значение узла
    Node* left;     ///< Указатель на левое поддерево
    Node* right;    ///< Указатель на правое поддерево

    /// <summary>
    /// Конструктор узла
    /// </summary>
    /// <param name="val">Значение узла</param>
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};
