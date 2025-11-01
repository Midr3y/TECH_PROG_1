#pragma once
#include <iostream>
#include <fstream>
#include "MyException.h"

class Base {
public:
    Base() { std::cout << "Base: конструктор по умолчанию\n"; }
    virtual ~Base() { std::cout << "Base: деструктор\n"; }

    virtual void Show() const = 0;
    virtual void Edit() = 0;

    virtual void SaveToFile(std::ofstream& fout) const = 0; // бинарное сохранение
    virtual void LoadFromFile(std::ifstream& fin) = 0;     // бинарная загрузка

    virtual Base* Clone() const = 0;
};
