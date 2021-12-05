//Structure pour un client
typedef struct Client {
float h_arrivee;
float t_attente;
float h_guichet;
float t_service;
float h_sortie;
struct Client *suiv;
} Client;

//Structure pour les statistiques, un élément de la liste chainée correspond à une journée
typedef struct Stats{
    float tailleMoy;
    int tailleMax;
    float debit_journalier;
    float tauxNonServis;
    float tempsRep;
    struct Stats *suiv;
} Stats;

typedef struct TailleFile {
    int taille;
    struct TailleFile *suiv;
} TailleFile;

//Ces deux structures nous permettent de voir l'évolution de la taille de la file
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
#define FICHIER_STATS "Statistiques.txt"

//en minutes
#define HEURE_START 510 // 8h30
#define HEURE_END 1050  // 17h30
#define HEURE_FIN_ENTREE 1020 //17h
#define MINSRV 2 // minimum du temps de service
#define MAXSRV 10 // maximum du temps de service
#include <time.h>
#include <math.h>

float ecartArrivee (float lambda);
void ajouterClient(Client *tete, float tempsEcart, float tempsService,float *totale_attente, int *compteurClients, int *compteur_nonServis);
void premierClient(Client *tete,float tempsEcart,float tempsService);
void premiereJournee(float lambda,Liste *ListesClients,int journee, Stats *teteStats);
void affichageListe(Client *tete);
float tempsService ();
float heureArriveeDernier(Client *tete);
void afficherHeure(float temps);
int conversionMinutesHeure(float heure,int *minutes);
int ecritureFichiersClients(Client *tete, int journee);
int ecritureFichiersStats( Stats *teteStats);
void nouvelleJournee(float lambda,Liste *ListesClients,int journee, Stats *teteStats);
void remplissageHGuichet(Client *ClientTete, HeureGuichet *hGuichetTete);
void remplissageHArrivee(Client *ClientTete, HeureArrivee *hArriveeTete);
void affichageListeHeures(HeureGuichet *teteGuichet,HeureArrivee *teteArrivee);
float tailleMoyenneFile(TailleFile *teteTaille, HeureGuichet *teteGuichet, HeureArrivee *teteArrivee);
void initHGuichet(Client *ClientTete, HeureGuichet *hGuichetTete);
void initHArrivee(Client *ClientTete, HeureArrivee *hArriveeTete);
int tailleMax(TailleFile *teteFile);