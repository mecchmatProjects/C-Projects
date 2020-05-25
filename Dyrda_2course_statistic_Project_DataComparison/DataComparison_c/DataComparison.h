#include < stdio.h >  
#include < stdlib.h >


int compar()
{
    int c = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if(i == j){
            if(a[i] == b[j]) {
                ++ c;
                break;
            }
            else {
                printf(“Difference %d between array elements:  : %d\n”, i,abs(a[i]-b[j]));
        }
      }
    }
    return c;
}
