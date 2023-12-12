/* File main.cpp
Realzation of tests for Interval, SetIntervals and QuadraticInequality class functions
Done by Kharchenko Oleksandr (group 2)
Date 11.29.2023
Tests for Interval, SetIntervals and QuadraticInequality classes
*/



#include <iostream>
#include <fstream>
#include "Interval.h"
using namespace std;

//тест 1 - множенн€ (перетин) ≤нтервал≥в
int test_1(){
    Interval I1(1,0,0,1,-100,0);    //[-100, inf)
    Interval I2(0,0,0,0,-100,3);    //(-100, 3)
    Interval I3(1,0,0,1,-1,0);      //[-1, inf)
    Interval I4(1,1,0,0,-300,-100); //[-300, -100]
    if(I1*I1!=I1) return 1;
    if(I1*I2!=I2) return 2;
    if(I1*I3!=I3) return 3;
    if(I1*I4!=Interval(1,1,0,0,-100,-100)) return 4;

    if(I2*I1!=I2) return 5;
    if(I2*I2!=I2) return 6;
    if(I2*I3!=Interval(1,0,0,0,-1,3)) return 7;
    if(I2*I4!=Interval()) return 8;

    if(I3*I1!=I3) return 9;
    if(I3*I2!=Interval(1,0,0,0,-1,3)) return 10;
    if(I3*I3!=I3) return 11;
    if(I3*I4!=Interval()) return 12;

    if(I4*I1!=Interval(1,1,0,0,-100,-100)) return 13;
    if(I4*I2!=Interval()) return 14;
    if(I4*I3!=Interval()) return 15;
    if(I4*I4!=I4) return 16;
    return 0;
}

//тест 2 - множенн€ (перетин) ≤нтервал≥в з файлу
int test_2(int n=4){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_2"){
        file>>s;
    }
    Interval A[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
    }
    Interval B[n*n];
    for (int i=0; i<n*n; ++i){
        file>>B[i];

    }
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            if(A[i]*A[j]!=B[n*i+j]) return n*i+j+1;
        }
    }

    file.close();
    return 0;
}

//тест 3 - додаванн€ (об'Їднанн€) ≤нтервал≥в
int test_3(){
    Interval I1(0,0,0,0,-4,2);    //(-4 2)
    Interval I2(0,0,0,0,-1,3);    //(-1, 3)
    Interval I3(1,0,0,1,3,0);      //[3, inf)
    Interval I4(1,0,0,0,-4,-1); //[-4,-1)
    if(I1+I1!=SetIntervals(vector<Interval> {I1})) return 1;
    if(I1+I2!=SetIntervals(vector<Interval> {Interval(0,0,0,0,-4,3)})) return 2;
    if(I1+I3!=SetIntervals(vector<Interval> {I1, I3})) return 3;
    if(I1+I4!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-4,2)})) return 4;

    if(I2+I1!=SetIntervals(vector<Interval> {Interval(0,0,0,0,-4,3)})) return 5;
    if(I2+I2!=SetIntervals(vector<Interval> {I2})) return 6;
    if(I2+I3!=SetIntervals(vector<Interval> {Interval(0,0,0,1,-1,0)})) return 7;
    if(I2+I4!=SetIntervals(vector<Interval> {I2,I4})) return 8;

    if(I3+I1!=SetIntervals(vector<Interval> {I1, I3})) return 9;
    if(I3+I2!=SetIntervals(vector<Interval> {Interval(0,0,0,1,-1,0)})) return 10;
    if(I3+I3!=SetIntervals(vector<Interval> {I3})) return 11;
    if(I3+I4!=SetIntervals(vector<Interval> {I3,I4})) return 12;

    if(I4+I1!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-4,2)})) return 13;
    if(I4+I2!=SetIntervals(vector<Interval> {I2,I4})) return 14;
    if(I4+I3!=SetIntervals(vector<Interval> {I3,I4})) return 15;
    if(I4+I4!=SetIntervals(vector<Interval> {I4})) return 16;
    return 0;
}

//тест 4 - додаванн€ (об'Їднанн€) ≤нтервал≥в з файлу
int test_4(int n=4){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_4"){
        file>>s;
    }
    Interval A[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
    }
    SetIntervals B[n*n];
    for (int i=0; i<n*n; ++i){
        file>>B[i];
    }
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            if(A[i]+A[j]!=B[n*i+j]) return n*i+j+1;
        }
    }

    file.close();
    return 0;
}

//тест 5 - р≥зниц€ ≤нтервал≥в
int test_5(){
    Interval I1(0,0,1,1,0,0);    //(-inf, inf)
    Interval I2(1,0,0,1,5,0);    //[5, inf)
    Interval I3(0,1,0,0,-3,5);      //(-3, 5]
    Interval I4(1,0,0,0,-3,0); //[-3, 0)
    if(I1-I1!=SetIntervals()) return 1;
    if(I1-I2!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,5)})) return 2;
    if(I1-I3!=SetIntervals(vector<Interval> {Interval(0,1,1,0,0,-3), Interval(0,0,0,1,5,0) })) return 3;
    if(I1-I4!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-3), Interval(1,0,0,1,0,0) })) return 4;

    if(I2-I1!=SetIntervals()) return 5;
    if(I2-I2!=SetIntervals()) return 6;
    if(I2-I3!=SetIntervals(vector<Interval> {Interval(0,0,0,1,5,0)})) return 7;
    if(I2-I4!=SetIntervals(vector<Interval> {I2})) return 8;

    if(I3-I1!=SetIntervals(vector<Interval> {Interval()})) return 9;
    if(I3-I2!=SetIntervals(vector<Interval> {Interval(0,0,0,0,-3,5)})) return 10;
    if(I3-I3!=SetIntervals()) return 11;
    if(I3-I4!=SetIntervals(vector<Interval> {Interval(1,1,0,0,0,5)})) return 12;

    if(I4-I1!=SetIntervals()) return 13;
    if(I4-I2!=SetIntervals(vector<Interval> {I4})) return 14;
    if(I4-I3!=SetIntervals(vector<Interval> {Interval(1,1,0,0,-3,-3)})) return 15;
    if(I4-I4!=SetIntervals()) return 16;
    return 0;
}

//тест 6 - р≥зниц€ ≤нтервал≥в з файлу
int test_6(int n=4){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_6"){
        file>>s;
    }
    Interval A[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
    }
    SetIntervals B[n*n];
    for (int i=0; i<n*n; ++i){
        file>>B[i];
    }
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            if(A[i]-A[j]!=B[n*i+j]) return n*i+j+1;
        }
    }

    file.close();
    return 0;
}
//тест 7 - довжина SetIntervals
int test_7(float eps=10e-7){
    SetIntervals S1(vector<Interval> {Interval(0,1,1,0,0,-10), Interval(1,1,0,0,11,12)});    //(-inf, -10] [11, 12]
    SetIntervals S2(vector<Interval> {Interval(1,1,0,0,-3,-3),Interval(1,1,0,0,-4,-4),Interval(0,0,0,0,5,5.5)});  //[-3, -3] [-4, -4], (5, 5.5)
    SetIntervals S3(vector<Interval> {Interval(0,0,0,0,-7,-3),Interval(0,1,0,0,-3,1),Interval(1,0,0,0,2,3.14)});  //(-7, -3) (-3, 1], [2,3.14)
    SetIntervals S4(vector<Interval>{}); //Empty
    if(S1.length()!=-1) return 1;
    if(abs(S2.length()-0.5)>eps) return 2;
    if(abs(S3.length()-9.14)>eps) return 3;
    if((S4.length())!=0) return 4;
    return 0;
}

//тест 8 - довжина SetIntervals з файлу
int test_8(int n=4, float eps=10e-7){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_8"){
        file>>s;
    }

    SetIntervals A[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
    }
    float B[n];
    for (int i=0; i<n; ++i){
        file>>B[i];
    }
    for (int i=0; i<n; ++i){
            if((abs(A[i].length()-B[i])>eps)) return i+1;
    }

    file.close();
    return 0;
}

//тест 9 - множенн€ (перетин) SetIntervals
int test_9(){
    SetIntervals S1(vector<Interval> {Interval(0,0,1,0,0,-10), Interval(1,0,0,0,5,10), Interval(0,0,0,1,100,0)});    //(-inf -10) [5 10) (100 inf)
    SetIntervals S2(vector<Interval> {Interval(1,0,0,0, -7,-6), Interval(0,1,0,0,3,5), Interval(0,1,0,0,10,100)}); // [-7 -6) (3 5] (10 100]
    SetIntervals S3(vector<Interval> {Interval(0,0,0,0, -6, 4), Interval(1,0,0,1,7,0)}); // (-6 4) [7 inf)
    SetIntervals S4(vector<Interval> {Interval(1,0,0,0,-10,-7), Interval(1,1,0,0,5,5)}); // [-10 -7) [5 5]
    if(S1*S1!=S1) return 1;
    if(S1*S2!=SetIntervals(vector<Interval> {Interval(1,1,0,0,5,5)})) return 2; //[5 5]
    if(S1*S3!=SetIntervals(vector<Interval> {Interval(1,0,0,0,7,10), Interval(0,0,0,1,100,0)})) return 3; //[7 10) (100 inf)
    if(S1*S4!=SetIntervals(vector<Interval> {Interval(1,1,0,0,5,5)})) return 4; //[5 5]

    if(S2*S1!=SetIntervals(vector<Interval> {Interval(1,1,0,0,5,5)})) return 5; //[5 5]
    if(S2*S2!=S2) return 6;
    if(S2*S3!=SetIntervals(vector<Interval> {Interval(0,0,0,0,3,4),Interval(0,1,0,0,10,100)})) return 7; //(3 4) (10 100]
    if(S2*S4!=SetIntervals(vector<Interval> {Interval(1,1,0,0,5,5)})) return 8; //[5 5]

    if(S3*S1!=SetIntervals(vector<Interval> {Interval(1,0,0,0,7,10), Interval(0,0,0,1,100,0)})) return 9; //[7 10) (100 inf)
    if(S3*S2!=SetIntervals(vector<Interval> {Interval(0,0,0,0,3,4),Interval(0,1,0,0,10,100)})) return 10; //(3 4) (10 100]
    if(S3*S3!=S3) return 11;
    if(S3*S4!=SetIntervals()) return 12;

    if(S4*S1!=SetIntervals(vector<Interval> {Interval(1,1,0,0,5,5)})) return 13;
    if(S4*S2!=SetIntervals(vector<Interval> {Interval(1,1,0,0,5,5)})) return 14;
    if(S4*S3!=SetIntervals()) return 15;
    if(S4*S4!=S4) return 16;
    return 0;
}

//тест 10 - множенн€ (перетин) SetIntervals з файлу
int test_10(int n=4){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_10"){
        file>>s;
    }
    SetIntervals A[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
    }
    SetIntervals B[n*n];
    for (int i=0; i<n*n; ++i){
        file>>B[i];
    }
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            if(A[i]*A[j]!=B[n*i+j]) return n*i+j+1;
        }
    }

    file.close();
    return 0;
}
//тест 11 - додаванн€ (об'Їднанн€) SetIntervals
int test_11(){
    SetIntervals S1(vector<Interval> {Interval(0,0,1,0,0,-10), Interval(1,0,0,0,5,10), Interval(0,0,0,1,100,0)});    //(-inf -10) [5 10) (100 inf)
    SetIntervals S2(vector<Interval> {Interval(1,0,0,0, -7,-6), Interval(0,1,0,0,3,5), Interval(0,1,0,0,10,100)}); // [-7 -6) (3 5] (10 100]
    SetIntervals S3(vector<Interval> {Interval(0,0,0,0, -6, 4), Interval(1,0,0,1,7,0)}); // (-6 4) [7 inf)
    SetIntervals S4(vector<Interval> {Interval(1,0,0,0,-10,-7), Interval(1,1,0,0,5,5)}); // [-10 -7) [5 5]
    if(S1+S1!=S1) return 1;
    if(S1+S2!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-10),Interval(1,0,0,0, -7,-6),Interval(0,0,0,0,3,10),Interval(0,0,0,1,10,0)})) return 2; //(-inf -10) [-7 -6) (3 10) (10 inf)
    if(S1+S3!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-10),Interval(0,0,0,0, -6, 4),Interval(1,0,0,1,5,0)})) return 3; //(-inf -10) (-6 4) [5 inf)
    if(S1+S4!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-7), Interval(1,0,0,0,5,10), Interval(0,0,0,1,100,0)})) return 4; //(-inf -7) [5 10) (100 inf)

    if(S2+S1!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-10),Interval(1,0,0,0, -7,-6),Interval(0,0,0,0,3,10),Interval(0,0,0,1,10,0)})) return 5;
    if(S2+S2!=S2) return 6;
    if(S2+S3!=SetIntervals(vector<Interval> {Interval(1,0,0,0, -7,-6),Interval(0,1,0,0, -6, 5), Interval(1,0,0,1,7,0)})) return 7; //[-7 -6) (-6 5] [7 inf)
    if(S2+S4!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-10,-6),Interval(0,1,0,0,3,5), Interval(0,1,0,0,10,100)})) return 8; //[-10 -6) (3 5] (10 100]

    if(S3+S1!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-10),Interval(0,0,0,0, -6, 4),Interval(1,0,0,1,5,0)})) return 9;
    if(S3+S2!=SetIntervals(vector<Interval> {Interval(1,0,0,0, -7,-6),Interval(0,1,0,0, -6, 5), Interval(1,0,0,1,7,0)})) return 10;
    if(S3+S3!=S3) return 11;
    if(S3+S4!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-10,-7),Interval(0,0,0,0, -6, 4), Interval(1,1,0,0,5,5),Interval(1,0,0,1,7,0)})) return 12; // [-10 -7) (-6 4) [5 5] [7 inf)

    if(S4+S1!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-7), Interval(1,0,0,0,5,10), Interval(0,0,0,1,100,0)})) return 13;
    if(S4+S2!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-10,-6),Interval(0,1,0,0,3,5), Interval(0,1,0,0,10,100)})) return 14;
    if(S4+S3!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-10,-7),Interval(0,0,0,0, -6, 4), Interval(1,1,0,0,5,5),Interval(1,0,0,1,7,0)}))return 15;
    if(S4*S4!=S4) return 16;
    return 0;
}

//тест 12 - додаванн€ (об'Їднанн€) SetIntervals з файлу
int test_12(int n=4){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_12"){
        file>>s;
    }
    SetIntervals A[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
    }
    SetIntervals B[n*n];
    for (int i=0; i<n*n; ++i){
        file>>B[i];
    }
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            if(A[i]+A[j]!=B[n*i+j]) return n*i+j+1;
        }
    }

    file.close();
    return 0;
}

//тест 13 - р≥зниц€ SetIntervals
int test_13(){
    SetIntervals S1(vector<Interval> {Interval(0,0,1,0,0,-10), Interval(1,0,0,0,5,10), Interval(0,0,0,1,100,0)});    //(-inf -10) [5 10) (100 inf)
    SetIntervals S2(vector<Interval> {Interval(1,0,0,0, -7,-6), Interval(0,1,0,0,3,5), Interval(0,1,0,0,10,100)}); // [-7 -6) (3 5] (10 100]
    SetIntervals S3(vector<Interval> {Interval(0,0,0,0, -6, 4), Interval(1,0,0,1,7,0)}); // (-6 4) [7 inf)
    SetIntervals S4(vector<Interval> {Interval(1,0,0,0,-10,-7), Interval(1,1,0,0,5,5)}); // [-10 -7) [5 5]
    if(S1-S1!=SetIntervals()) return 1;
    if(S1-S2!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-10), Interval(0,0,0,0,5,10), Interval(0,0,0,1,100,0)})) return 2; //(-inf -10) (5 10) (100 inf)
    if(S1-S3!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-10), Interval(1,0,0,0,5,7)})) return 3; //(-inf -10) [5 7)
    if(S1-S4!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,-10), Interval(0,0,0,0,5,10), Interval(0,0,0,1,100,0)})) return 4; //(-inf -10) (5 10) (100 inf)

    if(S2-S1!=SetIntervals(vector<Interval> {Interval(1,0,0,0, -7,-6), Interval(0,0,0,0,3,5), Interval(0,1,0,0,10,100)})) return 5; //[-7 -6) (3 5) (10 100]
    if(S2-S2!=SetIntervals()) return 6;
    if(S2-S3!=SetIntervals(vector<Interval> {Interval(1,0,0,0, -7,-6), Interval(1,1,0,0,4,5)})) return 7;  // [-7 -6) [4 5]
    if(S2-S4!=SetIntervals(vector<Interval> {Interval(1,0,0,0, -7,-6), Interval(0,0,0,0,3,5), Interval(0,1,0,0,10,100)})) return 8;  //[-7 -6) (3 5) (10 100]

    if(S3-S1!=SetIntervals(vector<Interval> {Interval(0,0,0,0, -6, 4), Interval(1,1,0,0,10,100)})) return 9; //(-6 4) [10 100]
    if(S3-S2!=SetIntervals(vector<Interval> {Interval(0,1,0,0, -6, 3), Interval(1,1,0,0,7,10),Interval(0,0,0,1,100,0)})) return 10; //(-6 3] [7 10] (100 inf)
    if(S3-S3!=SetIntervals()) return 11;
    if(S3-S4!=S3) return 12;

    if(S4-S1!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-10,-7)})) return 13; //[-10 -7)
    if(S4-S2!=SetIntervals(vector<Interval> {Interval(1,0,0,0,-10,-7)})) return 14; //[-10 -7)
    if(S4-S3!=S4) return 15;
    if(S4-S4!=SetIntervals()) return 16;
    return 0;
}


//тест 13 - р≥зниц€ SetIntervals з файлу
int test_14(int n=4){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_14"){
        file>>s;
    }
    SetIntervals A[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
    }
    SetIntervals B[n*n];
    for (int i=0; i<n*n; ++i){
        file>>B[i];
    }
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            if(A[i]-A[j]!=B[n*i+j]) return n*i+j+1;
        }
    }

    file.close();
    return 0;
}

//тест 15 - toIntervals - перетворенн€  вадратних Ќер≥вностей в toIntervals
int test_15(){
    QuadraticInequality Q1(0,0,0,"=");
    if (Q1.toIntervals()!=SetIntervals(vector<Interval> {Interval(0,0,1,1,0,0)})) return 1;

    QuadraticInequality Q2(0,0,0,">");
    if (Q2.toIntervals()!=SetIntervals()) return 2;

    QuadraticInequality Q3(0,0,-1,"<=");
    if (Q3.toIntervals()!=SetIntervals(vector<Interval> {Interval(0,0,1,1,0,0)})) return 3;

    QuadraticInequality Q4(0,0,-1,"!=");
    if (Q4.toIntervals()!=SetIntervals(vector<Interval> {Interval(0,0,1,1,0,0)})) return 4;

    QuadraticInequality Q5(0,1,2,"=");
    if (Q5.toIntervals()!=SetIntervals(vector<Interval> {Interval(1,1,0,0,-2,-2)})) return 5;

    QuadraticInequality Q6(0,-2,-5,">=");
    if (Q6.toIntervals()!=SetIntervals(vector<Interval> {Interval(0,1,1,0,0,-2.5)})) return 6;

    QuadraticInequality Q7(1,-2,5,">=");
    if (Q7.toIntervals()!=SetIntervals(vector<Interval> {Interval(0,0,1,1,0,0)})) return 7;

    QuadraticInequality Q8(-3,-2,-1,"=");
    if (Q8.toIntervals()!=SetIntervals()) return 8;

    QuadraticInequality Q9(2,8,8,"<=");
    if (Q9.toIntervals()!=SetIntervals(vector<Interval> {Interval(1,1,0,0,-2,-2)})) return 9;

    QuadraticInequality Q10(1,-2,1,">");
    if (Q10.toIntervals()!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,1), Interval(0,0,0,1,1,0)})) return 10;

    QuadraticInequality Q11(0.5,-1.5,1,"<=");
    if (Q11.toIntervals()!=SetIntervals(vector<Interval> {Interval(1,1,0,0,1,2)})) return 11;

    QuadraticInequality Q12(-1,5,-6,"!=");
    if (Q12.toIntervals()!=SetIntervals(vector<Interval> {Interval(0,0,1,0,0,2),Interval(0,0,0,0,2,3), Interval(0,0,0,1,3,0)})) return 12;

    return 0;
}

//тест 16 - toIntervals - перетворенн€  вадратних Ќер≥вностей з файлу в toIntervals
int test_16(int n=12){

    fstream file("Interval_test.txt");
    string s="";
    while (s!="test_16"){
        file>>s;
    }

    QuadraticInequality A[n];
    SetIntervals B[n];
    for (int i=0; i<n; ++i){
        file>>A[i];
        file>>B[i];
    }

    for (int i=0; i<n; ++i){
            if(A[i].toIntervals()!=B[i]) return i+1;
    }

    file.close();
    return 0;
}

//функц≥€ розв'€зуЇ систему квадрадних нер≥вностей, €ка вводитьс€ з клав≥атури
SetIntervals SolveSystem(){
    int n;
    vector<Interval> v={Interval(0,0,1,1,0,0)};
    SetIntervals res(v);
    QuadraticInequality Q(0,0,0,"");
    cout<<"Enter number of systems:";
    cin>>n;
    for (int i=0; i<n; ++i){
        cout<<"Enter inequality "<<i+1<<":";
        cin>>Q;
        res=res*Q.toIntervals();
    }
    return res;
}
int main()
{
    cout<<SolveSystem()<<endl;
    if(!test_1()) cout<<"test 1 passed"<<endl;
    if(!test_2()) cout<<"test 2 passed"<<endl;
    if(!test_3()) cout<<"test 3 passed"<<endl;
    if(!test_4()) cout<<"test 4 passed"<<endl;
    if(!test_5()) cout<<"test 5 passed"<<endl;
    if(!test_6()) cout<<"test 6 passed"<<endl;
    if(!test_7()) cout<<"test 7 passed"<<endl;
    if(!test_8()) cout<<"test 8 passed"<<endl;
    if(!test_9()) cout<<"test 9 passed"<<endl;
    if(!test_10()) cout<<"test 10 passed"<<endl;
    if(!test_11()) cout<<"test 11 passed"<<endl;
    if(!test_12()) cout<<"test 12 passed"<<endl;
    if(!test_13()) cout<<"test 13 passed"<<endl;
    if(!test_14()) cout<<"test 14 passed"<<endl;
    if(!test_15()) cout<<"test 15 passed"<<endl;
    if(!test_16()) cout<<"test 16 passed"<<endl;


    //SetIntervals S;
    //cin>>S;

    return 0;
}
