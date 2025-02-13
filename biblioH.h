#ifndef BIBLIOH
#define BIBLIOH
#include "biblio.h"
#include <stdlib.h>
#include <string.h>

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
void liberer biblio(BiblioH* b);
#endif