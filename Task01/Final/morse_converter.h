#pragma once
#include <string>
#include <map>
#include <locale>

/// <summary>
/// Конвертирует строку UTF-8 в широкую строку (wstring)
/// </summary>
/// <param name="utf8">Входная строка в UTF-8</param>
/// <returns>Преобразованная широкая строка</returns>
std::wstring utf8_to_wstring(const std::string& utf8);

/// <summary>
/// Конвертирует широкую строку (wstring) в строку UTF-8
/// </summary>
/// <param name="str">Входная широкая строка</param>
/// <returns>Преобразованная строка в UTF-8</returns>
std::string wstring_to_utf8(const std::wstring& str);

/// <summary>
/// Возвращает карту соответствия русских букв и Morse кодов
/// </summary>
/// <returns>Константную ссылку на map с соответствиями</returns>
const std::map<std::string, std::string>& get_morse_map();

/// <summary>
/// Конвертирует русский текст в Morse код
/// </summary>
/// <param name="input">Входная строка в UTF-8</param>
/// <param name="hasErrors">Флаг наличия ошибок конвертации</param>
/// <returns>Строку с Morse кодом</returns>
std::string convert_to_morse(const std::string& input, bool& hasErrors);
