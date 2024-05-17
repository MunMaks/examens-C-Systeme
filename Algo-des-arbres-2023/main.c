#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



/*
    Exercice 1. Arbres binaires (6 points)
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


/*
    La fonctionne auxiliaire
*/
int complet_aux(Arbre a, int *hauteur){
    if (!a) { *hauteur = -1; return 1; }

    int hauteur_fg = 0, hauteur_fd = 0;

    int left = complet_aux(a->fg, &hauteur_fg);
    int right = complet_aux(a->fd, &hauteur_fd);

    *hauteur = (hauteur_fg > hauteur_fd) ? (hauteur_fg + 1) : (hauteur_fd + 1);
    return left && right && deux_enfants(a);
}

/*
    ça fonctionne, j'ai vérifié, mais si vous voulez, vous pouvez tester
*/
int complet(Arbre a){
    if (!a) return 1;

    int hauteur_fg = 0, hauteur_fd = 0;

    int left = complet_aux(a->fg, hauteur_fg);
    int right = complet_aux(a->fd, hauteur_fd);

    return left && right && hauteur_fd == hauteur_fg;
}





/*
    Exercice 2. QuadTree.
*/

#define MAX 512

typedef struct Qneu{
    unsigned char couleur;
    struct Qneu *fils[4];
} Qnoeud, *Qarbre;

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




/*
    // reçoit un arbre quaternaire décrivant une image carrée de taille `MAX`
    // et remplit le tableau `image` avec les couleurs correspondantes
    void arbre_2_img(Qarbre a, unsigned char[][MAX]);


    // reçoit une image et construit un arbre quaternaire la représentant.
    int img_2_arbre(unsigned char image[][MAX], Qarbre *a);

    // L'arbre reçu sera supposé vide au premier appel.
    // L'entier renvoyé indiquera si l'arbre a bien était construit
*/

/* TO DO */
void arbre_2_img(Qarbre a, unsigned char[][MAX]){
    return;
}

int img_2_arbre(unsigned char image[][MAX], Qarbre *a){
    return 0;
}




/*
    Exercice 3. Arbre binaires de recherche (3 points)

    Faire en papier, 3 points gratuis
*/




/*
    Exercice 4: Union-Find (3,5 points)

    la table de pères:

    idx: 0   1   2   3   4   5   6   7   8
    tab: 0   0   0   4   4   3   0   2   5  

On va réaliser:

x = Trouver(7);
y = Trouver(6);
Fusion(x, y);


1)
Le forêt:

        0           4
      / | \         |
     1  2  6        3
        |           |
        7           5
                    |
                    8

2) Le répresentant de 6 c'est 0 et le répresentant de 7 c'est aussi 0, donc on fait rien...
    Le forêt ne soit pas changer:

        0           4
      / | \         |
     1  2  6        3
        |           |
        7           5
                    |
                    8


3) Le rang avant: 2
   Le range après: 2
    Autrement dit, on ne fait rien

        0           4
      / | \         |
     1  2  6        3
        |           |
        7           5
                    |
                    8

4) En utilisant la compression des chemins, on obtient le résultat suivant:


        0           4
     / | | \        |
    1  2 6  7       3
                    |
                    5
                    |
                    8

    la table de pères finale:

    idx: 0   1   2   3   4   5   6   7   8
    tab: 0   0   0   4   4   3   0   0   5  

*/





/*
    Exercice 5: AVL(4 points)

1) L'arbre de Fibonacci F_4:

              F_4
          /         \
        F_3         F_2
       /   \       /   \
      F_2  F_1    F_1  F_0
     /  \
   F_1  F_0


2) L'ordre d'insertion des entiesr 1, 2, ..., 7 dans un AVL initialement vide qui
    permet d'obtenir F_4 sans qu'une rotation soit nécessaire pour équilibrer l'arbre.
    Justifiez la réponse.


               5
          /        \
         3           6
       /   \          \
      2     4          7
     /
    1

On doit effectuer l'insertion dans l'ordre suivant:
    5, 3, 6, 2, 4, 7, 1
    Pourquoi?
    Car on fait l'ajout BFS (en largeur), donc si on fait comme ça
    On assure que on effectue l'insertion des noeuds sans rotations



3) Prouver que dans un certain ordre on peut inserer 1 en dernier temps:
D'après la question précédente on obtient l'ordre suivant:

    5, 3, 6, 2, 4, 7, 1
    Vous pouvez remarquer que j'ai fait encore fois l'insertion en largeur




4) l'ordre des d'insertion pour effectuer seulement une rotation gauche:

    4, 1, 6, 2, 5, 7, 3

               4
            /     \
           1       6
          / \     / \
         2   3   5   7



5) l'ordre des d'insertion pour effectuer seulement une rotation droite-gauche

    4, 2, 5, 1, 3, 7, 6

               4
            /     \
           2       6
          / \     / \
         1   3   5   7


*/
























