/* File Interval.h
Realization of Interval, SetIntervals and QuadraticInequality classes (Task 3)
Done by Kharchenko Oleksandr (group 2)
Date 11.29.2023
Headers for Interval, SetIntervals and QuadraticInequality classes
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#ifndef INTERVAL_H
#define INTERVAL_H

//��������� triple - ������ ���������� ��� ����� ���������
struct triple{
    bool is_closed=0;
    bool is_inf=0;
    float num=0;

};
//���� ��������
class Interval{
private:
    pair<bool, bool> is_closed; //first - ���� �����, second - ������, 0 - ����� ��������, 1 - ���������
    pair<bool, bool> type_interval; //first - ���� �����, second - ������, 0 - �������� �����, 1 - ������������
    float a;   //a,b - ����� � ��������, a<=b
    float b;
public:
    //����������� ��������� ��� ���������
    Interval();

    //����������� ��������� � �����������
    Interval(bool _cl, bool _cr, bool _tl, bool _tr, float _a, float _b);

    //setter - �������, �� �������� ��������� �������� ���������
    void setter(bool _cl, bool _cr, bool _tl, bool _tr, float _a, float _b);

    //������� ������� is_closed.first
    bool get_cl() const;

    //������� ������� is_closed.second
    bool get_cr() const;

    //������� ������� type_interval.first
    bool get_tl() const;

    //������� ������� type_interval.second
    bool get_tr() const;

    //������� ������� a
    float get_a() const;

    //������� ������� b
    float get_b() const;

    //������� ������� ������� ���������
    float length() const;

    //��������������� �������� ==, �������� �� ��� ��� ���������
    friend bool operator== (const Interval& I1,const Interval& I2);

    //��������������� �������� !=, �������� �� �� ��� ��� ���������
    friend bool operator!= (const Interval& I1,const Interval& I2);

    //��������������� �������� <<, ��������� ���������
    friend ostream&operator<<(ostream&output,const  Interval& I);

    //��������������� �������� >>, �������� ���������
    friend istream&operator>>(istream& input, Interval& I);

    //��������������� �������� *, �������� (�������) ���������
    friend Interval operator*(const Interval& I1,const Interval& I2);

};
//������� ��������� ������ ���� ���� ����� ���� ���������
triple lMin(Interval I1, Interval I2);

//������� ��������� ������ ���� ������ ����� ���� ���������
triple rMin(Interval I1, Interval I2);

//������� ��������� ������ ������ ���� ����� ���� ���������
triple lMax(Interval I1, Interval I2);

//������� ��������� ������ ������ ������ ����� ���� ���������
triple rMax(Interval I1, Interval I2);

//���� SetIntervals - ������ � ���������
class SetIntervals{
private:
    vector<Interval> v;
public:

    //����������� SetIntervals ��� ���������
    SetIntervals();

    //����������� SetIntervals � ����������
    SetIntervals(vector<Interval> _v);

    //������� ��������� ������� ��������� � ������
    int size() const;

    //������� ��������� ������� SetIntervals - ������� ������� ��� ��������� � ������
    float length() const;

    //getter - ������� ������ v
    vector<Interval> getter() const;

    //��������������� �������� <<, ��������� SetIntervals
    friend ostream&operator<<(ostream&output,const SetIntervals& S);

    //��������������� �������� >>, �������� SetIntervals
    friend istream&operator>>(istream&output, SetIntervals& S);

    //������� ���� �������� �� SetIntervals (��'�������)
    SetIntervals addn(const Interval& I) const;

    //��������������� �������� +, ��������� (��'�������) SetIntervals
    friend SetIntervals operator+(const SetIntervals& S1,const SetIntervals& S2);

    //��������������� �������� *, �������� (�������) SetIntervals
    friend SetIntervals operator*(const SetIntervals& S1,const SetIntervals& S2);

    //��������������� �������� -, ������ SetIntervals
    friend SetIntervals operator-(const SetIntervals& S1,const SetIntervals& S2);

    //��������������� �������� !=, �������� �� �� ��� ��� SetIntervals
    friend bool operator!= (const SetIntervals& S1,const SetIntervals& S2);

};

//��������������� �������� +, ��������� (��'�������) ���������
SetIntervals operator+ (const Interval& I1,const Interval& I2);

//��������������� �������� -, ������ ���������
SetIntervals operator- (const Interval& I1,const Interval& I2);

//������ ���������� ��� ����� ����������� �������
struct sols{
    int num=0; //������� ������. ���� num=3, �� ������������
    float x1=0; //����� 1
    float x2=0; //����� 2
};

//���� ��������� ��������
class QuadraticInequality{
private:
    float a;
    float b;
    float c;
    string t;
public:
    //����������� ��������� �������� ��� ���������
    QuadraticInequality();

    //����������� ��������� �������� � �����������
    QuadraticInequality(float _a, float _b, float _c, string _t);

    //������� ��������� ����� ����������� ������� ax^2+bx+c=0
    sols roots() const;

    //������� ��������� �������� ax^2+bx+c � ����� x
    float value(const float x) const;

    //������� ���������� ��������� �������� � SetIntervals
    SetIntervals toIntervals() const;

    //��������������� �������� <<, ��������� ��������� ��������
    friend ostream&operator<<(ostream&output,const QuadraticInequality& Q);

    //��������������� �������� >>, �������� ��������� ��������
    friend istream&operator>>(istream&input, QuadraticInequality& Q);

};


#endif // INTERVAL_H
