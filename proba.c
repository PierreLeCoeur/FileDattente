#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "proba.h"
float LoiUnitaire()
{
	float nombre = 0;
	nombre = (float)rand() / (float)RAND_MAX;
	return nombre;
}

float ecartArrivee()
{
	return -logf(1.0 - LoiUnitaire()) / LAMBDA;
}

float tempsService()
{
	return (MINSRV+LoiUnitaire()*(MAXSRV-MINSRV));
}


void ajouterClient(Client *tete, float tempsEcart, float tempsService,float *totale_attente, int *compteurClients, int *compteur_nonServis)
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
        *totale_attente += (nouveau->h_sortie-nouveau->h_arrivee);
        *compteurClients ++;

    }
    else
    {
        if (dernier->h_sortie>HEURE_END)
        {
            nouveau->h_guichet = 0;
            nouveau->t_service = 0;
            nouveau->h_sortie = HEURE_END;
            nouveau->t_attente = HEURE_END - nouveau->h_arrivee;
            *compteur_nonServis ++;
            
        }
        else
        {
            nouveau->h_guichet = dernier->h_sortie;
            nouveau->h_sortie = nouveau->h_guichet + tempsService;
            nouveau->t_service = tempsService;
            nouveau->t_attente = dernier->h_sortie - nouveau->h_arrivee;
            *totale_attente += (nouveau->h_sortie-nouveau->h_arrivee);
            *compteurClients ++;
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

void affichageListeHeures(HeureGuichet *teteGuichet,HeureArrivee *teteArrivee)
{
    HeureGuichet *courantGuichet = teteGuichet->suiv->suiv;
    HeureArrivee *courantArrivee = teteArrivee->suiv->suiv;
    while(courantGuichet != NULL)
    {
        printf("Heure guichet ");
        afficherHeure(courantGuichet->h_guichet);
        courantGuichet = courantGuichet->suiv;
    }
    while(courantArrivee != NULL)
    {
        printf("Heure arrivee ");
        afficherHeure(courantArrivee->h_arrivee);
        courantArrivee = courantArrivee->suiv;
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
int ecritureFichiersStats( Stats *teteStats)
{
    FILE *fichier;
    fichier = fopen(FICHIER_STATS,"a+");
    if(fichier == NULL)
    {
        printf("echec ouverture fichier");
        return 0;
    }
    else
    {
        float tailleMoyTot = 0;
        float nonServisMoy = 0;
        int compteurJournee = 0;
        float tempsRepMoyTot=0;
        int tailleMax=0;
        float debitJournalierTot = 0;
        Stats *courant=teteStats->suiv;
        while (courant->suiv != NULL)
        {
            tailleMoyTot += courant->tailleMoy;
            tempsRepMoyTot += courant->tempsRep;
            debitJournalierTot += courant->debit_journalier;
            nonServisMoy += courant->tauxNonServis;
            compteurJournee ++;

            if (courant->tailleMax>tailleMax)
            {
                tailleMax = courant->tailleMax;
            }
            courant =  courant ->suiv;
        }
        nonServisMoy = nonServisMoy /compteurJournee;
        debitJournalierTot = debitJournalierTot / compteurJournee;
        tailleMoyTot = tailleMoyTot/compteurJournee;
        tempsRepMoyTot = tempsRepMoyTot/compteurJournee;
        fprintf(fichier,"Taille moyenne de la file %f\n",tailleMoyTot);
        fprintf(fichier,"La file d'attente la plus longue faisait %d clients \n",tailleMax);
        fprintf(fichier,"En moyenne, le temps de réponse est de %f minutes \n",tempsRepMoyTot);
        fprintf(fichier,"Le débit journalier est en moyenne de %f clients par jour \n",debitJournalierTot);
        fprintf(fichier,"En moyenne, %f clients ne sont pas servis chaque jour", nonServisMoy);
        return 1;
    }

}
//Boolen; renvoie 0 pour echec d'ouverture, 1 sinon
int ecritureFichiersClients(Client *tete, int journee)
//Boolen; renvoie 0 pour echec d'ouverture, 1 sinon
{
    FILE *fichier;
    fichier = fopen(FICHIER_CLIENTS,"a+");

    if(fichier == NULL)
    {
        printf("echec ouverture fichier");
        return 0;
    }
    else
    {
        fprintf(fichier,"Journée numéro : %d\n", journee+1);
        Client *courant = tete->suiv;
        int minutes = 0;
        conversionMinutesHeure(courant->h_arrivee,&minutes);     
        int compteurClient = 1;  
        while(courant !=NULL)
        {          
            fprintf(fichier,"Client n°%d\n",compteurClient);
            fprintf(fichier,"Heure d'arrivée: %dh",conversionMinutesHeure(courant->h_arrivee,&minutes));
            fprintf(fichier,"%d \n",minutes); 
            fprintf(fichier,"Temps d'attente %dh",conversionMinutesHeure(courant->t_attente,&minutes));
            fprintf(fichier,"%d \n",minutes); 
            fprintf(fichier,"Heure du début de service: %dh",conversionMinutesHeure(courant->h_guichet,&minutes));
            fprintf(fichier,"%d \n",minutes); 
            fprintf(fichier,"Heure de fin de service: %dh",conversionMinutesHeure(courant->h_sortie,&minutes));
            fprintf(fichier,"%d \n\n",minutes); 
            
            courant = courant->suiv;
            compteurClient++;
        } 
        fprintf(fichier,"\n\n-----------------------------------\n\n\n\n");
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



void nouvelleJournee(int lambda,Liste *ListesClients,int journee, Stats *teteStats)
{
    float totale_attente = 0;
    premierClient(ListesClients->tete, ecartArrivee(lambda),tempsService(lambda));

    float h_actual=heureArriveeDernier((ListesClients->tete)->suiv);
    int compteurClients=0;
    int compteur_debit = 1;
    int compteur_nonServis = 0;
    //Creation liste clients
    while(h_actual<HEURE_FIN_ENTREE)
    {
        
        float t_ecart = ecartArrivee(lambda);
        float t_service = tempsService(lambda);
        if(h_actual+t_ecart<HEURE_FIN_ENTREE)
        {
            ajouterClient(ListesClients->tete, t_ecart, t_service,&totale_attente,&compteurClients,&compteur_nonServis);
            h_actual = heureArriveeDernier(ListesClients->tete);
            compteur_debit++;
            
        }
        else
            break;
    }
    HeureGuichet teteGuichet;
    teteGuichet.suiv =(HeureGuichet *)malloc(sizeof(HeureGuichet));
    HeureArrivee teteArrivee;
    teteArrivee.suiv =(HeureArrivee *)malloc(sizeof(HeureArrivee));
    TailleFile teteFile;
    teteFile.suiv = (TailleFile *)malloc(sizeof(TailleFile));
    TailleFile premierClient;
    teteFile.suiv = &premierClient;
    premierClient.taille=0;
    premierClient.suiv=NULL;

    
    remplissageHGuichet(ListesClients->tete,&teteGuichet);
    remplissageHArrivee(ListesClients->tete,&teteArrivee);
    
    Stats *courant = teteStats;
    while(courant->suiv != NULL)
    {
        courant=courant->suiv;
    }
    Stats *nouveauStats = (Stats *)malloc(sizeof(Stats));
    courant->suiv = nouveauStats;
    nouveauStats->suiv=NULL;
    nouveauStats->tailleMoy = tailleMoyenneFile(&teteFile,&teteGuichet,&teteArrivee);
    nouveauStats->tailleMax = tailleMax(&teteFile);
    nouveauStats->debit_journalier=compteur_debit;
    printf("Clients servis : %d\n",compteurClients);
    printf("Clients non servis : %d\n",compteur_nonServis);
    nouveauStats->tempsRep = (0+totale_attente)/(compteurClients+1);//Cas où clients pas servis pas pris en compte
    nouveauStats->tauxNonServis = compteur_nonServis;
}

int tailleMax(TailleFile *teteFile)
{
    int max=0;
    TailleFile *courant = teteFile;
    while(courant != NULL)
    {
        if(courant->taille > max)
            max = courant->taille;
        courant = courant->suiv;
    }
    return max;
}
void initHArrivee(Client *ClientTete, HeureArrivee *hArriveeTete)
{
    HeureArrivee *nouvelleHeureArrivee = (HeureArrivee *)malloc(sizeof(HeureArrivee));
    nouvelleHeureArrivee->h_arrivee = ClientTete->suiv->h_arrivee;
    hArriveeTete->suiv = nouvelleHeureArrivee;
    nouvelleHeureArrivee->suiv = NULL;
}
void initHGuichet(Client *ClientTete, HeureGuichet *hGuichetTete)
{
    HeureGuichet *nouvelleHeureGuichet = (HeureGuichet *)malloc(sizeof(HeureGuichet));
    nouvelleHeureGuichet->h_guichet = ClientTete->suiv->h_guichet;
    hGuichetTete->suiv = nouvelleHeureGuichet;
    nouvelleHeureGuichet->suiv = NULL;
}

void remplissageHGuichet(Client *ClientTete, HeureGuichet *hGuichetTete)
{ 
    
    Client *clientCourant = ClientTete->suiv;
    initHGuichet(ClientTete,hGuichetTete);
    clientCourant = clientCourant->suiv;
    while (clientCourant != NULL)
    {  
        if (clientCourant->h_guichet != 0)
        {
            HeureGuichet *nouvelleHeureGuichet = (HeureGuichet *)malloc(sizeof(HeureGuichet));
            HeureGuichet *derniereHeureGuichet = (HeureGuichet *)malloc(sizeof(HeureGuichet));
            derniereHeureGuichet = hGuichetTete;

            while(derniereHeureGuichet->suiv != NULL)
            {
                derniereHeureGuichet = derniereHeureGuichet->suiv;
            }
            derniereHeureGuichet->suiv = nouvelleHeureGuichet;
            nouvelleHeureGuichet->h_guichet = clientCourant->h_guichet;
            nouvelleHeureGuichet->suiv = NULL;
            clientCourant = clientCourant->suiv;
        }
        else 
        {
            clientCourant = clientCourant->suiv;
        }
    }
}

void remplissageHArrivee(Client *ClientTete, HeureArrivee *hArriveeTete)
{ 
    
    Client *clientCourant = ClientTete->suiv;
    initHArrivee(ClientTete,hArriveeTete);
    clientCourant = clientCourant->suiv;
    while (clientCourant != NULL)
    {  
        
        HeureArrivee *nouvelleHeureArrivee = (HeureArrivee *)malloc(sizeof(HeureArrivee));
        HeureArrivee *derniereHeureArrivee = (HeureArrivee *)malloc(sizeof(HeureArrivee));
        derniereHeureArrivee = hArriveeTete;
        while(derniereHeureArrivee->suiv != NULL)
        {
            derniereHeureArrivee = derniereHeureArrivee->suiv;
        }
        derniereHeureArrivee->suiv = nouvelleHeureArrivee;
        nouvelleHeureArrivee->h_arrivee = clientCourant->h_arrivee;
        
        nouvelleHeureArrivee->suiv = NULL;
        clientCourant = clientCourant->suiv;
    }
}

float tailleMoyenneFile(TailleFile *teteTaille, HeureGuichet *teteGuichet, HeureArrivee *teteArrivee)
{
    HeureGuichet *courantHeureGuichet = teteGuichet->suiv;
    HeureArrivee *courantHeureArrivee = teteArrivee->suiv;
    TailleFile  *courantFile = teteTaille->suiv;
    while(courantHeureArrivee != NULL && courantHeureGuichet != NULL)
    {

        while (courantHeureArrivee!= NULL && courantHeureGuichet != NULL && courantHeureArrivee->h_arrivee < courantHeureGuichet->h_guichet)
        {
            TailleFile *nouveauFile = (TailleFile *)malloc(sizeof(TailleFile));
            courantFile->suiv=nouveauFile;
            nouveauFile->taille = courantFile->taille+1;
            courantFile = nouveauFile;
            nouveauFile->suiv=NULL;
            courantHeureArrivee = courantHeureArrivee->suiv;
        }
        while (courantHeureArrivee!= NULL && courantHeureGuichet != NULL && courantHeureArrivee->h_arrivee > courantHeureGuichet->h_guichet)
        {
            TailleFile *nouveauFile = (TailleFile *)malloc(sizeof(TailleFile));
            courantFile->suiv=nouveauFile;
            nouveauFile->taille = courantFile->taille-1;
            courantFile = nouveauFile;
            nouveauFile->suiv=NULL;
            courantHeureGuichet= courantHeureGuichet->suiv;
        }
        while (courantHeureArrivee!= NULL && courantHeureGuichet != NULL && courantHeureArrivee->h_arrivee == courantHeureGuichet->h_guichet)
        {
            TailleFile *nouveauFile = (TailleFile *)malloc(sizeof(TailleFile));
            courantFile->suiv=nouveauFile;
            nouveauFile->taille = courantFile->taille;
            nouveauFile->suiv=NULL;
            courantFile = nouveauFile;
            courantHeureGuichet= courantHeureGuichet->suiv;
            courantHeureArrivee = courantHeureArrivee->suiv;
        }  
    }
    courantFile = teteTaille->suiv;
    float moyenneFile = 0;
    int compteurChangementFile = 0;
    while(courantFile != NULL)
    {
        moyenneFile = moyenneFile + courantFile->taille;
        compteurChangementFile ++;
        courantFile = courantFile->suiv;
    }
    return moyenneFile/compteurChangementFile;
} 