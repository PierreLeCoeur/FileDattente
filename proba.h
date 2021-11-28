
typedef struct Client {
float h_arrivee;
float t_attente;
float h_guichet;
float t_service;
float h_sortie;
struct Client *suiv;
} Client;


typedef struct TailleFile {
    int taille;
    struct TailleFile *suiv;
} TailleFile;

typedef struct HeureGuichet{
    float h_guichet;
    struct HeureGuichet *suiv;
} HeureGuichet;

typedef struct HeureArrivee{
    float h_arrivee;
    struct HeureArrivee *suiv;
} HeureArrivee;

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
void nouvelleJournee(int lambda);
void remplissageHGuichet(Client *ClientTete, HeureGuichet *hGuichetTete);
void remplissageHArrivee(Client *ClientTete, HeureArrivee *hArriveeTete);
void affichageListeHeures(HeureGuichet *teteGuichet,HeureArrivee *teteArrivee);
float tailleMoyenneFile(TailleFile *teteTaille, HeureGuichet *teteGuichet, HeureArrivee *teteArrivee);