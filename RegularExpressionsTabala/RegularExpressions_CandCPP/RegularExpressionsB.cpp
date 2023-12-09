/*
������ ����� 12, ����� "����'������ ���������� 2", ������ �����.
�) �������� ��� ������ �� �++ �� ��������� ������� ��������
(��� ���������� ������, ����� �������� <string>)
1) � ������ ���������� ���� ������ �� ������������� �� ������� ��
����� � ������ (����� �������������� �������� �� ������� ����������)
�� ����� ����� ���.
2) ������ � ������ ���������� ���� �� ���� � �������� __.__.__ ��
__/__/__ (� ���� ������ ���� 2 ��� 4 �����, � ����� ____(��).__.__) ��
��������� �� �� �� ������� ������� __(��) ����� ����� __(�����).
3) ������ �� ��� �� ���� ����� (� ��������� �� ���������� ������ �
�������/�����) �� �������� �� �� ������� ������� (����� ����� �
���������� �������, ������� 4 �������) �� ������� �������� �������.
4) ������ �� ���� �� ������ ���� � ���� �� ������ ����
�� ���. */

#ifdef _MSC_VER // ��� ���������� Microsoft Visual Studio
#define _CRT_SECURE_NO_WARNINGS // ³��������� ����������� ��� ������������ ����������� �������
#endif

// ������ ������� � ������
#include "RegularExpressionsB.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <ctime>
using namespace std;

// ��������� �������� ���� ��� ����, ��� ���� ������� ��������� � ���������
namespace RegularExpressionsB {

	void findHyperlinks(const string& filename) {
		// ³������� ����� ��� ������� � ������
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::trunc);

		// ��������, �� ������� ������� �����
		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// ������� ����� �� ������
		string line;
		while (getline(file, line)) {
			istringstream iss(line); // ��������� ������ ��� �����
			string word, prevWord; // ������� ����� �� �������� �����

			while (iss >> word) {
				// ���� ����� ���������� � http, �� ������� �������� ����� �� �������
				if (word.find("http") != string::npos) { // npos - ��������, ��� �����������, ���� �� ��������
					if (!prevWord.empty()) {
						cout << prevWord << " " << word << endl;
						fileB << prevWord << " " << word << endl;
					}
				}
				prevWord = word; // �������� ������� ����� �� ��������
			}
		}

		cout << "\n";
		fileB << "\n";

		// ����������, �� ������� ������� �� ��� ������� �����
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
	2) ������ � ������ ���������� ���� �� ���� � �������� __.__.__ ��
	__/__/__ (� ���� ������ ���� 2 ��� 4 �����, � ����� ____(��).__.__) ��
	��������� �� �� �� ������� ������� __(��) ����� ����� __(�����).
	*/

	// ��������� �������� ��� ������������ ����� ����� � ����� �����
	unordered_map<string, string> monthMap = {
		{"01", "January"}, {"02", "February"}, {"03", "March"},
		{"04", "April"}, {"05", "May"}, {"06", "June"},
		{"07", "July"}, {"08", "August"}, {"09", "September"},
		{"10", "October"}, {"11", "November"}, {"12", "December"}
	};

	// ��������, �� ���� � ����������
	bool isValidDate(const string& date) {
		stringstream ss(date); // ��������� ������ ��� ����
		char discard; // ����� ��� ��������� �������, �� ������ �������
		int day, month, year; // ���� ��� ��������� ���, ����� �� ����
		// ���� ���� ���������� � ���� (2019.12.05)
		if (date.find('.') == 4 || date.find('/') == 4) {
			ss >> year >> discard >> month >> discard >> day;
		}
		// ���� ���� ���������� � ��� (05.12.2019) ��� (05/12/2019)
		else {
			ss >> day >> discard >> month >> discard >> year;
		}

		return ss.eof() && ss.fail() == false && month > 0 && month <= 12 && day > 0 && day <= 31;
	}

	// ������������ ���� �� ������� �������
	void convertDates(const string& filename) {
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::app);

		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// ������� ����� �� ������
		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string word, prevWord;

			while (iss >> word) {
				// ���� ����� �� ������� ����� 8 ������� � ������ ������ ��� ����, �� �� ���� ���� ����
				if (word.size() >= 8 && (word.find('.') != string::npos || word.find('/') != string::npos)) {
					string cleanedDate = "";
					for (char c : word) {
						if (isdigit(c) || c == '.' || c == '/') {
							cleanedDate += c;
						}
					}

					// ���� ���� � ����������, �� ������� �� � ������� ������
					if (isValidDate(cleanedDate)) {
						stringstream dateStream(cleanedDate);
						int day, month, year;
						char discard;
						// ���� ���� ���������� � ���� (2019.12.05)
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

						// ���� ����� �� ������ 1-9, �� ������ 0 ����� ���
						string monthStr = month < 10 ? "0" + to_string(month) : to_string(month);
						string monthName = monthMap[monthStr]; // �������� ����� ����� �� ��������� ��������

						cout << "Original date: " << word << " -> Uniform date: " << year << " " << monthName << " " << day << endl;
						fileB << "Original date: " << word << " -> Uniform date: " << year << " " << monthName << " " << day << endl;
					}
				}
			}
		}
		cout << "\n";
		fileB << "\n";

		// ����������, �� ������� ������� �� ��� ������� �����
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileB.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileB.close();
	}

	/* 3) ������ �� ��� �� ���� ����� (� ��������� �� ���������� ������ �
	�������/�����) �� �������� �� �� ������� ������� (����� ����� �
	���������� �������, ������� 4 �������) �� ������� �������� �������. */

	// ������� ��� ��������, �� � ����� ������
	bool isNumber(const string& word) {
		stringstream ss(word);
		double num;
		ss >> num;
		return ss.eof() && ss.fail() == false;
	}

	// ������� ��� ������������ ����� �� ������� �������
	void convertNumbers(const string& filename) {
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::app);

		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// ������ ������ ���� �� ������ � ����������, �� � ����� ������, ���� ��� - �������� ���� � ������� ������
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

		// ����������, �� ������� ������� �� ��� ������� �����
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileB.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileB.close();
	}

	// ������� ��� ��������, �� � ��� ����������
	bool isValidTime(const string& time) {
		int hour, minute, second;

		// ���� ��� �� ������ hh:mm:ss
		if (sscanf_s(time.c_str(), "%d:%d:%d", &hour, &minute, &second) == 3) {
			if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
				return true;
			}
		}

		// ���� ��� �� ������ hh:mm
		if (sscanf_s(time.c_str(), "%d:%d", &hour, &minute) == 2) {
			if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
				return true;
			}
		}

		return false;
	}

	/* 4) ������ �� ���� �� ������ ���� � ���� �� ������ ���� �� ���. */
	void replaceDatesAndTimes(const char* filename) {
		ifstream file(filename);
		fstream fileB("RegExpB.txt", ios::out | ios::app);

		if (!file.is_open() || !fileB.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// ����������� �� ������, ��������� ������� ���� �� ��� � �������� �� � ����
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

				// ���� ����� �� ������ __.__.__ ��� __/__/__ �� �� ���� ���� ����
				if (cleanedWord.find('.') != string::npos || cleanedWord.find('/') != string::npos) {
					string cleanedDate;
					for (char c : cleanedWord) {
						if (isdigit(c) || c == '.' || c == '/') {
							cleanedDate += c;
						}
					}

					// ���� ���� � ����������, �� ������� �� � ������� ������
					if (isValidDate(cleanedDate)) {
						cout << 1900 + ltm->tm_year << " " << monthMap[to_string(1 + ltm->tm_mon)] << " " << ltm->tm_mday << "; ";
						fileB << 1900 + ltm->tm_year << " " << monthMap[to_string(1 + ltm->tm_mon)] << " " << ltm->tm_mday << "; ";
						containsDateOrTime = true;
					}
				}

				// ���� ����� �� ������ hh:mm:ss ��� hh:mm �� �� ���� ���� ���
				if (word.find(':') != string::npos) {
					string cleanedTime;
					for (char c : word) {
						if (isdigit(c) || c == ':') {
							cleanedTime += c;
						}
					}

					// ���� ��� � ������ hh:mm:ss ��� hh:mm � ����������, �� ������� ���� � ������� ������
					if (cleanedTime.length() == 8 && isValidTime(cleanedTime)) {
						// �������� ��� � ������ hh:mm:ss
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

		// ����������, �� ������� ������� �� ��� ������� �����
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
