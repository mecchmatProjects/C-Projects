/*
Задача номер 12, група "Комп'ютерна математика 2", Табала Матвій.
в) Розв’яжіть дані задачі на С++ за допомогою функцій бібліотеки <regex> (c++11)
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
#define _CRT_SECURE_NO_WARNINGS // Відключення застережень про небезпеку
#endif

// Підключаємо бібліотеки і хедер
#include "RegularExpressionsC.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <ctime>
using namespace std;

namespace RegularExpressionsC // Це простір імен
{
	/* 1) В даному текстовому файлі знайти всі гіперпосилання та вивести їх
	разом зі словом (слово відокремлюється пробілами та знаками пунктуації)
	що стоїть перед ним. */

	void findHyperlinks(const string& filename) {
		// Відкриваємо файл для читання
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::trunc); // Відкриваємо файл для запису з очищенням
		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Unable to open file.\n";
			return;
		}

		// Читаємо файл по рядках
		string line;
		regex linkRegex(R"(\S(\S+)\s+https?://\S+\b)"); // Регулярний вираз для пошуку гіперпосилань

		while (getline(file, line)) {
			smatch match;
			string::const_iterator searchStart(line.cbegin()); // Ітератор, що вказує на початок рядка
			
			// Пошук гіперпосилань в рядку
			while (regex_search(searchStart, line.cend(), match, linkRegex)) {
				string hyperlink = match[0].str(); // Зберігаємо гіперпосилання
				cout << hyperlink << "\n";
				fileC << hyperlink << "\n";

				// Оновлюємо позицію searchStart для наступного пошуку
				searchStart = match.suffix().first;
			}
		}

		cout << "\n";
		fileC << "\n";

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileC.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileC.close();
	}
	
	// Словник, що містить назви місяців
	unordered_map<string, string> monthMap = {
		{"01", "January"}, {"02", "February"}, {"03", "March"},
		{"04", "April"}, {"05", "May"}, {"06", "June"},
		{"07", "July"}, {"08", "August"}, {"09", "September"},
		{"10", "October"}, {"11", "November"}, {"12", "December"}
	};

	// Функція, що перевіряє, чи є дата коректною
	bool isValidDate(const string& date) {
		stringstream ss(date);
		char discard;
		int day, month, year;
		if (date.find('.') == 4 || date.find('/') == 4) {
			ss >> year >> discard >> month >> discard >> day;
		}
		else {
			ss >> day >> discard >> month >> discard >> year;
		}

		return ss.eof() && ss.fail() == false && month > 0 && month <= 12 && day > 0 && day <= 31;
	}

	/* 2) Знайти в даному текстовому файлі всі дати в форматах __.__.__ та
	__/__/__ (в кінці можуть бути 2 або 4 цифри, а також ____(рік).__.__) та
	перевести їх всі до єдиного формату __(рік) назва місяцю __(число). */

	// Фукнція, що перетворює дати до єдиного формату
	void convertDates(const string& filename) {
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::app);

		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Unable to open file.\n";
			return;
		}

		// Читаємо файл по рядках
		string line;
		regex dateRegex(R"(\b(\d{2}|\d{4})[./] ?(\d{2})[./] ?(\d{2}|\d{4})\b)"); // Регулярний вираз для пошуку дат
		regex yearRegex(R"(\b(\d{4})[./] ?(\d{2})[./] ?(\d{2})\b)"); // Регулярний вираз для пошуку дат, які починаються з року

		while (getline(file, line)) {
			smatch match;
			string::const_iterator searchStart(line.cbegin()); // Ітератор, що вказує на початок рядка

			while (regex_search(searchStart, line.cend(), match, dateRegex)) {
				string date = match[0].str(); // Зберігаємо дату
				stringstream ss(date);
				char discard;
				int day, month, year;
				// якщо рік вказаний двома цифрами, то додаємо до нього 1900 або 2000 року
				if (date.find('.') == 4 || date.find('/') == 4) {
					ss >> year >> discard >> month >> discard >> day;
				}
				else {
					ss >> day >> discard >> month >> discard >> year;
				}

				if (year < 100) {
					if (year >= 0 && year <= 69) {
						year += 2000;
					}
					else {
						year += 1900;
					}
				}

				// якщо місяць вказаний однією цифрою, то додаємо до нього 0
				string monthStr = month < 10 ? "0" + to_string(month) : to_string(month);
				string monthName = monthMap[monthStr];

				// Перетворюємо дату до єдиного формату
				string uniformDate = to_string(year) + " " + monthName + " " + to_string(day);
				cout << "Original date: " << match[0].str() << " -> Uniform date: " << uniformDate << endl;

				fileC << "Original date: " << match[0].str() << " -> Uniform date: " << uniformDate << endl;

				// Оновлюємо позицію searchStart для наступного пошуку
				searchStart = match.suffix().first;
			}
		}
		cout << "\n";
		fileC << "\n";

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileC.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileC.close();
	}

	/* 3) Знайти всі цілі та дійсні числа (в науковому та звичайному форматі з
	крапкою/комою) та привести їх до єдиного формату (дійсне число з
	фіксованою крапкою, точність 4 розряду) та оточити круглими дужками. */

	// Функція, що перевіряє, чи є слово числом
	void convertNumbers(const string& filename) {
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::app);

		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Unable to open file.\n";
			return;
		}

		string line;
		regex numberRegex(R"(\b(\d+\.?\d*)\b)"); // Пошук цілих та дійсних чисел
		regex scientificNumberRegex(R"(\b(\d+\.?\d*)e(\+|-)?(\d+)\b)"); // Пошук чисел у науковому форматі
		regex hypertextRegex(R"(<.*?>)"); // Пошук гіперпосилань

		while (getline(file, line)) {
			stringstream ss(line);
			string word;

			while (ss >> word) {
				// Прибираємо гіперпосилання
				word = regex_replace(word, hypertextRegex, "");

				if (regex_match(word, numberRegex) || regex_match(word, scientificNumberRegex)) {
					// Перетворюємо число до єдиного формату
					double num = stod(word);
					cout << fixed << setprecision(4) << num << ", ";
					fileC << fixed << setprecision(4) << num << ", ";
				}
			}
		}
		cout << "\n\n";
		fileC << "\n\n";

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileC.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileC.close();
}

	/* 4) Change all dates (year, month, day) to today's date (for example (2023) December 3) and time (hh:mm:ss) to current time. */
	// for example, you have a line: 10.05.2023 12:00:00 and you need to change it to 2023-October-05 21:33:00

	// Функція, що перевіряє, чи є час коректним
	bool isValidTime(const string& time) {
		regex timeRegex(R"(\b(\d{2}):(\d{2})\b)"); // Regex to match time format HH:MM
		return regex_match(time, timeRegex);
	}

	// Функція, що замінює дати та часи на поточні
	void replaceDatesAndTimes(const char* filename) {
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::app);

		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		string line;
		regex timeRegex(R"(\b\d{1,2}:\d{2}(:\d{2})?\b)"); // Пошук часу у форматі HH:MM або HH:MM:SS
		regex hypertextRegex(R"(<.*?>)"); // Пошук гіперпосилань

		while (getline(file, line)) {
			stringstream ss(line);
			string word;
			bool containsDateOrTime = false;
			time_t now = time(0); // Поточний час
			tm* ltm = localtime(&now); // Перетворюємо поточний час до структури tm

			while (ss >> word) {
				// Прибираємо гіперпосилання
				word = regex_replace(word, hypertextRegex, "");

				if (isValidDate(word)) {
					// Виводимо поточну дату
					cout << 1900 + ltm->tm_year << " "
						<< monthMap[to_string(1 + ltm->tm_mon)] << " "
						<< ltm->tm_mday << "; ";

					fileC << 1900 + ltm->tm_year << " "
						<< monthMap[to_string(1 + ltm->tm_mon)] << " "
						<< ltm->tm_mday << "; ";

					containsDateOrTime = true;
				}
				else if (regex_search(word, timeRegex)) {
					// Перевіряємо купу умови для коректного виводу часу (HH:MM або HH:MM:SS) для випадків з однією цифрою
					if (isValidTime(word)) {
						if (ltm->tm_hour < 10) {
							if (ltm->tm_min < 10) {
								cout << "0" << ltm->tm_hour << ":0" << ltm->tm_min << "; ";
								fileC << "0" << ltm->tm_hour << ":0" << ltm->tm_min << "; ";
							}
							else {
								cout << "0" << ltm->tm_hour << ":" << ltm->tm_min << "; ";
								fileC << "0" << ltm->tm_hour << ":" << ltm->tm_min << "; ";
							}
						}
						else {
							if (ltm->tm_min < 10) {
								cout << ltm->tm_hour << ":0" << ltm->tm_min << "; ";
								fileC << ltm->tm_hour << ":0" << ltm->tm_min << "; ";
							}
							else {
								cout << ltm->tm_hour << ":" << ltm->tm_min << "; ";
								fileC << ltm->tm_hour << ":" << ltm->tm_min << "; ";
							}
						}
						containsDateOrTime = true;
					}
					else {
						if (ltm->tm_hour < 10) {
							if (ltm->tm_min < 10) {
								if (ltm->tm_sec < 10) {
									cout << "0" << ltm->tm_hour << ":0" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
									fileC << "0" << ltm->tm_hour << ":0" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
								}
								else {
									cout << "0" << ltm->tm_hour << ":0" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
									fileC << "0" << ltm->tm_hour << ":0" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
								}
							}
							else {
								if (ltm->tm_sec < 10) {
									cout << "0" << ltm->tm_hour << ":" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
									fileC << "0" << ltm->tm_hour << ":" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
								}
								else {
									cout << "0" << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
									fileC << "0" << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
								}
							}
						}
						else {
							if (ltm->tm_min < 10) {
								if (ltm->tm_sec < 10) {
									cout << ltm->tm_hour << ":0" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
									fileC << ltm->tm_hour << ":0" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
								}
								else {
									cout << ltm->tm_hour << ":0" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
									fileC << ltm->tm_hour << ":0" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
								}
							}
							else {
								if (ltm->tm_sec < 10) {
									cout << ltm->tm_hour << ":" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
									fileC << ltm->tm_hour << ":" << ltm->tm_min << ":0" << ltm->tm_sec << "; ";
								}
								else {
									cout << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
									fileC << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "; ";
								}
							}
						}
					}

					containsDateOrTime = true;
				}
			}

			if (containsDateOrTime) {
				cout << endl;
				fileC << endl;
			}
		}

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileC.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileC.close();
	}

}
