#include <iostream>
#include "Keeper.h"
#include "Percussion.h"
#include "StringInstrument.h"
#include "WindInstrument.h"
#include "MyException.h"
#include <limits>
#include <windows.h>


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    Keeper keeper;

    while (true) {
        std::cout << "\n--- Меню ---\n"
                  << "1. Добавить инструмент\n"
                  << "2. Удалить инструмент\n"
                  << "3. Просмотреть все\n"
                  << "4. Изменить инструмент\n"
                  << "5. Сохранить в файл\n"
                  << "6. Загрузить из файла\n"
                  << "0. Выход\n"
                  << "Выбор: ";
        int ch;
        if (!(std::cin >> ch)) { std::cin.clear(); std::cin.ignore(10000, '\n'); continue; }
        try {
            if (ch == 0) break;
            switch (ch) {
                case 1: {
                    std::cout << "Выберите тип: 1-Ударный,2-Струнный,3-Духовой: ";
                    int t; std::cin >> t; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Base* b = nullptr;
                    if (t == 1) b = new Percussion();
                    else if (t == 2) b = new StringInstrument();
                    else if (t == 3) b = new WindInstrument();
                    else throw MyException("Неверный тип инструмента");
                    b->Edit();
                    keeper.Add(b);
                    break;
                }
                case 2: {
                    std::cout << "Индекс для удаления: "; int idx; std::cin >> idx; keeper.Delete(idx); break;
                }
                case 3: keeper.ShowAll(); break;
                case 4: {
                    std::cout << "Индекс для редактирования: "; int idx; std::cin >> idx; keeper.Edit(idx); break;
                }
                case 5: {
                    std::cout << "Имя файла для сохранения: "; std::string fname; std::cin >> fname; keeper.SaveAll(fname.c_str()); break;
                }
                case 6: {
                    std::cout << "Имя файла для загрузки: "; std::string fname; std::cin >> fname; keeper.LoadAll(fname.c_str()); break;
                }
                default: std::cout << "Неверный выбор\n";
            }
        } catch (const MyException& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "std::exception: " << e.what() << "\n";
        } catch (...) {
            std::cerr << "Неизвестная ошибка\n";
        }
    }
    std::cout << "Выход.\n";
    return 0;
}
