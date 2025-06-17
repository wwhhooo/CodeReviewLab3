#include <iostream>
#include <locale>
#include "morse_converter.h"

using namespace std;

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код завершения программы (0 - успех)</returns>
int main() {
    // Установка локали для поддержки UTF-8
    locale::global(locale("en_US.UTF-8"));
    cout.imbue(locale());

    // Ввод сообщения от пользователя
    cout << "Введите сообщение на русском: ";
    string input_utf8;
    getline(cin, input_utf8);

    // Проверка на пустую строку
    if (input_utf8.empty()) {
        cout << "Ошибка: пустая строка!" << endl;
        return 1;
    }

    // Конвертация в Morse код
    bool hasErrors = false;
    string result = convert_to_morse(input_utf8, hasErrors);

    // Вывод результата
    cout << "Результат перевода в азбуку Морзе:\n" << result << endl;
    
    // Вывод предупреждения о нераспознанных символах
    if (hasErrors) {
        cout << "Внимание: не все символы распознаны" << endl;
    }

    return 0;
}
