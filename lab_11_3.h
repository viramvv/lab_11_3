#ifndef LAB_11_3_H
#define LAB_11_3_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> // Для std::transform

using namespace std;

//  Структура для зберігання дати народження
struct Date {
    int day;
    int month;
    int year;
};

//  Структура для зберігання контакту
struct Contact {
    string fullName;  // Прізвище, ім'я
    string phoneNum;  // Номер телефону
    Date birthDate;   // День народження
};

// --- ОГОЛОШЕННЯ ФУНКЦІЙ ---

// Створює та поповнює список у файлі
void createOrAppendList(const string& filename);

// Зчитує весь список з файлу та виводить його на екран
void displayList(const string& filename);

// Здійснює пошук людини за прізвищем/ім'ям та виводить інформацію
void searchAndDisplay(const string& filename, const string& searchName);

// Допоміжна функція: записує один контакт у потік
void writeContact(ostream& os, const Contact& contact);

// Допоміжна функція: читає один контакт із потоку
bool readContact(istream& is, Contact& contact);

#endif // LAB_11_3_H