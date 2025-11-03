#include "Keeper.h"
#include "MyException.h"
#include "Percussion.h"
#include "StringInstrument.h"
#include "WindInstrument.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

Keeper::Keeper() : data(nullptr), size(0) {
    std::cout << "Keeper: конструктор по умолчанию\n";
}

Keeper::~Keeper() {
    std::cout << "Keeper: деструктор - освобождение объектов\n";
    for (int i = 0; i < size; ++i) delete data[i];
    delete[] data;
}

void Keeper::Resize(int newSize) {
    Base** nd = new Base*[newSize];
    for (int i = 0; i < newSize; ++i) nd[i] = nullptr;
    for (int i = 0; i < size && i < newSize; ++i) nd[i] = data[i];
    delete[] data;
    data = nd;
    size = (size < newSize) ? size : newSize;
}

void Keeper::Add(Base* obj) {
    if (!obj) throw MyException("Нельзя добавить пустой объект");
    // увеличиваем массив на 1
    Base** nd = new Base*[size + 1];
    for (int i = 0; i < size; ++i) nd[i] = data[i];
    nd[size] = obj;
    delete[] data;
    data = nd;
    ++size;
}

void Keeper::Delete(int index) {
    if (index < 0 || index >= size) throw MyException("Индекс вне диапазона");
    delete data[index];
    // сдвигаем
    for (int i = index; i < size - 1; ++i) data[i] = data[i+1];
    Base** nd = nullptr;
    if (size - 1 > 0) {
        nd = new Base*[size - 1];
        for (int i = 0; i < size - 1; ++i) nd[i] = data[i];
    }
    delete[] data;
    data = nd;
    --size;
}

void Keeper::ShowAll() const {
    if (size == 0) { std::cout << "Keeper пустой\n"; return; }
    std::cout << "Содержимое Keeper (" << size << "):\n";
    for (int i = 0; i < size; ++i) {
        std::cout << i << ": ";
        data[i]->Show();
    }
}

void Keeper::Edit(int index) {
    if (index < 0 || index >= size) throw MyException("Индекс вне диапазона");
    data[index]->Edit();
}

void Keeper::SaveAll(const char* filename) const {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) throw MyException("Не удалось открыть файл для записи");
    // Сначала количество
    int n = size;
    fout.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (int i = 0; i < size; ++i) {
        data[i]->SaveToFile(fout);
    }
    fout.close();
    std::cout << "Сохранение выполнено: " << filename << "\n";
}

void Keeper::LoadAll(const char* filename) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) throw MyException("Не удалось открыть файл для чтения");
    // Удаляем текущие
    for (int i = 0; i < size; ++i) delete data[i];
    delete[] data; data = nullptr; size = 0;

    int n = 0;
    fin.read(reinterpret_cast<char*>(&n), sizeof(n));
    if (!fin) throw MyException("Ошибка чтения количества объектов");
    for (int i = 0; i < n; ++i) {
        int kind = 0;
        fin.read(reinterpret_cast<char*>(&kind), sizeof(kind));
        if (!fin) throw MyException("Ошибка чтения типа объекта");
        Base* obj = nullptr;
        if (kind == 1) {
            Percussion* p = new Percussion();
            p->LoadFromFile(fin);
            obj = p;
        } else if (kind == 2) {
            StringInstrument* s = new StringInstrument();
            s->LoadFromFile(fin);
            obj = s;
        } else if (kind == 3) {
            WindInstrument* w = new WindInstrument();
            w->LoadFromFile(fin);
            obj = w;
        } else {
            throw MyException("Неизвестный тип в файле");
        }
        // добавляем в массив
        Base** nd = new Base*[size + 1];
        for (int k = 0; k < size; ++k) nd[k] = data[k];
        nd[size] = obj;
        delete[] data;
        data = nd;
        ++size;
    }
    fin.close();
    std::cout << "Загрузка выполнена: " << filename << " (" << size << ")\n";
}
