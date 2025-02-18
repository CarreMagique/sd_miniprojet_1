#include "entreeSortieH.h"

BiblioH* charger_n_entrees_h(char* nomfic, int n) {
    FILE *f = fopen(nomfic, "r");
    char buffer[100];
    char titre[40];
    char auteur[40];
    BiblioH *b=creer_biblio_h(17);
    int num;
    int i=0;
    while(i!=n && fgets(buffer,100,f)) {
        sscanf(buffer, "%d %s %s", &num, titre, auteur);
        inserer(b,num,titre,auteur);
        i++;
    }
    fclose(f);

    return b;
}

void affichage_livre_h(LivreH* l){
    printf("%d %s %s\n", l->num, l->titre, l->auteur);
}

void enregistrer_biblio_h(BiblioH *b, char* nomfic){
    FILE* f = fopen(nomfic, "w");
    LivreH* l;

    for(int i=0;i<b->m;i++) {
        l=b->T[i];
        while(l){
            fprintf(f, "%d %s %s\n", l->num, l->titre, l->auteur);
            l = l->suivant;
        }
    }

    fclose(f);
}

void affichage_biblio_h(BiblioH* b) {
    LivreH *l;
    for(int i=0; i<b->m; i++) {
        l=b->T[i];
        while(l) {
            affichage_livre_h(l);
            l=l->suivant;
        }
    }
}