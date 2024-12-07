//
// OMG8
// Created by Ю. Петрова
// Комп мат 1
// OMG8.cpp test file
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "OMG8.h"

int main(int argc, char** argv) {
    std::ifstream inf;
    std::ofstream outf;
    std::istream* in = &std::cin;
    std::ostream* out = &std::cout;

    if (argc > 2) {
        inf.open(argv[1]);
        outf.open(argv[2]);
        in = &inf;
        out = &outf;
    }

    int n1, n2;
    uint64_t val;
    int ind1, ind2;
    // цей тест очевидно допомагав писати AI і я не знаю як виправити помилку в 32 рядку
    OMG8 str1(0), str2(0), str3(0);

    *out << "Enter length n1, n2 and two sets of numbers with such length:\n";
    *in >> n1 >> n2;

    str1.read(in, n1);
    str2.read(in, n2);

    *out << "Two strings:\n";
    str1.print(out);
    str2.print(out);
    *out << std::endl;

    str3 = str1;
    *out << "enter index and value\n";
    *in >> ind1 >> val;
    str3.add(ind1, val);
    *out << "first string, add "<< val <<" to index " << ind1 << std::endl;
    str3.print(out);
    *out << std::endl;

    str3 = str1;
    *out << "enter index and value\n";
    *in >> ind1 >> val;
    str3[ind1] = val;
    *out << "first string, replace by " << val << " on index " << ind1 << std::endl;
    str3.print(out);
    *out << std::endl;

    str3 = str1;
    *out << "enter index\n";
    *in >> ind1;
    str3.add(ind1, str2);
    *out << "add second string to first string on index " << ind1 << std::endl;
    str3.print(out);
    *out << std::endl;

    *out << "find second (return first index where meet second string in first)" << std::endl;
    *out << str1.find(str2) << std::endl;
    *out << std::endl;

    *out << "enter index1 and index2\n";
    *in >> ind1 >> ind2;
    str3 = str1.cut(ind1, ind2);
    *out << "cut first string from index " << ind1 << " to " << ind2 << std::endl;
    str3.print(out);
    *out << std::endl;

    std::vector<unsigned char> enc = str1.encode();
    *out << "encode first string" << std::endl;
    for (int i = 0; i < enc.size(); i++)
        *out << (int)enc[i] << " ";
    *out << "\n\n";

    *out << "decode next bytes" << std::endl;
    for (int i = 0; i < enc.size(); i++)
        *out << (int)enc[i] << " ";
    *out << std::endl;
    str3.decode(enc);
    str3.print(out);

    *out << std::endl;

    *out << "2 : " << (int64_t)str1.toInt(2) << std::endl;
    *out << "10 : " << (int64_t)str1.toInt(10) << std::endl;
    *out << "16 : " << (int64_t)str1.toInt(16) << std::endl;

    if (str1.toInt(10) > 0){
        str3.fromInt(str1.toInt(10), 2);
        *out << std::endl << "str1 is number, binary:\n";
        str3.print(out);
    }

    return 0;
}