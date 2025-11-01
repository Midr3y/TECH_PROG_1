#pragma once
#include "Base.h"

class WindInstrument : public Base {
private:
    char* name;
    char* manufacturer;
    double cost;
    char* owner;
    int count;
    char* defects; // описание дефектов

public:
    WindInstrument();
    WindInstrument(const char*, const char*, double, const char*, int, const char*);
    WindInstrument(const WindInstrument& other);
    ~WindInstrument();

    void SetName(const char* n);
    const char* GetName() const { return name; }

    void SetManufacturer(const char* m);
    const char* GetManufacturer() const { return manufacturer; }

    void SetCost(double c) { cost = c; }
    double GetCost() const { return cost; }

    void SetOwner(const char* o);
    const char* GetOwner() const { return owner; }

    void SetCount(int cnt) { count = cnt; }
    int GetCount() const { return count; }

    void SetDefects(const char* d);
    const char* GetDefects() const { return defects; }

    void Show() const override;
    void Edit() override;

    void SaveToFile(std::ofstream& fout) const override;
    void LoadFromFile(std::ifstream& fin) override;

    Base* Clone() const override { return new WindInstrument(*this); }
};
