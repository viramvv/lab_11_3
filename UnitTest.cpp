#include "gtest/gtest.h"
#include "lab_11_3.h"

#include <sstream>
#include <iostream>

// Файл-заглушка для тестування функцій, що працюють із файлами
const string TEST_FILENAME = "test_contacts.txt";

// 🧪 Набір тестів для допоміжних функцій читання/запису
namespace {

    // --- ТЕСТ 1: Перевірка коректності запису у потік ---
    TEST(ContactFunctionsTest, WriteContact_CorrectFormat) {
        Contact testContact = {
            "Тест Прізвище",
            "0981234567",
            {10, 12, 2025}
        };

        // Використовуємо stringstream як потік-заглушку замість файлу
        stringstream ss;
        writeContact(ss, testContact);

        // Очікуваний формат запису: Ім'я|Телефон|Д/М/Р
        string expected = "Тест Прізвище|0981234567|10/12/2025\n";

        // Перевіряємо, чи згенерований рядок відповідає очікуваному
        ASSERT_EQ(ss.str(), expected);
    }

    // --- ТЕСТ 2: Перевірка коректності читання з потоку ---
    TEST(ContactFunctionsTest, ReadContact_CorrectParsing) {
        // Рядок, який імітує дані, записані у файлі
        string inputData = "Іваненко Петро|0509876543|25/8/1999\n";
        stringstream ss(inputData);

        // ЗМІНЕНА ЗМІННА: використовуємо contactData, щоб уникнути конфлікту з функцією readContact()
        Contact contactData;

        // Викликаємо функцію читання
        bool success = readContact(ss, contactData);

        // Перевіряємо, чи читання пройшло успішно
        ASSERT_TRUE(success);

        // Перевіряємо, чи правильно розпарсені поля
        ASSERT_EQ(contactData.fullName, "Іваненко Петро");
        ASSERT_EQ(contactData.phoneNum, "0509876543");
        ASSERT_EQ(contactData.birthDate.day, 25);
        ASSERT_EQ(contactData.birthDate.month, 8);
        ASSERT_EQ(contactData.birthDate.year, 1999);
    }

    // --- ТЕСТ 3: Перевірка функції пошуку (searchAndDisplay) ---
    TEST(SearchTest, SearchAndDisplay_FindsMatch) {
        // Створення тестового файлу
        ofstream fout(TEST_FILENAME, ios::trunc); // Очищуємо перед записом
        fout << "Тестовий Збіг|1112223344|01/01/2023" << endl;
        fout << "Петренко Іван|5556667788|15/05/2000" << endl;
        fout.close();

        // Перенаправлення стандартного виводу для перехоплення результату пошуку
        stringstream outputBuffer;
        streambuf* oldCout = cout.rdbuf();
        cout.rdbuf(outputBuffer.rdbuf());

        // Викликаємо функцію пошуку
        searchAndDisplay(TEST_FILENAME, "Тест"); // Перевіряємо пошук за частиною слова

        // Відновлюємо стандартний вивід
        cout.rdbuf(oldCout);

        // Перевіряємо, чи вивід містить ключові слова успішного пошуку
        ASSERT_TRUE(outputBuffer.str().find("Знайдено збіги") != string::npos);
        ASSERT_TRUE(outputBuffer.str().find("Тестовий Збіг") != string::npos);

        // Видалення тестового файлу після використання
        remove(TEST_FILENAME.c_str());
    }

    // --- ТЕСТ 4: Перевірка функції пошуку (searchAndDisplay) ---
    TEST(SearchTest, SearchAndDisplay_NoMatch) {
        // Створення тестового файлу
        ofstream fout(TEST_FILENAME, ios::trunc); 
        fout << "Тестовий Збіг|1112223344|01/01/2023" << endl;
        fout.close();

        stringstream outputBuffer;
        streambuf* oldCout = cout.rdbuf();
        cout.rdbuf(outputBuffer.rdbuf());

        // Викликаємо функцію пошуку для відсутнього контакту
        searchAndDisplay(TEST_FILENAME, "Відсутній");

        cout.rdbuf(oldCout);

        // Перевіряємо, чи вивід містить повідомлення про відсутність збігів
        ASSERT_TRUE(outputBuffer.str().find("не знайдено") != string::npos);

        // Видалення тестового файлу
        remove(TEST_FILENAME.c_str());
    }

} // end namespace

// Головна функція для запуску всіх тестів (використовується Google Test)
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}