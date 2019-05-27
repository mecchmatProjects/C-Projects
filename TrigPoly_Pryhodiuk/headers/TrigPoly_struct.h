# ifndef _TRIGPOLY_
# define _TRIGPOLY_
#include <stdio.h>
typedef double Dtype;
#define SI sizeof(Dtype)

    typedef struct{
        size_t n; //size of polynome
        double alpha;// starting real number Ц кут
        double * a;// coefficients of sin
        double * b;// coefficients of cos
    }TrigPoly;
# endif
