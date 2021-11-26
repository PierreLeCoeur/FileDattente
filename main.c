#include <stdio.h>
#include <stdlib.h>
#include "proba.h"

int main()
{

    
    float lambda = 4;
    Liste ListesClients;
    ListesClients.tete = (Client *)malloc(sizeof(Client));
    premierClient(ListesClients.tete, ecartArrivee(lambda),tempsService(lambda));

    float h_actual=heureArriveeDernier((ListesClients.tete)->suiv);

    //Creation liste clients
    while(h_actual<HEURE_FIN_ENTREE)
    {
        float t_ecart = ecartArrivee(lambda);
        float t_service = tempsService(lambda);
        if(h_actual+t_ecart<17*60)
        {
            ajouterClient(ListesClients.tete, t_ecart, t_service);
            h_actual = heureArriveeDernier(ListesClients.tete);
        }
        else
            break;
    }
    //affichageListe((&ListesClients)->tete);
    ecritureFichiersClients(ListesClients.tete);
    printf("test\n");
    return 0;

}
