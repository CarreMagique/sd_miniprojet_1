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
//Permet de libérer toute une bibliothèque c'est à dire la liste chaïnée et ses éléments
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
//Permet d'insérer en tête
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    Livre* l = creer_livre(num, titre, auteur);
    //On passe l'actuel tete de liste en suivant de l'élément que l'on souhaite ajouter
    l->suiv = b->L;
    b->L = l;
}
//Permet de rechercher un livre ayant un numéro précis
Livre* rechercher_num(Biblio* b, int num) {
    Livre* l=b->L;
    //Schéma classique de fonction recherche dans une liste chaînée
    while(l && l->num!=num) {
        l=l->suiv;
    }
    if(l) {return l;}
    return NULL;
}
//Permet de rechercher un livre avec un titre précis
Livre* rechercher_titre(Livre* l, char *titre) {
    //Schéma classique de fonction recherche dans une liste chaînée
    while(l && strcmp(titre,l->titre)!=0) {
        l=l->suiv;
    }
    if(l) {return l;}
    return NULL;
}
//Permet de rechercher un livre avec un titre précis
Biblio* rechercher_auteur(Biblio* b, char* auteur){
    //Dans ce cas il faut renvoyer une bibliothèque comme le livre n'est pas unique. La bibliothèque contiendra tous les livres de l'auteur recherché
    Biblio* r = creer_biblio();
    Livre* parcours = b->L;
    //Schéma classique de fonction recherche dans une liste chaînée
    while(parcours){
        if(strcmp(parcours->auteur,auteur)==0){
            //On utilise inserer_en_tete pour ajoute le livre trouvé à notre bibliothèque de retour
            inserer_en_tete(r, parcours->num, parcours->titre, parcours->auteur);
        }
        parcours = parcours ->suiv;
    }
    return r;
}
//Pour supprimer le livre on vérifie la correspondance du numéro du titre et de l'auteur 
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
    //Schéma classique d'une fonction du suppression dans une liste chaînée
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
//La fusion de deux listes chainée insère tous les éléments de b2 en tête de ceux de la liste b1
Biblio* fusion(Biblio *b1, Biblio *b2) {
    Livre *l2=b2->L;
    while(l2) {
        inserer_en_tete(b1,l2->num,l2->titre,l2->auteur);
        l2=l2->suiv;
    }
    //On desalloue b2
    liberer_biblio(b2);

    return b1;
}
//Recherche des livres ayant le même titre et même auteur afin de les retourner dans une liste particulière.
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
