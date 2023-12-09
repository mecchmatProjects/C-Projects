// ������ ����� 12, ����� "����'������ ���������� 2", ������ �����.
#pragma once // ��� ����� ��������� ��, �� ��� ���� ���� �������� ���� ���� ���
#include <string> // ��������� ��� ������ � ������� (std::string)

namespace RegularExpressionsC { // �� ������ ���� ��� RegularExpressionsC
    void findHyperlinks(const std::string& filename); // ����� ������������
    void convertDates(const std::string& filename); // ����������� ���
    void convertNumbers(const std::string& filename); // ����������� �����
    void replaceDatesAndTimes(const char* filename); // ����� ��� � ����
    bool isValidDate(const std::string& date); // ��������, �� � ���� ��������� 
    bool isValidTime(const std::string& time); // ��������, �� � ��� ���������
}
