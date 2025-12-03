#include "lab_11_3.h"

// Допоміжна функція: записує один контакт у потік (файл або cout)
void writeContact(ostream& os, const Contact& contact) {
    // Формат запису: Прізвище, Ім'я | Номер | День/Місяць/Рік
    os << contact.fullName << "|"
       << contact.phoneNum << "|"
       << contact.birthDate.day << "/"
       << contact.birthDate.month << "/"
       << contact.birthDate.year << endl;
}

// Допоміжна функція: читає один контакт із потоку (файлу)
bool readContact(istream& is, Contact& contact) {
    string line;
    if (getline(is, line)) {
        stringstream ss(line);
        string segment;

        // 1. Читаємо Прізвище, ім'я
        if (getline(ss, segment, '|')) {
            contact.fullName = segment;
        } else {
            return false;
        }

        // 2. Читаємо Номер телефону
        if (getline(ss, segment, '|')) {
            contact.phoneNum = segment;
        } else {
            return false;
        }

        // 3. Читаємо Дату народження (Д/М/Р)
        string dateSegment;
        if (getline(ss, dateSegment)) {
            stringstream ds(dateSegment);
            string d, m, y;
            // День
            if (getline(ds, d, '/')) {
                contact.birthDate.day = stoi(d);
            } else return false;
            // Місяць
            if (getline(ds, m, '/')) {
                contact.birthDate.month = stoi(m);
            } else return false;
            // Рік
            if (getline(ds, y)) {
                contact.birthDate.year = stoi(y);
            } else return false;
        } else {
            return false;
        }

        return true;
    }
    return false;
}

// 1. Створює та поповнює список у файлі
void createOrAppendList(const string& filename) {
    ofstream fout(filename, ios::app);
    if (!fout.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл " << filename << " для запису." << endl;
        return;
    }

    char continueInput;
    do {
        Contact newContact;
        cout << "\n--- Введення нового контакту ---\n";

        cout << "Введіть прізвище, ім'я: ";
        cin.ignore();
        getline(cin, newContact.fullName);

        cout << "Введіть номер телефону: ";
        getline(cin, newContact.phoneNum);

        cout << "Введіть день народження (ДД ММ РРРР): ";
        while (!(cin >> newContact.birthDate.day >> newContact.birthDate.month >> newContact.birthDate.year)) {
            cout << "Невірний формат. Спробуйте ще раз (ДД ММ РРРР): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        writeContact(fout, newContact);

        cout << "\nКонтакт записано. Продовжити введення (y/n)? ";
        cin >> continueInput;
        cin.ignore(10000, '\n');

    } while (continueInput == 'y' || continueInput == 'Y');

    fout.close();
}

// 2. Зчитує весь список з файлу та виводить його на екран
void displayList(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Файл " << filename << " не знайдено або порожній." << endl;
        return;
    }

    cout << "\n============================================\n";
    cout << "           СПИСОК КОНТАКТІВ\n";
    cout << "============================================\n";
    Contact contact;
    int count = 0;
    while (readContact(fin, contact)) {
        cout << "[" << ++count << "] "
             << contact.fullName
             << " | Тел: " << contact.phoneNum
             << " | ДН: " << contact.birthDate.day << "/"
             << contact.birthDate.month << "/"
             << contact.birthDate.year
             << endl;
    }
    cout << "============================================\n";

    fin.close();
}

// 3. Здійснює пошук людини за прізвищем/ім'ям та виводить інформацію
void searchAndDisplay(const string& filename, const string& searchName) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл " << filename << " для пошуку." << endl;
        return;
    }

    Contact contact;
    bool found = false;
// Перетворюємо пошуковий запит у нижній регістр
string lowerSearchName = searchName;
transform(lowerSearchName.begin(), lowerSearchName.end(), lowerSearchName.begin(), ::tolower);

while (readContact(fin, contact)) {
    // Перетворюємо ім'я контакту у нижній регістр
    string lowerContactName = contact.fullName;
    transform(lowerContactName.begin(), lowerContactName.end(), lowerContactName.begin(), ::tolower);

    // Пошук підрядка
    if (lowerContactName.find(lowerSearchName) != string::npos) {
        if (!found) {
            cout << "\n Знайдено збіги для \"" << searchName << "\":\n";
            found = true;
        }
        cout << "--------------------------------------------\n";
        cout << "Прізвище, Ім'я: " << contact.fullName << endl;
        cout << "Номер телефону: " << contact.phoneNum << endl;
        cout << "День народження: " << contact.birthDate.day << "/"
             << contact.birthDate.month << "/"
             << contact.birthDate.year << endl;
        cout << "--------------------------------------------\n";
    }
}

if (!found) {
    cout << "\n Повідомлення: Контакт з іменем/прізвищем, що містить \"" << searchName << "\", не знайдено." << endl;
}

fin.close();
}