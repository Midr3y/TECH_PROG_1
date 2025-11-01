#pragma once
#include "Base.h"

class Percussion : public Base {
private:
    char* type;    // тип ударного
    char* name;    // название
    double cost;
    int count;
    char* owner;   // ФИО владельца

public:
    Percussion();
    Percussion(const char* t, const char* n, double c, int cnt, const char* o);
    Percussion(const Percussion& other);
    ~Percussion();

    // set/get
    void SetType(const char* t);
    const char* GetType() const { return type; }

    void SetName(const char* n);
    const char* GetName() const { return name; }

    void SetCost(double c) { cost = c; }
    double GetCost() const { return cost; }

    void SetCount(int cnt) { count = cnt; }
    int GetCount() const { return count; }

    void SetOwner(const char* o);
    const char* GetOwner() const { return owner; }

    void Show() const override;
    void Edit() override;

    void SaveToFile(std::ofstream& fout) const override;
    void LoadFromFile(std::ifstream& fin) override;

    Base* Clone() const override { return new Percussion(*this); }
};
