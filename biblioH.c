#include "biblioH.h"

int fonctionClef(char* auteur) {
    int taille=strlen(auteur);
    int tot=0;
    for(int i=0; i<taille;i++) {
        tot+=auteur[i];
    }
    return tot;
}

LivreH* creer_livre(int num,char* titre,char* auteur) {
    LivreH *l=(LivreH *)malloc(sizeof(LivreH));
    assert(l);
    l->num=num;
    l->titre=strdup(titre);
    l->auteur=strdup(auteur);
    l->clef=fonctionClef(l->auteur);
    l->suivant=NULL;
    return l;
}

void liberer_livre(LivreH* l) {
    free(l->titre);
    free(l->auteur);
    free(l);
}

BiblioH* creer_biblio(int m) {
    BiblioH* b=(BiblioH *)malloc(sizeof(BiblioH));
    assert(b);
    b->m=m;
    b->nE=0;
    b->T=(LivreH **)malloc(sizeof(LivreH *)*m);
    return b;
}

void liberer_biblio(BiblioH* b) {
    LivreH *temp, *l;
    for(int i=0; i<b->m; i++) {
        l=b->T[i];
        while(l) {
            temp=l;
            l=l->suivant;
            liberer_livre(temp);
        }
    }
    free(b->T);
    free(b);
}

int fonctionHachage(int cle, int m) {
    double A=(sqrt(5)-1)/2.0;
    int h=(int) (m*(cle*A - (int)(cle*A)));
    return h;
}

void inserer(BiblioH* b,int num,char* titre,char* auteur) {
    LivreH * l=creer_livre(num,titre,auteur);
    int h=fonctionHachage(l->clef,b->m);

    LivreH *tete=b->T[h];
    b->nE++;
    l->suivant=tete;
}

LivreH* rechercher_num(LivreH* l, int num) {
    while(l && l->num!=num) {
        l=l->suivant;
    }
    if(l) {return l;}
    return NULL;
}

LivreH* rechercher_titre(LivreH* l, char *titre) {
    while(l && strcmp(titre,l->titre)==0) {
        l=l->suivant;
    }
    if(l) {return l;}
    return NULL;
}

BiblioH* rechercher_auteur(BiblioH* b, char* auteur){
    BiblioH* r = creer_biblio(1);

    int h=fonctionHachage(fonctionClef(auteur),b->m);
    LivreH* parcours = b->T[h];
    r->T[0]=parcours;
    /*
    while(parcours){
        if(strcmp(parcours->auteur,auteur)==0){
            inserer_en_tete(r, parcours->num, parcours->titre, parcours->auteur);
        }
        parcours = parcours ->suiv;
    }
    */
    return r;
}

BiblioH* supprimer_livre(BiblioH* b, int num,char* titre,char* auteur){
    int h=fonctionHachage(fonctionClef(auteur),b->m);
    LivreH* parcours = b->T[h];
    if(parcours==NULL){
        return b;
    }
    if(parcours->num!=num && strcmp(parcours->titre, titre)==0){
        b->T[h] = parcours->suivant;
        liberer_livre(parcours);
        b->nE--;
        return b;
    }
    while(parcours->suivant!=NULL && parcours->suivant->num!=num && strcmp(parcours->suivant->titre, titre)==0){
        parcours = parcours->suivant;
    }
    if(parcours->suivant){
        LivreH* temp = parcours->suivant;
        parcours->suivant= parcours->suivant->suivant;
        liberer_livre(temp);
        b->nE--;
        return b;
    }
    return b;
}

BiblioH* fusion(BiblioH *b1, BiblioH *b2) {
        
    for(int i=0; i<b2->m;i++) {
        LivreH* l = b2->T[i];
        while(l){
            inserer(b1, l->num, l->titre, l->auteur);
            l = l->suivant;
        }
    }
    liberer_biblio(b2);
    return b1;
}

BiblioH* recherche_multiples(BiblioH *b) {
    BiblioH *bib = creer_biblio(b->m);
    int unique=1;

    for(int i = 0; i<b->m; i++){
        LivreH* l = b->T[i];
        unique=1;
        while(l){
            LivreH *l2=l->suivant;
            while(l2) {
                if(strcmp(l->titre,l2->titre)==0 && strcmp(l->auteur,l2->auteur)==0) {
                    inserer(bib,l2->num,l2->titre,l2->auteur);
                    LivreH *temp=l2;
                    l2=l2->suivant;
                    liberer_livre(temp);
                    unique=0;
                } else {
                    l2=l2->suivant;
                }
            }
            if(unique==0) {
                inserer(bib,l->num,l->titre,l->auteur);
            }
            l=l->suivant;
        }
    }
    
    return bib;
}
