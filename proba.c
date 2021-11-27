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
    float T=40;
    return T;
}

float tempsService (int lbd)
{

   // float U=0;
   // srand(time(NULL));
    //U=(float)rand();//(float)RAND_MAX;

    float T=50;
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
    if(nouveau->h_arrivee>dernier->h_sortie)//il n'y a personne quand il arrive
    {
        nouveau->t_attente= 0;
        nouveau->h_guichet = nouveau->h_arrivee;
        nouveau->h_sortie = nouveau->h_guichet + tempsService;
        nouveau->t_service = tempsService;

    }
    else
    {
        if (dernier->h_sortie>HEURE_END)
        {
            nouveau->h_guichet = 0;
            nouveau->t_service = 0;
            nouveau->h_sortie = HEURE_END;
            nouveau->t_attente = HEURE_END - nouveau->h_arrivee;
        }
        else
        {
            nouveau->h_guichet = dernier->h_sortie;
            nouveau->h_sortie = nouveau->h_guichet + tempsService;
            nouveau->t_service = tempsService;
            nouveau->t_attente = dernier->h_sortie - nouveau->h_arrivee;
        }
    }
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
    Client *courant = tete->suiv;
    //printf("%f",(courant->suiv)->h_arrivee);
    while(courant != NULL)
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
        int minutes = 0;
        conversionMinutesHeure(courant->h_arrivee,&minutes);     
        int compteurClient = 1;  
        while(courant !=NULL)
        {
            /*
            fprintf(fichier,"Client n°%d \n",compteurClient);
            fprintf(fichier,"heure arrivee: %f\n",courant->h_arrivee); 
            fprintf(fichier,"temps d'attente %f  \n",courant->t_attente);
            fprintf(fichier,"heure debut service: %f \n",courant->h_guichet);
            fprintf(fichier,"heure fin service: %f \n\n",courant->h_sortie);
            */
            
            fprintf(fichier,"Client n°%d ",compteurClient);
            fprintf(fichier,"heure arrivee: %dh",conversionMinutesHeure(courant->h_arrivee,&minutes));
            fprintf(fichier,"%d \n",minutes); 
            fprintf(fichier,"temps d'attente %dh",conversionMinutesHeure(courant->t_attente,&minutes));
            fprintf(fichier,"%d \n",minutes); 
            fprintf(fichier,"heure debut service: %dh",conversionMinutesHeure(courant->h_guichet,&minutes));
            fprintf(fichier,"%d \n",minutes); 
            fprintf(fichier,"heure fin service: %dh",conversionMinutesHeure(courant->h_sortie,&minutes));
            fprintf(fichier,"%d \n\n",minutes); 
            
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



void nouvelleJournee(int lambda)
{
    Liste ListesClients;
    ListesClients.tete = (Client *)malloc(sizeof(Client));
    premierClient(ListesClients.tete, ecartArrivee(lambda),tempsService(lambda));

    float h_actual=heureArriveeDernier((ListesClients.tete)->suiv);

    //Creation liste clients
    while(h_actual<HEURE_FIN_ENTREE)
    {
        float t_ecart = ecartArrivee(lambda);
        float t_service = tempsService(lambda);
        if(h_actual+t_ecart<HEURE_FIN_ENTREE)
        {
            ajouterClient(ListesClients.tete, t_ecart, t_service);
            h_actual = heureArriveeDernier(ListesClients.tete);
            //printf("%f\n",h_actual);
        }
        else
            break;
    }
    ecritureFichiersClients(ListesClients.tete);
}

/*
void remplissageHGuichet()
    (HeureGuichet *)malloc((sizeof(Client));
    Client *courant= ListesClients.tete;
    
    while (courant != NULL)
    {   
        HeureGuichet *nouveau = (HeureGuichet *)malloc((sizeof(Client));
        HeureGuichet *suivant = (HeureGuichet *)malloc((sizeof(Client));
        nouveau->h_guichet=courant->h_guichet;
        nouveau->suiv = suivant;
        courant = courant->suiv;
    }
}
*/