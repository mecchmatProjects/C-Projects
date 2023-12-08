/*
Задача номер 12, група "Комп'ютерна математика 2", Табала Матвій.
б) Розв’яжіть дані задачі на С++ за допомогою функцій бібліотеки
(без регулярних виразів, тільки бібліотека <string>)
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

// Імпорт бібліотек і хедерів
#include "RegularExpressionsB.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <ctime>
using namespace std;

// Створення простору імен для того, щоб було зручніше працювати з функціями
namespace RegularExpressionsB {

	void findHyperlinks(const string& filename) {
		// Відкриття файлу для читання і запису
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::trunc);

		// Перевірка, чи вдалося відкрити файли
		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// Читання файлу по рядках
		string line;
		while (getline(file, line)) {
			istringstream iss(line); // Створення потоку для рядка
			string word, prevWord; // Поточне слово та попереднє слово

			while (iss >> word) {
				// Якщо слово починається з http, то вивести попереднє слово та поточне
				if (word.find("http") != string::npos) { // npos - значення, яке повертається, якщо не знайдено
					if (!prevWord.empty()) {
						cout << prevWord << " " << word << endl;
						fileB << prevWord << " " << word << endl;
					}
				}
				prevWord = word; // Зберігаємо поточне слово як попереднє
			}
		}

		cout << "\n";
		fileB << "\n";

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileB.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileB.close();
	}

	/*
	2) Знайти в даному текстовому файлі всі дати в форматах __.__.__ та
	__/__/__ (в кінці можуть бути 2 або 4 цифри, а також ____(рік).__.__) та
	перевести їх всі до єдиного формату __(рік) назва місяцю __(число).
	*/

	// Створення словника для перетворення числа місяця в назву місяця
	unordered_map<string, string> monthMap = {
		{"01", "January"}, {"02", "February"}, {"03", "March"},
		{"04", "April"}, {"05", "May"}, {"06", "June"},
		{"07", "July"}, {"08", "August"}, {"09", "September"},
		{"10", "October"}, {"11", "November"}, {"12", "December"}
	};

	// Перевірка, чи дата є правильною
	bool isValidDate(const string& date) {
		stringstream ss(date); // Створення потоку для дати
		char discard; // Змінна для зберігання символів, які будуть видалені
		int day, month, year; // Змінні для зберігання дня, місяця та року
		// Якщо дата починається з року (2019.12.05)
		if (date.find('.') == 4 || date.find('/') == 4) {
			ss >> year >> discard >> month >> discard >> day;
		}
		// Якщо дата починається з дня (05.12.2019) або (05/12/2019)
		else {
			ss >> day >> discard >> month >> discard >> year;
		}

		return ss.eof() && ss.fail() == false && month > 0 && month <= 12 && day > 0 && day <= 31;
	}

	// Перетворення дати до єдиного формату
	void convertDates(const string& filename) {
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::app);

		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// Читання файлу по рядках
		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string word, prevWord;

			while (iss >> word) {
				// якщо слово має довжину більше 8 символів і містить крапку або слеш, то це може бути дата
				if (word.size() >= 8 && (word.find('.') != string::npos || word.find('/') != string::npos)) {
					string cleanedDate = "";
					for (char c : word) {
						if (isdigit(c) || c == '.' || c == '/') {
							cleanedDate += c;
						}
					}

					// якщо дата є правильною, то вивести її у єдиному форматі
					if (isValidDate(cleanedDate)) {
						stringstream dateStream(cleanedDate);
						int day, month, year;
						char discard;
						// якщо дата починається з року (2019.12.05)
						if (cleanedDate.find('.') == 4 || cleanedDate.find('/') == 4) {
							dateStream >> year >> discard >> month >> discard >> day;
						}
						else {
							dateStream >> day >> discard >> month >> discard >> year;
						}

						if (year < 100) {
							if (year >= 0 && year <= 69) {
								year += 2000;
							}
							else {
								year += 1900;
							}
						}

						// якщо місяць має формат 1-9, то додати 0 перед ним
						string monthStr = month < 10 ? "0" + to_string(month) : to_string(month);
						string monthName = monthMap[monthStr]; // отримати назву місяця за допомогою словника

						cout << "Original date: " << word << " -> Uniform date: " << year << " " << monthName << " " << day << endl;
						fileB << "Original date: " << word << " -> Uniform date: " << year << " " << monthName << " " << day << endl;
					}
				}
			}
		}
		cout << "\n";
		fileB << "\n";

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileB.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileB.close();
	}

	/* 3) Знайти всі цілі та дійсні числа (в науковому та звичайному форматі з
	крапкою/комою) та привести їх до єдиного формату (дійсне число з
	фіксованою крапкою, точність 4 розряду) та оточити круглими дужками. */

	// Функція для перевірки, чи є слово числом
	bool isNumber(const string& word) {
		stringstream ss(word);
		double num;
		ss >> num;
		return ss.eof() && ss.fail() == false;
	}

	// Функція для перетворення чисел до єдиного формату
	void convertNumbers(const string& filename) {
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::app);

		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// Просто читаємо файл по рядках і перевіряємо, чи є слово числом, якщо так - виводимо його в єдиному форматі
		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string word, prevWord;

			while (iss >> word) {
				if (isNumber(word)) {
					stringstream ss(word);
					double num;
					ss >> num;
					cout << fixed << setprecision(4) << num << ", ";
					fileB << fixed << setprecision(4) << num << ", ";
				}
			}
		}
		cout << "\n\n";
		fileB << "\n\n";

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileB.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileB.close();
	}

	// Функція для перевірки, чи є час правильним
	bool isValidTime(const string& time) {
		int hour, minute, second;

		// Якщо час має формат hh:mm:ss
		if (sscanf_s(time.c_str(), "%d:%d:%d", &hour, &minute, &second) == 3) {
			if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
				return true;
			}
		}

		// Якщо час має формат hh:mm
		if (sscanf_s(time.c_str(), "%d:%d", &hour, &minute) == 2) {
			if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
				return true;
			}
		}

		return false;
	}

	/* 4) Змінити всі дати та записи часу у файлі на поточні дату та час. */
	void replaceDatesAndTimes(const char* filename) {
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::app);

		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// Проходимось по рядкам, визначаємо поточну дату та час і замінюємо їх у файлі
		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string word;
			bool containsDateOrTime = false;
			time_t now = time(0);
			tm* ltm = localtime(&now);

			while (iss >> word) {
				string cleanedWord;
				for (char c : word) {
					if (isdigit(c) || c == '.' || c == '/') {
						cleanedWord += c;
					}
				}

				// якщо слово має формат __.__.__ або __/__/__ то це може бути дата
				if (cleanedWord.find('.') != string::npos || cleanedWord.find('/') != string::npos) {
					string cleanedDate;
					for (char c : cleanedWord) {
						if (isdigit(c) || c == '.' || c == '/') {
							cleanedDate += c;
						}
					}

					// якщо дата є правильною, то вивести її у єдиному форматі
					if (isValidDate(cleanedDate)) {
						cout << 1900 + ltm->tm_year << " " << monthMap[to_string(1 + ltm->tm_mon)] << " " << ltm->tm_mday << "; ";
						fileB << 1900 + ltm->tm_year << " " << monthMap[to_string(1 + ltm->tm_mon)] << " " << ltm->tm_mday << "; ";
						containsDateOrTime = true;
					}
				}

				// якщо слово має формат hh:mm:ss або hh:mm то це може бути час
				if (word.find(':') != string::npos) {
					string cleanedTime;
					for (char c : word) {
						if (isdigit(c) || c == ':') {
							cleanedTime += c;
						}
					}

					// якщо час у форматі hh:mm:ss або hh:mm є правильним, то вивести його у єдиному форматі
					if (cleanedTime.length() == 8 && isValidTime(cleanedTime)) {
						// Виводимо час у форматі hh:mm:ss
						cout << setw(2) << setfill('0') << ltm->tm_hour << ":"
							<< setw(2) << setfill('0') << ltm->tm_min << ":"
							<< setw(2) << setfill('0') << ltm->tm_sec << "; ";

						fileB << setw(2) << setfill('0') << ltm->tm_hour << ":"
							<< setw(2) << setfill('0') << ltm->tm_min << ":"
							<< setw(2) << setfill('0') << ltm->tm_sec << "; ";
						containsDateOrTime = true;
					}
					else if (cleanedTime.length() == 5 && isValidTime(cleanedTime)) {
						cout << setw(2) << setfill('0') << ltm->tm_hour << ":"
							<< setw(2) << setfill('0') << ltm->tm_min << "; ";

						fileB << setw(2) << setfill('0') << ltm->tm_hour << ":"
							<< setw(2) << setfill('0') << ltm->tm_min << "; ";
						containsDateOrTime = true;
					}
				}
			}

			if (containsDateOrTime) {
				cout << endl;
				fileB << endl;
			}
		}

		// Перевіряємо, чи виникли помилки під час читання файлу
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileB.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileB.close();
	}

} 
