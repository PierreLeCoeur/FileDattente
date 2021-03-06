#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int main()
{
    float minserv=0;
    float maxserv=0;

    srand(time(NULL));//Permet d'utiliser des nombres aléatoires
    //Paramètres de la simulation
    int nombreJournee;
    printf("Combien de Journée a simuler ?\n");
    scanf("%d",&nombreJournee);
    // Cas où le nombre de journée n'est pas compatible avec la réalité
    if (nombreJournee <= 0)
    {
        printf ("Erreur, veuillez entrer un entier strictement positif.\n");
        return 0;
    }   
    printf("Que voulez vous comme temps de service maximum (en minutes) ?");
    scanf("%f", &maxserv);
    printf("Que voulez vous comme temps de service minimum (en minutes) ?");
    scanf("%f", &minserv);


    float lambda = 0.2; //valeur par défaut
    printf("Lambda = \n");
    scanf("%f",&lambda);
    printf("%f\n",lambda);    
    //Initialisation de la liste des clients et de la liste contenant les stats de la simulation
    Liste ListeClients;
    ListeClients.tete = (Client *)malloc(sizeof(Client));
    Stats teteStats;
    teteStats.suiv = (Stats *)malloc(sizeof(Stats));
    //On supprime les informations de la simulation précédente
    FILE *fichier;
    fichier = fopen(FICHIER_CLIENTS,"w+");

    //Simulation sur plusieurs jours et sauvegarde de la liste des clients et des statistiques de la simulation
    
    for(int journee = 0; journee<nombreJournee ;journee++)
    {
        nouvelleJournee(lambda,&ListeClients,journee,&teteStats, minserv,maxserv);
        ecritureFichiersClients(ListeClients.tete,journee);       
    }
    ecritureFichiersStats(&teteStats);
    return 0;
}
