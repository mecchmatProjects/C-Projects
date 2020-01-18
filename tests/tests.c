#include "../headers/BigNumbers.h"
#include "assert.h"


void testBinPow(){
    assert(binPow(2, 8) == 256);
    assert(binPow(10, 4) == 10000);
    assert(binPow(0, 1) == 0);
    assert(binPow(5, 0) == 1);
    assert(binPow(1, 10) == 1);
}


void testConvert2int(){
    assert(convert2int('1') == 1);
    assert(convert2int('4') == 4);
    assert(convert2int('a') == 10);
    assert(convert2int('f') == 15);
    assert(convert2int('0') == 0);
}


void testFromOtherChars(){
    BigInteger *test = fromOtherChars("1234567890", 10, 10);
    assert(test->body[0] == 34567890);
    assert(test->body[1] == 12);
    assert(fromOtherChars("12345", 5, 10)->body[0] == 12345);
    assert(fromOtherChars("34757235", 8, 8)->body[0] == 7593629);
    assert(fromOtherChars("101010101", 9, 2)->body[0] == 341);
    assert(fromOtherChars("12abf", 5, 16)->body[0] == 76479);
    free(test->body);
    free(test);
}


void testFromChars(){
    BigInteger *test = fromChars("123456781234567812345678", 24);
    assert(test->body[0] == test->body[1] && test->body[1] == test->body[2]);
    assert(test->body[2] == 12345678);
    assert(fromChars("0", 1)->body[0] == 0);
}


void testFromInt(){
    BigInteger *test = fromInt(3485732394875);
    assert(test->body[0] == 32394875);
    assert(test->body[1] == 34857);

    assert(fromInt(123311)->body[0] == 123311);
    assert(fromInt(0)->body[0] == 0);
    assert(fromInt(1)->body[0] == 1);
}


void testAbsRelation(){
    BigInteger *test1 = fromChars("23874928347928347928374293234", 29);
    BigInteger *test2 = fromChars("23874928347928347928374293234", 29);
    BigInteger *test3 = fromChars("23429347234", 11);
    BigInteger *test4 = fromChars("23874928347928347888888888888", 29);

    assert(absRelation(test1, test2) == 0);
    assert(absRelation(test1, test3) == 1);
    assert(absRelation(test4, test1) == -1);
}

void testPrint(){
    printf("%s", "testing print big number 29837492837492837492837492374982:\n");
    print(fromChars("29837492837492837492837492374982", 32));
    printf("%s", "testing print big number 10000000000000800000000000000010:\n");
    print(fromChars("10000000000000800000000000000010", 32));
}


void testWrite(){
    FILE *test_f = fopen(".../tests/output.txt", "w");
    if (test_f == NULL){
        printf("Couldn't open the file.");
        return;
    }
    fprintf(test_f, "%s", "testing print big number 29837492837492837492837492374982:\n");
    fprint(test_f, fromChars("29837492837492837492837492374982", 32));
    fprintf(test_f, "%s", "testing print big number 10000000000000800000000000000010:\n");
    fprint(test_f, fromChars("10000000000000800000000000000010", 32));
    fclose(test_f);
}


void testInput(){
    printf("%s", "please, enter the any big number in decimal system:\n--> ");
    BigInteger *test = inputBigInt();
    printf("%s", "did you input this number (y/n)?: ");
    print(test);
    printf("--> ");
    char *ans = (char*) malloc(sizeof(char)*100);
    fgets(ans, 100, stdin);
    assert(ans[0] == 'y' || ans[0] == 'Y');
    free(test->body);
    free(test);

    printf("%s", "please, enter the any big number in hexadecimal system:\n--> ");
    BigInteger *test2 = inputAnyBigInt(16);
    printf("%s", "did you input this number (y/n)?: ");
    print(test2);
    printf("--> ");
    fgets(ans, 100, stdin);
    assert(ans[0] == 'y' || ans[0] == 'Y');
    free(test2->body);
    free(test2);

    printf("%s", "please, enter the any big number in binary system:\n--> ");
    BigInteger *test3 = inputAnyBigInt(16);
    printf("%s", "did you input this number (y/n)?: ");
    print(test3);
    printf("--> ");
    fgets(ans, 100, stdin);
    assert(ans[0] == 'y' || ans[0] == 'Y');
    free(test3->body);
    free(test3);

}


void testAdd(){
    BigInteger *test1 = fromChars("230948230492834230409928342034410409342", 39);
    BigInteger *test2 = fromChars("22034023402340230423094823049283048203480", 41);
    BigInteger *test3 = fromChars("22264971632833064653504751391317458612822", 41);
    BigInteger *resAdd = add(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);

    test1 = fromChars("-230948230492834230409928342034410409342", 40);
    test2 = fromChars("-22034023402340230423094823049283048203480", 42);
    test3 = fromChars("22264971632833064653504751391317458612822", 41);
    resAdd = add(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == -1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);

    test1 = fromChars("-230948230492834230409928342034410409342", 40);
    test2 = fromChars("22034023402340230423094823049283048203480", 41);
    test3 = fromChars("21803075171847396192684894707248637794138", 41);
    resAdd = add(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);

    test1 = fromChars("230948230492834230409928342034410409342", 39);
    test2 = fromChars("-22034023402340230423094823049283048203480", 42);
    test3 = fromChars("21803075171847396192684894707248637794138", 41);
    resAdd = add(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == -1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);
}


void testSub(){
    BigInteger *test1 = fromChars("230948230492834230409928342034410409342", 39);
    BigInteger *test2 = fromChars("22034023402340230423094823049283048203480", 41);
    BigInteger *test3 = fromChars("21803075171847396192684894707248637794138", 41);
    BigInteger *resAdd = sub(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == -1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);

    test1 = fromChars("22034023402340230423094823049283048203480", 41);
    test2 = fromChars("230948230492834230409928342034410409342", 39);
    test3 = fromChars("21803075171847396192684894707248637794138", 41);
    resAdd = sub(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);

    test1 = fromChars("-22034023402340230423094823049283048203480", 42);
    test2 = fromChars("230948230492834230409928342034410409342", 39);
    test3 = fromChars("22264971632833064653504751391317458612822", 41);
    resAdd = sub(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == -1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);

    test1 = fromChars("22034023402340230423094823049283048203480", 41);
    test2 = fromChars("-230948230492834230409928342034410409342", 40);
    test3 = fromChars("22264971632833064653504751391317458612822", 41);
    resAdd = sub(test1, test2);
    assert(absRelation(resAdd, test3) == 0);
    assert(resAdd->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resAdd->body);
    free(test1);
    free(test2);
    free(test3);
    free(resAdd);
}


void testMul(){
    BigInteger *test1 = fromChars("233429374928374928374982374982374928374", 39);
    BigInteger *test2 = fromInt(0);
    BigInteger *resMul = mul(test1, test2);
    assert(absRelation(resMul, test2) == 0);
    free(test1->body);
    free(test2->body);
    free(resMul->body);
    free(test1);
    free(test2);
    free(resMul);

    test1 = fromChars("233429374928374928374982374982374928374", 39);
    test2 = fromChars("34293842398472937492387492837429", 32);
    BigInteger *test3 = fromChars("8005190194967739835174389342764921496012828908260664922868751901310446", 70);
    resMul = mul(test1, test2);
    assert(absRelation(resMul, test3) == 0);
    assert(resMul->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resMul->body);
    free(test1);
    free(test2);
    free(test3);
    free(resMul);

    test1 = fromChars("-233429374928374928374982374982374928374", 40);
    test2 = fromChars("34293842398472937492387492837429", 32);
    test3 = fromChars("8005190194967739835174389342764921496012828908260664922868751901310446", 70);
    resMul = mul(test1, test2);
    assert(absRelation(resMul, test3) == 0);
    assert(resMul->sign == -1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resMul->body);
    free(test1);
    free(test2);
    free(test3);
    free(resMul);


    test1 = fromChars("23342937492837492837498237234293875293875982875981275987293749217439213749123234982374928374", 92);
    test2 = fromChars("34293842398472937492387492837429383487534875684276587326458763248756384756832758372587324234", 92);
    test3 = fromChars("800519019496773983517438925224860279206409394870520273252097690010678123964436343976252396458580514919144887866121863461383303676305234655321004767498390498747532947974205436064415516", 183);
    resMul = mul(test1, test2);
    assert(absRelation(resMul, test3) == 0);
    assert(resMul->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resMul->body);
    free(test1);
    free(test2);
    free(test3);
    free(resMul);

}


void testDiv(){
    BigInteger *test1 = fromChars("398472938648273658723465827346587236458283468237462", 51);
    BigInteger *test2 = fromChars("94989249234293482347295823752935822939823985", 44);
    BigInteger *test3 = fromChars("4194926", 7);
    BigInteger *resDiv = divide(test1, test2);
    assert(absRelation(test3, resDiv) == 0);
    assert(resDiv->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resDiv->body);
    free(test1);
    free(test2);
    free(test3);
    free(resDiv);

    test1 = fromInt(0);
    test2 = fromChars("94989249234293482347295823752935822939823985", 44);
    test3 = fromInt(0);
    resDiv = divide(test1, test2);
    assert(absRelation(test3, resDiv) == 0);
    assert(resDiv->sign == 1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resDiv->body);
    free(test1);
    free(test2);
    free(test3);
    free(resDiv);


    test1 = fromChars("398472938648273658723465827346587236458283468237462", 51);
    test2 = fromChars("-94989249234293482347295823752935822939823985", 45);
    test3 = fromChars("4194927", 7);
    resDiv = divide(test1, test2);
    assert(absRelation(test3, resDiv) == 0);
    assert(resDiv->sign == -1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resDiv->body);
    free(test1);
    free(test2);
    free(test3);
    free(resDiv);


    test1 = fromChars("-398472938648273658723465827346587236458283468237462", 52);
    test2 = fromChars("94989249234293482347295823752935822939823985", 44);
    test3 = fromChars("4194927", 7);
    resDiv = divide(test1, test2);
    assert(absRelation(test3, resDiv) == 0);
    assert(resDiv->sign == -1);
    free(test1->body);
    free(test2->body);
    free(test3->body);
    free(resDiv->body);
    free(test1);
    free(test2);
    free(test3);
    free(resDiv);
}


void testGcd(){
    BigInteger *test1 = fromChars("242938402938409283509298450932845093845098384095830458309458", 60);
    BigInteger *test2 = fromChars("249273498273947239491294793874792837471199119119818721", 54);
    BigInteger *test3 = fromInt(1);
    BigInteger *resGCD = gcd(test1, test2);
    BigInteger **resXGCD = xgcd(test1, test2);
    BigInteger *tmp1 = mul(test1, resXGCD[0]);                   // check if xa + yb == gcd(a, b)
    BigInteger *tmp2 = mul(test2, resXGCD[1]);
    BigInteger *check = add(tmp1, tmp2);
    assert(absRelation(resGCD, test3) == 0);
    assert(absRelation(check, resGCD) == 0);
    assert(absRelation(resGCD, resXGCD[2]) == 0);
    free(test1->body); free(test1);
    free(test2->body); free(test2);
    free(test3->body); free(test3);
    free(resGCD->body); free(resGCD);
    free(resXGCD[0]->body); free(resXGCD[0]);
    free(resXGCD[1]->body); free(resXGCD[1]);
    free(resXGCD[2]->body); free(resXGCD[2]);
    free(tmp1->body); free(tmp1);
    free(tmp2->body); free(tmp2);
    free(check->body); free(check);


    test1 = fromChars("242938402938409283509298450932845093845098384095830458309458", 60);
    test2 = fromChars("1", 1);
    test3 = fromInt(1);
    resGCD = gcd(test1, test2);
    resXGCD = xgcd(test1, test2);
    tmp1 = mul(test1, resXGCD[0]);                   // check if xa + yb == gcd(a, b)
    tmp2 = mul(test2, resXGCD[1]);
    check = add(tmp1, tmp2);
    assert(absRelation(resGCD, test3) == 0);
    assert(absRelation(check, resGCD) == 0);
    assert(absRelation(resGCD, resXGCD[2]) == 0);
    free(test1->body); free(test1);
    free(test2->body); free(test2);
    free(test3->body); free(test3);
    free(resGCD->body); free(resGCD);
    free(resXGCD[0]->body); free(resXGCD[0]);
    free(resXGCD[1]->body); free(resXGCD[1]);
    free(resXGCD[2]->body); free(resXGCD[2]);
    free(tmp1->body); free(tmp1);
    free(tmp2->body); free(tmp2);
    free(check->body); free(check);


    test1 = fromChars("23847298387529875982375982759823759823", 38);
    test2 = fromChars("711566967485332047616502422590651880088702130682", 48);
    test3 = fromChars("23847298387529875982375982759823759823", 38);
    resGCD = gcd(test1, test2);
    resXGCD = xgcd(test1, test2);
    tmp1 = mul(test1, resXGCD[0]);                   // check if xa + yb == gcd(a, b)
    tmp2 = mul(test2, resXGCD[1]);
    check = add(tmp1, tmp2);
    assert(absRelation(resGCD, test3) == 0);
    assert(absRelation(check, resGCD) == 0);
    assert(absRelation(resGCD, resXGCD[2]) == 0);
    free(test1->body); free(test1);
    free(test2->body); free(test2);
    free(test3->body); free(test3);
    free(resGCD->body); free(resGCD);
    free(resXGCD[0]->body); free(resXGCD[0]);
    free(resXGCD[1]->body); free(resXGCD[1]);
    free(resXGCD[2]->body); free(resXGCD[2]);
    free(tmp1->body); free(tmp1);
    free(tmp2->body); free(tmp2);
    free(check->body); free(check);
}


void testLcm(){
    BigInteger *test1 = fromChars("938298375938487593847598347593", 30);
    BigInteger *test2 = fromChars("2239482342034202395334034045095", 31);
    BigInteger *test3 = fromChars("2101302644473612696602894588951078859161109796232327646706335", 61);
    BigInteger *resLcm = lcm(test1, test2);
    assert(absRelation(test3, resLcm) == 0);
    free(test1->body); free(test1);
    free(test2->body); free(test2);
    free(test3->body); free(test3);
    free(resLcm->body); free(resLcm);
}


void testRead(){
    FILE *test_f = fopen(".../tests/tests_input.txt", "r");

    if (test_f == NULL){
        printf("%s", "couldn't open the file with tests");
        return;
    }
    BigInteger *test_in = readBigInt(test_f);
    BigInteger *test_compare = fromChars("29348209398409218509128435082340958234098523094852320934029384029830238350893250983450388540939850938450939845093521385", 119);
    assert(absRelation(test_in, test_compare) == 0);

    free(test_in->body);
    free(test_compare->body);
    free(test_in);
    free(test_compare);

    test_in = readAnyBigInt(2, test_f);
    test_compare = fromChars("547354626757897374613016542524560549", 36);
    assert(absRelation(test_in, test_compare) == 0);

    free(test_in->body);
    free(test_compare->body);
    free(test_in);
    free(test_compare);

    test_in = readAnyBigInt(16, test_f);
    test_compare = fromChars("4114839360471398064001275390275898310250353272723278054983840922622348035285749229332018933217419558537285839429923", 115);
    assert(absRelation(test_in, test_compare) == 0);

    free(test_in->body);
    free(test_compare->body);
    free(test_in);
    free(test_compare);
    fclose(test_f);
}


int main(){
    printf("%s", "Start unittests...\n\n");
    testBinPow();
    testConvert2int();
    testFromChars();
    testFromInt();
    testFromOtherChars();
    testAbsRelation();
    testAdd();
    testSub();
    testMul();
    testDiv();
    testGcd();
    testLcm();
    printf("%s", "\n\nSUCCESS, start print tests...\n\n");
    testPrint();
    printf("%s", "\n\nSUCCESS, start filewrite tests...\n\n");
    testWrite();

    printf("%s", "\n\nSUCCESS, start input tests...\n\n");
    testInput();
    printf("%s", "\n\nSUCCESS, start fileread tests...\n\n");
    testRead();
    printf("%s", "\n\nSUCCESS, finish...");
}