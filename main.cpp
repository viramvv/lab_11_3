#include "lab_11_3.h"

//  Головне меню програми
void printMenu() {
    cout << "\n======================================\n";
    cout << "      МЕНЮ УПРАВЛІННЯ КОНТАКТАМИ       \n";
    cout << "======================================\n";
    cout << "1. Створити/Поповнити список контактів\n";
    cout << "2. Переглянути весь список контактів\n";
    cout << "3. Пошук інформації за прізвищем/ім'ям\n";
    cout << "0. Вийти\n";
    cout << "--------------------------------------\n";
    cout << "Ваш вибір: ";
}

int main() {
    //  Ім'я файлу, з яким працює програма
    const string filename = "contacts.txt";
    int choice;

    do {
        printMenu();

        // ⌨ Контроль помилок при введенні
        if (!(cin >> choice)) {
            cerr << "\n️ Помилка введення. Введіть число від 0 до 3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                // Створення/Поповнення списку
                createOrAppendList(filename);
                break;
            }
            case 2: {
                // Перегляд списку
                displayList(filename);
                break;
            }
            case 3: {
                // Пошук
                string searchName;
                cout << "\nВведіть прізвище або ім'я (або його частину) для пошуку: ";
                cin.ignore();
                getline(cin, searchName);
                searchAndDisplay(filename, searchName);
                break;
            }
            case 0: {
                // Вихід
                cout << "\nПрограма завершена. До побачення!\n";
                break;
            }
            default: {
                cout << "\n Невірний вибір. Спробуйте ще раз.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}