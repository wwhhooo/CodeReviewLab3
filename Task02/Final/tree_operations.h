#pragma once
#include <vector>
#include <string>
#include "node.h"

/// <summary>
/// Строит бинарное дерево из префиксного выражения
/// </summary>
/// <param name="tokens">Вектор токенов префиксного выражения</param>
/// <param name="index">Текущий индекс в векторе токенов</param>
/// <returns>Указатель на корень построенного дерева</returns>
Node* buildTreeFromPrefix(const std::vector<std::string>& tokens, int& index);

/// <summary>
/// Вычисляет значение поддерева
/// </summary>
/// <param name="root">Корень поддерева</param>
/// <returns>Результат вычисления</returns>
int evaluate(Node* root);

/// <summary>
/// Преобразует дерево, заменяя операции + и - на их значения
/// </summary>
/// <param name="root">Корень дерева для преобразования</param>
/// <returns>Указатель на корень преобразованного дерева</returns>
Node* transformTree(Node* root);

/// <summary>
/// Читает префиксное выражение из файла
/// </summary>
/// <param name="filename">Имя файла для чтения</param>
/// <returns>Вектор строк с токенами выражения</returns>
std::vector<std::string> readPrefixExpression(const std::string& filename);
