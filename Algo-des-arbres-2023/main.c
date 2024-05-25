/*
    Préparé par MUNAITPASOV M.
    Université Gustave Eiffel

    Pour trouver la question souhaitée, cherchez par Exercice
*/


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
    La fonctionne auxiliaire pour complet()
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

    int left = complet_aux(a->fg, &hauteur_fg);
    int right = complet_aux(a->fd, &hauteur_fd);

    return left && right && hauteur_fd == hauteur_fg;
}





/*
    Exercice 2. QuadTree (6,5 points)
*/

#define MAX 512

typedef struct Qneu{
    unsigned char couleur;
    struct Qneu *fils[4];
} Qnoeud, *Qarbre;

/* On suppose que l'on dispose des fonctions suivantes */

// renvoie l'adresse d'un Qnoeud de couleur `c` dont les quatre enfants sont vides
Qnoeud *alloue_noeud(unsigned char c){

    Qnoeud *new_noeud = malloc(sizeof(*new_noeud));
    if (!new_noeud) {
        fprintf(stderr, "Pas de memoire\n");
        return NULL;
    }

    new_noeud->couleur = c;

    for (int i = 0; i < 4; i++)
        new_noeud->fils[i] = NULL;

    return new_noeud;
}


// renvoie 1, si le carré de côté `taille`
// dont le coin supérieur gauche a pour coordonées (x, y) est unifforme en couleur
// i.e. est formé de pixels de la même couleur, et 0 sinon
int est_monochrome(unsigned char image[][MAX], int x, int y, int taille) {
    unsigned char couleur_reference = image[x][y];

    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < taille; ++j) {
            if (image[x + i][y + j] != couleur_reference) {
                return 0;
            }
        }
    }

    return 1;
}


// qui remplit avec couleur les cases du tableau correspondant au carré de côté `taille`
// dont le coin supérieur gauche a pour coordonées (x,y)
void colorie(unsigned char image[][MAX], int x, int y, int taille, unsigned char couleur){
    for (int i = 0; i < taille; ++i)
        for (int j = 0; j < taille; ++j)
            image[x + i][y + j] = couleur;
}




/*
    // reçoit un arbre quaternaire décrivant une image carrée de taille `MAX`
    // et remplit le tableau `image` avec les couleurs correspondantes
    void arbre_2_img(Qarbre a, unsigned char[][MAX]);


    // reçoit une image et construit un arbre quaternaire la représentant.
    int img_2_arbre(unsigned char image[][MAX], Qarbre *a);

    // L'arbre reçu sera supposé vide au premier appel.
    // L'entier renvoyé indiquera si l'arbre a bien était construit
*/



/*
    à vérifier plus tard
*/
void remplir_image(Qnoeud *noeud, unsigned char image[][MAX], int x, int y, int taille) {
    if (!noeud) return; // rien a faire

    // si le noeud n'a pas d'enfant, remplir le carré avec la couleur
    if ( !noeud->fils[0] && !noeud->fils[1] && !noeud->fils[2] && !noeud->fils[3]) {
        colorie(image, x, y, taille, noeud->couleur);
    }
    else {
        int demiTaille = taille / 2;
        remplir_image(noeud->fils[0], image, x, y, demiTaille);                             // haut-gauche
        remplir_image(noeud->fils[1], image, x, y + demiTaille, demiTaille);                // haut-droite
        remplir_image(noeud->fils[2], image, x + demiTaille, y, demiTaille);                // bas-gauche
        remplir_image(noeud->fils[3], image, x + demiTaille, y + demiTaille, demiTaille);   // bas-droite
    }
}


void arbre_2_img(Qarbre a, unsigned char image[][MAX]){
    if (!a) return;
    remplir_image(a, image, 0, 0, MAX);
}





/*
    à vérifier plus tard
*/
int img_2_arbre_helper(unsigned char image[][MAX], int x, int y, int taille, Qarbre *noeud) {

    if (est_monochrome(image, x, y, taille)) {
        unsigned char couleur = image[x][y];
        if (!(*noeud = alloue_noeud(couleur))) {
            fprintf(stderr, "Pas de memoire pour couleur: %c\n", couleur);
            return 0;
        }
        return 1;
    } else {
        if (!(*noeud = alloue_noeud(0))) {
            fprintf(stderr, "Pas de memoire pour malloc 0\n");
            return 0;
        }
        int demiTaille = taille / 2;
        if (!img_2_arbre_helper(image, x, y, demiTaille, &((*noeud)->fils[0])) ||
            !img_2_arbre_helper(image, x, y + demiTaille, demiTaille, &((*noeud)->fils[1])) ||
            !img_2_arbre_helper(image, x + demiTaille, y, demiTaille, &((*noeud)->fils[2])) ||
            !img_2_arbre_helper(image, x + demiTaille, y + demiTaille, demiTaille, &((*noeud)->fils[3]))) {
            return 0;
        }
        return 1;
    }
}


int img_2_arbre(unsigned char image[][MAX], Qarbre *a){
    return img_2_arbre_helper(image, 0, 0, MAX, a);
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


Je pense qu'ils préfèrent cette version:    
1) Fibonacci F_4 minimal (héréditairement gauche)
              F_4
          /         \
        F_3         F_2
       /   \       /   
      F_2  F_1    F_1  
     /  
   F_1  




2) L'ordre d'insertion des entiesr 1, 2, ..., 7 dans un AVL initialement vide qui
    permet d'obtenir F_4 sans qu'une rotation soit nécessaire pour équilibrer l'arbre.
    Justifiez la réponse.


               5
          /        \
         3           7
       /   \        /
      2     4      6
     /
    1

On doit effectuer l'insertion dans l'ordre suivant:
    5, 3, 7, 2, 4, 6, 1
    Pourquoi?
    Car on fait l'ajout BFS (en largeur), donc si on fait comme ça
    On assure que on effectue l'insertion des noeuds sans rotations



3) Prouver que dans un certain ordre on peut inserer 1 en dernier temps:
D'après la question précédente on obtient l'ordre suivant:

    5, 3, 6, 2, 4, 7, 1
    Vous pouvez remarquer que j'ai fait encore fois l'insertion en largeur



4) l'ordre des d'insertion pour effectuer seulement une rotation gauche:
    (c'est encoire fois l'ajout en largeur, et après faisant ça, vous devriez faire une rotation gauche)
    3, 2, 5, 4, 7, 6, 1

               5
          /        \
         3           7
       /   \        /
      2     4      6
     /
    1




5) l'ordre des d'insertion pour effectuer seulement une rotation droite-gauche

    3, 2, 6, 5, 7, 4, 1

               5
          /        \
         3           6
       /  \           \
      2    4           7
     /
    1                     

Ici, je n'ai pas réussi à faire héréditairement gauche,
Pourtant c'est toujous Fibonacci AVL minimal F_4 (7 noeuds, hauteur 3).

*/

