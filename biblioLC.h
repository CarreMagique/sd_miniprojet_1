#ifndef BIBLIOLC
#define BIBLIOLC
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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
Livre* rechercher_num(Livre* l, int num);
Livre* rechercher_titre(Livre* l, char *titre);
Biblio* rechercher_auteur(Biblio* b, char* auteur);
Biblio* supprimer_livre(Biblio* b, int num,char* titre,char* auteur);
Biblio* fusion(Biblio *b1, Biblio *b2);
Biblio* recherche_multiples(Biblio *b);
#endif