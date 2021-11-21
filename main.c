#include <stdio.h>
#include <stdlib.h>
#include "proba.h"

int main()
{

    //boucle
    float lambda = 4;
    Liste *ListesClients=NULL ;
    ListesClients->tete = NULL;
    initListe(ListesClients->tete, ecartArrivee(lambda),tempsService(lambda));

    float h_actual=heureArriveeDernier((ListesClients->tete)->suiv);

    //Creation liste clients
    while(h_actual<17*60)
    {
        float t_ecart = ecartArrivee(lambda);
        float t_service = tempsService(lambda);
        if(h_actual+t_ecart<17*60)
        {
        ajouterClient(ListesClients->tete, t_ecart, t_service);
        h_actual = heureArriveeDernier(ListesClients->tete);
        }
        else
            h_actual+=500; //pour sortir de la boucle, client suivant arriverait trop tard
    }
    affichageListe(ListesClients->tete);
    printf("of");
    return 0;

}

void afficherHeure(float temps)
{
    int h = temps/60;
    int min = (int)temps % 60;
    printf("%d heure  %d minutes \n",h,min);
}
