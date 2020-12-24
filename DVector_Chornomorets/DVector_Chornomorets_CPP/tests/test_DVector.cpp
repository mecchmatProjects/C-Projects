#include "../headers/common.h"
#include "../headers/DVector.h"
#include "../src/DVector.cpp"

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

int tests_add_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(5,2,3);
    c=qq(6,4,6);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    if ((a+b)!=c) return 1;
    if ((b+a)!=c) return 2;
    if ((a+d)!=e) return 3;
    if ((c+e)!=c) return 4;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(c);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int tests_sub_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(5,2,3);
    c=qq(6,4,6);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    if ((c-b)!=a) return 1;
    if ((c-a)!=b) return 2;
    if ((e-a)!=d) return 3;
    if ((c-e)!=c) return 4;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(c);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int tests_vmul_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(3,4,5);
    b=qq(3,4,-5);
    if (ifnoteq(a*a,50)) return 1;
    if (ifnoteq(a*b,0)) return 2;
    if (ifnoteq(b*a,0)) return 3;
    if (ifnoteq(b*b,50)) return 4;
    DVector_destroy(a);
    DVector_destroy(b);
    return 0;
}

int tests_dmul_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(2,4,6);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    if (a*0!=e) return 1;
    if (2*a!=b) return 2;
    if (a*(-1)!=d) return 3;
    if ((-0.5)*b!=d) return 4;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int tests_div_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(2,4,6);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    if ((e/357)!=e) return 1;
    if ((a/(1.0/2))!=b) return 2;
    if ((a/(-1))!=d) return 3;
    if ((b/(-2))!=d) return 4;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int tests_abs_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(5,2,3);
    c=qq(6,4,6);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    if (ifnoteq(abs(a),sqrt(14))) return 1;
    if (ifnoteq(abs(b),sqrt(38))) return 2;
    if (ifnoteq(abs(c),sqrt(88))) return 3;
    if (ifnoteq(abs(d),sqrt(14))) return 4;
    if (ifnoteq(abs(e),0)) return 5;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(c);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int tests_unadd_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(1,2,3);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    a+=e;
    if (a!=b) return 1;
    d+=a;
    if (d!=e) return 2;
    d+=a;
    if (a!=d) return 3;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int tests_unsub_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(1,2,3);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    a-=e;
    if (a!=b) return 1;
    e-=a;
    if (d!=e) return 2;
    d-=e;
    d-=e;
    if (a!=d) return 3;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int tests_undmul_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(1,2,3);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    a*=1;
    if (a!=b) return 1;
    a*=-1;
    if (a!=d) return 2;
    a*=0;
    if (a!=e) return 3;
    d*=-1;
    if (d!=b) return 4;
    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(d);
    DVector_destroy(e);
    return 0;
}

int main()
{
    DVector a;
    srand(time(NULL));
    int rez;

    printf("tests_add_DVector ");
    rez=tests_add_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_sub_DVector ");
    rez=tests_sub_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_vmul_DVector ");
    rez=tests_vmul_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_dmul_DVector ");
    rez=tests_dmul_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_div_DVector ");
    rez=tests_div_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_abs_DVector ");
    rez=tests_abs_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_unadd_DVector ");
    rez=tests_unadd_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_unsub_DVector ");
    rez=tests_unsub_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);

    printf("tests_undmul_DVector ");
    rez=tests_undmul_DVector();
    if (rez==0) printf("passed\n"); else printf("failed (%i)\n", rez);


    inputTextFile_DVector("vect1.txt",&a);
    printf("Vector from file vect1.txt : ");
    output_DVector(a,0,4,3);

    inputs_DVector(&a,"5 2 4 -3  1.5  -2");
    printf("Vector from string : ");
    output_DVector(a,1,1,1);

    a=generate_DVector(6);
    DVector b,c;
    printf("Generated vector: ");
    output_DVector(a,0,4,5);
    outputTextFile_DVector("vect_test.txt",a,0,3,4);
    inputTextFile_DVector("vect_test.txt",&b);
    printf("This vector after text file savings: ");
    output_DVector(b,0,4,5);
    outputBinaryFile_DVector("test.vct",a);
    inputBinaryFile_DVector("test.vct",&c);
    printf("This vector after binary file savings: ");
    output_DVector(c,0,4,5);

    input_DVector(&a);
    printf("Entered vector (in different formats): \n");
    output_DVector(a,0,3,2);
    output_DVector(a,1,1,1);

    DVector_destroy(a);
    DVector_destroy(b);
    DVector_destroy(c);

    return 0;
}
