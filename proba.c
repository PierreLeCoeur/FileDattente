#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "proba.h"

int tempsdattente (int lbd)
{
    float U=8;
    printf("ok");
    srand(time(NULL));
    U = (float) rand()/ (float)RAND_MAX;
    return U;
    //modif Pierre;
}
