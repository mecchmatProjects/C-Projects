// ������ ����� 12, ����� "����'������ ���������� 2", ������ �����.
#pragma once // ��� ����� ��������� ��, �� ��� ���� ���� �������� ���� ���� ���
#include <string> // ��������� ��� ������ � ������� (std::string)
#include <vector> // ��������� ��� ������ � ��������� (std::vector)

namespace RegularExpressionsB { // �� ������ ����
    void findHyperlinks(const std::string& filename); // ����� ������������
    void convertDates(const std::string& filename); // ����������� ���
    void convertNumbers(const std::string& filename); // ����������� �����
    void replaceDatesAndTimes(const char* filename); // ����� ��� � ����
    bool isNumber(const std::string& word); // ��������, �� � ����� ������
    bool isValidDate(const std::string& date); // ��������, �� � ���� ���������
    bool isValidTime(const std::string& time); // ��������, �� � ��� ���������
}
