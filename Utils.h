#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include "MyException.h"
#include <limits>

// Вспомогательные функции для работы со C-строками и бинарным вводом/выводом
inline char* ReadLineAlloc() {
    const int BUF = 1024;
    char buffer[BUF];

    if (std::cin.peek() == '\n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (!std::cin.getline(buffer, BUF)) {
        // если предыдущий ввод оставил символ \n
        std::cin.clear();
        std::cin.getline(buffer, BUF);
    }
    size_t len = std::strlen(buffer);
    char* res = new char[len + 1];
    std::strcpy(res, buffer);
    return res;
}

inline void WriteStringBin(std::ofstream& fout, const char* s) {
    if (!s) {
        int len = 0; fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        return;
    }
    int len = static_cast<int>(std::strlen(s));
    fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
    fout.write(s, len);
}

inline char* ReadStringBin(std::ifstream& fin) {
    int len = 0;
    fin.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!fin) throw MyException("Ошибка чтения строки из файла");
    if (len <= 0) {
        char* s = new char[1]; s[0] = '\0';
        return s;
    }
    char* buf = new char[len + 1];
    fin.read(buf, len);
    if (!fin) { delete[] buf; throw MyException("Ошибка чтения содержимого строки"); }
    buf[len] = '\0';
    return buf;
}
