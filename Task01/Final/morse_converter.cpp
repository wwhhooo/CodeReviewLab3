#include "morse_converter.h"
#include <codecvt>
#include <locale>
#include <cwctype>

using namespace std;

wstring utf8_to_wstring(const string& utf8) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(utf8);
}

string wstring_to_utf8(const wstring& str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(str);
}

const map<string, string>& get_morse_map() {
    static const map<string, string> morse = {
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
    return morse;
}

string convert_to_morse(const string& input, bool& hasErrors) {
    wstring wide_input = utf8_to_wstring(input);
    const auto& morse = get_morse_map();
    string result;
    hasErrors = false;

    for (size_t i = 0; i < wide_input.size(); ++i) {
        wchar_t wch = towupper(wide_input[i]);
        string char_utf8 = wstring_to_utf8(wstring(1, wch));

        if (wch == L' ') {
            result += "/ ";
        }
        else if (morse.count(char_utf8)) {
            result += morse.at(char_utf8) + " ";
        }
        else {
            if (wch != L'\n' && wch != L'\r' && wch != L'\t') {
                result += "? ";
                hasErrors = true;
            }
        }
    }

    return result;
}
