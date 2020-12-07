#include<iostream>
#include "../Data_Comparison_Falendysh/Header.h"

using namespace std;

int main()
{
    int choice; cout << "Enter 1 for keyboard data or 2 for txt file data: "; cin >> choice;
    if (choice == 1)
    {
        FILE* f = fopen("output.txt", "w");
        res Res = create();
        res1 Res1 = create1();
        res2 Res2 = create2();
        int dis = dist(Res);
        int cor = corr(Res);
        printf("dist = %d \n", dis); fprintf(f, "dist = %d \n", dis);
        printf("corr = %d \n", cor); fprintf(f, "corr = %d \n", cor);
        TP(Res1, f);
        FP(Res1, f);
        FN(Res1, f);
        TN(Res1, f);
        int tpr = TPR(Res1);
        int fpr = FPR(Res1);
        int ppv = PPV(Res1);
        int npv = NPV(Res1);
        int fnr = FNR(Res1);
        int fdr = FDR(Res1);
        int forr = FOR(Res1);
        int acc = ACC(Res1);
        int f1 = F1(Res1);
        printf("TPR = %d \n", tpr); fprintf(f, "TPR = %d \n", tpr);
        printf("FPR = %d \n", fpr); fprintf(f, "FPR = %d \n", fpr);
        printf("PPV = %d \n", ppv); fprintf(f, "PPV = %d \n", ppv);
        printf("NPV = %d \n", npv); fprintf(f, "NPV = %d \n", npv);
        printf("FNR = %d \n", fnr); fprintf(f, "FNR = %d \n", fnr);
        printf("FDR = %d \n", fdr); fprintf(f, "FDR = %d \n", fdr);
        printf("FOR = %d \n", forr); fprintf(f, "FOR = %d \n", forr);
        printf("ACC = %d \n", acc); fprintf(f, "ACC = %d \n", acc);
        printf("F1 = %d \n", f1); fprintf(f, "F1 = %d \n", f1);
        double df = dist_f(Res2);
        double los = loss(Res2);
        printf("%lf \n", df); fprintf(f, "dist_f = %lf \n", df);
        printf("%lf \n", los); fprintf(f, "loss = %lf \n", los);
        distfloss(Res2, f);
        fclose(f);
    }
    else if (choice == 2)
    {
        
        FILE* f = fopen("output.txt", "w");
        struct res Res = data_from_txt();
        struct res1 Res1 = data_from_txt1();
        struct res2 Res2 = data_from_txt2();
        int dis = dist(Res);
        int cor = corr(Res);
        printf("dist = %d \n", dis); fprintf(f, "dist = %d \n", dis);
        printf("corr = %d \n", cor); fprintf(f, "corr = %d \n", cor);
        TP(Res1, f);
        FP(Res1, f);
        FN(Res1, f);
        TN(Res1, f);
        int tpr = TPR(Res1);
        int fpr = FPR(Res1);
        int ppv = PPV(Res1);
        int npv = NPV(Res1);
        int fnr = FNR(Res1);
        int fdr = FDR(Res1);
        int forr = FOR(Res1);
        int acc = ACC(Res1);
        int f1 = F1(Res1);
        printf("TPR = %d \n", tpr); fprintf(f, "TPR = %d \n", tpr);
        printf("FPR = %d \n", fpr); fprintf(f, "FPR = %d \n", fpr);
        printf("PPV = %d \n", ppv); fprintf(f, "PPV = %d \n", ppv);
        printf("NPV = %d \n", npv); fprintf(f, "NPV = %d \n", npv);
        printf("FNR = %d \n", fnr); fprintf(f, "FNR = %d \n", fnr);
        printf("FDR = %d \n", fdr); fprintf(f, "FDR = %d \n", fdr);
        printf("FOR = %d \n", forr); fprintf(f, "FOR = %d \n", forr);
        printf("ACC = %d \n", acc); fprintf(f, "ACC = %d \n", acc);
        printf("F1 = %d \n", f1); fprintf(f, "F1 = %d \n", f1);
        func_distr(Res2);
        func_loss(Res2);
        double df = dist_f(Res2);
        double los = loss(Res2);
        printf("dist_f = %lf \n", df); fprintf(f, "dist_f = %lf \n", df);
        printf("loss = %lf \n", los); fprintf(f, "loss = %lf \n", los);
        distfloss(Res2, f);
        fclose(f);
    }
    else { cout << "Wrong input" << endl; }
    return 0;
}