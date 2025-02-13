#ifndef BIBLIOLC
#define BIBLIOLC
#include "biblioLC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct livre {
    int num;
    char * titre;
    char * auteur;
    struct livre * suiv;
} Livre;

typedef struct _biblio { /* Tete fictive */
    Livre * L; /* Premier element */
} Biblio;

Livre* creer_livre(int num,char* titre,char* auteur);
void liberer_livre(Livre* l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);
#endif