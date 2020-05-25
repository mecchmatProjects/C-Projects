int main()
{
    setlocale(LC_ALL, "");
    int a[10];
    for (int i = 0; i < 10; i++) {
            cout << "[" << i + 1 << "]" << ": ";
            cin >> a[i];
        }

    int b[2];
    for (int i = 0; i < 2; i++) {
            cout << "[" << i + 1 << "]" << ": ";
            cin >> b[i];
        }

    switch (arrcmp(a, 10, b, 2))
    {
    case arr_unequal: cout << "Масиви не співпадають" << endl;
        break;
    case arr_equal: cout << "массивы співпадають" << endl;
        break;
    }
    system("pause");
    return 0;
}

}
