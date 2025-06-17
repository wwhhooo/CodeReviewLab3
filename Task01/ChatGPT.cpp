#include <iostream>
#include <map>
#include <string>
#include <locale>

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8")); // Устанавливаем русскую локаль
    std::wcin.imbue(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    std::map<wchar_t, std::wstring> morse = {
        {L'А', L"·−"},   {L'Б', L"−···"}, {L'В', L"·−−"},  {L'Г', L"−−·"},
        {L'Д', L"−··"},  {L'Е', L"·"},    {L'Ж', L"···−"}, {L'З', L"−−··"},
        {L'И', L"··"},   {L'Й', L"·−−−"}, {L'К', L"−·−"},  {L'Л', L"·−··"},
        {L'М', L"−−"},   {L'Н', L"−·"},   {L'О', L"−−−"},  {L'П', L"·−−·"},
        {L'Р', L"·−·"},  {L'С', L"···"},  {L'Т', L"−"},    {L'У', L"··−"},
        {L'Ф', L"··−·"}, {L'Х', L"····"}, {L'Ц', L"−·−·"}, {L'Ч', L"−−−·"},
        {L'Ш', L"−−−−"}, {L'Щ', L"−−·−"}, {L'Ъ', L"−−·−−"}, {L'Ы', L"−·−−"},
        {L'Ь', L"−··−"}, {L'Э', L"··−··"}, {L'Ю', L"··−−"}, {L'Я', L"·−·−"}
    };

    std::wcout << L"Введите сообщение на русском: ";
    std::wstring input;
    std::getline(std::wcin, input);

    std::wcout << L"Сообщение в азбуке Морзе:\n";
    for (wchar_t ch : input) {
        ch = std::towupper(ch); // Приводим к верхнему регистру
        if (morse.count(ch))
            std::wcout << morse[ch] << L" ";
        else if (ch == L' ')
            std::wcout << L" / "; // Пробел — разделитель слов
    }

    std::wcout << std::endl;
    return 0;
}
