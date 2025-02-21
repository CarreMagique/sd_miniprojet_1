#include "biblioLC.h"
//Permet de créer le livre, a partir du nom, titre ainsi que de l'auteur
Livre* creer_livre(int num, char* titre, char* auteur){
    Livre* l = malloc(sizeof(Livre));
    assert(l);
    l->num = num;
    //On n'oublie pas de copier le titre et l'auteur qui sont deux chaines de carctères potentiellement désallouées à la fin de l'appel
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    return l;
}

void liberer_livre(Livre* l) {
    //En conséquence, on libère les deux chaines de caractères précédemment allouées par strdup dans creer_livre
    free(l->titre);
    free(l->auteur);
    free(l);
}
//Permet de créer une bibliothèque qui est une liste chaînée de livres
Biblio* creer_biblio(){
    Biblio* b = malloc(sizeof(Biblio));
    //On vérifie par assert que b n'est pas nulle, c'est à dire que l'allocation s'est bien passée
    assert(b);
    //On initialise la tete de liste à NULL
    b->L = NULL;
    return b;
}

void liberer_biblio(Biblio* b) {
    //On crée une variable de parcours L qui sera successivement égale à tous les livres de la bibliothèque (afin de les libérer)
    Livre *l=b->L;
    Livre *temp=l;
    while(l) {
        //Temp sert de variable intermédiaire pour pouvoir libérer l'espace mémoire après être passé au suivant
        temp=l;
        l=l->suiv;
        //On appelle la fonction précédemment définie afin de libérer livre
        liberer_livre(temp);
    }
    //On oublie pas de libérer la structure de donnée bibliothèque en plus des livres
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

Livre* rechercher_titre(Livre* l, char *titre) {
    while(l && strcmp(titre,l->titre)!=0) {
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
/*Nous regardons d'abord si la tete correspond au livre recherche, car elle ne sera pas regardee dans la boucle*/
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
        /*S'il n'est pas unique, alors il faut aussi ajouter l, car il n'est pas compare à lui-meme*/
        if(unique==0) {
            inserer_en_tete(bib,l->num,l->titre,l->auteur);
        }
        l=l->suiv;
    }

    return bib;
}
