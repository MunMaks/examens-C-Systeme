#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



/*
    Exercice 1. Arbres binaires
*/



typedef struct noeud{
    int val;
    struct noeud *fg, *fd;
} Noeud, *Arbre;


/* déjà fait */
int nb_fils_uniques(Arbre a);
int hauteur(Arbre a);



int egale(Arbre un, Arbre deux){
    if (!un && !deux)   return 1;   /* les deux sont NULL */
    else if (!un || !deux)   return 0;   /* l'un d'entre est NULL*/

    return (egale(un->fg, deux->fg) && egale(un->fd, deux->fd)) &&
            (un->val == deux->val);
}

/*
    soit deux enfants existent, soit il n'y pas d'enfants
*/
int deux_enfants(Arbre a){
    if (!a) {
        return 0;
    }
    else if ((a->fg && a->fd) || (!a->fg && !a->fd) ){
        return 1;
    }
    return 0;
}


int complet(Arbre a){
    if (!a) return 1;
    int fg_et_fd = deux_enfants(a);
    /* on a besoin une fonction externe qui calcule la hauteur, transmets par l'adresse */

    /* à finir plus tard */
    return 1;
}





/*
    Exercice 2. QuadTree.
*/

#define MAX 512

typedef struct Qneu{
    unsigned char couleur;
    struct Qneu *fils[4];
} Qnoeud, *Qarbre;

/*
    void arbre_2_img(Qarbre a, unsigned char[][MAX]);
    int img_2_arbre(unsigned char image[][MAX], Qarbre *a);
*/

/* On suppose que l'on dispose des fonctions suivantes */

// renvoie l'adresse d'un Qnoeud de couleur `c` dont les quatre enfants sont vides
Qnoeud *alloue_noeud(unsigned char);

// renvoie 1, si le carré de côté `taille`
// dont le coin supérieur gauche a pour coordonées (x, y) est unifforme en couleur
// i.e. est formé de pixels de la même couleur, et 0 sinon
int est_monochrome(unsigned char image[][MAX], int x, int y, int taille);

// qui remplit avec couleur les cases du tableau correspondant au carré de côté `taille`
// dont le coin supérieur gauche a pour coordonées (x,y)
void colorie(unsigned char image[][MAX], int x, int y, int taille, unsigned char couleur);




