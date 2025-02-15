#ifndef ENTSORTLC
#define ENTSORTLC
#include "biblioLC.h"

Biblio* charger_n_entrees(char* nomfic, int n);
void enregistrer_biblio(Biblio *b, char* nomfic);
void affichage_livre(Livre* l);
void affichage_biblio(Biblio* b);
#endif