/* 
Задача номер 12, група "Комп'ютерна математика 2", Табала Матвій.
а) Розв’яжіть дані задачі на С++ за допомогою функцій бібліотеки string.h 
(без регулярних виразів, тільки бібліотека <string.h>) 
1) В даному текстовому файлі знайти всі гіперпосилання та вивести їх 
разом зі словом (слово відокремлюється пробілами та знаками пунктуації) 
що стоїть перед ним. 
2) Знайти в даному текстовому файлі всі дати в форматах __.__.__ та 
__/__/__ (в кінці можуть бути 2 або 4 цифри, а також ____(рік).__.__) та 
перевести їх всі до єдиного формату __(рік) назва місяцю __(число). 
3) Знайти всі цілі та дійсні числа (в науковому та звичайному форматі з 
крапкою/комою) та привести їх до єдиного формату (дійсне число з 
фіксованою крапкою, точність 4 розряду) та оточити круглими дужками. 
4) Змінити всі дати та записи часу у файлі на поточні дату 
та час. */

#ifdef _MSC_VER // Для компілятора Microsoft Visual Studio
#define _CRT_SECURE_NO_WARNINGS // Відключення застережень про використання небезпечних функцій
#endif

// Підключаємо потрібні бібліотеки і хедер
#include "RegularExpressionsA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// Функція для перевірки чи є символ роздільником
bool isSeparator(char c) {
    char punctuations[] = ".,:;!?()[]{}\"\'";
    // Повертаємо true якщо символ не є буквою, цифрою, підкресленням або знаком пунктуації
    return !(isalnum(c) || c == '_' || strchr(punctuations, c) != NULL);
}

// Функція для пошуку гіперпосилань
void findHyperlinks(const char* filename) {
    /* Тут ми відкримаємо 2 файли, один для зчитування,
    інший для запису у нього даних для подальшого порівняння */
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "w");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char word[256], prevWord[256] = "";

        // Розбиваємо рядок на токени
        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            // Копіюємо токен у змінну word
            strcpy(word, token);

            // Якщо токен містить http, то виводимо попереднє слово та саме гіперпосилання
            if (strstr(word, "http") != NULL) {
                if (strlen(prevWord) > 0) {
                    printf("%s %s\n", prevWord, word);
                    fprintf(file2, "%s %s\n", prevWord, word);
                }
            }

            // Копіюємо токен у змінну prevWord
            strcpy(prevWord, "");
            for (int i = 0; word[i] != '\0'; i++) {
                if (!isSeparator(word[i])) {
                    strncat(prevWord, &word[i], 1);
                }
            }

            // Переходимо до наступного токену
            token = strtok(NULL, " \t\n");
        }
    }

    // Закриваємо файли
    printf("\n");
    fprintf(file2, "\n");
    fclose(file);
    fclose(file2);
}

// Функція для перевірки чи є дата правильною
bool isValidDate(const char* date) {
    int day, month, year;

    // Перевіряємо чи дата в форматі рік.місяць.день
    if (sscanf_s(date, "%d.%d.%d", &year, &month, &day) == 3) {
        if (year < 100) {
            if (year >= 0 && year <= 69) {
                year += 2000;
            }
            else {
                year += 1900;
            }
        }
        if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
            return true;
        }
    }

    // Перевіряємо чи дата в форматі день/місяць/рік або день.місяць.рік
    if (sscanf_s(date, "%d.%d.%d", &day, &month, &year) == 3 ||
        		sscanf_s(date, "%d/%d/%d", &day, &month, &year) == 3) {
		if (year < 100) {
			if (year >= 0 && year <= 69) {
				year += 2000;
			}
			else {
				year += 1900;
			}
		}
		if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
			return true;
		}
	}
    return false;
}

// Створюємо масив з назвами місяців
const char* monthMap[] = {
    NULL, "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// Функція для переведення дати до єдиного формату
void convertDates(const char* filename) {
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "a");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char word[256];

        // Розбиваємо рядок на токени
        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            strcpy(word, token);

            // Якщо токен містить крапку або слеш, то відкидаємо всі символи крім цифр, крапки та слеша
            if (strlen(word) >= 8 && (strstr(word, ".") != NULL || strstr(word, "/") != NULL)) {
                char cleanedDate[256] = "";
                for (int i = 0; word[i] != '\0'; i++) {
                    if (isdigit(word[i]) || word[i] == '.' || word[i] == '/') {
                        strncat(cleanedDate, &word[i], 1);
                    }
                }

                // Якщо дата є правильною, то виводимо її у єдиному форматі
                if (isValidDate(cleanedDate)) {
                    int day, month, year;
                    sscanf_s(cleanedDate, "%d.%d.%d", &day, &month, &year);
                    sscanf_s(cleanedDate, "%d/%d/%d", &day, &month, &year);

                    if (year < 100) {
                        if (year >= 0 && year <= 69) {
                            year += 2000;
                        }
                        else {
                            year += 1900;
                        }
                    }

                    // Якщо на початку стоїть рік
                    if (day >= 1000) {
                        sscanf_s(cleanedDate, "%d.%d.%d", &year, &month, &day);
						printf("Original date: %s -> ", word);
                        fprintf(file2, "Original date: %s -> ", word);

                        printf ("Uniform date: %d %s %d\n ", year, monthMap[month], day);
                        fprintf(file2, "Uniform date: %d %s %d\n", year, monthMap[month], day);
					}
					else {
                        printf("Original date: %s -> ", word);
						fprintf(file2, "Original date: %s -> ", word);

						printf("Uniform date: %d %s %d\n", year, monthMap[month], day);
						fprintf(file2, "Uniform date: %d %s %d\n", year, monthMap[month], day);
					}
                }
            }

            // Переходимо до наступного токену
            token = strtok(NULL, " \t\n");
        }
    }

    // Закриваємо файли
    printf("\n");
    fprintf(file2, "\n");
    fclose(file);
    fclose(file2);
}

// Функція для перевірки чи є слово числом
bool isNumber(const char* word) {
    char* endptr;
    // Перевіряємо чи є число дійсним
    strtod(word, &endptr);
    return *endptr == '\0';
}

// Переводимо число до єдиного формату
void convertNumbers(const char* filename) {
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "a");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char word[256];

        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            strcpy(word, token);

            // Якщо токен є числом, то виводимо його у єдиному форматі
            if (isNumber(word)) {
                double num = strtod(word, NULL);
                printf("%.4f, ", num);
                fprintf(file2, "%.4f, ", num);
            }

            // Переходимо до наступного токену
            token = strtok(NULL, " \t\n");
        }
    }
    
    // Закриваємо файли
    printf("\n\n");
    fprintf(file2, "\n\n");
    fclose(file);
    fclose(file2);
}

// Функція для перевірки чи є час правильним
bool isValidTime(const char* time) {
	int hour, minute, second;

	// Перевіряємо чи час є в форматі hh:mm:ss
    if (sscanf_s(time, "%2d:%2d:%2d", &hour, &minute, &second) == 4) {
        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
			return true;
		}
	}

	// Перевіряємо чи час є в форматі hh:mm
    if (sscanf_s(time, "%2d:%2d", &hour, &minute) == 2) {
        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
			return true;
		}
	}
	return false;
}

// Function to replace dates and times with current date and time
void replaceDatesAndTimes(const char* filename) {
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "a");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " \t\n");
        bool containsDateOrTime = false;

        while (token != NULL) {
            char word[256]; // Слово, яке буде перевірятись
            strcpy(word, token); // Копіюємо токен у змінну word
            time_t now = time(NULL); // Поточний час
            struct tm* ltm = localtime(&now); // Локальний час

            // Якщо токен містить крапку або слеш, то відкидаємо всі символи крім цифр, крапки та слеша
            if (strstr(word, ".") != NULL || strstr(word, "/") != NULL) {
                char cleanedDate[256] = ""; // Дата, яка буде перевірятись
                for (int i = 0; word[i] != '\0'; i++) {
                    if (isdigit(word[i]) || word[i] == '.' || word[i] == '/') {
                        strncat(cleanedDate, &word[i], 1);
                    }
                }
                
                // Якщо дата є правильною, то виводимо поточну дату
                if (isValidDate(cleanedDate)) {
                    printf("%d %s %d; ", 1900 + ltm->tm_year, monthMap[1+ltm->tm_mon], ltm->tm_mday);

                    fprintf(file2, "%d %s %d; ", 1900 + ltm->tm_year, monthMap[1+ltm->tm_mon], ltm->tm_mday);
                    containsDateOrTime = true;
                }
            }
            // Якщо токен містить двокрапку, то відкидаємо всі символи крім цифр та двокрапки
            if (strstr(word, ":") != NULL) {
                char cleanedTime[256] = "";
                for (int i = 0; word[i] != '\0'; i++) {
                    if (isdigit(word[i]) || word[i] == ':') {
                        strncat(cleanedTime, &word[i], 1);
                    }
                }

                // Якщо час є правильним, то виводимо поточний час
                if (strlen(cleanedTime) == 8 && isValidTime(cleanedTime)) {
                    // Перевіряємо купу умови, щоб формат виводу був правильним
                    if (ltm->tm_hour < 10) {
                        if (ltm->tm_min < 10) {
                            if (ltm->tm_sec < 10) {
                                printf("0%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("0%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                        else {
                            if (ltm->tm_sec < 10) {
                                printf("0%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("0%d:%d:%d;", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                    }
                    else {
                        if (ltm->tm_min < 10) {
                            if (ltm->tm_sec < 10) {
                                printf("%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                        else {
                            if (ltm->tm_sec < 10) {
                                printf("%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("%d:%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                    }
                    containsDateOrTime = true;
                }
                else if (strlen(cleanedTime) == 5 && isValidTime(cleanedTime)) {
                    if (ltm->tm_hour < 10) {
                        if (ltm->tm_min < 10) {
							printf("0%d:0%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "0%d:0%d; ", ltm->tm_hour, ltm->tm_min);
						}
						else {
							printf("0%d:%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "0%d:%d; ", ltm->tm_hour, ltm->tm_min);
						}
					}
					else {
						if (ltm->tm_min < 10) {
							printf("%d:0%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "%d:0%d; ", ltm->tm_hour, ltm->tm_min);
						}
						else {
							printf("%d:%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "%d:%d; ", ltm->tm_hour, ltm->tm_min);
						}
					}
                    containsDateOrTime = true;
                }
            }

            token = strtok(NULL, " \t\n");
        }

        // Якщо рядок містить дату або час, то переходимо на новий рядок
        if (containsDateOrTime) {
            printf("\n");
            fprintf(file2, "\n");
        }
    }
    // Закриваємо файли
    fclose(file);
    fclose(file2);
}

