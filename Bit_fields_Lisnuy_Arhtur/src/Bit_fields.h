#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream> 
using namespace std;
//структура продукта
struct product
{
    string product_name;
    unsigned short price;
    string producing_country;
    unsigned short eu_standart:1;
    unsigned short availability_in_the_store:1;
    unsigned short goods_of_the_month:1;
};
//стуктура "время"
struct time //4 бита
{
    unsigned short year:14; //максимально 16384 года
    unsigned short month:4;
    unsigned short day:5;
    unsigned short hour:5; 
    unsigned short minute:6;
    unsigned short second:6;

};
//безопасный ввод
string safe_string_fc(istream& file);
unsigned short safe_bool_fc(istream& file);
unsigned short safe_short_fc(istream& file);
unsigned short sec_min(istream& file);
unsigned short hour(istream& file);
unsigned short day(istream& file);
unsigned short month(istream& file);
unsigned short year(istream& file);
//функции:
//для магазина
void shop_manager(istream& file);
//проверка беззнакового числа на чётность
bool is_even(unsigned short n);
//проверка беззнакового числа на кратность 8
bool multiplicity8(unsigned short n);
//Разница времени
time diference(time a, time b);
//запись в файл
void write_in_file(string name);

