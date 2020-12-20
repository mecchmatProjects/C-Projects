#include <iostream>
#include "../Data_Comparison_Falendysh/Header.h"

using namespace std;
//Создание первой структуры(для методов dist и corr).
res create()
{
    int size;
    cout << "Enter arr size: "; cin >> size;
    res Arrays;
    Arrays.n = size;
    Arrays.R1 = new int[size];
    Arrays.R2 = new int[size];

    for (int i = 0; i < size; i++)
    {
        cout << "R1 elem ¹ " << i + 1 << " = "; cin >> Arrays.R1[i];
    }

    for (int j = 0; j < size; j++)
    {
        cout << "R2 elem ¹ " << j + 1 << " = "; cin >> Arrays.R2[j];
    }
    return Arrays;
}

//Создание второй структуры(для матрицы путаницы).
res1 create1()
{
    int size;
    cout << "Enter arr size: "; cin >> size;
    res1 Arrays1;
    Arrays1.n = size;
    Arrays1.R1 = new bool[size];
    Arrays1.R2 = new bool[size];

    for (int i = 0; i < size; i++)
    {
        cout << "R1 elem ¹ " << i + 1 << " = "; cin >> Arrays1.R1[i];
    }

    for (int j = 0; j < size; j++)
    {
        cout << "R2 elem ¹ " << j + 1 << " = "; cin >> Arrays1.R2[j];
    }

    return Arrays1;
}
//Создание третьей структуры(для методов распределения).
res2 create2()
{
    int size;
    cout << "Enter arr size: "; cin >> size;
    res2 Arrays2;
    Arrays2.n = size;
    Arrays2.R1 = new double[size];
    Arrays2.R2 = new double[size];

    for (int i = 0; i < size; i++)
    {
        cout << "R1 elem ¹ " << i + 1 << " = "; cin >> Arrays2.R1[i];
    }

    for (int j = 0; j < size; j++)
    {
        cout << "R2 elem ¹ " << j + 1 << " = "; cin >> Arrays2.R2[j];
    }

    Arrays2.R1clone1 = new double[size];
    Arrays2.R2clone1 = new double[size];
    Arrays2.R1clone2 = new double[size];
    Arrays2.R2clone2 = new double[size];
    return Arrays2;
}
//Чтение первой структуры из файла.
res data_from_txt()
{
    res Arrays;
    Arrays.R1 = new int[100];
    Arrays.R2 = new int[100];
    FILE* file = fopen("arrays.txt", "r");

    int amount;
    fscanf(file, "%i", &amount);
    Arrays.n = amount;
    int j = 0;
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%i", &Arrays.R1[i]);
    }
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%i", &Arrays.R2[i]);
    }
    return Arrays;
}
//Чтение второй структуры из файла.
res1 data_from_txt1()
{
    res1 Arrays1;
    Arrays1.R1 = new bool[100];
    Arrays1.R2 = new bool[100];
    FILE* file = fopen("arrays.txt", "r");
    fseek(file, 19, SEEK_CUR);

    int amount;
    fscanf(file, "%i", &amount);
    Arrays1.n = amount;
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%i", &Arrays1.R1[i]);
    }
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%i", &Arrays1.R2[i]);
    }
    return Arrays1;
}
//Чтение третьей структуры из файла.
res2 data_from_txt2()
{
    res2 Arrays2;
    Arrays2.R1 = new double[100];
    Arrays2.R2 = new double[100];
    FILE* file = fopen("arrays.txt", "r");
    fseek(file, 45, SEEK_CUR);

    int amount;
    fscanf(file, "%i", &amount);
    Arrays2.n = amount;
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%le", &Arrays2.R1[i]);
    }
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%le", &Arrays2.R2[i]);
    }

    Arrays2.R1clone1 = new double[Arrays2.n];
    Arrays2.R2clone1 = new double[Arrays2.n];
    Arrays2.R1clone2 = new double[Arrays2.n];
    Arrays2.R2clone2 = new double[Arrays2.n];
    return Arrays2;
}
//Метод подсчета расстояния между результатами.
int dist(res Arrays)
{
    int evkl = 0;
    for (int i = 0; i < Arrays.n; i++)
    {
        evkl += pow((Arrays.R1[i] - Arrays.R2[i]), 2);
    }
    evkl = sqrt(evkl);
    return evkl;
}
//Метод корреляции.
int corr(res Arrays)
{
    float R1Av = 0.0, R2Av = 0.0, cov = 0.0, sx = 0.0, sy = 0.0, kcor;
    for (int i = 0; i < Arrays.n; i++)
    {
        R1Av += Arrays.R1[i];
        R2Av += Arrays.R2[i];
    }
    R1Av = R1Av / Arrays.n;
    R2Av = R2Av / Arrays.n;

    for (int i = 0; i < Arrays.n; i++)
    {
        cov += (Arrays.R1[i] - R1Av) * (Arrays.R2[i] - R2Av);
        sx += pow((Arrays.R1[i] - R1Av), 2);
        sy += pow((Arrays.R2[i] - R2Av), 2);
    }

    kcor = (cov) / (sqrt(sx * sy));
    delete[] Arrays.R1;
    delete[] Arrays.R2;
    return kcor;
}

//True Positive
void TP(res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == true)
        {
            cout << "For " << i << " element TP is True" << endl;
            fprintf(file, "TP is True for element %d \n", i);
        }
        else
        {
            cout << "For " << i << " element TP is False" << endl;
            fprintf(file, "TP is False for element %d \n", i);
        }
    }
}
//True Negative
void TN(res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == false)
        {
            cout << "For " << i << " element TN is True" << endl;
            fprintf(file, "TN is True for element %d \n", i);
        }
        else
        {
            cout << "For " << i << " element TN is False" << endl;
            fprintf(file, "TN is False for element %d \n", i);
        }
    }
}

//False Positive
void FP(res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == true) && (Arrays1.R2[i] == false))
        {
            cout << "For " << i << " element FP is True" << endl;
            fprintf(file, "FP is True for element %d \n", i);
        }
        else
        {
            cout << "For " << i << " element FP is False" << endl;
            fprintf(file, "FP is False for element %d \n", i);
        }
    }
}

//False Negative
void FN(res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == false) && (Arrays1.R2[i] == true))
        {
            cout << "For " << i << " element FN is True" << endl;
            fprintf(file, "FN is True for element %d \n", i);
        }
        else
        {
            cout << "For " << i << " element FN is False" << endl;
            fprintf(file, "FN is False for element %d \n", i);
        }
    }
}
//True Positive Rate
int TPR(res1 Arrays1)
{
    int tp = 0, ay = 0, tpr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == true)
        {
            tp++;
        }
        else if (Arrays1.R2[i] == true)
        {
            ay++;
        }
    }
    tpr = tp / ay;
    return tpr;
}
//False Positive Rate
int FPR(res1 Arrays1)
{
    int fp = 0, an = 0, fpr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == true) && (Arrays1.R2[i] == false))
        {
            fp++;
        }
        else if (Arrays1.R2[i] == false)
        {
            an++;
        }
    }
    fpr = fp / an;
    return fpr;
}
//Accuracy
int ACC(res1 Arrays1)
{
    int tp = 0, tn = 0, acc;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == true)
        {
            tp++;
        }
        else if (Arrays1.R1[i] == Arrays1.R2[i] == false)
        {
            tn++;
        }
    }
    acc = (tp + tn) / (Arrays1.n);
    return acc;
}
//Positive predictive value
int PPV(res1 Arrays1)
{
    int tp = 0, fp = 0, ppv;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == true)
        {
            tp++;
        }
        else if ((Arrays1.R1[i] == true) && (Arrays1.R2[i] == false))
        {
            fp++;
        }
    }
    ppv = (tp) / (tp + fp);
    return ppv;
}
//Negative predictive value
int NPV(res1 Arrays1)
{
    int tn = 0, fn = 0, npv;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == false)
        {
            tn++;
        }
        else if ((Arrays1.R1[i] == false) && (Arrays1.R2[i] == true))
        {
            fn++;
        }
    }
    npv = (tn) / (tn + fn);
    return npv;
}
//False negative rate
int FNR(res1 Arrays1)
{
    int fn = 0, ay = 0, fnr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == false) && (Arrays1.R2[i] == true))
        {
            fn++;
        }
        else if (Arrays1.R2[i] == true)
        {
            ay++;
        }
    }
    fnr = fn / ay;
    return fnr;
}
//False discovery rate
int FDR(res1 Arrays1)
{
    int fp = 0, tp = 0, fdr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == true)
        {
            tp++;
        }
        else if ((Arrays1.R1[i] == true) && (Arrays1.R2[i] == false))
        {
            fp++;
        }
    }
    fdr = (fp) / (fp + tp);
    return fdr;
}
//False omission rate
int FOR(res1 Arrays1)
{
    int fn = 0, tn = 0, forr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == false)
        {
            tn++;
        }
        else if ((Arrays1.R1[i] == false) && (Arrays1.R2[i] == true))
        {
            fn++;
        }
    }
    forr = (fn) / (fn + tn);
    return forr;
}
//F1 score
int F1(res1 Arrays1)
{
    int fp = 0, tp = 0, fn = 0, f1;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == true)
        {
            tp++;
        }
        else if ((Arrays1.R1[i] == true) && (Arrays1.R2[i] == false))
        {
            fp++;
        }
        else if ((Arrays1.R1[i] == false) && (Arrays1.R2[i] == true))
        {
            fn++;
        }
    }

    f1 = (2 * tp) / (2 * tp + fp + fn);
    delete[] Arrays1.R1;
    delete[] Arrays1.R2;
    return f1;
}
//Первый метод распределения
double func_distr(res2 Arrays2)
{
    for (int i = 0; i < Arrays2.n; i++)
    {
        Arrays2.R1clone1[i] = Arrays2.R1[i] * pow(2, i);
        Arrays2.R2clone1[i] = Arrays2.R2[i] * pow(2, i);
    }
    return 0;
}
//Второй метод распределения
double func_loss(res2 Arrays2)
{
    for (int i = 0; i < Arrays2.n; i++)
    {
        Arrays2.R1clone2[i] = Arrays2.R1[i] * pow(2, (Arrays2.R1[i] - Arrays2.R2[i]));
        Arrays2.R2clone2[i] = Arrays2.R2[i] * pow(2, (Arrays2.R2[i] - Arrays2.R1[i]));
    }
    return 0;
}

//Расстояние между результатами после использования первого распределения
double dist_f(struct res2 Arrays2)
{
    double distf = 0;
    for (int i = 0; i < Arrays2.n; i++)
    {
        distf += pow((Arrays2.R2clone1[i] - Arrays2.R1clone1[i]), 2);
    }
    distf = sqrt(distf);
    return distf;
}
//Расстояние между результатами после использования второго распределения
double loss(struct res2 Arrays2)
{
    double loss = 0;
    for (int i = 0; i < Arrays2.n; i++)
    {
        loss += pow((Arrays2.R2clone2[i] - Arrays2.R1clone2[i]), 2);
    }
    loss = sqrt(loss);
    return loss;
}
//Расстояние между результатами после использования первого и второго распределения
void distfloss(struct res2 Arrays2, FILE* file)
{
    double dist1 = 0;
    for (int i = 0; i < Arrays2.n; i++)
    {
        dist1 += pow((Arrays2.R1clone2[i] - Arrays2.R1clone1[i]), 2);
    }
    dist1 = sqrt(dist1);
    double dist2 = 0;
    for (int i = 0; i < Arrays2.n; i++)
    {
        dist2 += pow((Arrays2.R2clone2[i] - Arrays2.R2clone1[i]), 2);
    }
    dist2 = sqrt(dist2);
    printf("dist1 = %lf, dist2 = %lf", dist1, dist2);
    fprintf(file, "dist1 = %lf, dist2 = %lf", dist1, dist2);

    delete[] Arrays2.R1;
    delete[] Arrays2.R2;
    delete[] Arrays2.R1clone1;
    delete[] Arrays2.R2clone1;
    delete[] Arrays2.R1clone2;
    delete[] Arrays2.R2clone2;
}
