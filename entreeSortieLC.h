#ifndef ENTSORTLC
#define ENTSORTLC
#include "entreeSortieLC.h"
#include "biblioLC.h"

Biblio* charger_n_entrees(char* nomfic, int n);
void enregistrer_biblio(Biblio *b, char* nomfic);
#endif