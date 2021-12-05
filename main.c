#include <stdio.h>
#include <stdlib.h>
#include "proba.h"

int main()
{
    
    srand(time(NULL));//Permet d'utiliser des nombres aléatoires

    //Paramètres de la simulation
    int nombreJournee;
    printf("Combien de Journée a simuler ?\n");
    scanf("%d",&nombreJournee);
    float lambda = 4;
    
    //Initialisation de la liste des clients
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
        nouvelleJournee(lambda,&ListeClients,journee,&teteStats);
        ecritureFichiersClients(ListeClients.tete,journee);       
    }
    ecritureFichiersStats(&teteStats);
    //affichageListe(ListesClients.tete);
    return 0;
}
