/* File  Lines2D_test.c
Realization of tests for Lines2D structure functions
Done by Platonov Denis and Oleksenko Vladisval  (group Statistic)
Email: ... & vlad.oleksenko99@gmail.com
*/
#include "Lines2D.c"

int main()
{
    printf("Enter N: ");
    int N;
    scanf("%d", &N);
    struct Point2D Points[N];
    for (int i=0; i<N; i++)
    {
        double n, m;
        printf("Coord N-kut: ");
        scanf("%lf", &n);
        scanf("%lf", &m);
        Points[i].x=n;
        Points[i].y=m;
    }
    struct Polygone2D pol = {N, Points};
    double res = polygon_square(pol);
    int res_2 = check_convex(pol);
    printf("%f ", res);
    printf("%d ", res_2);
    return 0;
}
