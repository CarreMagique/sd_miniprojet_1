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
LivreH* creer_livre_h(int num,char* titre,char* auteur);
void liberer_livre_h(LivreH* l);
BiblioH* creer_biblio_h(int m);
void liberer_biblio_h(BiblioH* b);
int fonctionHachage(int cle, int m);
void inserer(BiblioH* b,int num,char* titre,char* auteur);
LivreH* rechercher_num_h(BiblioH* b, int num);
LivreH* rechercher_titre_h(BiblioH* b, char *titre);
BiblioH* rechercher_auteur_h(BiblioH* b, char* auteur);
BiblioH* supprimer_livre_h(BiblioH* b, int num,char* titre,char* auteur);
BiblioH* fusion_h(BiblioH *b1, BiblioH *b2);
BiblioH* recherche_multiples_h(BiblioH *b);
#endif