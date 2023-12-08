// Задача номер 12, група "Комп'ютерна математика 2", Табала Матвій.
#pragma once // Цей рядок забезпечує те, що цей файл буде включено лише один раз
#include <string.h> // Бібліотека для роботи з рядками (char*)

void findHyperlinks(const char* filename); // Пошук гіперпосилань
void convertDates(const char* filename); // Конвертація дат
void convertNumbers(const char* filename); // Конвертація чисел
void replaceDatesAndTimes(const char* filename); // Заміна дат і часів
