/*
    Préparé par MUNAITPASOV M.
    Université Gustave Eiffel

    Pour trouver la question souhaitée, cherchez Exercice
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*
    Exercice 1. Arbres binaires
*/

typedef struct _noeud {
    int val;
    struct _noeud *fg, *fd;
} Noeud, *Arbre;


int hauteur(Arbre a){
    if (!a) return -1;
    int left = hauteur(a->fg);
    int right = hauteur(a->fd);
    return (left > right) ? (left + 1) : (right + 1);
}

/* les fonctions prédéfinies */
Noeud *alloue_noeud(int val);
void libere(Arbre a);


int copie_arbre(Arbre *dest, Arbre src){
    if (!src){
        *dest = NULL;
        return 1;
    }
    *dest = alloue_noeud(src->val);
    if (!*dest){
        fprintf(stderr, "Pas de mémoire disponible\n");
        return 0;
    }
    int left = copie_arbre(&(*dest)->fg, src->fg);
    int right = copie_arbre(&(*dest)->fd, src->fd);
    if (!left || !right){
        libere(*dest);
        return 0;
    }
    return left && right;
}

int est_somme(Arbre a){
    if (!a)
        return 1;
    int gauche = est_somme(a->fg);
    int droite = est_somme(a->fd);

    int left_val = (a->fg) ? (a->fg->val) : (0);
    int right_val = (a->fd) ? (a->fd->val) : (0);
    if ((left_val + right_val) != a->val){
        return 0;
    }
    return gauche && droite;
}


/* j'ai beaucoup de question à propos de cette fonction ... */
void etiquette_en_abr(Arbre a, int *min){
    if (!a){
        return;
    }
    
}




/*
    Exercice 2. Fusion d'arbres binaires de recherche

                2               6
    A =        / \       B =   / \
              1   5           4   7
                             /
                            3


1)  A + B:

                2 
               / \
              1   6 
                 / \
                5   7
                 \
                  4
                 /
                3 


    B + A:

                6
               / \
              4   2 
             /   / \
            3   7   5
                 \
                  1

b) Non, ce ne sont pas les ABR, car ces abres ne respectent pas la propriété des ABR:
    sous-arbres gauches doivent être inférieur à la racine (s'ils existent) et
    sous-arbres droites doivent être supérieur à la racine (s'ils existent).

2. Dans cette question, on suppose désormais que A et B sont deux ABR sans doublons
    tels que les étiquettes de A sont strictement plus petites que celle de B.

    a) Démontrer que A + B est un arbre binaire sans doublons.

    Tel que tous les etiquettes de A sont strictement plus petites que celle de B et
    que A et B sont des ABR, nous sommes sûr que A + B est un arbre binaire sans doublons!

    b) En déduire que A + B est un arbre binaire de recherche.

    Tel que la fusion de A et B se passe bien, et que d'après les réglès de fusion connues.
    Les sous-arbres droites de A sont toujours plus petits que les sous-arbres gauches de B.
    De plus, on sait que c'est un arbre binaire sans doublons (question précédente),
    donc on peut en déduire que A + B est un ABR.
*/


void fusion(Arbre *A, Arbre B){
    if (!B){
        return;
    }
    if (!*A){
        /* peut être il faut faire la copie, to do plus tard! */
        *A = B;
        return;
    }

}



/*
    Exercice 3. File de priorités
*/

typedef struct {
    int *arr;
    int taille;
} Pile;

/* qui teste si la pile p est vide */
int est_vide(Pile p);

/* renvoie la valeur au sommet de la pile p */
int consulter(Pile p);

/* retire de la pile p son sommet et le stocke dans *sortant
    renvoie 1 si tout OK, 0 sinon */
int depiler(Pile p, int *sortant);

/* libère l'espace */
void liberer(Pile *p);



/* TO DO 1, 2, 3, 4*/
























int main(int argc, char *argv[]){
    return 0;
}
