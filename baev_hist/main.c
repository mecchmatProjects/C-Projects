#include <stdio.h>
#include <string.h>
#include <stdlib.h> // size_t
#include <math.h>
#include "hist.h"

 int main()
{

    int i;
    setM(5);
    InputFromTxtFile();
    for (i = 0; i < hist.M; i++)
        printf("%i\t",hist.frequency[i]);
    printf("\n");
    printf ("\nnum = %i",num());
    printf ("\nmean = %f",mean());
    printf ("\nmedian = %f",median());
    printf ("\ndev = %f",dev());
    printf ("\nvariance = %f", variance());
    asymmetry();
  return 0;
}


