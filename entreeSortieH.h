#ifndef ENTSORTH
#define ENTSORTH
#include "biblioH.h"
#include <stdio.h>

BiblioH* charger_n_entrees_h(char* nomfic, int n);
void affichage_livre_h(LivreH* l);
void enregistrer_biblio_h(BiblioH *b, char* nomfic);
void affichage_biblio_h(BiblioH* b);
#endif