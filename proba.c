#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "proba.h"

float ecartarrivee (int lbd)
{
    float U=0;
    srand(time(NULL));
    U=(float)rand();//(float)RAND_MAX;
    printf("%d\n", RAND_MAX);
    float T=30;
    return T;
}

void ajouterClient(Client *tete, int tempsEcart)
{
    Client *courant = tete;

    while(courant-> suiv != NULL)
    {
        courant = courant->suiv;
    }
    Client *nouveau;
    nouveau = (Client *)malloc(sizeof(Client));

    courant->suiv = nouveau;
    nouveau->h_arrivee = courant->h_arrivee + tempsEcart;
    nouveau->suiv =NULL;
}

void initListe(Client *tete,int tempsEcart)
{
    Client *nouveau;
    nouveau = (Client *)malloc(sizeof(Client));

    tete->suiv = nouveau;
    nouveau->h_arrivee = HEURE-START + tempsEcart;
    nouveau->suiv = NULL;
}

void affichageListe(Client *tete)
{
    Client *courant = tete;
    while(courant != NULL)
    {
        printf("Heure arrivee :%d\n",courant->h_arrivee);
        courant = courant->suiv;
    }
}
