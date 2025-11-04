#include "StringInstrument.h"
#include "Utils.h"
#include <iostream>

StringInstrument::StringInstrument()
    : name(nullptr), owner(nullptr), manufacturer(nullptr), cost(0.0), count(0), description(nullptr)
{
    std::cout << "StringInstrument: конструктор по умолчанию\n";
    name = new char[1]; name[0] = '\0';
    owner = new char[1]; owner[0] = '\0';
    manufacturer = new char[1]; manufacturer[0] = '\0';
    description = new char[1]; description[0] = '\0';
}

StringInstrument::StringInstrument(const char* n, const char* o, const char* m, double c, int cnt, const char* d)
    : name(nullptr), owner(nullptr), manufacturer(nullptr), cost(c), count(cnt), description(nullptr)
{
    std::cout << "StringInstrument: конструктор с параметрами\n";
    SetName(n); SetOwner(o); SetManufacturer(m); SetDescription(d);
}

StringInstrument::StringInstrument(const StringInstrument& other)
    : name(nullptr), owner(nullptr), manufacturer(nullptr), cost(other.cost), count(other.count), description(nullptr)
{
    std::cout << "StringInstrument: конструктор копирования\n";
    SetName(other.name);
    SetOwner(other.owner);
    SetManufacturer(other.manufacturer);
    SetDescription(other.description);
}

StringInstrument::~StringInstrument() {
    std::cout << "StringInstrument: деструктор\n";
    delete[] name; delete[] owner; delete[] manufacturer; delete[] description;
}

void StringInstrument::SetName(const char* n) {
    delete[] name;
    if (!n) { name = new char[1]; name[0] = '\0'; return; }
    size_t l = std::strlen(n);
    name = new char[l+1]; std::strcpy(name, n);
}

void StringInstrument::SetOwner(const char* o) {
    delete[] owner;
    if (!o) { owner = new char[1]; owner[0] = '\0'; return; }
    size_t l = std::strlen(o);
    owner = new char[l+1]; std::strcpy(owner, o);
}

void StringInstrument::SetManufacturer(const char* m) {
    delete[] manufacturer;
    if (!m) { manufacturer = new char[1]; manufacturer[0] = '\0'; return; }
    size_t l = std::strlen(m);
    manufacturer = new char[l+1]; std::strcpy(manufacturer, m);
}

void StringInstrument::SetDescription(const char* d) {
    delete[] description;
    if (!d) { description = new char[1]; description[0] = '\0'; return; }
    size_t l = std::strlen(d);
    description = new char[l+1]; std::strcpy(description, d);
}

void StringInstrument::Show() const {
    std::cout << "[Струнный] Название: " << name << ", Владелец: " << owner
              << ", Производитель: " << manufacturer << ", Стоимость(РУБ): " << cost
              << ", Кол-во: " << count << ", Описание: " << description << "\n";
}

void StringInstrument::Edit() {
    std::cout << "Ввод данных для струнного инструмента:\n";
    std::cout << "Название: "; char* n = ReadLineAlloc(); SetName(n); delete[] n;
    std::cout << "ФИО владельца: "; char* o = ReadLineAlloc(); SetOwner(o); delete[] o;
    std::cout << "Производитель: "; char* m = ReadLineAlloc(); SetManufacturer(m); delete[] m;
    std::cout << "Стоимость(РУБ): "; double c; 
        if(!(std::cin >> c)) 
            throw MyException("Неверный ввод стоимости"); 
            SetCost(c);
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Кол-во: "; int cnt; 
        if(!(std::cin >> cnt)) 
            throw MyException("Неверный ввод количества"); 
            SetCount(cnt);
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Краткое описание: "; char* d = ReadLineAlloc(); SetDescription(d); delete[] d;
}

void StringInstrument::SaveToFile(std::ofstream& fout) const {
    int kind = 2; // 2 = StringInstrument
    fout.write(reinterpret_cast<const char*>(&kind), sizeof(kind));
    WriteStringBin(fout, name);
    WriteStringBin(fout, owner);
    WriteStringBin(fout, manufacturer);
    fout.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
    fout.write(reinterpret_cast<const char*>(&count), sizeof(count));
    WriteStringBin(fout, description);
}

void StringInstrument::LoadFromFile(std::ifstream& fin) {
    delete[] name; delete[] owner; delete[] manufacturer; delete[] description;
    name = ReadStringBin(fin);
    owner = ReadStringBin(fin);
    manufacturer = ReadStringBin(fin);
    fin.read(reinterpret_cast<char*>(&cost), sizeof(cost));
    fin.read(reinterpret_cast<char*>(&count), sizeof(count));
    description = ReadStringBin(fin);
}
