//#include "Bit_fields.h"
string safe_string_fc(istream& file)
{
    string st;
    if (!file)
        getline(cin, st);
    else
    {
        getline(file, st);
        cout << st << endl;
    }
    return st;
}

unsigned short safe_bool_fc(istream& file)
{
    string st;
    while (true)
    {
        if (!file)
            getline(cin, st);
        else
        {
            getline(file, st);
            cout << st << endl;
        }
        if ( st == "yes" )
            return 1;
        if ( st == "no" )
            return 0;
        cout << "Incorect answer, try again:" << endl;
    }
}

unsigned short safe_short_fc(istream& file)
{
    string st;
    while (true)
    {
        if (!file)
            getline(cin, st);
        else
        {
            getline(file, st);
            cout << st << endl;
        }
        if (st.find_first_not_of("0123456789") == string::npos)
            return stoi(st);
        cout << "Incorect answer, try again:" << endl;
    }
}

void shop_manager(istream& file)
{
    product shop[5];
    for (int i = 0; i<5; i++)
    {
        cout << "Product name:" << endl;
        shop[i].product_name = safe_string_fc(file);
        cout << "Product price:" << endl;
        shop[i].price = safe_short_fc(file);
        cout << "Producing country:" << endl;
        shop[i].producing_country = safe_string_fc(file);
        cout << "Matches EU standarts(yes,no):" << endl;
        shop[i].eu_standart = safe_bool_fc(file);
        cout << "Available in shop(yes,no):" << endl;
        shop[i].availability_in_the_store = safe_bool_fc(file);
        cout << "Is good of the month(yes,no):" << endl;
        shop[i].goods_of_the_month = safe_bool_fc(file);
    }
    cout << endl << "Product list:" << endl;
    for (int i = 0; i<5; i++)
    {
        cout << shop[i].product_name << endl;
        cout << "Price: " << shop[i].price << endl;
        cout << "Made in: " << shop[i].producing_country << endl;
        cout << "EU standarts: " << shop[i].eu_standart << endl;
        cout << "Available in shop: " << shop[i].availability_in_the_store << endl;
        cout << "Is good of the month " << shop[i].goods_of_the_month << endl;
    }
    cout << endl << "Products in shop that doesn't match EU standarts:" << endl;
    for (int i = 0; i<5; i++)
    {
        if ((shop[i].availability_in_the_store == 1) && (shop[i].eu_standart == 0))
            cout << shop[i].product_name << endl;
    }
    //добавил вывод в текстовый файл
    ofstream cout("shop_manager.txt");
    cout << "Product list:" << endl;
    for (int i = 0; i<5; i++)
    {
        cout << shop[i].product_name << endl;
        cout << "Price: " << shop[i].price << endl;
        cout << "Made in: " << shop[i].producing_country << endl;
        cout << "EU standarts: " << shop[i].eu_standart << endl;
        cout << "Available in shop: " << shop[i].availability_in_the_store << endl;
        cout << "Is good of the month " << shop[i].goods_of_the_month << endl;
    }
    cout << endl << "Products in shop that doesn't match EU standarts:" << endl;
    for (int i = 0; i<5; i++)
    {
        if ((shop[i].availability_in_the_store == 1) && (shop[i].eu_standart == 0))
            cout << shop[i].product_name << endl;
    }
    cout.close();
}

bool is_even(unsigned short n)
{
    unsigned short a;
    a = n >> 1;
    a = a << 1;
    if (a == n)
        return true;
    else
        return false;
}

bool multiplicity8(unsigned short n)
{
    unsigned a;
    a = n >> 3;
    a = a << 3;
    if (a == n)
        return true;
    else
        return false;
}

unsigned short sec_min(istream& file)
{
    while (true)
    {
        unsigned short x = safe_short_fc(file);
        if (x < 59)
            return x;
        cout << "Max is 59:" << endl;
    }
}

unsigned short hour(istream& file)
{
    while (true)
    {
        unsigned short x = safe_short_fc(file);
        if (x < 24)
            return x;
        cout << "Max is 23:" << endl;
    }
}

unsigned short day(istream& file)
{
    while (true)
    {
        unsigned short x = safe_short_fc(file);
        if (x < 32)
            return x;
        cout << "Max is 31:" << endl;
    }
}

unsigned short month(istream& file)
{
    while (true)
    {
        unsigned short x = safe_short_fc(file);
        if (x < 13)
            return x;
        cout << "Max is 12:" << endl;
    }
}

unsigned short year(istream& file)
{
    while (true)
    {
        unsigned short x = safe_short_fc(file);
        if (x < 16385)
            return x;
        cout << "Max is 16384:" << endl;
    }
}

time diference(time a, time b)
{
    time c,d;
    d.year = 0;
    d.month = 0;
    d.day = 0;
    d.hour = 0;
    d.minute = 0;
    d.second = 0;
    int year_c = 0, month_c = 0, day_c = 0, hour_c = 0 , minute_c = 0, second_c = 0, temp;
    //поменяем местами а и б, если б больше а
    if (a.year < b.year)
        return diference(b,a);
    else if (a.year == b.year)
    {
        if (a.month < b.month)
            return diference(b,a);
        else if (a.month == b.month)
        {
            if (a.day < b.day)
            {
            return diference(b,a);
            }
            else if (a.day == b.day)
            {
                if (a.hour < b.hour)
                    return diference(b,a);
                else if (a.hour == b.hour)
                {
                    if (a.minute < b.minute)
                        return diference(b,a);
                    else if (a.minute == b.minute)
                    {
                        if (a.second < b.second)
                            return diference(b,a);
                        else if (a.second == b.second)
                        {
                            return d;
                        }
                    }
                }
            }
        }
    }
    //считаем разницу
    //секунды
    second_c = second_c + a.second - b.second;
    if (second_c < 0)
    {
        minute_c--;
        c.second = 60 + second_c;
    }
    else
        c.second = second_c;
    //минуты
    minute_c = minute_c + a.minute - b.minute;
    if (minute_c < 0)
    {
        hour_c--;
        c.minute = 60 + minute_c;
    }
    else
        c.minute = minute_c;
    //часы
    hour_c = hour_c + a.hour - b.hour;
    if (hour_c < 0)
    {
        day_c--;
        c.hour = 24 + hour_c;
    }
    else
        c.hour = hour_c;
    //дни
    day_c = day_c + a.day - b.day;
    if (day_c < 0)
    {
        month_c--;
        temp = month_c + a.month;
        if (temp < 0)
        {
            temp = 12 + temp;
            year_c--;
        }
        //31 дней
        if ((temp == 1) || (temp == 3) || (temp == 5) || (temp == 7) || (temp == 8) || (temp== 10) || (temp == 12))
            c.day = 31 + day_c;
        //30 дней
        else if ((temp == 4) || (temp == 6) || (temp == 9) || (temp == 11))
            c.day = 30 + day_c;
        //(28/29) дней
        else
        {
            temp = year_c + a.year - b.year;
            if (temp % 4 == 0)
                c.day = 28 + day_c;
            else
                c.day = 29 + day_c;
        }
    }
    else
        c.day = day_c;
    //месяца
    month_c = month_c + a.month - b.month;
    if (month_c < 0)
    {
        year_c--;
        c.month = 12 + month_c;
    }
    else
        c.month = month_c;
    //года
    year_c = year_c + a.year - b.year;
    if (year_c < 0)
        c.year = 0;
    else
        c.year = year_c;
    return c;
}

/*void write_in_file(string name, string x)
{
    freopen(name, "a", stdout); // перенаправить стандартный поток вывода в файл
    cout << x;
    fclose (stdout);
}
*/

/*int main()
{
    ifstream file; // создаем объект класса ifstream
    file.open("d:\\1\\файл.txt"); // открываем файл
    file.open("d:\\2\\файл.txt");
    string x = safe_string_fc(file);
    cout << x;
    //1
    //shop_manager();

    //2 or 3
    //int n;
    //cout << "Enter integer = " << endl;
    //cout << multiplicity8(safe_int_fc());

    //3
    
}*/
