/*
                        L2 Algorithmique des arbres
                              Durée 2 heures.
                Notes de cours, de TD et de TP autorisées.

    • Les différentes parties sont indépendantes et peuvent être traitées dans n'importe quel ordre.
    • On veillera à minimiser la complexité des fonctions.
    • On pourra écrire des fonctions annexes, si l'utilisation de paramètres supplémentaires est nécessaire.
    • Le présent sujet est à rendre avec sa copie (voir Exercice 3)
    
*/





/*
    Exercice 1. Arbres binaires
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct noeud{
    int val;
    struct noeud *fg, *fd;
} Noeud, *Arbre;



/*
    1. Écrire une fonction `int nombreFilsUniques(Arbre a)` qui renvoie le nombre de noeuds internes ayant un unique fils.

    2. Écrire une fonction `int estTournoi(Arbre a)` qui renvoie 1 si a est un arbre tournoi et 0 sinon.
        Rappel : Un arbre est dit tournoi lorsque l' étiquette d'un noeud est supérieure ou égale à l'étiquette de son père.

    3. Écrire une fonction `int plusCourte(Arbre a)` qui renvoie la hauteur de la plus courte branche
*/

int nombreFilsUniques(Arbre a){
    if (!a) { return 0; }                   /* la racine est NULL */
    if (!a->fg && !a->fd) { return 0; }     /* deux enfants sont NULL */
    if (a->fg && a->fd) { return 0; }       /* noeud a deux enfants */

    int left = nombreFilsUniques(a->fg);
    int right = nombreFilsUniques(a->fd);

    return left + right + 1;                /* noeud a un unique fils */
}


int estTournoi(Arbre a){
    if (!a) return 1;   /* si la racine est NULL, donc c'est un tournoi */

    if (a->fg){
        /* 
            si fils gauche existe, on vérifie que sa valeur est plus petite
            que la valeur de son père(donc n'est pas tournoi), sinon on vérifie la propriété pour cet enfant
        */
        return (a->fg->val < a->val) ? (0) : (estTournoi(a->fg));
    }
    if (a->fd){
        /* 
            si fils droite existe, on vérifie que sa valeur est plus petite
            que la valeur de son père(donc n'est pas tournoi), sinon on vérifie la propriété pour cet enfant
        */
        return (a->fd->val < a->val) ? (0) : (estTournoi(a->fd));
    }
    return 1;   /* s'il n'y pas d'enfant, donc c'est un tournoi */
}



/*
    normalement c'est la fonction `hauteur()`
    mais cette fonction prend le minimum entre les hauteurs
*/

int plusCourte(Arbre a){
    if (!a) return -1;
    int left = plusCourte(a->fg);
    int right = plusCourte(a->fd);
    return (left < right) ? (left + 1) : (right + 1);
}




/*
Exercice 2. Arbre lexicographique
    On représente un arbre lexicographique à l'aide d'un arbre ternaire de recherche
*/

typedef struct neuLex{
    char lettre;
    struct neuLex *frg, *fils, *frd;
} NoeudT, * ArbreT;


/*
1. Ecrire une fonction int nombreMots(ArbreT a) qui renvoie le nombre de mots mémorisés par l'arbre.

2. Ecrire une fonction int estPrefixe(ArbreT a, char mot[])
    qui renvoie 1 si mot est le préfixe, au sens large, d'un mot mémorisé dans l'arbre
*/



int nombreMots(ArbreT a){
    if (!a) return 0;   /* la racine est NULL, rien à faire */
    int left = nombreMots(a->frg);
    int mid = nombreMots(a->fils);
    int right = nombreMots(a->frd);
    if (a->lettre == '\0'){     /* if (!a->lettre) */
        return left + mid + right + 1;
    }
    return left + mid + right;
}


int estPrefixe(ArbreT a, char mot[]){
    if (*mot == '\0') return 1; /* nous avons trouvé le préfixe d'un mot */
    if (!a) { return 0; }       /* l'arbre est NULL, rien à faire */

    if (a->lettre < *mot){
        /* si la lettre actuelle est plus petite, on doit chercher au sous-arbre droite */
        return estPrefixe(a->frd, mot);
    }
    else if (a->lettre > *mot){
        /* si la lettre actuelle est plus petite, on doit chercher au sous-arbre gauche */
        return estPrefixe(a->frg, mot);
    }

    /* donc on a trouvé la lettre nécessaires pour pouvoir avancer */
    return estPrefixe(a->fils, mot + 1);
}

/*
mot: bon
a: bonjour, bonsoir, bottle, 
                b
                |
                o
                |   
                n_______  
                |       \
                j___    t
                |   \   |
                o   s   t
                |   |   |
                u   o   l
                |   |   |
                r   i   e
                |   |   |
               '\0' r  '\0'
                    |
                   '\0'

Si vous avez besoin plus d'explications, posez vos questions
*/





/*
Exercice 3. Compression de Huffman
On a reçu un fichier compressé par la méthode de Huffman contenant :
    0 1 1
    0 0 0 1 [H] 1 [O] 0 1 [P] 0 1 [!] 1 [A] 0 0 0 1 [D] 1 [E] 0 1 [R] 1 [W] 0 1 [L] 0 1 [Y] 1 [esp]
    0 0 0 1 0 0 1 1 1 0 1 1 0 0 0 1 1 1 1 1 0 0 0 0 1 1 1 0 1 0 1 1 1 0 1 1 1 1 1 0 1 1 0 0 1 1 0 1 0 1 1 0 1 0 0 0 0 1 1 0
    0 0 1

    Ici, esp désigne le caractère espace.
    
    1. Dessiner l'arbre de Huffman associée à ce codage, en expliquant la méthode de construction.
    
    2. Donner le codage utilisé pour chaque lettre dans le tableau ci-dessous :

    Lettre |Codage associé                   Lettre Codage associé
    !      |                                 L                      
    espace |                                 O                      
    A      |                                 P                      
    D      |                                 R                      
    E      |                                 W                      
    H      |                                 Y                      

3. Décompresser le texte, en expliquant la méthode utilisée.
*/

/*
    1) Trois premiers bits c'est le padding (dans ce cas c'est 3)
    2) Après on construire arbre binaire (tel que les feuilles soient des lettres)
    3) Message codé
    4) padding de 0 à 7 bits inutiles (d'après 1) c'est 3 bits).

1)
                                            *
                                /                         \
                                *                          *
                            /      \                  /        \
                            *       *                *          *
                          /   \   /   \           /      \    /   \
                         H    O   P     *        *        *   L    *
                                      /   \    /   \    /   \    /   \
                                      !    A   D    E   R    W   Y   esp

Je vous invite à vérifier l'arbre obtenue, `*` désigne un noeud interne
                                            les feilles ce sont des lettres


2) Donnons le codage utilisé pour chaque lettre dans le tableau ci-dessous
    Lettre |Codage associé                   Lettre | Codage associé
    !      |     0110                        L      |     110
    espace |     1111                        O      |     001
    A      |     0111                        P      |     010        
    D      |     1000                        R      |     1010       
    E      |     1001                        W      |     1011       
    H      |      000                        Y      |     1110      



Maintenant, décodant le message suivant, d'après le table construit:
0 0 0 1 0 0 1 1 1 0 1 1 0 0 0 1 1 1 1 1 0 0 0 0 1 1 1 0 1 0 1 1 1 0 1 1 1 1 1 0 1 1 0 0 1 1 0 1 0 1 1 0 1 0 0 0 0 1 1 0
     |       |     |     |     |       |     |       |     |       |       |       |     |       |     |       |       |
H        E      L     L     O     esp     H      A       P      Y     esp      W      O      R      L      D       !  

Donc le message décodé est: "HELLO HAPY WORLD!"
*/





/*
Exercice 4. Tas
1. Le tableau suivant représente t-il un tas ?
    2 5 3 11 18 6 16 10 12
    Si oui, dessiner le tas correspondant sous forme d'arbre.
    Si non, faire les échanges nécessaires pour qu'il devienne un tas en dessinant clairement les échanges effectués.
2. Donner le tableau obtenu après la suppression du minimum du tas précédent.
    On donnera tous les échanges intermédiaires nécessaires pour maintenir la structure de tas
    en dessinant les arbres intermédiaires correspondants.

*/


/*
C'est possible de faire ça en papier et évidemment plus rapide.
Je vous donne directement la réponse, si vous avez toujours des questions, posez les! 

1)                2
              /      \
              5       3
            /   \   /   \
           11   18  6   16
          /  \
         10  12
Comme on vois, ce tableau ne représente un tas, car il ne suit pas les réglès démandées

Nous avons une branche qu'on doit changer pour obtenir un tas minimal: c'est 2->5->11->10 (gauche)

Pour obtenir un tas minimal, on doit changer 10 et 11:
                  2
              /      \
              5       3
            /   \   /   \
           10   18  6   16
          /  \
         11  12


2) Maintenant, on va supprimer la racine (valeur minimale)
Vous pouvez dessiner tous les arbres intermédiaires, mais je ne vais écris que les échanges nécessaires:
    - 2 est supprimé, 12 prend sa place.
    - 12 est plus grand que ses enfants, on fait changement de 12 et 3, car 3 est le minimum entre deux enfants
    - 12 est toujours plus grand que ses enfants, on fait changement de 12 et 6, car 6 est le minimum entre deux enfants

Désormais, nous avons un tas minimal:

                  3
              /      \
              5       6
            /   \   /   \
           10   18 12   16
          /
         11

*/




/*
Exercice 5. AVL
    On ajoute successivement dans un arbre vide les valeurs : 7, 3, 2, 4, 1, 6, 5.
    Puis, on supprime 3.

    Dessiner les arbres obtenus après chaque ajout ou suppression, ainsi que les arbres intermédiaires s'il y a rotation.

    Dans ce cas, on indiquera aussi clairement quelle rotation est utilisé et sur quel noeud elle s'applique.

    Pour les suppressions, on fera remonter le plus grand élément inférieur à celui qui est supprimé.

    Si cela n'est pas possible, on fera alors remonter le plus petit élément supérieur.

*/


/*

Je vous donne directement l'arbre obtenu, après tous les ajouts et un autre arbre après la suppression de 3.
Vous pouvez comparer votre arbre obtenu et le mien.


                  3
               /     \
              2       6
            /       /   \
           1       4     7
                    \
                     5

La suppression de 3 et remontons le plus grand de sous-arbre gauche

                  2
               /     \
              1       6
                    /   \
                   4     7
                    \
                     5

C'est clair, qu'on doit faire les rotations, faisons-les

On fait:
    rotation droite (4, 6)

                  2
               /     \
              1       4
                        \
                         6
                        / \
                       5   7
Maintenant on peut faire:
    rotation gauche (2, 4)

                  4
               /     \
              2       6
             /       /  \
            1       5    7

Maintenant, nous avons AVL.

*/


/*
Exercice 6. Ensembles, représentation par tableau des pères
    Pour représenter un ensemble d'arbres, on utilise la structure suivante :
*/

typedef struct {
    int *peres;
    int nbNoeuds;
} Foret;



/*
Les noeuds des arbres seront les entiers 0, 1, 2, . . ., nbNoeuds − 1.
    Aucun de ces entiers ne sera utilisé deux fois.
    Si f est une Foret, f.peres[i] est le numéro du père du noeud i.
    On considère que la racine d'un arbre est son propre père.
    On supposera que la forêt est bien définie;
    On ne cherchera pas à le vérifier.


1. Écrire une fonction int nbArbres(Foret f) qui renvoie le nombre d'arbres présent dans la forêt f.

2. Écrire une fonction int plusGrand(Foret f) qui renvoie le numéro de la racine de
    l'arbre ayant le plus grand nombre de noeuds.
    En cas d'égalité de nombre de noeuds maximum, peu importe quel arbre sera désigné par la fonction plusGrand.
    L'algorithme utilisé devra être explicitement expliqué.
    Il sera de complexité linéaire.

*/



int nbArbres(Foret f){
    int count = 0, i = 0;
    for (i = 0; i < f.nbNoeuds; ++i){
        if (f.peres[i] == i){   /* on considère que la racine d'un arbre est son propre père */
            ++count;
        }
    }
    return count;
}


#define MAX_NOEUDS 1000

int plusGrand(Foret f){
    int max = 0, max_idx = 0, i = 0;
    int indice = 0;

    /* tableau qui compte le nombre de noeuds pour chaque indice */
    int tab[MAX_NOEUDS] = {0};  /* on suppose que MAX_NOEUDS >= F.nbNoeuds */

    for (i = 0; i < f.nbNoeuds; ++i){
        indice = i;
        while (f.peres[indice] != indice){  /* chercher sa racine */
            indice = f.peres[indice];
        }
        tab[indice]++;          /* incrémentation le compteur */
    }

    for (i = 0; i < f.nbNoeuds; ++i){
        if (tab[i] > max){  /* la recherche de plus grand */
            max = tab[i];
            max_idx = i;    /* l'indice de plus grande valeur*/
        }
    }
    return max_idx;
}


/*
    QCM assez simple et similaire à ce qu'on a fait
    Je crois que vous êtes capable de le faire vous même
*/


int main(void){
    return 0;
}

