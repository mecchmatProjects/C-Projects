#include <iostream>


using namespace std;

enum cmp { arr_unequal, arr_equal };
cmp arrcmp(int *a, int la, int*b, int lb)
{

    if (la == lb)
    {
        for (int i = 0; i < la; i++)
        {
            if (a[i] != b[i]) return arr_unequal;
        }
        return arr_equal;
    }

    int *lMax = nullptr, *lMin = nullptr, *arrBig = nullptr, *arrSmall = nullptr;
    int count = 0;

    if (la < lb)
    {
        lMax = &lb;
        arrBig = b;
        lMin = &la;
        arrSmall = a;

    }
    else
    {
        lMax = &la;
        arrBig = a;
        lMin = &lb;
        arrSmall = b;
    }
    for (int i = 0; i < *lMax; i++)
    {


        if (arrBig[i] != arrSmall[count])
        {
            count = 0;
            continue;
        }
        else
        {
            count++;
            continue;
        }

    }
    if (count == *lMin) return arr_insert;
    return arr_unequal;
}
