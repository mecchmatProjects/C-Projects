/*
������ ����� 12, ����� "����'������ ���������� 2", ������ �����.
�) �������� ��� ������ �� �++ �� ��������� ������� �������� <regex> (c++11)
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
#define _CRT_SECURE_NO_WARNINGS // ³��������� ����������� ��� ���������
#endif

// ϳ�������� �������� � �����
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

namespace RegularExpressionsC // �� ������ ����
{
	/* 1) � ������ ���������� ���� ������ �� ������������� �� ������� ��
	����� � ������ (����� �������������� �������� �� ������� ����������)
	�� ����� ����� ���. */

	void findHyperlinks(const string& filename) {
		// ³�������� ���� ��� �������
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::trunc); // ³�������� ���� ��� ������ � ���������
		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Unable to open file.\n";
			return;
		}

		// ������ ���� �� ������
		string line;
		regex linkRegex(R"(\S(\S+)\s+https?://\S+\b)"); // ���������� ����� ��� ������ ������������

		while (getline(file, line)) {
			smatch match;
			string::const_iterator searchStart(line.cbegin()); // ��������, �� ����� �� ������� �����
			
			// ����� ������������ � �����
			while (regex_search(searchStart, line.cend(), match, linkRegex)) {
				string hyperlink = match[0].str(); // �������� �������������
				cout << hyperlink << "\n";
				fileC << hyperlink << "\n";

				// ��������� ������� searchStart ��� ���������� ������
				searchStart = match.suffix().first;
			}
		}

		cout << "\n";
		fileC << "\n";

		// ����������, �� ������� ������� �� ��� ������� �����
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileC.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileC.close();
	}
	
	// �������, �� ������ ����� ������
	unordered_map<string, string> monthMap = {
		{"01", "January"}, {"02", "February"}, {"03", "March"},
		{"04", "April"}, {"05", "May"}, {"06", "June"},
		{"07", "July"}, {"08", "August"}, {"09", "September"},
		{"10", "October"}, {"11", "November"}, {"12", "December"}
	};

	// �������, �� ��������, �� � ���� ���������
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

	/* 2) ������ � ������ ���������� ���� �� ���� � �������� __.__.__ ��
	__/__/__ (� ���� ������ ���� 2 ��� 4 �����, � ����� ____(��).__.__) ��
	��������� �� �� �� ������� ������� __(��) ����� ����� __(�����). */

	// �������, �� ���������� ���� �� ������� �������
	void convertDates(const string& filename) {
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::app);

		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Unable to open file.\n";
			return;
		}

		// ������ ���� �� ������
		string line;
		regex dateRegex(R"(\b(\d{2}|\d{4})[./] ?(\d{2})[./] ?(\d{2}|\d{4})\b)"); // ���������� ����� ��� ������ ���
		regex yearRegex(R"(\b(\d{4})[./] ?(\d{2})[./] ?(\d{2})\b)"); // ���������� ����� ��� ������ ���, �� ����������� � ����

		while (getline(file, line)) {
			smatch match;
			string::const_iterator searchStart(line.cbegin()); // ��������, �� ����� �� ������� �����

			while (regex_search(searchStart, line.cend(), match, dateRegex)) {
				string date = match[0].str(); // �������� ����
				stringstream ss(date);
				char discard;
				int day, month, year;
				// ���� �� �������� ����� �������, �� ������ �� ����� 1900 ��� 2000 ����
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

				// ���� ����� �������� ���� ������, �� ������ �� ����� 0
				string monthStr = month < 10 ? "0" + to_string(month) : to_string(month);
				string monthName = monthMap[monthStr];

				// ������������ ���� �� ������� �������
				string uniformDate = to_string(year) + " " + monthName + " " + to_string(day);
				cout << "Original date: " << match[0].str() << " -> Uniform date: " << uniformDate << endl;

				fileC << "Original date: " << match[0].str() << " -> Uniform date: " << uniformDate << endl;

				// ��������� ������� searchStart ��� ���������� ������
				searchStart = match.suffix().first;
			}
		}
		cout << "\n";
		fileC << "\n";

		// ����������, �� ������� ������� �� ��� ������� �����
		if (file.bad()) {
			cerr << "Error occurred while reading file: " << filename << endl;
		}
		if (fileC.bad()) {
			cerr << "Error occurred while writing to file RegExpB.txt" << endl;
		}

		file.close();
		fileC.close();
	}

	/* 3) ������ �� ��� �� ���� ����� (� ��������� �� ���������� ������ �
	�������/�����) �� �������� �� �� ������� ������� (����� ����� �
	���������� �������, ������� 4 �������) �� ������� �������� �������. */

	// �������, �� ��������, �� � ����� ������
	void convertNumbers(const string& filename) {
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::app);

		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Unable to open file.\n";
			return;
		}

		string line;
		regex numberRegex(R"(\b(\d+\.?\d*)\b)"); // ����� ����� �� ������ �����
		regex scientificNumberRegex(R"(\b(\d+\.?\d*)e(\+|-)?(\d+)\b)"); // ����� ����� � ��������� ������
		regex hypertextRegex(R"(<.*?>)"); // ����� ������������

		while (getline(file, line)) {
			stringstream ss(line);
			string word;

			while (ss >> word) {
				// ��������� �������������
				word = regex_replace(word, hypertextRegex, "");

				if (regex_match(word, numberRegex) || regex_match(word, scientificNumberRegex)) {
					// ������������ ����� �� ������� �������
					double num = stod(word);
					cout << fixed << setprecision(4) << num << ", ";
					fileC << fixed << setprecision(4) << num << ", ";
				}
			}
		}
		cout << "\n\n";
		fileC << "\n\n";

		// ����������, �� ������� ������� �� ��� ������� �����
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

	// �������, �� ��������, �� � ��� ���������
	bool isValidTime(const string& time) {
		regex timeRegex(R"(\b(\d{2}):(\d{2})\b)"); // Regex to match time format HH:MM
		return regex_match(time, timeRegex);
	}

	// �������, �� ������ ���� �� ���� �� ������
	void replaceDatesAndTimes(const char* filename) {
		ifstream file(filename);
		fstream fileC("RegExpC.txt", ios::out | ios::app);

		if (!file.is_open() || !fileC.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		string line;
		regex timeRegex(R"(\b\d{1,2}:\d{2}(:\d{2})?\b)"); // ����� ���� � ������ HH:MM ��� HH:MM:SS
		regex hypertextRegex(R"(<.*?>)"); // ����� ������������

		while (getline(file, line)) {
			stringstream ss(line);
			string word;
			bool containsDateOrTime = false;
			time_t now = time(0); // �������� ���
			tm* ltm = localtime(&now); // ������������ �������� ��� �� ��������� tm

			while (ss >> word) {
				// ��������� �������������
				word = regex_replace(word, hypertextRegex, "");

				if (isValidDate(word)) {
					// �������� ������� ����
					cout << 1900 + ltm->tm_year << " "
						<< monthMap[to_string(1 + ltm->tm_mon)] << " "
						<< ltm->tm_mday << "; ";

					fileC << 1900 + ltm->tm_year << " "
						<< monthMap[to_string(1 + ltm->tm_mon)] << " "
						<< ltm->tm_mday << "; ";

					containsDateOrTime = true;
				}
				else if (regex_search(word, timeRegex)) {
					// ���������� ���� ����� ��� ���������� ������ ���� (HH:MM ��� HH:MM:SS) ��� ������� � ���� ������
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

		// ����������, �� ������� ������� �� ��� ������� �����
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
