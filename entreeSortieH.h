#ifndef ENTSORTH
#define ENTSORTH
#include "biblioH.h"
#include <stdio.h>

BiblioH* charger_n_entrees(char* nomfic, int n);
void affichage_livre(LivreH* l);
void enregistrer_biblio(BiblioH *b, char* nomfic);
void affichage_biblio_h(BiblioH* b);
#endif