#include "../headers/common.h"
#include "../headers/DVector.h"
#include "../headers/DMatrix.h"
#include "../src/DVector.cpp"
#include "../src/DMatrix.cpp"

Itype ifnoteq(Dtype x,Dtype y)
{
    return (abs(x-y)>pow(10,-5));
}

DVector qq(Dtype a1,Dtype a2,Dtype a3)
{
    Dtype* items=(Dtype*)malloc(3*sizeof(Dtype));
    items[0]=a1;
    items[1]=a2;
    items[2]=a3;
    return DVector(3,items);
}

DMatrix m22(Dtype a1,Dtype a2,Dtype a3, Dtype a4)
{
    Dtype* items=(Dtype*)malloc(4*sizeof(Dtype));
    items[0]=a1;
    items[1]=a2;
    items[2]=a3;
    items[3]=a4;
    return DMatrix(2,2,items);
}

DMatrix m32(Dtype a1,Dtype a2,Dtype a3, Dtype a4,Dtype a5,Dtype a6)
{
    Dtype* items=(Dtype*)malloc(6*sizeof(Dtype));
    items[0]=a1;
    items[1]=a2;
    items[2]=a3;
    items[3]=a4;
    items[4]=a5;
    items[5]=a6;
    return DMatrix(3,2,items);
}

DMatrix m23(Dtype a1,Dtype a2,Dtype a3, Dtype a4,Dtype a5,Dtype a6)
{
    Dtype* items=(Dtype*)malloc(6*sizeof(Dtype));
    items[0]=a1;
    items[1]=a2;
    items[2]=a3;
    items[3]=a4;
    items[4]=a5;
    items[5]=a6;
    return DMatrix(2,3,items);
}

DMatrix m33(Dtype a1,Dtype a2,Dtype a3, Dtype a4,
            Dtype a5,Dtype a6,Dtype a7,Dtype a8, Dtype a9)
{
    Dtype* items=(Dtype*)malloc(9*sizeof(Dtype));
    items[0]=a1;
    items[1]=a2;
    items[2]=a3;
    items[3]=a4;
    items[4]=a5;
    items[5]=a6;
    items[6]=a7;
    items[7]=a8;
    items[8]=a9;
    return DMatrix(3,3,items);
}

DMatrix m44(Dtype a1,Dtype a2,Dtype a3, Dtype a4, Dtype a5,
            Dtype a6,Dtype a7,Dtype a8, Dtype a9,Dtype a10,
            Dtype a11,Dtype a12,Dtype a13, Dtype a14,
            Dtype a15,Dtype a16)
{
    Dtype* items=(Dtype*)malloc(16*sizeof(Dtype));
    items[0]=a1; items[1]=a2; items[2]=a3;
    items[3]=a4; items[4]=a5; items[5]=a6;
    items[6]=a7; items[7]=a8; items[8]=a9; items[9]=a10;
    items[10]=a11; items[11]=a12; items[12]=a13;
    items[13]=a14; items[14]=a15; items[15]=a16;
    return DMatrix(4,4,items);
}

int tests_add_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(5,2,3,7);
    c=m22(6,4,6,11);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    if ((a+b)!=c) return 1;
    if ((b+a)!=c) return 2;
    if ((a+d)!=e) return 3;
    if ((c+e)!=c) return 4;
    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(c);
    DMatrix_destroy(d);
    DMatrix_destroy(e);
    return 0;
}

int tests_sub_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(5,2,3,7);
    c=m22(6,4,6,11);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    if ((c-b)!=a) return 1;
    if ((c-a)!=b) return 2;
    if ((e-a)!=d) return 3;
    if ((c-e)!=c) return 4;
    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(c);
    DMatrix_destroy(d);
    DMatrix_destroy(e);
    return 0;
}

int tests_mmul_DMatrix ()
{
    DMatrix a,b,c,d,e,f;
    a=m23(1,2,3,4,5,6);
    b=m32(1,2,3,4,5,6);
    c=m33(9,12,15,19,26,33,29,40,51);
    d=m22(22,28,49,64);
    e=m22(1856,2408,4214,5468);
    f=m23(134,184,234,305,418,531);
    if (a*b!=d) return 1;
    if (b*a!=c) return 2;
    if (d*d!=e) return 3;
    if (d*a!=f) return 4;
    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(c);
    DMatrix_destroy(d);
    DMatrix_destroy(e);
    DMatrix_destroy(f);
    return 0;
}

int tests_dmul_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(2,4,6,8);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    if (a*0!=e) return 1;
    if (2*a!=b) return 2;
    if ((-1)*a!=d) return 3;
    if (b*(-0.5)!=d) return 4;
    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(d);
    DMatrix_destroy(e);
    return 0;
}

int tests_mulv_DMatrix ()
{
    DMatrix a,b;
    DVector v1;
    v1=qq(1,2,3);
    a=m23(1,2,3,4,5,6);
    Dtype* it=(Dtype*)malloc(2*sizeof(Dtype));
    it[0]=14; it[1]=32;
    b=DMatrix(2,1,it);
    if ((a*v1)!=DMatrix(2,1,it));
    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DVector_destroy(v1);
    return 0;
}

int tests_vmul_DMatrix ()
{
    DMatrix a,b;
    DVector v1;
    v1=qq(1,2,3);
    a=m32(1,2,3,4,5,6);

    Dtype* it=(Dtype*)malloc(2*sizeof(Dtype));
    it[0]=22; it[1]=28;
    b=DMatrix(1,2,it);
    if ((v1*a)!=DMatrix(2,1,it));

    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DVector_destroy(v1);
    return 0;
}

int tests_det_DMatrix ()
{
    DMatrix a,b,c,d,e,f;
    a=m22(1,2,3,4);
    b=m33(1,2,3,4,5,6,7,8,9);
    c=m33(1,2,3,4,5,6,8,8,9);
    d=m22(1,2,-4,-6);
    Dtype* it=(Dtype*)malloc(sizeof(Dtype)); it[0]=2;
    e=DMatrix(1,1,it);
    f=m44(1,2,5,1,-2,3,-1,-2,1,0,1,2,3,-2,-3,1);
    if (ifnoteq(det(a),-2)) return 1;
    if (ifnoteq(det(b),0)) return 2;
    if (ifnoteq(det(c),-3)) return 3;
    if (ifnoteq(det(d),2)) return 4;
    if (ifnoteq(det(e),2)) return 5;
    if (ifnoteq(det(f),74)) return 6;
    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(c);
    DMatrix_destroy(d);
    DMatrix_destroy(e);
    DMatrix_destroy(f);
    return 0;
}

int tests_inverse_DMatrix ()
{
    DMatrix a,b,c,d,e,f,g,h;
    a=m22(1,2,3,4);
    b=m22(-2,1,1.5,-0.5);
    c=m33(1,2,3,4,5,6,8,8,9);
    d=m33(1,-2,1,-4,5,-2,8.0/3,-8.0/3,1);
    Dtype* it=(Dtype*)malloc(sizeof(Dtype)); it[0]=2;
    e=DMatrix(1,1,it);
    it=(Dtype*)malloc(sizeof(Dtype)); it[0]=1.0/2;
    f=DMatrix(1,1,it);
    g=m44(1,2,5,1,-2,3,-1,-2,1,0,1,2,3,-2,-3,1);
    h=m44(21.0/74,2.0/37,-10.0/37,27.0/74,
          7.0/74,13.0/37,9.0/37,9.0/74,
          11.0/74,-6.0/37,-7.0/37,-7.0/74,
          -8.0/37,2.0/37,27.0/37,-5.0/37);
    if (inverse(a)!=b) return 1;
    if (inverse(b)!=a) return 2;
    if (inverse(c)!=d) return 3;
    if (inverse(d)!=c) return 4;
    if (inverse(e)!=f) return 5;
     if (inverse(f)!=e) return 6;
   if (inverse(g)!=h) return 7;
   if (inverse(h)!=g) return 8;
    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(c);
    DMatrix_destroy(d);
    DMatrix_destroy(e);
    DMatrix_destroy(f);
    DMatrix_destroy(g);
    DMatrix_destroy(h);
    return 0;
}

int tests_unadd_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(1,2,3,4);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    a+=e;
    if (a!=b) return 1;
    d+=a;
    if (e!=d) return 2;
    d+=a;
    if (d!=a) return 3;
    return 0;
}

int tests_unsub_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(1,2,3,4);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    a-=e;
    if (a!=b) return 1;
    e-=a;
    if (d!=e) return 2;
    d-=e;
    d-=e;
    if (a!=d) return 3;
    return 0;
}

int tests_undmul_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(1,2,3,4);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    a*=1;
    if (a!=b) return 1;
    a*=-1;
    if (a!=d) return 2;
    a*=0;
    if (a!=e) return 3;
    d*=-1;
    if (d!=b) return 4;
    return 0;
}

int main()
{
    DMatrix a;
    srand(time(NULL));
    int rez;

    int n1,n2;

    printf("tests_add_DMatrix ");
    rez=tests_add_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_sub_DMatrix ");
    rez=tests_sub_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_mmul_DMatrix ");
    rez=tests_mmul_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_dmul_DMatrix ");
    rez=tests_dmul_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_mulv_DMatrix ");
    rez=tests_mulv_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_vmul_DMatrix ");
    rez=tests_vmul_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_det_DMatrix ");
    rez=tests_det_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_inverse_DMatrix ");
    rez=tests_inverse_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);


    printf("tests_unadd_DMatrix ");
    rez=tests_unadd_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_unsub_DMatrix ");
    rez=tests_unsub_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_undmul_DMatrix ");
    rez=tests_undmul_DMatrix();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    inputTextFile_DMatrix("matr1.txt",&a);
    printf("Matrix from file matr1.txt : ");
    output_DMatrix(a,0,4,3);

    inputs_DMatrix(&a,"3 3    1 5 6 2 3 44.56 1367 0.12 3 1 7 6");
    printf("Matrix from string : ");
    output_DMatrix(a,1,2,3);

    a=generate_DMatrix(2,3);
    DMatrix b,c;
    printf("Generated matrix: ");
    output_DMatrix(a,0,4,5);
    outputTextFile_DMatrix("matr_test.txt",a,0,3,4);
    inputTextFile_DMatrix("matr_test.txt",&b);
    printf("This matrix after text file savings: ");
    output_DMatrix(b,0,4,5);
    outputBinaryFile_DMatrix("test.vct",a);
    inputBinaryFile_DMatrix("test.vct",&c);
    printf("This matrix after binary file savings: ");
    output_DMatrix(c,0,4,5);

    input_DMatrix(&a);
    printf("Entered matrix (in different formats): \n");
    output_DMatrix(a,0,3,2);
    output_DMatrix(a,1,1,1);

    printf("Testing swap_rows. ");
    printf("Enter numbers of rows (starting from 1): \n");

    scanf("%u",&n1);
    scanf("%u",&n2);
    a.swap_rows(n1,n2);
    output_DMatrix(a,0,3,2);

    printf("Testing swap_columns. ");
    printf("Enter numbers of columns (starting from 1): \n");

    scanf("%u",&n1);
    scanf("%u",&n2);
    a.swap_columns(n1,n2);
    output_DMatrix(a,0,3,2);

    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(c);
    return 0;
}

