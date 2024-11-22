#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> computeLPSArray(const std::string& pattern);
std::vector<int> KMPSearch(const std::string& text, const std::string& pattern);

int main() {
    setlocale(LC_ALL, "RU");
    std::string pattern;
    std::string filename;

    std::cout << "Введите шаблон для поиска: ";
    std::cin >> pattern;

    std::cout << "Введите имя файла: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::vector<int> occurrences = KMPSearch(text, pattern);

    if (occurrences.empty()) {
        std::cout << "Шаблон не найден." << std::endl;
    }
    else {
        std::cout << "Шаблон найден в следующих позициях: ";
        for (int pos : occurrences) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

std::vector<int> computeLPSArray(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> lps(m, 0);
    int length = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0) {
                length = lps[length - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

std::vector<int> KMPSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> lps = computeLPSArray(pattern);
    int n = text.length();
    int m = pattern.length();
    std::vector<int> occurrences;
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    return occurrences;
}