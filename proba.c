#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "proba.h"

float TempsEntreArriveeClient(int lambda)
{
    float U = 0;
    srand(time(NULL));
    //On s'assure que U soit dans l'intervalle [O;1[
    int r;
    do
    {
        r = rand();
        U = (float) r/(float)RAND_MAX;
        printf("U = %f\n",U);
        printf("RAND_MAX : %d\nrand() : %d\n",RAND_MAX,r);
    } while (U == 1);
    return U;
}
