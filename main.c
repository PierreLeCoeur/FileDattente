#include <stdio.h>
#include <stdlib.h>
#include "proba.h"

int main()
{
    int nombreJournee;
    printf("Combien de Journée a simuler ?\n");
    scanf("%d",&nombreJournee);
    Liste ListeClients;
    ListeClients.tete = (Client *)malloc(sizeof(Client));
    Stats teteStats;
    teteStats.suiv = (Stats *)malloc(sizeof(Stats));
    float lambda = 4;
    for(int journee = 0; journee<nombreJournee ;journee++)
    {
        nouvelleJournee(lambda,&ListeClients,journee,&teteStats);
        ecritureFichiersClients(ListeClients.tete,journee);       
    }
    ecritureFichiersStats( &teteStats);
    //affichageListe(ListesClients.tete);
    return 0;
}
