#include "biblioLC.h"

Livre* creer_livre(int num, char* titre, char* auteur){
    Livre* l = malloc(sizeof(Livre));
    assert(l);
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    return l;
}

void liberer_livre(Livre* l) {
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio* creer_biblio(){
    Biblio* b = malloc(sizeof(Biblio));
    assert(b);
    b->L = NULL;
    return b;
}

void liberer_biblio(Biblio* b) {
    Livre *l=b->L;
    Livre *temp=l;
    while(l) {
        temp=l;
        l=l->suiv;
        liberer_livre(temp);
    }
    free(b);
}

void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    Livre* l = creer_livre(num, titre, auteur);
    l->suiv = b->L;
    b->L = l;
}

Livre* rechercher_num(Biblio* b, int num) {
    Livre* l=b->L;
    while(l && l->num!=num) {
        l=l->suiv;
    }
    if(l) {return l;}
    return NULL;
}

Livre* rechercher_titre(Biblio* b, char *titre) {
    Livre *l=b->L;
    while(l && strcmp(titre,l->titre)==0) {
        l=l->suiv;
    }
    if(l) {return l;}
    return NULL;
}
Biblio* rechercher_auteur(Biblio* b, char* auteur){
    Biblio* r = creer_biblio();
    Livre* parcours = b->L;
    while(parcours){
        if(strcmp(parcours->auteur,auteur)==0){
            inserer_en_tete(r, parcours->num, parcours->titre, parcours->auteur);
        }
        parcours = parcours ->suiv;
    }
    return r;
}

Biblio* supprimer_livre(Biblio* b, int num,char* titre,char* auteur){
    Livre* parcours = b->L;
    if(!parcours){
        return b;
    }
    if(parcours->num!=num && strcmp(parcours->titre, titre)==0 && strcmp(parcours->auteur, auteur) ==0){
        b->L = parcours->suiv;
        liberer_livre(parcours);
        return b;
    }
    while(parcours->suiv!=NULL && parcours->suiv->num!=num && strcmp(parcours->suiv->titre, titre)==0 && strcmp(parcours->suiv->auteur, auteur)){
        parcours = parcours->suiv;
    }
    if(parcours->suiv){
        Livre* temp = parcours->suiv;
        parcours->suiv= parcours->suiv->suiv;
        liberer_livre(temp);
        return b;
    }
    return b;
}

Biblio* fusion(Biblio *b1, Biblio *b2) {
    Livre *l2=b2->L;
    while(l2) {
        inserer_en_tete(b1,l2->num,l2->titre,l2->auteur);
        l2=l2->suiv;
    }
    liberer_biblio(b2);

    return b1;
}

Biblio* recherche_multiples(Biblio *b) {
    Livre *l=b->L;
    Biblio *bib = creer_biblio();
    int unique=1;

    while(l) {
        Livre *l2=l->suiv;
        while(l2) {
            if(strcmp(l->titre,l2->titre)==0 && strcmp(l->auteur,l2->auteur)==0) {
                inserer_en_tete(bib,l2->num,l2->titre,l2->auteur);
                Livre *temp=l2;
                l2=l2->suiv;
                liberer_livre(temp);
                unique=0;
            } else {
                l2=l2->suiv;
            }
        }
        if(unique==0) {
            inserer_en_tete(bib,l->num,l->titre,l->auteur);
        }
        l=l->suiv;
    }

    return bib;
}
