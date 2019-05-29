#include <stdio.h>
#include <string.h>
#include <stdlib.h> // size_t
#include <math.h>
#include "hist.h"
char *fname = "file.txt";
// imya failu
void InputFromTxtFile() // Zchituvannya histogrammi z txt failu
{
    FILE *file;
	file = fopen(fname,"r+");
    if(file == NULL)
	{
		printf("\nError\n");
		return;
	}
	double var , var_min, var_max;
	if (fscanf(file,"%lf",&var)!=EOF)
    {
        var_min = var_max = var;
        int i = 1;
        while (fscanf(file,"%lf",&var)!=EOF)
        {
            if (var > var_max) var_max = var;
            if (var < var_min) var_min = var;
            i++;
        }
        fclose(file);
        file = fopen(fname,"r+");
        setMin(var_min);
        setMax(var_max);     int j;
    for (j = 0; j <i; j++)
        {
            fscanf(file,"%lf",&var);
            addNumber_1 (var);
        }
    }
	else printf("Empty file.\n");


}


void setMax(double m) // max znach
{
    hist.max_hist = m;
   // hist.frequency[hist.M - 1]++;
}
void setMin(double m) // min znach
{
    hist.min_hist = m;
    //hist.frequency[0]++;
}
void setM(unsigned m) // kilkist stovbtsiv na intervali[min_hist, max_hist]
{
    hist.M = m;
    hist.frequency = (unsigned *)malloc(sizeof (unsigned)*hist.M);
    int i;
    for (i = 0; i < hist.M; i++)
        hist.frequency[i] = 0;
}
void addNumber_1(double x) // dodavannya chisel sho ne vhodyyat v interval [min_hist, max_hist] ne dodayutsya
{
    if (x < hist.max_hist && x >= hist.min_hist)
        {
            int h = (x-hist.min_hist)*hist.M/(hist.max_hist - hist.min_hist);
            hist.frequency[h]++;
        }
    else if (x == hist.max_hist)
        hist.frequency[hist.M-1]++;
}
void addNumber_2(double x) //odavannya chisel sho ne vhodyyat v interval [min_hist, max_hist]  dodayutsya do krainih intervaliv
{
    if (x <hist.max_hist && x >= hist.min_hist)
        {
            int h = (x-hist.min_hist)*hist.M/(hist.max_hist - hist.min_hist);
            hist.frequency[h]++;
        }
    else if (x >= hist.max_hist)
        hist.frequency[hist.M-1]++;
    else if (x<hist.min_hist)
        hist.frequency[0]++;
    else
        hist.frequency[hist.M - 1]++;
}
void addNumber_3(double x)
{
    FILE *file;
    file = fopen(fname,"a");
    fprintf(file," %f",x);
    fclose(file);
    if (x < hist.max_hist && x >= hist.min_hist)
        {
            int h = (x-hist.min_hist)*hist.M/(hist.max_hist - hist.min_hist);
            hist.frequency[h]++;
        }
    else if (x == hist.max_hist)
            hist.frequency[hist.M-1]++;
    else if (x<hist.min_hist || x>hist.max_hist)
    {
        int i;
        for (i = 0; i < hist.M; i++)
        hist.frequency[i]=0;
        InputFromTxtFile();
    }

}

void addbatch_1(double data[], size_t dataSize)
{
    int i;
    for (i = 0; i < dataSize; i++)
        addNumber_1(data[i]);
}
void addbatch_2(double data[], size_t dataSize)
{
    int i;
    for (i = 0; i < dataSize; i++)
        addNumber_2(data[i]);
}
void addbatch_3(double data[], size_t dataSize)
{
    int i;
    for (i = 0; i < dataSize; i++)
        addNumber_3(data[i]);
}

unsigned num() // kilkist el v histogramme
{
    unsigned Num = 0;
    int i;
    for (i = 0; i < hist.M; i++)
        Num += hist.frequency[i];
    return Num;
}
unsigned numHist(unsigned i) // chastota vidpovidnogo stovbchika
{
    return hist.frequency[i];
}

double mean() // Vidnoshennya kilkosti elementiv do kilkosti stovbtsiv
{
    double Num = num();
    return (Num / hist.M);
}
double median() // mediana
{
    unsigned * copy_frequency;
    copy_frequency = (unsigned *)malloc(sizeof (unsigned)*hist.M);
    int i,j;
    for (i = 0; i < hist.M; i++)
        copy_frequency [i] = hist.frequency[i];

    for (i = 0; i < hist.M - 1; i++)
    {
        unsigned index_mn = i;
        for (j = i+1; j < hist.M; j++)
            if (copy_frequency [j] < copy_frequency [index_mn])
        {
            index_mn = j;
        }
        unsigned nm = copy_frequency [i];
        copy_frequency [i] = copy_frequency [index_mn];
        copy_frequency [index_mn] = nm;
    }
    double Mean;
    if (hist.M % 2 == 1)
        Mean = copy_frequency [hist.M / 2];
    else
        Mean = (copy_frequency [hist.M / 2] + copy_frequency [hist.M/2 - 1])*0.5;

    return Mean;
}
double variance() // variatsiya
{
    return (hist.max_hist - hist.min_hist);
}
double dev() // seredne vidhilennya
{
    double Av, Sum, StDev;
    Sum  = 0.0;
    int i;
    for (i = 0; i < hist.M; i++)
        Sum += hist.frequency[i];
   Av = Sum / hist.M;
   StDev = 0.0;
   for (i = 0; i < hist.M; i++)
        StDev += pow(hist.frequency[i] - Av, 2);
    return sqrt(StDev / hist.M);
}
void asymmetry() // assymetriya
 {
    int k = 0, l = 0, i;
    float c = 0;
    for (i=0; i < hist.M; i++)
        {
            if (k==hist.frequency[i])
                 l=1; // perevirka na multimodalnist
            else if (k > hist.frequency[i])
                continue;
            else if (k < hist.frequency[i])
                {
                 k = hist.frequency[i];
                 l = 0;
                 c = i+1; // interval de znahoditsya moda
                 }}
    if (hist.M %2 == 0){
       if (c <= (hist.M / 2) && l==0)
           printf("\nasymmetry to the right");
       else if (c > (hist.M / 2) && l==0)
           printf ("\nasymmetry to the left");
       else if (l!=0)
           printf("\nhistogram is multimodal");}
    else{
       if (c < (hist.M / 2) && l==0)
           printf("\nasymmetry to the right");
       else if (c > (hist.M / 2) && l==0)
           printf ("\nasymmetry to the left");
       else if (c==(hist.M / 2))
           printf("\nsymmetry");
       else if (l!=0)
           printf("\nhistogram is multimodal");}
 }
