//#include "../src/Bit_fields.cpp"
#include "../src/Bit_fields.h"
int main()
{
    unsigned short x,y;
    bool ct;
    ifstream file;
    time a,b,c;
    file.open("");

    cout << "Console(yes/no)?" << endl;
    ct = safe_bool_fc(file);
    if (!ct)
        file.open("Bit_fields_test.txt");
    
    cout << "Shop manager" << endl;
    shop_manager(file);

    cout << endl <<"Is even" << endl;
    x = safe_short_fc(file);
    cout << is_even(x) << endl;
    
    ofstream cout1("is_even.txt");
    cout1 << is_even(x) << endl;
    cout1.close();
    
    cout << endl <<"Multiplicity 8" << endl;
    y = safe_short_fc(file);
    cout << multiplicity8(y) << endl;
    
    ofstream cout2("Multiplicity_8.txt");
    cout2 << multiplicity8(y) << endl;
    cout2.close();
    
    cout << endl <<"Time diference" << endl;
    cout << "year = " << endl;
    a.year = year(file);
    cout << "month = " << endl;
    a.month = month(file);
    cout << "day = " << endl;
    a.day = day(file);
    cout << "hour = " << endl;
    a.hour = hour(file);
    cout << "minute = " << endl;
    a.minute = sec_min(file);
    cout << "sec = " << endl;
    a.second = sec_min(file);
    cout << "year = " << endl;
    b.year = year(file);
    cout << "month = " << endl;
    b.month = month(file);
    cout << "day = " << endl;
    b.day = day(file);
    cout << "hour = " << endl;
    b.hour = hour(file);
    cout << "minute = " << endl;
    b.minute = sec_min(file);
    cout << "sec = " << endl;
    b.second = sec_min(file);
    cout << "diference" << endl;
    c = diference(a,b);
    cout << c.year << " " << c.month << " " << c.day << " " << c.hour << " " << c.minute << " " << c.second << " " <<endl;
    
    ofstream cout3("diference.txt");
    cout3 << c.year << " " << c.month << " " << c.day << " " << c.hour << " " << c.minute << " " << c.second << " " <<endl;
    cout3.close();
    file.close();
    cout << "Press any button to exit..." << endl;
    getc(stdin);
}
