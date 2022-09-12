#include <stdio.h>
#include <math.h>

int main()
{
/*
    int x = 2;
    int y = 31;

    int z = x + y;

    printf("z=%d \n", z);

    float x1 = 0.0001f;
    double x2 = 1e-4;
    long double x3 = pow(10,-4);
    // 4.33E5,π,e,√5,ln(100)
    double y1 = 4.33e5;
    double pi1 = M_PI;
    double eee = M_E;
    double e2 = exp(1);
    double s5 = sqrt(5);
    double l2 = log(100);

    printf("%.4f %.4lf %.4Lf\n",x1,x2,x3);
*/
//
//    int a;
//
//    scanf("%d",&a);
//
//    if(a<0 || a>9){
//        printf("a=%d -is not a digit!",a);
//        return 0;
//    }
//
//    printf(" %d-%d-%d\n%d|%d|%d\n%d-%d-%d\n", a,a,a,a,a,a,a,a,a);
//

/*
    double m1,m2,r;

    printf("m1=");
    scanf("%lf",&m1);

    printf("m2=");
    scanf("%lf",&m2);

    printf("r=");
    scanf("%lf",&r);

    long double gamma = 6.673e-11L;

    long double F = gamma * m1 * m2 / (r*r);

    printf("F = %Le, F = %Lf\n", F,F);
  */

  // task 5g
  /*int x = 2;
  int x1 = x * x; //x^2
  int x2 = x1 * x; //x^3
  int x3 = x2 * x2; //x^6
  int x4 = x3 * x3; //x^12
  int x5 = x4 * x2;*/

//
//  double w;
//  printf("Input real x=");
//  scanf("%lf",&w);
//
//  int w1 = (int) w;
//  int w2 = floor(w);
//  int w3 = ceil(w);
//  int w4 = round(w);
//
//
//  printf("%d %d %d %d\n" ,w1,w2,w3,w4);
//

  // y =x^15 -  5 mults

  double x,y;
  scanf("%lf %lf",&x, &y);
  //scanf("%lf",&y);
  printf("%lf %le",(x+y)/2, 2/(1/x + 1/y));


}


