#include "BigNumber.h"
#include <stdio.h>
#include<stdlib.h>
/* File  BigNumber_test.c
Realization of BigNumber
Done by Zelenko Petro & Goryslavets Dmytro Statistics 2 curs
Email:  zelenko.peter369@gmail.com & d.goryslavets@ukr.net
Date 26.05.2019 */


int test1()//input number from string
{
    Tlong x;
    input_from_str(&x,"100101010000001011111001000000000",2);
    int res;
    if(x.num[nmax-1] == 705032704 && x.num[nmax-2] == 1 && x.len == 2 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test2()//input number from string
{
    Tlong x;
    input_from_str(&x,"-5000000000",10);
    int res;
    if(x.num[nmax-1] == 705032704 && x.num[nmax-2] == 1 && x.len == 2 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test3()//input number from string
{
    Tlong x;
    input_from_str(&x,"12A05F200",16);
    int res;
    if(x.num[nmax-1] == 705032704 && x.num[nmax-2] == 1 && x.len == 2 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test4()//input number from text file
{
    Tlong x;
    inputTextFile("f1.txt", &x, 10);
    int res;
    if(x.num[nmax-1] == 705032704 && x.num[nmax-2] == 1 && x.len == 2 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test5()//input number from text file
{
    Tlong x;
    inputTextFile("f2.txt", &x, 2);
    int res;
    if(x.num[nmax-1] == 5 && x.len == 1 && x.sign==-1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test6()//input number from binary file
{
    Tlong x;
    inputBinaryFile("f3.dat", &x);
    int res;
    if(x.num[nmax-1] == 705032704 && x.num[nmax-2] == 1 && x.len == 2 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test7()//addition two long
{
    Tlong x, y, c;
    input_from_str(&x, "855955565584849194941819194", 10);
    input_from_str(&y, "555555555999999999777111", 10);
    c = add(&x, &y);
    int res;
    if(c.num[nmax-1] == 2399715985 && c.num[nmax-2] == 3929659660 && c.num[nmax-3] == 46431560 && c.len == 3 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test8()//subtraction two long
{
    Tlong x, y, c;
    input_from_str(&x, "855955565584849194941819194", 10);
    input_from_str(&y, "-555555555999999999777111", 10);
    c = sub(&x, &y);
    int res;
    if(c.num[nmax-1] == 2399715985 && c.num[nmax-2] == 3929659660 && c.num[nmax-3] == 46431560 && c.len == 3 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test9()//subtraction two long
{
    Tlong x, y, c;
    input_from_str(&x, "16000000000", 10);
    input_from_str(&y, "15500000000", 10);
    c = sub(&x, &y);
    int res;
    if(c.num[nmax-1] == 500000000 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test10()//multiply two long
{
    Tlong x, y, c;
    input_from_str(&x, "5000", 10);
    input_from_str(&y, "15500000000", 10);
    c = mul(&x, &y);
    int res;
    if(c.num[nmax-1] == 1610110976 && c.num[nmax-2] == 18044 && c.len == 2 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test11()//multiply two long with different sign
{
    Tlong x, y, c;
    input_from_str(&x, "-5000", 10);
    input_from_str(&y, "15500000000", 10);
    c = mul(&x, &y);
    int res;
    if(c.num[nmax-1] == 1610110976 && c.num[nmax-2] == 18044 && c.len == 2 && c.sign==-1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test12()//multiply two long(one is zero)
{
    Tlong x, y, c;
    input_from_str(&x, "-5000", 10);
    input_from_str(&y, "0", 10);
    c = mul(&x, &y);
    int res;
    if(c.num[nmax-1] == 0 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test13()//division two long(first is zero)
{
    Tlong x, y, c;
    input_from_str(&x, "0", 10);
    input_from_str(&y, "1", 10);
    c = divT(&x, &y);
    int res;
    if(c.num[nmax-1] == 0 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test14()//division two long
{
    Tlong x, y, c;
    input_from_str(&x, "15000000000", 10);
    input_from_str(&y, "10", 10);
    c = divT(&x, &y);
    int res;
    if(c.num[nmax-1] == 1500000000 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test15()//remaining from dividing
{
    Tlong x, y, c;
    input_from_str(&x, "15000000000", 10);
    input_from_str(&y, "10", 10);
    c = modT(&x, &y);
    int res;
    if(c.num[nmax-1] == 0 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test16()//remaining from dividing one short one long
{
    Tlong x, c;
    long long y=10;
    input_from_str(&x, "15000000000", 10);
    c = modT_scal(&x, y);
    int res;
    if(c.num[nmax-1] == 0 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&c);
    return res;
}
int test17()//division one long one short
{
    Tlong x, y, c;
    input_from_str(&x, "15000000000", 10);
    input_from_str(&y, "14999999999", 10);
    c = divT(&x, &y);
    int res;
    if(c.num[nmax-1] == 1 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test18()//nsd two long
{
    Tlong x, y, c;
    input_from_str(&x, "30", 10);
    input_from_str(&y, "20", 10);
    c = NSD(&x, &y);
    int res;
    if(c.num[nmax-1] == 10 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test19()//nsd two long
{
    Tlong x, y, c;
    input_from_str(&x, "123123123", 10);
    input_from_str(&y, "23454", 10);
    c = NSD(&x, &y);
    int res;
    if(c.num[nmax-1] == 9 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test20()//nsk two long
{
    Tlong x, y, c;
    input_from_str(&x, "30", 10);
    input_from_str(&y, "20", 10);
    c = NSK(&x, &y);
    int res;
    if(c.num[nmax-1] == 60 && c.len == 1 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test21()//nsk two long
{
    Tlong x, y, c;
    input_from_str(&x, "123123123", 10);
    input_from_str(&y, "23454", 10);
    c = NSK(&x, &y);
    int res;
    if(c.num[nmax-1] == 3031278634 && c.num[nmax-2] == 74 && c.len == 2 && c.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    destroy(&c);
    return res;
}
int test22()//compare in modules
{
    Tlong x, y;
    input_from_str(&x, "123123123123", 10);
    input_from_str(&y, "123123122123", 10);
    int res;
    if(comp_abs(&x,&y)>0) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    return res;
}
int test23()////compare in modules
{
    Tlong x, y;
    input_from_str(&x, "123123123123", 10);
    input_from_str(&y, "123123122123", 10);
    int res;
    if(comp_abs(&y,&x)<0) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    return res;
}
int test24()//compare two long
{
    Tlong x, y;
    input_from_str(&x, "123123123", 10);
    input_from_str(&y, "123123122123", 10);
    int res;
    if(compare(&x,&y)<0) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    return res;
}
int test25()//update testing
{
    Tlong x;
    input_from_str(&x,"115",10);
    update(&x,1,1);
    int res;
    if(x.num[nmax-1] == 1 && x.len == 1 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test26()//append testing
{
    Tlong x;
    input_from_str(&x,"115",10);
    append(&x, 10);
    int res;
    if(x.num[nmax-1] == 10 && x.num[nmax-2] == 115 && x.len == 2 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test27()//convert testing
{
    Tlong x;
    convert(123123);
    int res;
    if(x.num[nmax-1] == 123123 && x.len == 1 && x.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test28()//compare long and short
{
    Tlong x,y;
    input_from_str(&x,"115",10);
    int res;
    if(compare_scal(&x,116)<0) res= 1;
    else res= 0;
    destroy(&x);
    return res;
}
int test29()//division short on long
{
    Tlong x,y;
    input_from_str(&x,"115",10);
    y = divscal_T(230, &x);
    int res;
    if(y.num[nmax-1] == 2 && y.len == 1 && y.sign==1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    return res;
}
int test30()//division short on long
{
    Tlong x,y;
    input_from_str(&x,"230",10);
    y = divT_scal(&x, -115);
    int res;
    if(y.num[nmax-1] == 2 && y.len == 1 && y.sign==-1) res= 1;
    else res= 0;
    destroy(&x);
    destroy(&y);
    return res;
}
int main()
{
    if(test1()) printf("test 1 passed\n");
    if(test2()) printf("test 2 passed\n");
    if(test3()) printf("test 3 passed\n");
    if(test4()) printf("test 4 passed\n");
    if(test5()) printf("test 5 passed\n");
    if(test6()) printf("test 6 passed\n");
    if(test7()) printf("test 7 passed\n");
    if(test8()) printf("test 8 passed\n");
    if(test9()) printf("test 9 passed\n");
    if(test10()) printf("test 10 passed\n");
    if(test11()) printf("test 11 passed\n");
    if(test12()) printf("test 12 passed\n");
    if(test13()) printf("test 13 passed\n");
    if(test14()) printf("test 14 passed\n");
    if(test15()) printf("test 15 passed\n");
    if(test16()) printf("test 16 passed\n");
    if(test17()) printf("test 17 passed\n");
    if(test18()) printf("test 18 passed\n");
    if(test19()) printf("test 19 passed\n");
    if(test20()) printf("test 20 passed\n");
    if(test21()) printf("test 21 passed\n");
    if(test22()) printf("test 22 passed\n");
    if(test23()) printf("test 23 passed\n");
    if(test24()) printf("test 24 passed\n");
    if(test25()) printf("test 25 passed\n");
    if(test26()) printf("test 26 passed\n");
    if(test27()) printf("test 27 passed\n");
    if(test28()) printf("test 28 passed\n");
    if(test29()) printf("test 29 passed\n");
    if(test30()) printf("test 30 passed\n");
    Tlong x1,x2,x3,x4,x5,x6,x7,x8,x9;
    printf("Enter first number: ");
    input_console_oneline(&x1, 10);
    printf("Enter second number: ");
    input_console_oneline(&x2, 10);
    printf("Enter third number(digit in 2^32 sys sch)(point must be after the last symbol like: 123 123.): ");
    input_from_console(&x3, 10);
    int x,y;
    printf("Enter size x*y of table to vision of number in future(like: 3 4, 0 - auto): ");
    scanf("%d %d",&x,&y);
    printf("Numbers in table: \n");
    printf("x1= ");
    outputConsole(&x1, x,y);
    printf("x2= ");
    outputConsole(&x2, x,y);
    printf("x3= ");
    outputConsole(&x3, x,y);
    outputBinaryFile("f4.dat", &x1);
    printf("first number in f4.dat\n");
    destroy(&x1);
    inputBinaryFile("f4.dat", &x1);
    printf("x1 from f4.dat: ");
    outputConsole(&x1, x,y);
    outputTextFile("f5.txt", &x2,x,y);
    printf("second number in f5.txt\n");
    int r = compare(&x1,&x2);
    if(r>0) printf("x1 > x2");
    else
    {
        if(r==0) printf("x1 == x2");
        else printf("x1 < x2");
    }
    x3 = add(&x1, &x2);
    printf("\nx1+x2= ");
    outputConsole(&x3, x,y);
    x4 = sub(&x1, &x2);
    printf("x1-x2= ");
    outputConsole(&x4, x,y);
    x5 = mul(&x1, &x2);
    printf("x1*x2= ");
    outputConsole(&x5, x,y);
    x6 = divT(&x1, &x2);
    printf("x1/x2= ");
    outputConsole(&x6, x,y);
    x7 = modT(&x1, &x2);
    printf("x1 mod x2= ");
    outputConsole(&x7, x,y);
    x8 = NSD(&x1, &x2);
    printf("nsd(x1,x2)= ");
    outputConsole(&x8, x,y);
    x9 = NSK(&x1, &x2);
    printf("nsk(x1,x2)= ");
    outputConsole(&x9, x,y);
    destroy(&x1);
    destroy(&x2);
    destroy(&x3);
    destroy(&x4);
    destroy(&x5);
    destroy(&x6);
    destroy(&x7);
    destroy(&x8);
    destroy(&x9);
    return 0;
}
