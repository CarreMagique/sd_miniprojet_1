#include "biblioH.h"

int fonctionClef(char* auteur) {
    int taille=strlen(auteur);
    int tot=0;
    for(int i=0; i<taille;i++) {
        tot+=auteur[i];
    }
    return tot;
}

LivreH* creer_livre_h(int num,char* titre,char* auteur) {
    LivreH *l=(LivreH *)malloc(sizeof(LivreH));
    assert(l);
    l->num=num;
    l->titre=strdup(titre);
    l->auteur=strdup(auteur);
    l->clef=fonctionClef(l->auteur);
    l->suivant=NULL;
    return l;
}

void liberer_livre_h(LivreH* l) {
    free(l->titre);
    free(l->auteur);
    free(l);
}

BiblioH* creer_biblio_h(int m) {
    BiblioH* b=(BiblioH *)malloc(sizeof(BiblioH));
    assert(b);
    b->m=m;
    b->nE=0;
    b->T=(LivreH **)malloc(sizeof(LivreH *)*b->m);
    for(int i=0; i<b->m; i++) {
        b->T[i]=NULL;
    }
    return b;
}

void liberer_biblio_h(BiblioH* b) {
    LivreH *temp, *l;
    for(int i=0; i<b->m; i++) {
        l=b->T[i];
        while(l) {
            temp=l;
            l=l->suivant;
            liberer_livre_h(temp);
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
    LivreH * l=creer_livre_h(num,titre,auteur);
    int h=fonctionHachage(l->clef,b->m);

    l->suivant=b->T[h];
    b->T[h]=l;
    b->nE++;
}

LivreH* rechercher_num_h(BiblioH* b, int num) {
/*Nous sommes obliges de parcourir toute la table, car nous ne pouvons avoir la cle qu'a partir du nom de l'auteur*/
    for(int i=0; i<b->m;i++) {
        LivreH *l=b->T[i];
        while(l && l->num!=num) {
            l=l->suivant;
        }

        if(l) {
            return l;
        }
    }
    
    return NULL;
}

LivreH* rechercher_titre_h(BiblioH* b, char *titre) {
/*Nous sommes obliges de parcourir toute la table, car nous ne pouvons avoir la cle qu'a partir du nom de l'auteur*/
    for(int i=0; i<b->m;i++) {
        LivreH *l=b->T[i];
        while(l && strcmp(titre,l->titre)!=0) {
            l=l->suivant;
        }

        if(l) {
            return l;
        }
    }
    
    return NULL;
}

BiblioH* rechercher_auteur_h(BiblioH* b, char* auteur){
    BiblioH* r = creer_biblio_h(1);
/*Avec le nom de l'auteur, nous pouvons trouver beaucoup plus rapidemeent l'ensemble de ses livres*/
/*Il faut tout de même vérifier que ces livres ont le bon auteur, car la table ayant une taille limitee peut avoir plusieurs auteur au meme indice*/
    int h=fonctionHachage(fonctionClef(auteur),b->m);
    LivreH* parcours = b->T[h];
    
    while(parcours){
        if(strcmp(parcours->auteur,auteur)==0){
            inserer(r, parcours->num, parcours->titre, parcours->auteur);
        }
        parcours = parcours ->suivant;
    }
    
    return r;
}

BiblioH* supprimer_livre_h(BiblioH* b, int num,char* titre,char* auteur){
/*Nous pouvons rapidement reduire notre recherche a l'indice calcule a partir du nom de l'auteur*/
    int h=fonctionHachage(fonctionClef(auteur),b->m);
    LivreH* parcours = b->T[h];
    if(parcours==NULL){
        return b;
    }
    if(parcours->num!=num && strcmp(parcours->titre, titre)==0){
        b->T[h] = parcours->suivant;
        liberer_livre_h(parcours);
        b->nE--;
        return b;
    }
    while(parcours->suivant!=NULL && parcours->suivant->num!=num && strcmp(parcours->suivant->titre, titre)!=0){
        parcours = parcours->suivant;
    }
    if(parcours->suivant){
        LivreH* temp = parcours->suivant;
        parcours->suivant= parcours->suivant->suivant;
        liberer_livre_h(temp);
        b->nE--;
    }
    return b;
}

BiblioH* fusion_h(BiblioH *b1, BiblioH *b2) {
        
    for(int i=0; i<b2->m;i++) {
        LivreH* l = b2->T[i];
        while(l){
            inserer(b1, l->num, l->titre, l->auteur);
            l = l->suivant;
        }
    }
    liberer_biblio_h(b2);
    return b1;
}

BiblioH* recherche_multiples_h(BiblioH *b) {
    BiblioH *bib = creer_biblio_h(b->m);
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
                    liberer_livre_h(temp);
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
