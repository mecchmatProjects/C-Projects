#include "../headers/Data_Comparison_Falendysh.h"

int main()
{
    int choice;
    printf("Enter 1 for keyboard data or 2 for txt file data: ");
    scanf("%d",&choice);
    if (choice == 1)
    {
        FILE *f;
        f = fopen("output.txt","w");
        struct res Res = create();
        struct res1 Res1 = create1();
        struct res2 Res2 = create2();
        int dis = dist(Res); fprintf(f,"dist = %d \n",dist(Res));
        int cor = corr(Res); fprintf(f,"corr = %d \n",corr(Res));
        printf("dist = %d \n", dis);
        printf("corr = %d \n", cor);
        TP(Res1,f);
        FP(Res1,f);
        FN(Res1,f);
        TN(Res1,f);
        int tpr = TPR(Res1);
        int fpr = FPR(Res1);
        int ppv = PPV(Res1);
        int npv = NPV(Res1);
        int fnr = FNR(Res1);
        int fdr = FDR(Res1);
        int forr = FOR(Res1);
        int acc = ACC(Res1);
        int f1 = F1(Res1);
        printf("TPR = %d \n", tpr); fprintf(f,"TPR = %d \n",TPR(Res1));
        printf("FPR = %d \n", fpr); fprintf(f,"FPR = %d \n",FPR(Res1));
        printf("PPV = %d \n", ppv); fprintf(f,"PPV = %d \n",PPV(Res1));
        printf("NPV = %d \n", npv); fprintf(f,"NPV = %d \n",NPV(Res1));
        printf("FNR = %d \n", fnr); fprintf(f,"FNR = %d \n",FNR(Res1));
        printf("FDR = %d \n", fdr); fprintf(f,"FDR = %d \n",FDR(Res1));
        printf("FOR = %d \n", forr); fprintf(f,"FOR = %d \n",FOR(Res1));
        printf("ACC = %d \n", acc); fprintf(f,"ACC = %d \n",ACC(Res1));
        printf("F1 = %d \n", f1); fprintf(f,"F1 = %d \n",F1(Res1));
        double df = dist_f(Res2);
        double los = loss(Res2);
        printf("dist_f = %lf \n", df); fprintf(f,"dist_f = %lf \n",dist_f(Res2));
        printf("loss = %lf \n", los); fprintf(f,"loss = %lf \n",loss(Res2));
        dist_f_loss(Res2,f);
        fclose(f);
    }
    else if (choice == 2)
    {
        FILE *f;
        f = fopen("output.txt","w");
        struct res Res = data_from_txt();
        struct res1 Res1 = data_from_txt1();
        struct res2 Res2 = data_from_txt2();
        int dis = dist(Res); fprintf(f,"dist = %d \n",dist(Res));
        int cor = corr(Res); fprintf(f,"corr = %d \n",corr(Res));
        printf("dist = %d \n", dis);
        printf("corr = %d \n", cor);
        TP(Res1,f);
        FP(Res1,f);
        FN(Res1,f);
        TN(Res1,f);
        int tpr = TPR(Res1); fprintf(f,"TPR = %d \n",TPR(Res1));
        int fpr = FPR(Res1); fprintf(f,"FPR = %d \n",FPR(Res1));
        int ppv = PPV(Res1); fprintf(f,"PPV = %d \n",PPV(Res1));
        int npv = NPV(Res1); fprintf(f,"NPV = %d \n",NPV(Res1));
        int fnr = FNR(Res1); fprintf(f,"FNR = %d \n",FNR(Res1));
        int fdr = FDR(Res1); fprintf(f,"FDR = %d \n",FDR(Res1));
        int forr = FOR(Res1); fprintf(f,"FOR = %d \n",FOR(Res1));
        int acc = ACC(Res1); fprintf(f,"ACC = %d \n",ACC(Res1));
        int f1 = F1(Res1); fprintf(f,"F1 = %d \n",F1(Res1));
        printf("TPR = %d \n", tpr);
        printf("FPR = %d \n", fpr);
        printf("PPV = %d \n", ppv);
        printf("NPV = %d \n", npv);
        printf("FNR = %d \n", fnr);
        printf("FDR = %d \n", fdr);
        printf("FOR = %d \n", forr);
        printf("ACC = %d \n", acc);
        printf("F1 = %d \n", f1);
        func_distr(Res2);
        func_loss(Res2);
        double df = dist_f(Res2); fprintf(f,"dist_f = %lf \n",dist_f(Res2));
        double los = loss(Res2); fprintf(f,"loss = %lf \n",loss(Res2));
        printf("dist_f = %lf \n", df);
        printf("loss = %lf \n", los);
        dist_f_loss(Res2,f);
        fclose(f);
    }
    else { printf("Wrong input \n"); }
    return 0;
}