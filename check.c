#include "common.h"

DTYPE f1(DTYPE x){
	return x*x;
}


int main(){

DTYPE a =1;
ITYPE b =0;
const UTYPE c=10;

DPoint pts[c];
R1RFunc f = f1;

printf("%lf", f(a));

}
