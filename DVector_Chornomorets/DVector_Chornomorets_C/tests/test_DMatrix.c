#include "../headers/common.h"
#include "../headers/DVector.h"
#include "../headers/DMatrix.h"
#include "../src/DVector.c"
#include "../src/DMatrix.c"

Itype ifnotequal(DVector x,DVector y)
{
    if (x.n!=y.n) return 1;
    for (Ntype i=0;i<x.n;i++)
        if (abs(x.items[i]-y.items[i])>pow(10,-5))
            return 1;
    return 0;
}

Itype ifneq(DMatrix x,DMatrix y)
{
    if (x.n!=y.n||x.m!=y.m) return 1;
    for (Ntype i=0;i<x.n*x.m;i++)
        if (abs(x.items[i]-y.items[i])>pow(10,-6))
            return 1;
    return 0;
}

Itype ifnoteq(Dtype x,Dtype y)
{
    return (abs(x-y)>pow(10,-5));
}

DVector qq(Dtype a1,Dtype a2,Dtype a3)
{
    DVector s;
    s.n=3;
    s.items=malloc(3*sizeof(Dtype));
    s.items[0]=a1;
    s.items[1]=a2;
    s.items[2]=a3;
    return s;
}

DMatrix m22(Dtype a1,Dtype a2,Dtype a3, Dtype a4)
{
    DMatrix s;
    s.n=2;
    s.m=2;
    s.items=malloc(4*sizeof(Dtype));
    s.items[0]=a1;
    s.items[1]=a2;
    s.items[2]=a3;
    s.items[3]=a4;
    return s;
}

DMatrix m32(Dtype a1,Dtype a2,Dtype a3, Dtype a4,Dtype a5,Dtype a6)
{
    DMatrix s;
    s.n=3;
    s.m=2;
    s.items=malloc(6*sizeof(Dtype));
    s.items[0]=a1;
    s.items[1]=a2;
    s.items[2]=a3;
    s.items[3]=a4;
    s.items[4]=a5;
    s.items[5]=a6;
    return s;
}

DMatrix m23(Dtype a1,Dtype a2,Dtype a3, Dtype a4,Dtype a5,Dtype a6)
{
    DMatrix s;
    s.n=2;
    s.m=3;
    s.items=malloc(6*sizeof(Dtype));
    s.items[0]=a1;
    s.items[1]=a2;
    s.items[2]=a3;
    s.items[3]=a4;
    s.items[4]=a5;
    s.items[5]=a6;
    return s;
}

DMatrix m33(Dtype a1,Dtype a2,Dtype a3, Dtype a4,
            Dtype a5,Dtype a6,Dtype a7,Dtype a8, Dtype a9)
{
    DMatrix s;
    s.n=3;
    s.m=3;
    s.items=malloc(9*sizeof(Dtype));
    s.items[0]=a1;
    s.items[1]=a2;
    s.items[2]=a3;
    s.items[3]=a4;
    s.items[4]=a5;
    s.items[5]=a6;
    s.items[6]=a7;
    s.items[7]=a8;
    s.items[8]=a9;
    return s;
}

DMatrix m44(Dtype a1,Dtype a2,Dtype a3, Dtype a4, Dtype a5,
            Dtype a6,Dtype a7,Dtype a8, Dtype a9,Dtype a10,
            Dtype a11,Dtype a12,Dtype a13, Dtype a14,
            Dtype a15,Dtype a16)
{
    DMatrix s; s.n=4; s.m=4;
    s.items=malloc(16*sizeof(Dtype));
    s.items[0]=a1; s.items[1]=a2; s.items[2]=a3;
    s.items[3]=a4; s.items[4]=a5; s.items[5]=a6;
    s.items[6]=a7; s.items[7]=a8; s.items[8]=a9; s.items[9]=a10;
    s.items[10]=a11; s.items[11]=a12; s.items[12]=a13;
    s.items[13]=a14; s.items[14]=a15; s.items[15]=a16;
    return s;
}

int tests_add_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(5,2,3,7);
    c=m22(6,4,6,11);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    if (ifneq(add_DMatrix(a,b),c)) return 1;
    if (ifneq(add_DMatrix(b,a),c)) return 2;
    if (ifneq(add_DMatrix(a,d),e)) return 3;
    if (ifneq(add_DMatrix(c,e),c)) return 4;
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
    if (ifneq(sub_DMatrix(c,b),a)) return 1;
    if (ifneq(sub_DMatrix(c,a),b)) return 2;
    if (ifneq(sub_DMatrix(e,a),d)) return 3;
    if (ifneq(sub_DMatrix(c,e),c)) return 4;
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
    if (ifneq(mmul_DMatrix(a,b),d)) return 1;
    if (ifneq(mmul_DMatrix(b,a),c)) return 2;
    if (ifneq(mmul_DMatrix(d,d),e)) return 3;
    if (ifneq(mmul_DMatrix(d,a),f)) return 4;
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
    if (ifneq(dmul_DMatrix(a,0),e)) return 1;
    if (ifneq(dmul_DMatrix(a,2),b)) return 2;
    if (ifneq(dmul_DMatrix(a,-1),d)) return 3;
    if (ifneq(dmul_DMatrix(b,-0.5),d)) return 4;
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
    b=mulv_DMatrix(a,v1);
    if (b.n!=2 || b.m!=1) return 1;
    if (b.items[0]!=14 || b.items[1]!=32) return 2;
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
    b=vmul_DMatrix(v1,a);
    if (b.n!=1 || b.m!=2) return 1;
    if (b.items[0]!=22 || b.items[1]!=28) return 2;
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
    e.n=1;e.m=1;e.items=(Dtype*)malloc(sizeof(Dtype));
    e.items[0]=2;
    f=m44(1,2,5,1,-2,3,-1,-2,1,0,1,2,3,-2,-3,1);
    if (ifnoteq(det_DMatrix(a),-2)) return 1;
    if (ifnoteq(det_DMatrix(b),0)) return 2;
    if (ifnoteq(det_DMatrix(c),-3)) return 3;
    if (ifnoteq(det_DMatrix(d),2)) return 4;
    if (ifnoteq(det_DMatrix(e),2)) return 5;
    if (ifnoteq(det_DMatrix(f),74)) return 6;
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
    e.n=1;e.m=1;e.items=(Dtype*)malloc(sizeof(Dtype));
    e.items[0]=2;
    f.n=1;f.m=1;f.items=(Dtype*)malloc(sizeof(Dtype));
    f.items[0]=1/2;
    g=m44(1,2,5,1,-2,3,-1,-2,1,0,1,2,3,-2,-3,1);
    h=m44(21.0/74,2.0/37,-10.0/37,27.0/74,
          7.0/74,13.0/37,9.0/37,9.0/74,
          11.0/74,-6.0/37,-7.0/37,-7.0/74,
          -8.0/37,2.0/37,27.0/37,-5.0/37);
    if (ifneq(inverse_DMatrix(a),b)) return 1;
    if (ifneq(inverse_DMatrix(b),a)) return 2;
    if (ifneq(inverse_DMatrix(c),d)) return 3;
    if (ifneq(inverse_DMatrix(d),c)) return 4;
    if (ifneq(inverse_DMatrix(e),f)) return 5;
     if (ifneq(inverse_DMatrix(f),e)) return 6;
   if (ifneq(inverse_DMatrix(g),h)) return 7;
   if (ifneq(inverse_DMatrix(h),g)) return 8;
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
    unadd_DMatrix(&a,e);
    if (ifneq(a,b)) return 1;
    unadd_DMatrix(&d,a);
    if (ifneq(d,e)) return 2;
    unadd_DMatrix(&d,a);
    if (ifneq(a,d)) return 3;
    return 0;
}

int tests_unsub_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(1,2,3,4);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    unsub_DMatrix(&a,e);
    if (ifneq(a,b)) return 1;
    unsub_DMatrix(&e,a);
    if (ifneq(d,e)) return 2;
    unsub_DMatrix(&d,e);
    unsub_DMatrix(&d,e);
    if (ifneq(a,d)) return 3;
    return 0;
}

int tests_undmul_DMatrix ()
{
    DMatrix a,b,c,d,e;
    a=m22(1,2,3,4);
    b=m22(1,2,3,4);
    d=m22(-1,-2,-3,-4);
    e=m22(0,0,0,0);
    undmul_DMatrix(&a,1);
    if (ifneq(a,b)) return 1;
    undmul_DMatrix(&a,-1);
    if (ifneq(a,d)) return 2;
    undmul_DMatrix(&a,0);
    if (ifneq(a,e)) return 3;
    undmul_DMatrix(&d,-1);
    if (ifneq(d,b)) return 4;
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
    output_DMatrix(a,1,1,1);

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
    swap_rows_DMatrix(&a,n1,n2);
    output_DMatrix(a,0,3,2);

    printf("Testing swap_columns. ");
    printf("Enter numbers of columns (starting from 1): \n");

    scanf("%u",&n1);
    scanf("%u",&n2);
    swap_columns_DMatrix(&a,n1,n2);
    output_DMatrix(a,0,3,2);

    DMatrix_destroy(a);
    DMatrix_destroy(b);
    DMatrix_destroy(c);
    return 0;
}

