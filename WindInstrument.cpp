#include "WindInstrument.h"
#include "Utils.h"
#include <iostream>

WindInstrument::WindInstrument()
    : name(nullptr), manufacturer(nullptr), cost(0.0), owner(nullptr), count(0), defects(nullptr)
{
    std::cout << "WindInstrument: конструктор по умолчанию\n";
    name = new char[1]; name[0] = '\0';
    manufacturer = new char[1]; manufacturer[0] = '\0';
    owner = new char[1]; owner[0] = '\0';
    defects = new char[1]; defects[0] = '\0';
}

WindInstrument::WindInstrument(const char* n, const char* m, double c, const char* o, int cnt, const char* d)
    : name(nullptr), manufacturer(nullptr), cost(c), owner(nullptr), count(cnt), defects(nullptr)
{
    std::cout << "WindInstrument: конструктор с параметрами\n";
    SetName(n); SetManufacturer(m); SetOwner(o); SetDefects(d);
}

WindInstrument::WindInstrument(const WindInstrument& other)
    : name(nullptr), manufacturer(nullptr), cost(other.cost), owner(nullptr), count(other.count), defects(nullptr)
{
    std::cout << "WindInstrument: конструктор копирования\n";
    SetName(other.name);
    SetManufacturer(other.manufacturer);
    SetOwner(other.owner);
    SetDefects(other.defects);
}

WindInstrument::~WindInstrument() {
    std::cout << "WindInstrument: деструктор\n";
    delete[] name; delete[] manufacturer; delete[] owner; delete[] defects;
}

void WindInstrument::SetName(const char* n) {
    delete[] name;
    if (!n) { name = new char[1]; name[0] = '\0'; return; }
    size_t l = std::strlen(n);
    name = new char[l+1]; std::strcpy(name, n);
}

void WindInstrument::SetManufacturer(const char* m) {
    delete[] manufacturer;
    if (!m) { manufacturer = new char[1]; manufacturer[0] = '\0'; return; }
    size_t l = std::strlen(m);
    manufacturer = new char[l+1]; std::strcpy(manufacturer, m);
}

void WindInstrument::SetOwner(const char* o) {
    delete[] owner;
    if (!o) { owner = new char[1]; owner[0] = '\0'; return; }
    size_t l = std::strlen(o);
    owner = new char[l+1]; std::strcpy(owner, o);
}

void WindInstrument::SetDefects(const char* d) {
    delete[] defects;
    if (!d) { defects = new char[1]; defects[0] = '\0'; return; }
    size_t l = std::strlen(d);
    defects = new char[l+1]; std::strcpy(defects, d);
}

void WindInstrument::Show() const {
    std::cout << "[Духовой] Название: " << name << ", Производитель: " << manufacturer
              << ", Стоимость(РУБ): " << cost << ", Владелец: " << owner
              << ", Кол-во: " << count << ", Дефекты: " << defects << "\n";
}

void WindInstrument::Edit() {
    std::cout << "Ввод данных для духового инструмента:\n";
    std::cout << "Название: "; char* n = ReadLineAlloc(); SetName(n); delete[] n;
    std::cout << "Производитель: "; char* m = ReadLineAlloc(); SetManufacturer(m); delete[] m;
    std::cout << "Стоимость(РУБ): "; double c; 
        if(!(std::cin >> c)) 
            throw MyException("Неверный ввод стоимости"); 
            SetCost(c);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "ФИО владельца: "; std::cin.ignore(); char* o = ReadLineAlloc(); SetOwner(o); delete[] o;
    std::cout << "Кол-во: "; int cnt; 
        if(!(std::cin >> cnt)) 
            throw MyException("Неверный ввод количества"); 
            SetCount(cnt);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Дефекты (описание): "; char* d = ReadLineAlloc(); SetDefects(d); delete[] d;
}

void WindInstrument::SaveToFile(std::ofstream& fout) const {
    int kind = 3; // 3 = WindInstrument
    fout.write(reinterpret_cast<const char*>(&kind), sizeof(kind));
    WriteStringBin(fout, name);
    WriteStringBin(fout, manufacturer);
    fout.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
    WriteStringBin(fout, owner);
    fout.write(reinterpret_cast<const char*>(&count), sizeof(count));
    WriteStringBin(fout, defects);
}

void WindInstrument::LoadFromFile(std::ifstream& fin) {
    delete[] name; delete[] manufacturer; delete[] owner; delete[] defects;
    name = ReadStringBin(fin);
    manufacturer = ReadStringBin(fin);
    fin.read(reinterpret_cast<char*>(&cost), sizeof(cost));
    owner = ReadStringBin(fin);
    fin.read(reinterpret_cast<char*>(&count), sizeof(count));
    defects = ReadStringBin(fin);
}
