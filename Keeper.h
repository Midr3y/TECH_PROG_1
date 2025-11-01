#pragma once
#include "Base.h"

class Keeper {
private:
    Base** data;
    int size;

    void Resize(int newSize);

public:
    Keeper();
    ~Keeper();

    void Add(Base* obj); // владеет obj
    void Delete(int index); // удаляет объект и сдвигает
    void ShowAll() const;
    void Edit(int index);

    void SaveAll(const char* filename) const;
    void LoadAll(const char* filename);

    int GetSize() const { return size; }
};
