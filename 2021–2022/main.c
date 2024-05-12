/*
    Préparé par MUNAITPASOV M.
    Université Gustave Eiffel

    Pour trouver la question souhaitée, cherchez par [Qn], avec n = {1, ..., 15}
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
[Q1] Lister les éventuels effets secondaires et donner la valeur de l’expression
    sous-jacente à chacune des instructions du morceau de programme suivant.

    int i, j, *p;                           // pas d'effets de bord
    i = 99;                                 // effets de bord, i devient 99
    i = printf("%d\n", i);                  // la valeur de i devient 99
    j = ++i;                                // incrementation de i et affectation à j
    i = j = j + 5;                          // incrementation j de la valeur 5 et affectation à i
    p = (int *) malloc(sizeof(int) * i);    // allocation dynamique de mémoire pour un tableau d'entiers de taille i
    p[j < 8] = 32;                          // écriture de la valeur 32 dans p à l'indice `0 ou 1` si la valeur de j est inférieur à 8
    printf("%d\n", p[0]);                   // affichage de la valeur de p[0] sur stdout (sortie standart)
    p[1] = i == j;                          // écriture de la valeur 1, si i est égale à j et 0 sinon
    free(p);                                // libération de la mémoire
*/


/*
[Q2] En supposant que x est un identificateur de variable de type int *,
    expliquer si l’expression `*(x + 1) = *x + 1`
    est correctement typée. Si c’est le cas donner son type. Justifier les réponses

int *x;
*(x + 1)        // correct! c'est équivalent à x[1], autrement dit l'élément suivant en mémoire

*x + 1          // correct! c'est équivalent à x[0] + 1, donc on effectue l'addition

Donc `*(x + 1) = *x + 1` est correcte! Et son type de retour est `int`.
Pourquoi?

Pour voir on peut avoir un autre variable, on l'appelle `y`.
Donc on peut avoir aussi:

int y = ( *(x + 1) = *x + 1 );

Après l'affectation, en C les variables renvoient sa valeur:

int x, y, z = 0;
x = y = z + 1;

*/

/*
[Q3] En supposant que x est un identificateur de variable de type int * et que f est un identificateur
    de fonction de signature (int **, int *, int) et à type de retour int *,
    expliquer si l’expression: `*f(&x, f(NULL, x, *x), ’a’) + 5` est correctement typée.
    Si c’est le cas, donner son type. Justifier les réponses.

// ce que nous avons d'après l'énoncé
int *x;
int *(*f)(int **, int *, int);

étudions cette expression petit à petit: *f(&x, f(NULL, x, *x), ’a’) + 5

f(NULL, x, *x)                      // correctement typée, (NULL, x, *x) ont comme les types (void *, int *, int)

f(&x, f(NULL, x, *x), ’a’)          // correctement typée, l'expression précédente renvoie int*,
                                    // donc on a: (int **, int *, char) mais `char` devient `int`

*f(&x, f(NULL, x, *x), ’a’) + 5     // correctement typée, on prend la valeur renvoie d'après l'exepression précedente
                                    // on fait le déréférencement et on ajout la valeur 5

le type de cette expression est un entier: `int`

*/


/*
[Q4] En supposant que x est un identificateur de variable de type char *
    et que xx est un identificateur de variable de type char,
    écrire une instruction dans laquelle la sous-expression &x + 1 apparaît
    en tant que valeur droite et la sous-expression xx apparaît en tant que valeur gauche.

char *x;
char xx;

// char = char **
    xx    = &x + 1;

Donc on doit prendre deux fois son adresse:
    char = char
    xx =  *(*(&x + 1));
*/


/*
[Q5] Soit un projet constitué de quatre modules A, B, C et D, et d’un module principal Main.
    Il figure dans ce projet les inclusions suivantes :
    — Main.c inclut A.h et B.h ;
    — A.h inclut B.h, C.h et D.h ;
    — B.c inclut D.h ;
    — C.h inclut B.h ;
    — C.c inclut B.h ;
    — D.c inclut C.h.
    Tracer le graphe d’inclusions (étendues) du projet.

Il suffit de regarder CM3-CM4, c'est simple


[Q6] Expliquer si le projet considéré en [Q5] contient une ou plusieurs incohérences.
    Pour chacune d’elle, expliquer s’il s’agit d’un défaut majeur
    (impliquant que le projet n’est pas accepté à la compilation).

Il suffit de regarder CM3
*/


/*
[Q7] (TT) Écrire, pour le projet considéré en [Q5],
    un fichier Makefile simple.

$(CC) = gcc
$(CFLAGS) = -std=c17
$(OBJ) = main.o A.o B.o C.o D.o

main : $(OBJ)
    $(CC) -o $@ $^ $(CFLAGS)

main.o : main.c A.h B.h

A.o : A.c A.h B.h C.h D.h

B.o : B.c B.h

C.o : C.c C.h B.h

D.o : D.c D.h

%.o : %.c
    $(CC) -c -o $@ $< $(CFLAGS)

*/



/*
[Q8] Déclarer un type structuré Bulletin permettant de représenter un bulletin de notes. Il s’agit
    donc de représenter une collection de notes, avec comme informations pour chacune d’elle sur
    combien elle est définie, son coefficient et le nom de l’épreuve. Par exemple, il doit être possible de
    spécifier un bulletin contenant une note de 3 sur 5 à coefficient 4 en "cryptozoologie", de 8.25 sur
    10 à coefficient 1 en "cryptanalyse" et de 20 sur 20 à coefficient 0.01 en "cryptogénétique".

*/

/*
    soit on fait avec une constante,
    soit on fait allocation dynamiquement si on ne sait pas
    combien de matieres contient un bulletin
*/

#define MAX_MATIERES 15
typedef struct matiere {
    char nom_matiere[50];   // 50 caractères suffit pour présenter n'importe quelle matière
    float note;             // on peut avoir double, mais sinon la présicion de float suffit.
    float coeff;
} Matiere;

typedef struct bulletin {
    Matiere matieres[MAX_MATIERES];  // une liste de matières
} Bulletin;




/*
[Q9] Déclarer un type Carte permettant de représenter une carte d’un jeu de 52 cartes.
    On rappelle qu’une telle carte possède une couleur (pique, trèfle, cœur, carreau)
    et une valeur (as, deux, trois, ... , dix, valet, dame, roi).
*/

/* Pour simplifier la vie, on d*/
typedef enum couleur{
    PIQUE, TREFLE, COEUR, CARREAU
} Couleur;

typedef enum valeur {
    DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUITE, NEUF, DIX, VALET, DAME, ROI, AS
} Valeur;

/*
    Je ne fais pas typedef pour Couleur ou Valeur
    pour que le programmeur comprend bien que c'est un `enum`
    sinon, (enum couleur == Couleur) et (enum valeur == Valeur) ils sont équivalents
*/
typedef struct carte{
    enum couleur couleur_carte;
    enum valeur valeur_carte;
} Carte;

/*
[Q10] Définir une fonction dernier_indice_pair_valeur paramétrée par un tableau tab d’entiers
    et un entier x et qui renseigne sur le plus grand indice pair d’apparition de x dans tab.
*/

/*
                indices:  0  1   2    3    4   5  6    7      8    9  10  11  12
    supposons que tab = { 0, 2, 521, 232, 231, x, x, -313, 323341, 0, x, 33, 202};
    donc on doit renvoyer l'indice 10
*/
int dernier_indice_pair_valeur(int tab[], int taille, int x){
    int indice = -1;
    int i = taille - 1;

    for (i = taille - 1; i >= 0; --i){
        if (tab[i] == x && !(i % 2) ){
            indice = i;
            break;
        }
    }
    return indice;
}



/*
[Q11] (TT) Écrire une fonction allouer_profil paramétrée par un tableau tab d’entiers positifs et
    qui produit un nouveau tableau à deux dimensions d’entiers.
    Ce tableau possède la même longueur que celle de tab.
    Pour tout indice i valide, la case d’indice i du tableau renvoyé
    est un tableau d’entiers de longueur tab[i] + 1.
    Toutes les cases du tableau renvoyé doivent contenir la valeur 0.
*/

int **allouer_profil(int tab[], int taille){
    int **new_tab = NULL;
    int i = 0, j = 0;
    int longueur = 0;

    if ( !(new_tab = malloc(sizeof(*new_tab) * taille)) ){  /* sizeof(*new_tab) == sizeof(int *) */
        fprintf(stderr, "Pas assez de mémoire\n");
        return NULL;
    }

    /* on va utiliser calloc pour initialiser toutes les valeurs à 0 */
    for (i = 0; i < taille; ++i){
        longueur = tab[i] + 1;
        new_tab[i] = calloc(longueur, sizeof(*new_tab[i]));    /* sizeof(*new_tab[i]) == sizeof(int) */
        /* liberer toute la memoire allouee
            si au moins une fois, l'allocation est ratée */
        if (!new_tab[i]){
            fprintf(stderr, "Allocation du tableau est ratée!\n");
            for (j = 0; j < i; ++j){ free(new_tab[j]); }
            free(new_tab);
            return NULL;
        }
    }
    return new_tab;
}


/*
[Q12] Écrire une fonction nb_101 paramétrée par un nombre de 64 bits et qui renvoie le nombre
    de fois que l’on peut rencontrer un bit à 1 suivi d’un 0, lui-même suivi d’un 1. Par exemple, la fonction
    appelée avec le nombre 11011101010...0 renvoie 3 à cause des trois occurrences 11011101010...0,
    11011101010...0 et 11011101010...0 du motif 101.

*/

typedef unsigned long long ull;

int nb_101(ull n){
    int count = 0;
    while (n > 0){
        if (n & 5){     /* car 5 en binaire: 101 */
            ++count;
        }
        n >>= 1;
    }
    return count;
}



/*
[Q13] Écrire une fonction hamming paramétrée par deux nombres de 64 bits et qui renvoie le
    nombre de leurs bits qui sont différents, position par position.
    Par exemple, la fonction appelée avec les nombres 110010...0 et 011010...0 renvoie 2.
*/


int hamming(ull a, ull b){
    int count = 0;
    ull val = a ^ b;    /* xor ne conserve que les bits différents de a et b */
    while (val > 0){
                        /* on vérifie si le bit poids faible est égale à 1 */
        if (val & 1){   /* donc dans ce `bit`, a et b étaient différents */
            ++count;
        }
        val >>= 1;      /* itération */
    }
    return count;
}



/*
[Q14] (TT) Écrire une fonction lire_valeur à gestion d’erreur paramétrée par deux entiers a et b
    tels que a est inférieur à b. Cette fonction doit lire une valeur sur l’entrée standard.
    Si cette valeur est comprise dans l’intervalle formé par a et b,
    elle la transmet en sortie, sinon elle doit transmettre une erreur.
*/

/* On suppose que -1, c'est une erreur */
int lire_valeur(int a, int b){
    /*  c'est complémentaire 
    if (a > b){
        fprintf(stderr, "a doit être inférieur à b\n");
        return -1;
    }
    */
    int valeur = 0;

    printf("Donnez une valeur: \n");
    if (scanf("%9d", &valeur) != 1){    /* pour être sur que c'est un int */
        fprintf(stderr, "Erreur, scanf() n'a pas lu.\n");
        return -1;
    }
    if (a <= valeur && valeur <= b){
        return valeur;
    }
    fprintf(stderr, "Erreur!\n");
    return -1;
}



/*
[Q15] Écrire une fonction test_universel_tab paramétrée par un tableau tab d’entiers et par
    un pointeur sur une fonction f à type de retour int et à un paramètre de type int. La fonction
    test_universel_tab renvoie 1 si pour chaque élément x de tab, la fonction f appelée sur x renvoie
    une valeur non nulle et renvoie 0 dans le cas contraire.
*/


int test_universel_tab(int tab[], int taille, int (*f)(int)){
    int i = 0;
    for (i = 0; i < taille; ++i){
        if ( 0 == f(tab[i]) ){  /* il suffit de vérifier si au moins une fois f() renvoie 0 */
            return 0;
        }
    }    
    return 1;   /* sinon, tout est bon! */
}




/* gcc -o main -std=c17 -ansi main.c */
int main(void){
    return 0;
}


