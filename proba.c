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
    Client *dernier;
    dernier = (Client *)malloc(sizeof(Client));
    dernier = tete;

    while(dernier-> suiv != NULL)
    {
        dernier = dernier->suiv;
    }
    dernier->suiv = nouveau;

    nouveau->h_arrivee = dernier->h_arrivee + tempsEcart;
    if(nouveau->h_arrivee>dernier->h_sortie)
    {
        nouveau->t_attente= 0;
    }
    else
        nouveau->t_attente = dernier->h_sortie - nouveau->h_arrivee;
    nouveau->h_guichet = dernier->h_sortie;
    nouveau->h_sortie = nouveau->h_guichet + tempsService;
    nouveau->t_service = tempsService;
    nouveau->suiv = NULL;
}

void premierClient(Client *tete,float tempsEcart,float tempsService)
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
    printf("%f",(courant->suiv)->h_arrivee);
    while(courant->suiv != NULL)
    {
        printf("Heure arrivee \n");
        afficherHeure(courant->h_arrivee);
        courant = courant->suiv;
    }
}

float heureArriveeDernier(Client *tete)
{
    Client *dernier = tete;

    while(dernier-> suiv != NULL)
    {
        dernier = dernier->suiv;
    }
    return dernier->h_arrivee;
}


void afficherHeure(float temps)
{
    int heures,minutes;
    heures = conversionMinutesHeure(temps,&minutes);
    printf("%d heure(s)  %d minute(s) \n",heures,minutes);
}

int ecritureFichiersClients(Client *tete)
//Boolen; renvoie 0 pour echec d'ouverture, 1 sinon
{
    FILE *fichier;
    fichier = fopen(FICHIER_CLIENTS,"w+");

    if(fichier == NULL)
    {
        printf("echec ouverture fichier");
        return 0;
    }
    else
    {
        Client *courant = tete->suiv;
        int minutes =0;
        conversionMinutesHeure(courant->h_arrivee,&minutes);     
        int compteurClient = 1;  
        while(courant->suiv !=NULL)
        {
            
            fprintf(fichier,"Client n°%d ",compteurClient);
            fprintf(fichier,"heure arrivee: %dh%d ",conversionMinutesHeure(courant->h_arrivee,&minutes),minutes); 
            fprintf(fichier,"temps d'attente %dh%d ",conversionMinutesHeure(courant->t_attente,&minutes),minutes);
            fprintf(fichier,"heure debut service: %dh%d ",conversionMinutesHeure(courant->h_guichet,&minutes),minutes);
            fprintf(fichier,"heure fin service: %dh%d\n",conversionMinutesHeure(courant->h_sortie,&minutes),minutes);
            courant = courant->suiv;
            compteurClient++;
        } 
        fclose(fichier);
        return 1;
    }

}

int conversionMinutesHeure(float heure,int *minutes)
{
    int h = heure/60;
    *minutes = (int)heure % 60;
    return h;
}