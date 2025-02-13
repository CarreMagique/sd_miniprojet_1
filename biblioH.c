#include "biblio.h"

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
    l->num=num;
    l->titre=strdup(titre);
    l->auteur=strdup(auteur);
    l->clef=fonctionClef(l->auteur);
    l->suivant=NULL;
}

void liberer_livre(LivreH* l) {
    free(l->titre);
    free(l->auteur);
    free(l);
}

BiblioH* creer_biblio(int m) {
    BiblioH* b=(BiblioH *)malloc(sizeof(BiblioH));
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
    int h=(int) (m*(cle*A - (int)(cle*A)))
    return h;
}

void inserer(BiblioH* b,int num,char* titre,char* auteur) {
    LivreH * l=creer_livre(num,titre,auteur);
    int h=fonctionHachage(l->cle,b->m);

    LivreH *tete=b->T[h];
    b->nE++;
    l->suivant=tete;
}

Livre* rechercher_num(Livre* l, int num) {
    while(l && l->num!=num) {
        l=l->suiv;
    }
    if(l) {return l;}
    return NULL;
}

Livre* rechercher_titre(Livre* l, char *titre) {
    while(l && strcmp(titre,l->titre)==0) {
        l=l->suiv;
    }
    if(l) {return l;}
    return NULL;
}

Biblio* rechercher_auteur(Biblio* b, char* auteur){
    Biblio* r = creer_biblio(1);

    int h=fonctionHachage(fonctionClef(auteur),b->m);
    Livre* parcours = b->T[h];
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

Biblio* supprimer_livre(Biblio* b, int num,char* titre,char* auteur){
    int h=fonctionHachage(fonctionClef(auteur),b->m);
    Livre* parcours = b->T[h];
    if(parcours==NULL){
        return b;
    }
    if(parcours->num!=num && strcmp(parcours->titre, titre)==0){
        b->L = parcours->suiv;
        liberer_livre(parcours);
        b->nE--;
        return b;
    }
    while(parcours->suiv!=NULL && parcours->suiv->num!=num && strcmp(parcours->suiv->titre, titre)==0){
        parcours = parcours->suiv;
    }
    if(parcours->suiv){
        Livre* temp = parcours->suiv;
        parcours->suiv= parcours->suiv->suiv;
        liberer_livre(temp);
        b->nE--;
        return b;
    }
    return b;
}

Biblio* fusion(Biblio *b1, Biblio *b2) {
        
    for(int i=0; i<b2->m;i++) {
        Livre* l = b2->T[i];
        while(l){
            inserer(b1, l->num, l->titre, l->auteur);
            l = l->suivant;
        }
    }
    liberer_biblio(b2);
    return b1;
}

Biblio* recherche_multiples(Biblio *b) {
    Livre *l=b->L;
    Biblio *bib = creer_biblio();
    int unique=1;

    for(int i = 0; i<b->m; i++){
        Livre* l = b->T[i];
        unique=1;
        while(l){
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
    }
    
    return bib;
}
