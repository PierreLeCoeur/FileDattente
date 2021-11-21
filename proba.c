#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "proba.h"

float ecartArrivee (int lbd)
{
    /*
    float U=0;
    srand(time(NULL));
    U=(float)rand();//(float)RAND_MAX;
    */
    float T=20;
    return T;
}

float tempsService (int lbd)
{

   // float U=0;
   // srand(time(NULL));
    //U=(float)rand();//(float)RAND_MAX;

    float T=10;
    return T;
}

void ajouterClient(Client *tete, float tempsEcart, float tempsService)
{
    Client *nouveau;
    nouveau = (Client *)malloc(sizeof(Client));
    Client *courant;
    courant = (Client *)malloc(sizeof(Client));

    while(courant-> suiv != NULL)
    {
        courant = courant->suiv;
    }
    courant->suiv = nouveau;

    nouveau->h_arrivee = courant->h_arrivee + tempsEcart;
    nouveau->t_attente = courant->h_sortie - nouveau->h_arrivee;
    nouveau->h_guichet = courant->h_sortie;
    nouveau->h_sortie = nouveau->h_guichet + tempsService;
    nouveau->t_service = tempsService;
    nouveau->suiv = NULL;
}

void initListe(Client *tete,float tempsEcart,float tempsService)
{
    Client *nouveau;
    nouveau = (Client *)malloc(sizeof(Client));

    tete->suiv = nouveau;
    nouveau->h_arrivee = HEURE_START + tempsEcart;
    nouveau->h_guichet = nouveau->h_arrivee;
    nouveau->t_attente = 0;
    nouveau->t_service = tempsService;
    nouveau->h_sortie = nouveau->h_guichet + tempsService;
    nouveau->suiv = NULL;
}

void affichageListe(Client *tete)
{
    Client *courant = tete;
    printf("ok");
    printf("%f",(courant->suiv)->h_arrivee);
    while(courant->suiv != NULL)
    {
        printf("Heure arrivee :%f\n",courant->h_arrivee);
        courant = courant->suiv;
    }
}

float heureArriveeDernier(Client *tete)
{
    Client *courant = tete;

    while(courant-> suiv != NULL)
    {
        courant = courant->suiv;
    }
    return courant->h_arrivee;
}
