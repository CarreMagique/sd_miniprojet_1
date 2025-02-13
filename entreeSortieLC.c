#include "entreeSortieLC.h"

Biblio* charger_n_entrees(char* nomfic, int n) {
    FILE *f = fopen(nomfic, "r");
    char buffer[100];
    char titre[40];
    char auteur[40];
    Biblio *b=creer_biblio();
    int num;
    int i=0;
    while(i!=n && fgets(buffer,100,f)) {
        sscanf(buffer, "%d %s %s", &num, titre, auteur);
        inserer_en_tete(b,num,titre,auteur);
        i++;
    }
    fclose(f);

    return b;
}

void enregistrer_biblio(Biblio *b, char* nomfic){
    FILE* f = fopen(nomfic, "w");
    Livre* l = b->L;

    while(l){
        fprintf(f, "%d %s %s\n", l->num, l->titre, l->auteur);
        l = l->suiv;
    }

    fclose(f);
}

void affichage_livre(Livre* l){
    printf("%d %s %s\n", l->num, l->titre, l->auteur);
}

void affichage_biblio(Biblio* b) {
    Livre *l=b->L;
    while(l) {
        affichage_livre(l);
        l=l->suiv;
    }
}
