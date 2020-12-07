#include "../headers/Data_Comparison_Falendysh.h"

struct res create()
{
    int size;
    printf("Enter arr size: ");
    scanf("%d",&size);
    struct res Arrays;
    Arrays.n = size;
    Arrays.R1 = (int*)malloc(size*sizeof(int));
    Arrays.R2 = (int*)malloc(size*sizeof(int));

    for (int i = 0; i < size; i++)
    {
        printf("R1 elem: %d", i + 1);
        scanf("%d", &Arrays.R1[i]);
    }

    for (int j = 0; j < size; j++)
    {
        printf("R2 elem: %d", j + 1);
        scanf("%d", &Arrays.R2[j]);
    }

    return Arrays;
}


struct res1 create1()
{
    int size1;
    printf("Enter arr size: ");
    scanf("%d", &size1);
    struct res1 Arrays1;
    Arrays1.n = size1;
    Arrays1.R1 = (int*)malloc(size1*sizeof(int));
    Arrays1.R2 = (int*)malloc(size1*sizeof(int));

    for (int i = 0; i < size1; i++)
    {
        printf("R1 elem: %d", i + 1);
        scanf("%d",&Arrays1.R1[i]);
    }

    for (int j = 0; j < size1; j++)
    {
        printf("R2 elem: %d", j + 1);
        scanf("%d",&Arrays1.R2[j]);
    }

    return Arrays1;
}

struct res2 create2()
{
    int size;
    printf("Enter arr size: ");
    scanf("%d",&size);
    struct res2 Arrays2;
    Arrays2.n = size;
    Arrays2.R1 = (double*)malloc(size*sizeof(double));
    Arrays2.R2 = (double*)malloc(size*sizeof(double));

    for (int i = 0; i < size; i++)
    {
        printf("R1 elem: %d", i + 1);
        scanf("%le",&Arrays2.R1[i]);
    }

    for (int j = 0; j < size; j++)
    {
        printf("R2 elem: %d", j + 1);
        scanf("%le",&Arrays2.R2[j]);
    }

    Arrays2.R1clone1 = (double*)malloc((Arrays2.n)*sizeof(double));
    Arrays2.R2clone1 = (double*)malloc((Arrays2.n)*sizeof(double));
    Arrays2.R1clone2 = (double*)malloc((Arrays2.n)*sizeof(double));
    Arrays2.R2clone2 = (double*)malloc((Arrays2.n)*sizeof(double));

    return Arrays2;
}

struct res data_from_txt()
{
    struct res Arrays;
    Arrays.R1 = (int*)malloc(100*sizeof(int));
    Arrays.R2 = (int*)malloc(100*sizeof(int));
    FILE* file = fopen("tests/data.txt", "r");

    if (file==NULL)
    {
        printf ("\ncant open\n");
        exit(0);
    }

    int amount;
    fscanf(file, "%d", &amount);
    Arrays.n = amount;
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%d", &Arrays.R1[i]);
    }
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%d", &Arrays.R2[i]);
    }
    return Arrays;
}

struct res1 data_from_txt1()
{
    struct res1 Arrays1;
    Arrays1.R1 = (int*)malloc(100*sizeof(int));
    Arrays1.R2 = (int*)malloc(100*sizeof(int));
    FILE* file = fopen("tests/data.txt", "r");
    if (file==NULL)
    {
        printf ("\ncant open\n");
        exit(0);
    }
    fseek(file, 19, SEEK_CUR);

    int amount;
    fscanf(file, "%d", &amount);
    Arrays1.n = amount;
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%d", &Arrays1.R1[i]);
    }
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%d", &Arrays1.R2[i]);
    }
    return Arrays1;
}

struct res2 data_from_txt2()
{
    struct res2 Arrays2;
    Arrays2.R1 = (double*)malloc(100*sizeof(double));
    Arrays2.R2 = (double*)malloc(100*sizeof(double));
    FILE* file = fopen("tests/data.txt", "r");
    if (file==NULL)
    {
        printf ("\ncant open\n");
        exit(0);
    }
    fseek(file, 45, SEEK_CUR);

    int amount;
    fscanf(file, "%d", &amount);
    Arrays2.n = amount;
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%lf", &Arrays2.R1[i]);
    }
    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%lf", &Arrays2.R2[i]);
    }
    Arrays2.R1clone1 = (double*)malloc((Arrays2.n)*sizeof(double));
    Arrays2.R2clone1 = (double*)malloc((Arrays2.n)*sizeof(double));
    Arrays2.R1clone2 = (double*)malloc((Arrays2.n)*sizeof(double));
    Arrays2.R2clone2 = (double*)malloc((Arrays2.n)*sizeof(double));
    return Arrays2;
}

int dist(struct res Arrays)
{
    int evkl = 0;
    for (int i = 0; i < Arrays.n; i++)
    {
        evkl += pow((Arrays.R1[i] - Arrays.R2[i]), 2.0);
    }
    evkl = sqrt(evkl);
    return evkl;
}

int corr(struct res Arrays)
{
    double R1Av = 0, R2Av = 0, cov = 0, sx = 0, sy = 0, kcor;
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
    free(Arrays.R1);
    free(Arrays.R2);
    return kcor;
}


void TP(struct res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == TRUE)
        {
            printf("TP is True for element %d \n",i);
            fprintf(file,"TP is True for element %d \n",i);
        }
        else
        {
            printf("TP is False for element %d \n",i);
            fprintf(file,"TP is False for element %d \n",i);
        }
    }
}

void TN(struct res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == FALSE)
        {
            printf("TN is True for element %d \n",i);
            fprintf(file,"TN is True for element %d \n",i);
        }
        else
        {
            printf("TN is False for element %d \n",i);
            fprintf(file,"TN is False for element %d \n",i);
        }
    }
}


void FP(struct res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == TRUE) && (Arrays1.R2[i] == FALSE))
        {
            printf("FP is True for element %d \n",i);
            fprintf(file,"FP is True for element %d \n",i);
        }
        else
        {
            printf("FP is False for element %d \n",i);
            fprintf(file,"FP is False for element %d \n",i);
        }
    }
}


void FN(struct res1 Arrays1, FILE* file)
{
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == FALSE) && (Arrays1.R2[i] == TRUE))
        {
            printf("FN is True for element %d \n",i);
            fprintf(file,"FN is True for element %d \n",i);
        }
        else
        {
            printf("FN is False for element %d \n",i);
            fprintf(file,"FN is False for element %d \n",i);
        }
    }
}

int TPR(struct res1 Arrays1)
{
    int tp = 0, ay = 0, tpr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == TRUE)
        {
            tp++;
        }
        else if (Arrays1.R2[i] == TRUE)
        {
            ay++;
        }
    }
    tpr = tp / ay;
    return tpr;
}

int FPR(struct res1 Arrays1)
{
    int fp = 0, an = 0, fpr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == TRUE) && (Arrays1.R2[i] == FALSE))
        {
            fp++;
        }
        else if (Arrays1.R2[i] == FALSE)
        {
            an++;
        }
    }
    fpr = fp / an;
    return fpr;
}

int ACC(struct res1 Arrays1)
{
    int tp = 0, tn = 0, acc;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == TRUE)
        {
            tp++;
        }
        else if (Arrays1.R1[i] == Arrays1.R2[i] == FALSE)
        {
            tn++;
        }
    }
    acc = (tp + tn) / (Arrays1.n);
    return acc;
}

int PPV(struct res1 Arrays1)
{
    int tp = 0, fp = 0, ppv;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == TRUE)
        {
            tp++;
        }
        else if ((Arrays1.R1[i] == TRUE) && (Arrays1.R2[i] == FALSE))
        {
            fp++;
        }
    }
    ppv = (tp) / (tp + fp);
    return ppv;
}

int NPV(struct res1 Arrays1)
{
    int tn = 0, fn = 0, npv;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == FALSE)
        {
            tn++;
        }
        else if ((Arrays1.R1[i] == FALSE) && (Arrays1.R2[i] == TRUE))
        {
            fn++;
        }
    }
    npv = (tn) / (tn + fn);
    return npv;
}

int FNR(struct res1 Arrays1)
{
    int fn = 0, ay = 0, fnr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if ((Arrays1.R1[i] == FALSE) && (Arrays1.R2[i] == TRUE))
        {
            fn++;
        }
        else if (Arrays1.R2[i] == TRUE)
        {
            ay++;
        }
    }
    fnr = fn / ay;
    return fnr;
}

int FDR(struct res1 Arrays1)
{
    int fp = 0, tp = 0, fdr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == TRUE)
        {
            tp++;
        }
        else if ((Arrays1.R1[i] == TRUE) && (Arrays1.R2[i] == FALSE))
        {
            fp++;
        }
    }
    fdr = (fp) / (fp + tp);
    return fdr;
}

int FOR(struct res1 Arrays1)
{
    int fn = 0, tn = 0, forr;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == FALSE)
        {
            tn++;
        }
        else if ((Arrays1.R1[i] == FALSE) && (Arrays1.R2[i] == TRUE))
        {
            fn++;
        }
    }
    forr = (fn) / (fn + tn);
    return forr;
}

int F1(struct res1 Arrays1)
{
    int fp = 0, tp = 0, fn = 0, f1;
    for (int i = 0; i < Arrays1.n; i++)
    {
        if (Arrays1.R1[i] == Arrays1.R2[i] == TRUE)
        {
            tp++;
        }
        else if ((Arrays1.R1[i] == TRUE) && (Arrays1.R2[i] == FALSE))
        {
            fp++;
        }
        else if ((Arrays1.R1[i] == FALSE) && (Arrays1.R2[i] == TRUE))
        {
            fn++;
        }
    }

    f1 = (2 * tp) / (2 * tp + fp + fn);
    free(Arrays1.R1);
    free(Arrays1.R2);
    return f1;
}

double func_distr(struct res2 Arrays2)
{
    for (int i = 0; i < Arrays2.n; i++)
    {
        Arrays2.R1clone1[i] = Arrays2.R1[i] * pow(2, i);
        Arrays2.R2clone1[i] = Arrays2.R2[i] * pow(2, i);
    }
    return 0;
}

double func_loss(struct res2 Arrays2)
{
    for (int i = 0; i < Arrays2.n; i++)
    {
        Arrays2.R1clone2[i] = Arrays2.R1[i] * pow(2, (Arrays2.R1[i] - Arrays2.R2[i]));
        Arrays2.R2clone2[i] = Arrays2.R2[i] * pow(2, (Arrays2.R2[i] - Arrays2.R1[i]));
    }
    return 0;
}


double dist_f(struct res2 Arrays2)
{
    double distf = 0;
    for (int i = 0; i < Arrays2.n; i++)
    {
        distf += pow((Arrays2.R2clone1[i] - Arrays2.R1clone1[i]),2);
    }
    distf = sqrt(distf);
    return distf;
}

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

void dist_f_loss(struct res2 Arrays2, FILE* file)
{
    double dist1 = 0;
    for (int i = 0; i < Arrays2.n; i++)
    {
        dist1 += pow((Arrays2.R1clone2[i] - Arrays2.R1clone1[i]),2);
    }
    dist1 = sqrt(dist1);
    double dist2 = 0;
    for (int i = 0; i < Arrays2.n; i++)
    {
        dist2 += pow((Arrays2.R2clone2[i] - Arrays2.R2clone1[i]), 2);
    }
    dist2 = sqrt(dist2);
    printf("dist1 = %lf, dist2 = %lf",dist1,dist2);
    fprintf(file,"dist1 = %lf, dist2 = %lf",dist1,dist2);

    free(Arrays2.R1);
    free(Arrays2.R2);
    free(Arrays2.R1clone1);
    free(Arrays2.R2clone1);
    free(Arrays2.R1clone1);
    free(Arrays2.R2clone2);
}