// ������ ����� 12, ����� "����'������ ���������� 2", ������ �����.
#pragma once // ��� ����� ��������� ��, �� ��� ���� ���� �������� ���� ���� ���
#include <string.h> // ��������� ��� ������ � ������� (char*)

void findHyperlinks(const char* filename); // ����� ������������
void convertDates(const char* filename); // ����������� ���
void convertNumbers(const char* filename); // ����������� �����
void replaceDatesAndTimes(const char* filename); // ����� ��� � ����
