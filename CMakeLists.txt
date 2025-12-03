# Визначення мінімально необхідної версії CMake
cmake_minimum_required(VERSION 3.10)

# Назва вашого проєкту
project(lab_11_3)

# Встановлення стандарту C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- 1. Ціль: Основна програма ---
add_executable(lab_11_3_app
        main.cpp
        lab_11_3.cpp
)

# ------------------------------------------------------------------
# --- 2. ВИПРАВЛЕНИЙ БЛОК ДЛЯ GOOGLE TEST (Обхід помилки завантаження) ---
# ------------------------------------------------------------------

# Знаходимо встановлену бібліотеку GTest (CLion зазвичай має її внутрішньо)
find_package(GTest REQUIRED)

# --- 3. Ціль: Юніт-тести ---
add_executable(unit_tests
        UnitTest.cpp
        lab_11_3.cpp  # Включаємо реалізацію функцій для тестування
)

# Лінкування тестувального виконуваного файлу з бібліотеками GTest
target_link_libraries(unit_tests
        PRIVATE GTest::gtest_main
)

# Додавання цілі до набору тестів CTest
include(CTest)
add_test(NAME run_unit_tests COMMAND unit_tests)