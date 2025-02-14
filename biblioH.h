#ifndef BIBLIOH
#define BIBLIOH
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

typedef struct livreh {
    int clef;
    int num;
    char * titre;
    char * auteur;
    struct livreh * suivant ;
} LivreH;

typedef struct table {
    int nE; /*nombre d’elements contenus dans la table de hachage */
    int m; /*taille de la table de hachage */
    LivreH ** T; /*table de hachage avec resolution des collisions par chainage */
} BiblioH;

int fonctionClef(char* auteur);
LivreH* creer_livre(int num,char* titre,char* auteur);
void liberer_livre(LivreH* l);
BiblioH* creer_biblio(int m);
void liberer_biblio(BiblioH* b);
int fonctionHachage(int cle, int m);
void inserer(BiblioH* b,int num,char* titre,char* auteur);
LivreH* rechercher_num(LivreH* l, int num);
BiblioH* rechercher_auteur(BiblioH* b, char* auteur);
BiblioH* supprimer_livre(BiblioH* b, int num,char* titre,char* auteur);
BiblioH* fusion(BiblioH *b1, BiblioH *b2);
BiblioH* recherche_multiples(BiblioH *b);
#endif