#include <iostream>
#include <map>
#include "converter.h"

using namespace std;

int main() {
    locale::global(locale("en_US.UTF-8"));
    cout.imbue(locale());

    map<string, string> morse = {
        {"А", ".-"}, {"Б", "-..."}, {"В", ".--"}, {"Г", "--."},
        {"Д", "-.."}, {"Е", "."}, {"Ж", "...-"}, {"З", "--.."},
        {"И", ".."}, {"Й", ".---"}, {"К", "-.-"}, {"Л", ".-.."},
        {"М", "--"}, {"Н", "-"}, {"О", "---"}, {"П", ".--."},
        {"Р", ".-."}, {"С", "..."}, {"Т", "-"}, {"У", "..-"},
        {"Ф", "..-."}, {"Х", "...."}, {"Ц", "-.-."}, {"Ч", "---."},
        {"Ш", "----"}, {"Щ", "--.-"}, {"Ъ", "--.--"}, {"Ы", "-.--"},
        {"Ь", "-..-"}, {"Э", "..-.."}, {"Ю", "..--"}, {"Я", ".-.-"},
        {" ", "/"}
    };

    cout << "Введите сообщение на русском: ";
    string input_utf8;
    getline(cin, input_utf8);

    wstring input = utf8_to_wstring(input_utf8);

    if (input.empty()) {
        cout << "Ошибка: пустая строка!" << endl;
        return 1;
    }

    cout << "Результат перевода в азбуку Морзе:\n";
    bool hasErrors = false;
    string result;

    for (size_t i = 0; i < input.size(); ++i) {
        wchar_t wch = towupper(input[i]);
        string char_utf8 = wstring_to_utf8(wstring(1, wch));

        if (wch == L' ') {
            result += "/ ";
        }
        else if (morse.count(char_utf8)) {
            result += morse[char_utf8] + " ";
        }
        else {
            if (wch != L'\n' && wch != L'\r' && wch != L'\t') {
                result += "? ";
                hasErrors = true;
            }
        }
    }

    cout << result << endl;
    if (hasErrors) {
        cout << "Внимание: не все символы распознаны" << endl;
    }

    return 0;
}
