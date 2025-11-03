#include "Percussion.h"
#include "Utils.h"
#include <iostream>

Percussion::Percussion()
    : type(nullptr), name(nullptr), cost(0.0), count(0), owner(nullptr)
{
    std::cout << "Percussion: конструктор по умолчанию\n";
    type = new char[1]; type[0] = '\0';
    name = new char[1]; name[0] = '\0';
    owner = new char[1]; owner[0] = '\0';
}

Percussion::Percussion(const char* t, const char* n, double c, int cnt, const char* o)
    : type(nullptr), name(nullptr), cost(c), count(cnt), owner(nullptr)
{
    std::cout << "Percussion: конструктор с параметрами\n";
    SetType(t); SetName(n); SetOwner(o);
}

Percussion::Percussion(const Percussion& other)
    : type(nullptr), name(nullptr), cost(other.cost), count(other.count), owner(nullptr)
{
    std::cout << "Percussion: конструктор копирования\n";
    SetType(other.type);
    SetName(other.name);
    SetOwner(other.owner);
}

Percussion::~Percussion() {
    std::cout << "Percussion: деструктор\n";
    delete[] type; delete[] name; delete[] owner;
}

void Percussion::SetType(const char* t) {
    delete[] type;
    if (!t) { type = new char[1]; type[0] = '\0'; return; }
    size_t l = std::strlen(t);
    type = new char[l+1]; std::strcpy(type, t);
}

void Percussion::SetName(const char* n) {
    delete[] name;
    if (!n) { name = new char[1]; name[0] = '\0'; return; }
    size_t l = std::strlen(n);
    name = new char[l+1]; std::strcpy(name, n);
}

void Percussion::SetOwner(const char* o) {
    delete[] owner;
    if (!o) { owner = new char[1]; owner[0] = '\0'; return; }
    size_t l = std::strlen(o);
    owner = new char[l+1]; std::strcpy(owner, o);
}

void Percussion::Show() const {
    std::cout << "[Ударный] Тип: " << type << ", Название: " << name
              << ", Стоимость: " << cost << ", Кол-во: " << count
              << ", Владелец: " << owner << "\n";
}

void Percussion::Edit() {
    std::cout << "Ввод данных для ударного инструмента:\n";
    std::cout << "Тип: "; char* t = ReadLineAlloc(); SetType(t); delete[] t;
    std::cout << "Название: "; char* n = ReadLineAlloc(); SetName(n); delete[] n;
    std::cout << "Стоимость: "; double c; if(!(std::cin >> c)) throw MyException("Неверный ввод стоимости"); SetCost(c);
    std::cout << "Кол-во: "; int cnt; if(!(std::cin >> cnt)) throw MyException("Неверный ввод количества"); SetCount(cnt);
    std::cin.ignore();
    std::cout << "ФИО владельца: "; char* o = ReadLineAlloc(); SetOwner(o); delete[] o;
}

void Percussion::SaveToFile(std::ofstream& fout) const {
    int kind = 1; // 1 = Percussion
    fout.write(reinterpret_cast<const char*>(&kind), sizeof(kind));
    WriteStringBin(fout, type);
    WriteStringBin(fout, name);
    fout.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
    fout.write(reinterpret_cast<const char*>(&count), sizeof(count));
    WriteStringBin(fout, owner);
}

void Percussion::LoadFromFile(std::ifstream& fin) {
    // предполагается, что тип уже прочитан внешне
    delete[] type; delete[] name; delete[] owner;
    type = ReadStringBin(fin);
    name = ReadStringBin(fin);
    fin.read(reinterpret_cast<char*>(&cost), sizeof(cost));
    fin.read(reinterpret_cast<char*>(&count), sizeof(count));
    owner = ReadStringBin(fin);
}
