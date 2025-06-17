#pragma once
#include <vector>
#include <string>

/// <summary>
/// Находит города, достижимые из начального города за L пересадок
/// </summary>
/// <param name="FileName">Имя файла с матрицей смежности</param>
/// <param name="K">Номер начального города (1..N)</param>
/// <param name="L">Требуемое количество пересадок</param>
/// <returns>
/// Вектор с номерами городов (на 1 больше индексов),
/// или вектор с -1 в случае ошибки
/// </returns>
std::vector<int> findCities(const std::string& FileName, int K, int L);
