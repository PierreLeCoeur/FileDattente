float ecartarrivee (int lbd);
typedef struct Client {
int h_arrivee;
int t_attente;
int h_guichet;
int t_service;
int h_sortie;
struct Client *suiv;
} Client;
#define HEURE-START 510 // en minutes
#define HEURE-END 1050


