float ecartarrivee (int lbd);
typedef struct client {
int h_arrivee;
int t_attente;
int h_guichet;
int t_service;
int h_sortie;
struct Client *suiv;
} Client;
