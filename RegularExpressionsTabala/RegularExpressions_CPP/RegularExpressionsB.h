// Задача номер 12, група "Комп'ютерна математика 2", Табала Матвій.
#pragma once // Цей рядок забезпечує те, що цей файл буде включено лише один раз
#include <string> // Бібліотека для роботи з рядками (std::string)
#include <vector> // Бібліотека для роботи з векторами (std::vector)

namespace RegularExpressionsB { // Це простір імен
    void findHyperlinks(const std::string& filename); // Пошук гіперпосилань
    void convertDates(const std::string& filename); // Конвертація дат
    void convertNumbers(const std::string& filename); // Конвертація чисел
    void replaceDatesAndTimes(const char* filename); // Заміна дат і часів
    bool isNumber(const std::string& word); // Перевірка, чи є слово числом
    bool isValidDate(const std::string& date); // Перевірка, чи є дата коректною
    bool isValidTime(const std::string& time); // Перевірка, чи є час коректним
}
