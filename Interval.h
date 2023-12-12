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

//структура triple - зберігає інформацію про кінець інтервала
struct triple{
    bool is_closed=0;
    bool is_inf=0;
    float num=0;

};
//клас Інтервал
class Interval{
private:
    pair<bool, bool> is_closed; //first - лівий кінець, second - правий, 0 - кінець відкритий, 1 - замкнутий
    pair<bool, bool> type_interval; //first - лівий кінець, second - правий, 0 - скінченне число, 1 - нескінченність
    float a;   //a,b - числа в інтервалі, a<=b
    float b;
public:
    //конструктор Інтервала без параметрів
    Interval();

    //конструктор Інтервала з параметрами
    Interval(bool _cl, bool _cr, bool _tl, bool _tr, float _a, float _b);

    //setter - функція, що присвоює інтервалу значення параметрів
    void setter(bool _cl, bool _cr, bool _tl, bool _tr, float _a, float _b);

    //функція повертає is_closed.first
    bool get_cl() const;

    //функція повертає is_closed.second
    bool get_cr() const;

    //функція повертає type_interval.first
    bool get_tl() const;

    //функція повертає type_interval.second
    bool get_tr() const;

    //функція повертає a
    float get_a() const;

    //функція повертає b
    float get_b() const;

    //функція повертає довжину інтервала
    float length() const;

    //перевизначається оператор ==, перевіряє чи рівні два Інтервали
    friend bool operator== (const Interval& I1,const Interval& I2);

    //перевизначається оператор !=, перевіряє чи не рівні два Інтервали
    friend bool operator!= (const Interval& I1,const Interval& I2);

    //перевизначається оператор <<, виведення Інтервала
    friend ostream&operator<<(ostream&output,const  Interval& I);

    //перевизначається оператор >>, введення Інтервала
    friend istream&operator>>(istream& input, Interval& I);

    //перевизначається оператор *, множення (перетин) Інтервалів
    friend Interval operator*(const Interval& I1,const Interval& I2);

};
//функція знаходить крайній зліва лівий кінець двох Інтервалів
triple lMin(Interval I1, Interval I2);

//функція знаходить крайній зліва правий кінець двох Інтервалів
triple rMin(Interval I1, Interval I2);

//функція знаходить крайній справа лівий кінець двох Інтервалів
triple lMax(Interval I1, Interval I2);

//функція знаходить крайній справа правий кінець двох Інтервалів
triple rMax(Interval I1, Interval I2);

//клас SetIntervals - вектор з Інтервалів
class SetIntervals{
private:
    vector<Interval> v;
public:

    //конструктор SetIntervals без параметрів
    SetIntervals();

    //конструктор SetIntervals з параметром
    SetIntervals(vector<Interval> _v);

    //функція знаходить кількість Інтервалів у векторі
    int size() const;

    //функція знаходить довжину SetIntervals - сумарна довжина всіх Інтервалів у векторі
    float length() const;

    //getter - повертає вектор v
    vector<Interval> getter() const;

    //перевизначається оператор <<, виведення SetIntervals
    friend ostream&operator<<(ostream&output,const SetIntervals& S);

    //перевизначається оператор >>, введення SetIntervals
    friend istream&operator>>(istream&output, SetIntervals& S);

    //функція додає Інтервал до SetIntervals (об'єднання)
    SetIntervals addn(const Interval& I) const;

    //перевизначається оператор +, додавання (об'єднання) SetIntervals
    friend SetIntervals operator+(const SetIntervals& S1,const SetIntervals& S2);

    //перевизначається оператор *, множення (перетин) SetIntervals
    friend SetIntervals operator*(const SetIntervals& S1,const SetIntervals& S2);

    //перевизначається оператор -, різниця SetIntervals
    friend SetIntervals operator-(const SetIntervals& S1,const SetIntervals& S2);

    //перевизначається оператор !=, перевіряє чи не рівні два SetIntervals
    friend bool operator!= (const SetIntervals& S1,const SetIntervals& S2);

};

//перевизначається оператор +, додавання (об'єднання) Інтервалів
SetIntervals operator+ (const Interval& I1,const Interval& I2);

//перевизначається оператор -, різниця Інтервалів
SetIntervals operator- (const Interval& I1,const Interval& I2);

//зберігає інформацію про корені квадратного рівняння
struct sols{
    int num=0; //кількість коренів. Якщо num=3, то нескінченність
    float x1=0; //корінь 1
    float x2=0; //корінь 2
};

//клас Квадратна Нерівність
class QuadraticInequality{
private:
    float a;
    float b;
    float c;
    string t;
public:
    //конструктор Квадратної Нерівності без параметрів
    QuadraticInequality();

    //конструктор Квадратної Нерівності з параметрами
    QuadraticInequality(float _a, float _b, float _c, string _t);

    //функція знаходить корені квадратного рівняння ax^2+bx+c=0
    sols roots() const;

    //функція знаходить значення ax^2+bx+c в точці x
    float value(const float x) const;

    //функція перетворює Квадратну Нерівність в SetIntervals
    SetIntervals toIntervals() const;

    //перевизначається оператор <<, виведення Квадратної нерівності
    friend ostream&operator<<(ostream&output,const QuadraticInequality& Q);

    //перевизначається оператор >>, введення Квадратної нерівності
    friend istream&operator>>(istream&input, QuadraticInequality& Q);

};


#endif // INTERVAL_H
