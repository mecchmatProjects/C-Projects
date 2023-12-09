// ������ ����� 12, ����� "����'������ ���������� 2", ������ �����.
#ifdef _MSC_VER // ��� ���������� Microsoft Visual Studio
#define _CRT_SECURE_NO_WARNINGS // ��� �� ���������� ������������ ��� ������������ ����������� �������
#endif

extern "C" // ������� ��� ������ � �-���������
{
#include "RegularExpressionsA.h"
}

#include "RegularExpressionsB.h"
#include "RegularExpressionsC.h"

// ϳ�������� ��������
#include <iostream>
#include <fstream>

bool compareFiles(const char* p1, const char* p2) {
	// ³�������� ����� ��� �������
	std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate); // ate - ���������� �������� � ����� �����
	std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);  // binary - ������� ���� � �������� �����

	if (f1.fail() || f2.fail()) {
		return false; // �� ������� ������� ���� � �����
	}

	if (f1.tellg() != f2.tellg()) {
		return false; // ������ ����� �� ����������
	}

	// ������ ��������� �� ������� �����
	f1.seekg(0, std::ifstream::beg);
	f2.seekg(0, std::ifstream::beg);
	// ��������� ����� �����������
	return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::istreambuf_iterator<char>(f2.rdbuf())); // rdbuf - ����� �����-������
}

int main() {
	int choice; // ����� ��� ������ ������� �����
	const char* filename = "text.txt"; // ��'� �����, ���� ������ ���������

	// ���� 1, �� ������������� ���������� ���, ���� 2 - ��������
	std::cout << "Enter 1 to use console input or 2 to use file input: "; std::cin >> choice; std::cin.ignore();

	if (choice == 1) {
		for (int i = 0; i < 3; ++i) {
			// ��������� �������� �����
			std::string tempFilename = "temp" + std::to_string(i + 1) + ".txt";

			std::cout << "Enter input for RegularExpressions" << char('A' + i) << ": ";
			std::string userInput;
			std::getline(std::cin, userInput);

			// �������� � ��� ��� � ������
			std::ofstream file(tempFilename);
			if (file.is_open()) {
				file << userInput;

				file.close();
			}
			else {
				std::cerr << "Unable to open file for writing." << std::endl;
				return 1;
			}
		}
		std::cout << "\n";

		std::cout << "RegularExpressionsA:" << std::endl;
		findHyperlinks("temp1.txt");
		convertDates("temp1.txt");
		convertNumbers("temp1.txt");
		replaceDatesAndTimes("temp1.txt");

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		std::cout << "RegularExpressionsB:" << std::endl;
		RegularExpressionsB::findHyperlinks("temp2.txt");
		RegularExpressionsB::convertDates("temp2.txt");
		RegularExpressionsB::convertNumbers("temp2.txt");
		RegularExpressionsB::replaceDatesAndTimes("temp2.txt");

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		std::cout << "RegularExpressionsC:" << std::endl;
		RegularExpressionsC::findHyperlinks("temp3.txt");
		RegularExpressionsC::convertDates("temp3.txt");
		RegularExpressionsC::convertNumbers("temp3.txt");
		RegularExpressionsC::replaceDatesAndTimes("temp3.txt");

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		std::cout << "Comparing files:" << std::endl;
		std::cout << "A and B: " << (compareFiles("RegExpA.txt", "RegExpB.txt") ? "true" : "false") << std::endl;
		std::cout << "A and C: " << (compareFiles("RegExpA.txt", "RegExpC.txt") ? "true" : "false") << std::endl;
		std::cout << "B and C: " << (compareFiles("RegExpB.txt", "RegExpC.txt") ? "true" : "false") << std::endl;

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		if (compareFiles("RegExpA.txt", "RegExpB.txt") && compareFiles("RegExpA.txt", "RegExpC.txt") && compareFiles("RegExpB.txt", "RegExpC.txt")) {
			std::cout << "All files are equal!" << std::endl;
		}
		else {
			std::cout << "Files are not equal!" << std::endl;
		}
	}
	else if (choice == 2) {
		// ������ ������� � �����
		std::cout << "RegularExpressionsA:" << std::endl;
		findHyperlinks(filename);
		convertDates(filename);
		convertNumbers(filename);
		replaceDatesAndTimes(filename);

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		std::cout << "RegularExpressionsB:" << std::endl;
		RegularExpressionsB::findHyperlinks(filename);
		RegularExpressionsB::convertDates(filename);
		RegularExpressionsB::convertNumbers(filename);
		RegularExpressionsB::replaceDatesAndTimes(filename);

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		std::cout << "RegularExpressionsC:" << std::endl;
		RegularExpressionsC::findHyperlinks(filename);
		RegularExpressionsC::convertDates(filename);
		RegularExpressionsC::convertNumbers(filename);
		RegularExpressionsC::replaceDatesAndTimes(filename);

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		std::cout << "Comparing files:" << std::endl;
		std::cout << "A and B: " << (compareFiles("RegExpA.txt", "RegExpB.txt") ? "true" : "false") << std::endl;
		std::cout << "A and C: " << (compareFiles("RegExpA.txt", "RegExpC.txt") ? "true" : "false") << std::endl;
		std::cout << "B and C: " << (compareFiles("RegExpB.txt", "RegExpC.txt") ? "true" : "false") << std::endl;

		std::cout << "------------------------------------------------------------------------------------" << std::endl;

		if (compareFiles("RegExpA.txt", "RegExpB.txt") && compareFiles("RegExpA.txt", "RegExpC.txt") && compareFiles("RegExpB.txt", "RegExpC.txt")) {
			std::cout << "All files are equal!" << std::endl;
		}
		else {
			std::cout << "Files are not equal!" << std::endl;
		}
	}
	else {
		std::cout << "Invalid input!" << std::endl;
		return 1;
	}

	system("pause"); // ��������� �������
	return 0;
}
