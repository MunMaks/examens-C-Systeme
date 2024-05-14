/*
                        L2 Algorithmique des arbres
                              Durée 2 heures.
                Notes de cours, de TD et de TP autorisées.

    • Les différentes parties sont indépendantes et peuvent être traitées dans n'importe quel ordre.
    • On veillera à minimiser la complexité des fonctions.
    • On pourra écrire des fonctions annexes, si l'utilisation de paramètres supplémentaires est nécessaire.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*
Exercice 1. Arbres binaires. (5 points)

    1. Écrire une fonction int nombre2Enfants(Arbre a) qui renvoie le nombre de noeuds internes
        de l’arbre a ayant exactement deux enfants.

    2. Écrire une fonction int hauteur(Arbre a) qui renvoie la hauteur de l’arbre a.

    3. Écrire une fonction void afficheNiveau(Arbre a,int n) qui affiche les étiquettes des
        noeuds de niveau n de l’arbre a. L’ordre d’affichage est libre.

    4. Écrire une fonction void libere(Arbre * a) libérant l’espace mémoire alloué
        sur le tas pour stocker l’arbre *a.

    5. Écrire une fonction Arbre copieArbre(Arbre a) qui renvoie une copie de l’arbre a.
        On supposera que l’on dispose d’une fonction Noeud * alloueNoeud(int n)
        permettant d’allouer un noeud contenant l’entier n.

On utilise la structure :
*/

typedef struct noeud{
    int val;
    struct noeud *fg, *fd;
} Noeud, *Arbre;


int nombre2Enfants(Arbre a){
    if (!a)
        return 0;
    int left = nombre2Enfants(a->fg);
    int right = nombre2Enfants(a->fd);

    if (a->fg && a->fd){
        return 1;
    }
    return left + right;
}


int hauteur(Arbre a){
    if (!a) return -1;
    int left = hauteur(a->fg);
    int right = hauteur(a->fd);
    return (left < right) ? (right + 1) : (left + 1);
}



void afficheNiveau(Arbre a, int n){
    if (!a) return;

    if ( 0 == n ){
        printf("%d ", a->val);
    }
    afficheNiveau(a->fg, n - 1);
    afficheNiveau(a->fd, n - 1);
}



void libere(Arbre *a){
    if (!*a) return;
    libere(&(*a)->fg);
    libere(&(*a)->fd);
    free(*a);
    *a = NULL;
}

/* on suppose qu'elle existe */
Noeud *alloueNoeud(int n){
    Noeud *new_noeud = malloc(sizeof(*new_noeud));
    if (!new_noeud){
        fprintf(stderr, "Pas de memoire\n");
        return NULL;
    }
    new_noeud->val = n;
    new_noeud->fg = NULL;
    new_noeud->fd = NULL;
    return new_noeud;
}



Arbre copieArbre(Arbre a){
    if (!a) return NULL;
    Noeud *new_arbre = alloueNoeud(a->val);
    new_arbre->fg = copieArbre(a->fg);
    new_arbre->fd = copieArbre(a->fd);
    return new_arbre;
}



/*
Exercice 2. Insertions et suppressions dans différents types d’arbres (6 points)
    Dans tout cet exercice, lors d’une suppression dans un arbre binaire de recherche, on remontera
    lorsqu’il y aura le choix la valeur maximale du sous-arbre de gauche.

    Attention : Les nombres à insérer varient d’une question à l’autre !
    1.  (a) Dessiner l’arbre binaire de recherche obtenu après insertion dans
            un arbre initialement vide des nombres 6, 9, 7, 4, 8, 1, 5, 10, 3 et 2.

        (b) Dessiner chaque arbre binaire de recherche obtenus après suppression des nombres 10, 1, 6 et 9 dans l’arbre précédent

    2. (a) Dessiner les arbres de type AVL obtenus après les ajouts suivants : 6, 4, 2, 7, 8, 5, 3, 1.
        On précisera bien toutes les rotations qui seront effectuées et sur quels noeuds elles sont réalisées ;
        l’arbre sera dessiné avant et après chaque rotation.
*/





/*
Exercice 3. Union-Find (3 points)
    Soit l’ensemble S = {0, 1, 2, 3, 4}.
    En utilisant la fusion par rang et la compression des chemins, dessinez la forêt d’ensembles
        disjoints représentant les ensembles obtenus après chacune des opérations suivantes :
            Union(0,1)
            Union(1,3)
            Union(4,2)
            Union(3,2)
            Union(2,4)

    Pour chaque représentation, on précisera la valeur du rang de chaque arbre et
        on donnera sa représentation sous forme de tableau des pères.

    Remarque : Lors d’une fusion, en cas d’égalité de rang, la nouvelle racine sera choisie comme
                le plus petit des représentants des éléments fusionnés.



    indices:    0   1   2   3   4
      peres:    0   1   2   3   4

    Après Union(0, 1):

    indices:    0   1   2   3   4
      peres:    0   0   2   3   4

    Après Union(1, 3):

    indices:    0   1   2   3   4
      peres:    0   0   2   0   4

    Après Union(4, 2):

    indices:    0   1   2   3   4
      peres:    0   0   2   0   2

    Après Union(3, 2):

    indices:    0   1   2   3   4
      peres:    0   0   0   0   2

    Après Union(2, 4):

    indices:    0   1   2   3   4
      peres:    0   0   0   0   2

*/






/*
Exercice 4. Représentation d’un arbre "fils gauche, frère droit" (4 points)
    On représente un arbre lexicographique à l’aide d’un arbre binaire "fils gauche, frère droit".
    La liste des frères est ordonnée.
*/

typedef struct noeudL {
    char lettre;
    struct noeudL *fg,*frd;
} NoeudL, * ArbreL;


/*
Figure 1 (page 3)
Donner sa représentation "fils gauche, frère droit".

              a
             / 
            b    ->     f    ->    j
          /            /          /
        c -> d -> e   g          k
                     /
                    h -> i


*/


/*
Insérer les mots suivants dans un arbre lexicographique initialement vide.
    mais, on, ile, onde, ma, ils, ilot.

        m
        |
        a
        |
        i
        |
        s
        |
       '\0'

    TO DO
*/





/*
    Écrire une fonction int nombreMots(ArbreL a) qui renvoie le nombre de mots mémorisés dans l’arbre a.
*/


int nombreMots(ArbreL a){
    if (!a) return 0;
    int left = nombreMots(a->fg);
    int right = nombreMots(a->frd);
    if (a->lettre == '\0'){
        return 1;
    }
    return left + right;
}



/*
    Écrire une fonction void affichePrefixe(ArbreL A, char *pref) qui affiche
        les mots mémorisés par l’arbre a qui ont pour préfixe pref.
    Par exemple, avec l’arbre A construit à la question 2., l’appel affichePrefixe(A,"m")
        entraine l’affichage :
            MA
            MAIS
    Alors que l’appel affichePrefixe(A,"n") entrainera l’affichage :
    Pas de mots trouvé !
*/



/*
    Exercice 5. Tas (2 points)
    Dans cet exercice, on considère un tas binaire maximum (i.e. un noeud est plus grand que ses enfants).
    Chacune des réponses aux questions suivantes devra être justifiée, i.e. le résultat affirmé devra être démontré.
    1. Quelle est la complexité de l’ajout d’un élément dans un tas binaire ?
    2. Quelle est la complexité de l’extraction de l’élément maximum du tas ?

    
    1) l'ajout s'effectue en O(hauteur) ou dans ce cas c'est O(log2(N)), avec N - nombre de noeuds

    2) la suppression s'effectue en 0(1), car il faut soustraire la racine
*/


/*
    Exercice 6. AVL (1,5 points)
    1. Quel est le nombre maximum de noeuds d’un arbre AVL de hauteur 6 ?
    2. Quel est le nombre minimum de noeuds d’un arbre AVL de hauteur 6 ?
    Justifiez vos réponses


    1) 2^7 - 1 (c'est un arbre de hauteur 6 parfait, quand chaque noeud a 2 enfants)
    autrement dit c'est:
    2^0 + 2^1 + ... + 2^6 = 1 + 2 + ... + 64


    2) F_6 = F_5 + F_4 (Fibonacci autrement dit, car il faut le minimum de noeud pour chaque hauteur)

    hauteur 0: 1 noeuds
    hauteur 1: 2 noeuds
    hauteur 2: 3 noeuds
    hauteur 3: 5 noeuds
    hauteur 4: 8 noeuds
    hauteur 5: 13 noeuds
    hauteur 6: 21 noeuds

*/



int main(void){
    return 0;
}
