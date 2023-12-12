/* File Interval.cpp
Realzation of Interval, SetIntervals and QuadraticInequality class functions
Done by Kharchenko Oleksandr (group 2)
Date 11.29.2023
Implementation of  Interval, SetIntervals and QuadraticInequality classes
*/

#include <iostream>
#include "Interval.h"

using namespace std;

//конструктор Інтервала без параметрів
Interval::Interval(){
    is_closed.first=0;
    is_closed.second=0;
    type_interval.first=0;
    type_interval.second=0;
    a=0;
    b=0;
};

//конструктор Інтервала з параметрами
Interval::Interval(bool _cl, bool _cr, bool _tl, bool _tr, float _a, float _b){
    type_interval.first=_tl;
    type_interval.second=_tr;
    _cl=_cl&(!_tl);
    _cr=_cr&(!_tr);
    is_closed.first=_cl;
    is_closed.second=_cr;

    if ((_a>=_b) && (!(_tl|_tr))&&(!(_cl&_cr))){
        a=0;
        b=0;
        is_closed.first=0;
        is_closed.second=0;
    }else{
        if(_a>_b && (_cl&_cr) && (!(_tl|_tr))){
            a=0;
            b=0;
            is_closed.first=0;
            is_closed.second=0;
        }else{
        a=_a;
        b=_b;
        }
    }
}

//setter - функція, що присвоює інтервалу значення параметрів
void Interval::setter(bool _cl, bool _cr, bool _tl, bool _tr, float _a, float _b) {
    type_interval.first=_tl;
    type_interval.second=_tr;
    _cl=_cl&(!_tl);
    _cr=_cr&(!_tr);
    is_closed.first=_cl;
    is_closed.second=_cr;

    if (_a>=_b && (!(_tl|_tr))&&(!(_cl&_cr))){
        a=0;
        b=0;
        is_closed.first=0;
        is_closed.second=0;
    }else{
        if(_a>_b && (_cl&_cr) && (!(_tl|_tr))){
            a=0;
            b=0;
            is_closed.first=0;
            is_closed.second=0;
        }else{
        a=_a;
        b=_b;
        }
    }
}

//функція повертає is_closed.first
bool Interval::get_cl() const{
    return is_closed.first;
}

//функція повертає is_closed.second
bool Interval::get_cr() const{
    return is_closed.second;
}


//функція повертає type_interval.first
bool Interval::get_tl() const{
    return type_interval.first;
}

//функція повертає type_interval.second
bool Interval::get_tr() const{
    return type_interval.second;
}

//функція повертає a
float Interval::get_a() const{
    return a;
}

//функція повертає b
float Interval::get_b() const{
    return b;
}

//функція знаходить крайній зліва лівий кінець двох Інтервалів
triple lMin(Interval I1, Interval I2){
    triple T;
    if (I1.get_tl() || I2.get_tl()){
        T.is_inf=1;
        return T;
    }

    if (I1.get_a()<I2.get_a()){
        T.is_closed=I1.get_cl();
        T.num=I1.get_a();
        return T;
    }
    if(I1.get_a()>I2.get_a()){
        T.is_closed=I2.get_cl();
        T.num=I2.get_a();
        return T;
    }
    T.is_closed=I1.get_cl()||I2.get_cl();
    T.num=I1.get_a();
    return T;
}

//функція знаходить крайній зліва правий кінець двох Інтервалів
triple rMin(Interval I1, Interval I2){
    triple T;
    if (I1.get_tr() && I2.get_tr()){
        T.is_inf=1;
        return T;
    }

    if (!I1.get_tr() && I2.get_tr()){
        T.is_closed=I1.get_cr();
        T.num=I1.get_b();
        return T;
    }

    if (I1.get_tr() && !I2.get_tr()){
        T.is_closed=I2.get_cr();
        T.num=I2.get_b();
        return T;
    }

    if (I1.get_b()<I2.get_b()){
        T.is_closed=I1.get_cr();
        T.num=I1.get_b();
        return T;
    }

    if (I1.get_b()>I2.get_b()){
        T.is_closed=I2.get_cr();
        T.num=I2.get_b();
        return T;
    }

    T.is_closed=I1.get_cr()&&I2.get_cr();
    T.num=I1.get_b();
    return T;
}

//функція знаходить крайній справа лівий кінець двох Інтервалів
triple lMax(Interval I1, Interval I2){
    triple T;
    if (I1.get_tl() && I2.get_tl()){
        T.is_inf=1;
        return T;
    }

    if (!I1.get_tl() && I2.get_tl()){
        T.is_closed=I1.get_cl();
        T.num=I1.get_a();
        return T;
    }

    if (I1.get_tl() && !I2.get_tl()){
        T.is_closed=I2.get_cl();
        T.num=I2.get_a();
        return T;
    }

    if (I1.get_a()>I2.get_a()){
        T.is_closed=I1.get_cl();
        T.num=I1.get_a();
        return T;
    }

    if (I1.get_a()<I2.get_a()){
        T.is_closed=I2.get_cl();
        T.num=I2.get_a();
        return T;
    }

    T.is_closed=I1.get_cl()&&I2.get_cl();
    T.num=I1.get_a();
    return T;
}

//функція знаходить крайній справа правий кінець двох Інтервалів
triple rMax(Interval I1, Interval I2){
    triple T;
    if (I1.get_tr() || I2.get_tr()){
        T.is_inf=1;
        return T;
    }

    if (I1.get_b()>I2.get_b()){
        T.is_closed=I1.get_cr();
        T.num=I1.get_b();
        return T;
    }
    if(I1.get_b()<I2.get_b()){
        T.is_closed=I2.get_cr();
        T.num=I2.get_b();
        return T;
    }
    T.is_closed=I1.get_cr()||I2.get_cr();
    T.num=I1.get_b();
    return T;
}

//функція повертає довжину інтервала
float Interval::length() const{
    if(type_interval.first||type_interval.second){
        return -1;
    }else{
        return b-a;
    }
}

//перевизначається оператор ==, перевіряє чи рівні два Інтервали
bool operator== (const Interval& I1,const Interval& I2){
    float eps=10e-7;
    if (I1.type_interval!=I2.type_interval){
        return false;
    }
    if(I1.is_closed!=I2.is_closed){
        return false;
    }
    if ((!I1.type_interval.first)&&(!I1.type_interval.second)){
        if(abs(I1.a-I2.a)<eps && abs(I1.b-I2.b)<eps){
            return true;
        }else{
            return false;
        }
    }

    if((I1.type_interval.first)&&(!I1.type_interval.second)){
        if(abs(I1.b-I2.b)<eps){
            return true;
        }else{
            return false;
        }
    }

    if((!I1.type_interval.first)&&(I1.type_interval.second)){
        if(abs(I1.a-I2.a)<eps){
            return true;
        }else{
            return false;
        }
    }

    return true;
};

//перевизначається оператор !=, перевіряє чи не рівні два Інтервали
bool operator!= (const Interval& I1,const Interval& I2){
    return !(I1==I2);
}

//перевизначається оператор <<, виведення Інтервала
ostream& operator << (ostream& output,const Interval& I){
    if(I.get_cl()){
        output<<"[";
    }else{
        output<<"(";
    }

    if(I.get_tl()){
        output<<"-inf, ";
    }else{
        output<<I.a<<", ";
    }
    if(I.get_tr()){
        output<<"inf";
    }else{
        output<<I.b;
    }

    if(I.get_cr()){
        output<<"]";
    }else{
        output<<")";
    }
    return output;
}

//перевизначається оператор >>, введення Інтервала
istream& operator >> (istream& input, Interval &I){
    string a,b;
    input>>a>>b;
    if(a[a.length()-1]==','){
        a=a.substr(0,a.length()-1);
    }
    if (a[0]=='['){
        I.is_closed.first=1;
    }else{
        I.is_closed.first=0;
    }

    if (b[b.length()-1]==']'){
        I.is_closed.second=1;
    }else{
        I.is_closed.second=0;
    }

    a=a.substr(1,a.length()-1);
    b=b.substr(0,b.length()-1);
    if (a=="-inf"){
        I.type_interval.first=1;
        I.a=0;
    }else{
        I.type_interval.first=0;
        I.a=stof(a);
    }

    if (b=="inf"){
        I.type_interval.second=1;
        I.b=0;
    }else{
        I.type_interval.second=0;
        I.b=stof(b);
    }

    I.setter(I.get_cl(), I.get_cr(),I.get_tl(), I.get_tr(), I.get_a(),I.get_b());
    return input;
}

//перевизначається оператор *, множення (перетин) Інтервалів
Interval operator * (const Interval& I1,const Interval& I2){
    triple P1, P2;
    P1=lMax(I1,I2);
    P2=rMin(I1,I2);
    Interval I(P1.is_closed, P2.is_closed, P1.is_inf,P2.is_inf, P1.num, P2.num);
    return I;
}

//конструктор SetIntervals без параметрів
SetIntervals::SetIntervals(){
    v=vector<Interval>();
}

//конструктор SetIntervals з параметром
SetIntervals::SetIntervals(vector<Interval> _v){
    v=vector<Interval>();
    for (int i=0; i<_v.size();++i){
        if(_v[i]!=Interval()){
            v.push_back(_v[i]);
        }
    }
}

//функція знаходить кількість Інтервалів у векторі
int SetIntervals::size() const{
    return v.size();
}

//функція знаходить довжину SetIntervals - сумарна довжина всіх Інтервалів у векторі
float SetIntervals::length() const{
    float sum=0;
    for (int i=0; i<v.size(); ++i){
        float l=v[i].length();
        if (l<0){
            return -1;
        }
        sum+=l;
    }
    return sum;
}

//getter - повертає вектор v
vector<Interval> SetIntervals::getter() const{
    return v;
}

//перевизначається оператор <<, виведення SetIntervals
ostream& operator << (ostream& output,const SetIntervals& S){
    vector<Interval> v=S.getter();
    output<<"< ";
    if(S.size()){
        for (int i=0; i<S.size(); ++i){
            output<<v[i]<<" ";
        }
    }else{
        output<<"Empty ";
    }
    output<<">";
    return output;
}

//перевизначається оператор >>, введення SetIntervals
istream& operator >> (istream& input, SetIntervals& S){
    int n;
    vector<Interval> v;
    if (&input==&cin){
        cout<<"Enter number of intervals: ";
    }
    input>>n;
    if (n==0){
        S=SetIntervals(v);
        return input;
    }
    if (&input==&cin){
    cout<<"Enter intervals: ";
    }
    Interval I;
    for (int i=0; i<n; ++i){
        input>>I;
        v.push_back(I);
    }

    S=SetIntervals(v);
    return input;
}

//перевизначається оператор +, додавання (об'єднання) Інтервалів
SetIntervals operator+ (const Interval& I1,const Interval& I2){
    vector<Interval> v;
    if ((I1*I2)==Interval()){
        if (I1.get_b()<I2.get_a()&&(!I1.get_tr())&&(!I2.get_tl())){
            v.push_back(I1);
            v.push_back(I2);
            return SetIntervals(v);
        }
        if (I2.get_b()<I1.get_a()&&(!I2.get_tr())&&(!I1.get_tl())){
            v.push_back(I2);
            v.push_back(I1);
            return SetIntervals(v);
        }
        triple P1, P2, P3, P4;
        P1=lMin(I1,I2);
        P2=lMax(I1,I2);
        P3=rMin(I1,I2);
        P4=rMax(I1,I2);
        if (!(P2.is_closed||P3.is_closed)){
            v.push_back(Interval(P1.is_closed,0, P1.is_inf, P2.is_inf, P1.num, P2.num));
            v.push_back(Interval(0,P4.is_closed, P3.is_inf, P4.is_inf, P3.num, P4.num));
            return SetIntervals(v);
        }
            v.push_back(Interval(P1.is_closed, P4.is_closed, P1.is_inf, P4.is_inf, P1.num, P4.num));
            return SetIntervals(v);
    }else{
        triple P1, P2;
        P1=lMin(I1,I2);
        P2=rMax(I1,I2);
        v.push_back(Interval(P1.is_closed, P2.is_closed, P1.is_inf, P2.is_inf, P1.num, P2.num));
        return SetIntervals(v);

    }
};

//перевизначається оператор -, різниця Інтервалів
SetIntervals operator- (const Interval& I1,const Interval& I2){
    Interval I=I1*I2;
    vector<Interval> v;
    if (I==Interval()){
        v.push_back(I1);
        return SetIntervals(v);
    }
    if (!I.get_tl()){
        v.push_back(Interval(I1.get_cl(),!I.get_cl(),I1.get_tl(),0,I1.get_a(),I.get_a()));
    }
    if (!I.get_tr()){
        v.push_back(Interval(!I.get_cr(),I1.get_cr(),0,I1.get_tr(),I.get_b(),I1.get_b()));
    }
    return SetIntervals(v);
}

//перевизначається оператор *, множення (перетин) SetIntervals
SetIntervals operator* (const SetIntervals& S1, const SetIntervals& S2){
    vector<Interval> v;
    for (int i=0; i<S1.size(); ++i){
        for (int j=0; j<S2.size(); ++j){
            v.push_back(S1.getter()[i]*S2.getter()[j]);
        }
    }
    return SetIntervals(v);
}

//функція додає Інтервал до SetIntervals (об'єднання)
SetIntervals SetIntervals::addn (const Interval& I) const {
    vector<Interval> v1;
    Interval I1=I;
    for (int i=0; i<v.size(); ++i){
            if((v[i]+I1).size()==1){
                I1=(v[i]+I1).getter()[0];
            }else{
                v1.push_back(v[i]);
            }
        }
    v1.push_back(I1);
    return SetIntervals(v1);
}

//перевизначається оператор +, додавання (об'єднання) SetIntervals
SetIntervals operator+ (const SetIntervals& S1, const SetIntervals& S2){

    SetIntervals S=S1;
    for (int j=0; j<S2.size(); ++j){
        S=S.addn(S2.getter()[j]);
    }
    return S;
}

//перевизначається оператор -, різниця SetIntervals
SetIntervals operator- (const SetIntervals& S1, const SetIntervals& S2){
    SetIntervals S3, S=S1;
    vector<Interval> v;
    for (int j=0; j<S2.size(); ++j){
        for (int i=0; i<S.size();++i){
            S3=S.getter()[i]-S2.getter()[j];
            for (int k=0; k<S3.size(); ++k){
                v.push_back(S3.getter()[k]);
            }
        }
        S=SetIntervals(v);
        v.clear();
    }
    return S;
}

//перевизначається оператор !=, перевіряє чи не рівні два SetIntervals
bool operator!= (const SetIntervals& S1,const SetIntervals& S2){
    if(S1.size()!=S2.size()){
        return true;
    }
    for(int i=0; i<S1.size(); ++i){
        int eq=0;
        for(int j=0; j<S2.size(); ++j){
            if(S1.getter()[i]==S2.getter()[j]){
                eq=1;
                break;
            }
        }
        if(eq==0){
            return true;
        }
    }
    return false;
};

//конструктор Квадратної Нерівності без параметрів
QuadraticInequality::QuadraticInequality(){
    a=0;
    b=0;
    c=0;
    t="";
}

//конструктор Квадратної Нерівності з параметрами
QuadraticInequality::QuadraticInequality(float _a, float _b, float _c, string _t){
    a=_a;
    b=_b;
    c=_c;
    t=_t;
}

//функція знаходить корені квадратного рівняння ax^2+bx+c=0
sols QuadraticInequality::roots() const{
    float eps=10e-7;
    sols res;
    if (abs(a)<eps){
        if(abs(b)<eps){
            if (abs(c)<eps){
                res.num=3;
                return res;
            }else{
                return res;
            }
        }else{
            res.num=1;
            res.x1=-c/b;
            return res;
        }
    }else{
        float D=b*b-4*a*c;
        if(D<0){
            return res;
        }
        if(D>0){
            res.num=2;
            if(a>0){
                res.x1=(-b-sqrt(D))/(2*a);
                res.x2=(-b+sqrt(D))/(2*a);
            }else{
                res.x1=(-b+sqrt(D))/(2*a);
                res.x2=(-b-sqrt(D))/(2*a);
            }
            return res;
        }
        res.num=1;
        res.x1=(-b+sqrt(D))/(2*a);
        return res;

    }
}

//функція знаходить значення ax^2+bx+c в точці x
float QuadraticInequality::value(const float x) const{
    return a*x*x+b*x+c;
}

//функція перетворює Квадратну Нерівність в SetIntervals
SetIntervals QuadraticInequality::toIntervals() const{
    sols r=this->roots();
    vector<Interval> v;
    switch(r.num){
    case 3:
        if(t==">"||t=="<"||t=="!="){
            return SetIntervals(v);
        }else{
            v.push_back(Interval(0,0,1,1,0,0));
            return SetIntervals(v);
        }


    case 2:

        if(t=="="){
            v.push_back(Interval(1,1,0,0,r.x1,r.x1));
            v.push_back(Interval(1,1,0,0,r.x2,r.x2));
            return SetIntervals(v);
        }

        if(t=="!="){
            v.push_back(Interval(0,0,1,0,0,r.x1));
            v.push_back(Interval(0,0,0,0,r.x1,r.x2));
            v.push_back(Interval(0,0,0,1,r.x2,0));
            return SetIntervals(v);
        }

        if (t=="<"){
            if(this->value(r.x1-1)<0){
                v.push_back(Interval(0,0,1,0,0,r.x1));
                v.push_back(Interval(0,0,0,1,r.x2,0));
            }else{
                v.push_back(Interval(0,0,0,0,r.x1,r.x2));
            }
            return SetIntervals(v);
        }

        if (t=="<="){
            if(this->value(r.x1-1)<0){
                v.push_back(Interval(0,1,1,0,0,r.x1));
                v.push_back(Interval(1,0,0,1,r.x2,0));
            }else{
                v.push_back(Interval(1,1,0,0,r.x1,r.x2));
            }
            return SetIntervals(v);
        }

        if (t==">"){
            if(this->value(r.x1-1)>0){
                v.push_back(Interval(0,0,1,0,0,r.x1));
                v.push_back(Interval(0,0,0,1,r.x2,0));
            }else{
                v.push_back(Interval(0,0,0,0,r.x1,r.x2));
            }
            return SetIntervals(v);
        }

        if (t==">="){
            if(this->value(r.x1-1)>0){
                v.push_back(Interval(0,1,1,0,0,r.x1));
                v.push_back(Interval(1,0,0,1,r.x2,0));
            }else{
                v.push_back(Interval(1,1,0,0,r.x1,r.x2));
            }
            return SetIntervals(v);
        }

    case 1:
        if(t=="="){
            v.push_back(Interval(1,1,0,0,r.x1,r.x1));
            return SetIntervals(v);
        }
        if (t=="!="){
            v.push_back(Interval(0,0,1,0,0,r.x1));
            v.push_back(Interval(0,0,0,1,r.x1,0));
            return SetIntervals(v);
        }
        if(t==">"){
            if(this->value(r.x1-1)>0){
                v.push_back(Interval(0,0,1,0,0,r.x1));
            }
            if(this->value(r.x1+1)>0){
                v.push_back(Interval(0,0,0,1,r.x1,0));
            }
            return SetIntervals(v);
        }
        if(t==">="){
            if(a>0){
                v.push_back(Interval(0,0,1,1,0,0));
                return SetIntervals(v);
            }
            if(a<0){
                v.push_back(Interval(1,1,0,0,r.x1,r.x1));
                return SetIntervals(v);
            }
            if(this->value(r.x1-1)>0){
                v.push_back(Interval(0,1,1,0,0,r.x1));
                return SetIntervals(v);
            }
            if(this->value(r.x1+1)>0){
                v.push_back(Interval(1,0,0,1,r.x1,0));
                return SetIntervals(v);
            }

        }

        if(t=="<"){
            if(this->value(r.x1-1)<0){
                v.push_back(Interval(0,0,1,0,0,r.x1));
            }
            if(this->value(r.x1+1)<0){
                v.push_back(Interval(0,0,0,1,r.x1,0));
            }
            return SetIntervals(v);
        }

        if(t=="<="){
            if(a<0){
                v.push_back(Interval(0,0,1,1,0,0));
                return SetIntervals(v);
            }
            if(a>0){
                v.push_back(Interval(1,1,0,0,r.x1,r.x1));
                return SetIntervals(v);
            }
            if(this->value(r.x1-1)<0){
                v.push_back(Interval(0,1,1,0,0,r.x1));
                return SetIntervals(v);
            }
            if(this->value(r.x1+1)<0){
                v.push_back(Interval(1,0,0,1,r.x1,0));
                return SetIntervals(v);
            }
        }


    case 0:
        if (t=="!="){
            v.push_back(Interval(0,0,1,1,0,0));
            return SetIntervals(v);
        }
        if (t=="="){
            return SetIntervals(v);
        }
        if (t==">" ||t==">="){
            if(this->value(0)>0){
                v.push_back(Interval(0,0,1,1,0,0));
                return SetIntervals(v);
            }else{
                return SetIntervals(v);
            }
        }
        if (t=="<" ||t=="<="){
            if(this->value(0)<0){
                v.push_back(Interval(0,0,1,1,0,0));
                return SetIntervals(v);
            }else{
                return SetIntervals(v);
            }
        }
    }
    return SetIntervals();
}

//перевизначається оператор <<, виведення Квадратної нерівності
ostream&operator<<(ostream&output,const QuadraticInequality& Q){
    output<<Q.a<<"x^2";
    if(Q.b>=0){
        output<<"+";
    }
    output<<Q.b<<"x";
    if(Q.c>=0){
        output<<"+";
    }
    output<<Q.c<<Q.t<<0;
    return output;
};

//перевизначається оператор >>, введення Квадратної нерівності
istream&operator>>(istream&input, QuadraticInequality& Q){
    input>>Q.a>>Q.b>>Q.c>>Q.t;
    return input;

};
