
typedef struct Client {
float h_arrivee;
float t_attente;
float h_guichet;
float t_service;
float h_sortie;
struct Client *suiv;
} Client;

typedef struct{
Client *tete;
}  Liste;

#define FICHIER_CLIENTS "Liste Clients.txt"
//en minutes
#define HEURE_START 510 // 8h30
#define HEURE_END 1050  // 17h30
#define HEURE_FIN_ENTREE 1020 //17h


float ecartArrivee (int lbd);
void ajouterClient(Client *tete, float tempsEcart, float tempsService);
void premierClient(Client *tete,float tempsEcart,float tempsService);
void affichageListe(Client *tete);
float tempsService (int lbd);
float heureArriveeDernier(Client *tete);
void afficherHeure(float temps);
int conversionMinutesHeure(float heure,int *minutes);
int ecritureFichiersClients(Client *tete);