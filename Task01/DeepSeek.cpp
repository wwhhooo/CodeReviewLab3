#include <iostream>
#include <map>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;

wstring utf8_to_wstring(const string& str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

string wstring_to_utf8(const wstring& str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(str);
}

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
    string result;

    for (wchar_t wch : input) {
        wch = towupper(wch);
        string char_utf8 = wstring_to_utf8(wstring(1, wch));

        if (wch == L' ') {
            result += "/ ";
        }
        else if (morse.count(char_utf8)) {
            result += morse[char_utf8] + " ";
        }
    }

    cout << "Результат перевода:\n" << result << endl;
    return 0;
}
