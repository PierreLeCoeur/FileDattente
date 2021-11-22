
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


#define HEURE_START 510 // en minutes
#define HEURE_END 1050

float ecartArrivee (int lbd);
void ajouterClient(Client *tete, float tempsEcart, float tempsService);
void initListe(Client *tete,float tempsEcart,float tempsService);
void affichageListe(Client *tete);
float tempsService (int lbd);
float heureArriveeDernier(Client *tete);

