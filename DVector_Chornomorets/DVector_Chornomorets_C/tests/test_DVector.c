#include "../headers/common.h"
#include "../headers/DVector.h"
#include "../src/DVector.c"

/*int test_1 ()
{
    DVector a,b,c;
    int o1,o2;
    a=generate_DVector(50);
    if (a.n!=50) return 5;
    o1=outputBinaryFile_DVector("test1.vct",a);
    if (o1!=a.n) return 1;
    o2=inputBinaryFile_DVector("test1.vct",&b);
    if (o2!=a.n) return 2;
    if (b.n!=a.n) return 3;
    for (int i=0; i<a.n; i++) if (abs(b.items[i]-a.items[i])>pow(10,-3)) return 4;
    return 0;
}


int test_2 ()
{
    DVector a,b,c,d;
    Itype o1,o2;
    a=generate_DVector(5);
    o1=inputTextFile_DVector("vect1.txt",&b);
    o2=inputs_DVector(&c,"5 2 4 -3 1.5 -2");
    if (o1!=5) return 1;
    if (o2!=5) return 2;
    //output_DVector(c,0,3,2);
    //output_DVector(c,0,3,2);
    if (!(b.n==a.n && c.n==a.n)) return 3;
    for (int i=0; i<b.n; i++) if (abs(b.items[i]-c.items[i])>pow(10,-3)) return 4;
    d=sub_DVector(b,c);
    for (int i=0; i<b.n; i++) if (d.items[i]>pow(10,-3)) return 5;
    o2=unadd_DVector(&b,a);
    d=sub_DVector(b,c);
    for (int i=0; i<b.n; i++) if (abs(d.items[i]-a.items[i])>pow(10,-3)) return 6;
    d=mul_DVector(a,34);
    Dtype q=mmul_DVector(a,b);
    Dtype q1=mmul_DVector(d,b);
    if ((q1-34*q)>pow(10,-3)) return 7;
    if ((abs_DVector(d)-34*abs_DVector(a))>pow(10,-3) ) return 9;
    d=div_DVector(d,34);
    for (int i=0; i<b.n; i++) if (abs(d.items[i]-a.items[i])>pow(10,-3)) return 8;
    o2=unsub_DVector(&b,a);
    for (int i=0; i<b.n; i++) if (abs(b.items[i]-c.items[i])>pow(10,-3)) return 10;
    o2=unmul_DVector(&b,abs_DVector(d)/abs_DVector(b));
    if ((abs_DVector(d)-abs_DVector(b))>pow(10,-3) ) return 11;
    return 0;
}

int test_3 ()
{
    DVector a,b,c;
    Itype o1,o2;
    a=generate_DVector(50);
    if (a.n!=50) return 5;
    o1=outputTextFile_DVector("test3.txt",a,0,3,2);
    o2=inputTextFile_DVector("test3.txt",&b);
    if (b.n!=a.n) return 3;
    for (int i=0; i<a.n; i++) if (abs(b.items[i]-a.items[i])>pow(10,-3)) return 4;
    return 0;
}*/

Itype ifnotequal(DVector x,DVector y)
{
    if (x.n!=y.n) return 1;
    for (Ntype i=0;i<x.n;i++)
        if (abs(x.items[i]-y.items[i])>pow(10,-5))
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

int tests_add_DVector ()
{
    DVector a,b,c,d,e;
    a=qq(1,2,3);
    b=qq(5,2,3);
    c=qq(6,4,6);
    d=qq(-1,-2,-3);
    e=qq(0,0,0);
    if (ifnotequal(add_DVector(a,b),c)) return 1;
    if (ifnotequal(add_DVector(b,a),c)) return 2;
    if (ifnotequal(add_DVector(a,d),e)) return 3;
    if (ifnotequal(add_DVector(c,e),c)) return 4;
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
    if (ifnotequal(sub_DVector(c,b),a)) return 1;
    if (ifnotequal(sub_DVector(c,a),b)) return 2;
    if (ifnotequal(sub_DVector(e,a),d)) return 3;
    if (ifnotequal(sub_DVector(c,e),c)) return 4;
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
    if (ifnoteq(vmul_DVector(a,a),50)) return 1;
    if (ifnoteq(vmul_DVector(a,b),0)) return 2;
    if (ifnoteq(vmul_DVector(b,a),0)) return 3;
    if (ifnoteq(vmul_DVector(b,b),50)) return 4;
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
    if (ifnotequal(dmul_DVector(a,0),e)) return 1;
    if (ifnotequal(dmul_DVector(a,2),b)) return 2;
    if (ifnotequal(dmul_DVector(a,-1),d)) return 3;
    if (ifnotequal(dmul_DVector(b,-0.5),d)) return 4;
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
    if (ifnotequal(div_DVector(e,357),e)) return 1;
    if (ifnotequal(div_DVector(a,1.0/2),b)) return 2;
    if (ifnotequal(div_DVector(a,-1),d)) return 3;
    if (ifnotequal(div_DVector(b,-2),d)) return 4;
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
    if (ifnoteq(abs_DVector(a),sqrt(14))) return 1;
    if (ifnoteq(abs_DVector(b),sqrt(38))) return 2;
    if (ifnoteq(abs_DVector(c),sqrt(88))) return 3;
    if (ifnoteq(abs_DVector(d),sqrt(14))) return 4;
    if (ifnoteq(abs_DVector(e),0)) return 5;
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
    unadd_DVector(&a,e);
    if (ifnotequal(a,b)) return 1;
    unadd_DVector(&d,a);
    if (ifnotequal(d,e)) return 2;
    unadd_DVector(&d,a);
    if (ifnotequal(a,d)) return 3;
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
    unsub_DVector(&a,e);
    if (ifnotequal(a,b)) return 1;
    unsub_DVector(&e,a);
    if (ifnotequal(d,e)) return 2;
    unsub_DVector(&d,e);
    unsub_DVector(&d,e);
    if (ifnotequal(a,d)) return 3;
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
    undmul_DVector(&a,1);
    if (ifnotequal(a,b)) return 1;
    undmul_DVector(&a,-1);
    if (ifnotequal(a,d)) return 2;
    undmul_DVector(&a,0);
    if (ifnotequal(a,e)) return 3;
    undmul_DVector(&d,-1);
    if (ifnotequal(d,b)) return 4;
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
