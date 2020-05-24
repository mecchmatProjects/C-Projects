#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// Задання початкового набору значень
double ** getData(int n) {
  double **f;
  f = new double*[2];
  f[0] = new double[n];
  f[1] = new double[n];
  for (int i = 0; i<n; i++) {
    f[0][i] = (double)i;
    f[1][i] = 8 * (double)i - 3;
    f[1][i] = 8*(double)i - 3 + ((rand()%100)-50)*0.05;
  }
  return f;
}
// Обчислення коефіцієнтів апроксимуючої прямої
void getApprox(double **x, double *a, double *b, int n) {
  double sumx = 0;
  double sumy = 0;
  double sumx2 = 0;
  double sumxy = 0;
  for (int i = 0; i<n; i++) {
    sumx += x[0][i];
    sumy += x[1][i];
    sumx2 += x[0][i] * x[0][i];
    sumxy += x[0][i] * x[1][i];
  }
  *a = (n*sumxy - (sumx*sumy)) / (n*sumx2 - sumx*sumx);
  *b = (sumy - *a*sumx) / n;
  return;
}
int main() {
  double **x, a, b;
  int n;
  system("chcp 1251");
  system("cls");
  printf("Введіть кількість точок: ");
  scanf("%d", &n);
  x = getData(n);
  for (int i = 0; i<n; i++)
    printf("%5.1lf - %7.3lf\n", x[0][i], x[1][i]);
  getApprox(x, &a, &b, n);
  printf("a = %lf\nb = %lf", a, b);
  getchar(); getchar();
  return 0;
}