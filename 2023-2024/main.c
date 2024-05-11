/*
Q1) Lister les éventuels effets de bords et donner la valeur de l’expression
    sous-jacente à chacune des instructions du morceau de programme suivant:
    1) int a, b, *p;                             // pas d'effets de bords  déclaration de 3 variables: a (entier), b (entier), p (pointeur vers un entier)
    2) a = b = 2;                                // effets de bords,       attribution de la valeur 2 à `b` et puis à `a` 
    3) b = a = b + 1;                            // effets de bords        incrementation de b à 1, puis assignation de la valeur de a à b.
    4) a = a >= 3 ? 1 : a;                       // effets de bords        changement de la valeur de a à 1 si la valeur de a est plus grande que 3, sinon on fait rien 
    5) p = (int *) malloc(sizeof(int) * 64);     // effets de bords        allocation dynamique de mémoire pour un tableau de 64 entiers stocké dans `p`.
    6) p[(a + b) << 1] = 32;                     // effets de bords        attribution la valeur 32 à la variable p à l'indice `(a + b) << 1`
    7) printf("%d\n", p[1 << b]);                // effets de bords        affichage la valeur stocké dans p à l'indice `1 << b` ce qui vaut `8` avec b == 3. (la valeur de p[1 << b] n'est pas définie
    8) free(p);                                  // effets de bords        Libération de la mémoire allouée pour `p`
*/


/*
Q2) En supposant que y est un identificateur de variable de type float *,
    donner le type de l’expression *(&y + 1)- 1. Justifier la réponse.

float *y;
*(&y + 1) - 1;

Regardons cet exemple:
&y                                  le type `float **`
(&y + 1) la case suivant avec       le type `float **`
*(&y + 1) déréférencer ce pointeur, le type `float *` 
*(&y + 1) - 1; case précédente de   le type `float *` 
*/


/*
Q3) En supposant que x est un identificateur de variable de type int** et y un identificateur de
    variable de type int, écrire une instruction dans laquelle la sous-expression y apparaît en tant que
    valeur droite et la sous-expression *(x + 1) en tant que valeur gauche.

lvalue = rvalue;
`int *` = `int *` donc c'est bon
*(x + 1) = &y;
*/


/*
[Q4] En supposant que f est un identificateur de fonction à type de retour char* et de signature
    (int, char*), dire si l’expression *f(f(16, NULL)[2], "1000")- ’8’ est correctement typée. Si
    c’est le cas, donner son type. Justifier les réponses

char *(*f)(int, char *);
Examinons l'example suivant:
*f(f(16, NULL)[2], "1000")- ’8’

f(16, NULL)                        // c'est correct, 16 est bien un int et NULL c'est (void *) devient (char *)
f(16, NULL)[2]                     // c'est correct, `f` renvoie char *, donc [2] nous dit de prendre la valeur à l'indice 2 (char, mais devient int)
f(f(16, NULL)[2], "1000")          // c'est correct, après l'expression précédente, f(16, NULL)[2] est un int, et "1000" est char *, donc tout est bon!
*f(f(16, NULL)[2], "1000")         // c'est correct, l'expression précédente nous a renvoyé (char *) et en ajoutant *, donc obtient (char)
*f(f(16, NULL)[2], "1000")- ’8’    // c'est correct, on fait la soustraction de la valeur obtenue par '8' (valeur 8 selon la table ASCII))
*/



/*
[Q5] Soit un projet constitué de quatre modules A, B, C, D et d’un module principal Main. Il figure
    dans ce projet les inclusions suivantes :
— Main.c inclut A.h et B.h
— A.h inclut B.h et C.h
— B.c inclut A.h
— C.h inclut B.h
— C.c inclut B.h
Tracer le graphe d’inclusions (étendues) du projet.
':'         - 'module_un.c inclut module_deux.h' 
'|' et '->' - 'module_un.h inclut module_deux.h'

    :::::::> (A) -----> (C)
    :      ^ |          |:
    :      : |          |:
(main.c)   : |          |:       (D)
    :      : |          |:
    :      : v          |:
    :::::::> (B) <----- |:        
*/

/*
[Q6] Voir le CM 3
*/

/*
[Q7] Écrire un Makefile simple pour compiler le projet.
CC = gcc
OBJ = main.o A.o B.o C.o D.0
CFLAGS = -std=c17

Main: $(OBJ)
    $(CC) -o $@ $^ $(CFLAGS)

main.o : main.c A.h B.h
A.o : A.c A.h C.h B.h
B.o : B.c B.h
C.o : C.c C.h B.h
D.o : D.c D.h

# d'apres le cours CM 4 la derniere page
%.o : %.c
    $(CC) $(CFLAGS) -c -o $@ $<
*/


/*
[Q8] Après une compilation (qu’on supposera bien déroulée), on modifie le fichier A.h,
    donner la suite d’instructions de compilation suffisantes pour re-compiler le programme.
    gcc -o A.o -std=c17
    gcc -o main.o -std=c17
Car si on effectue le changement de A.h alors il faut recompiler tout ce qui inclut A.h donc c'est `A.o` et `main.o`
*/


/*
[Q9] Définir un type QuatreCouleurs permettant de représenter l’état d’un stylo quatre couleurs.
    Pour chacune des quatre couleurs (noir, rouge, vert, bleu), on souhaite représenter la quantité d’encre
    restante (de 0 pour vide, à 100 pour plein), et on doit également représenter si une pointe est sortie
    ainsi que sa couleur.

typedef enum couleur{
    noir,
    rouge,
    vert,
    bleu
} Couleur;

typedef struct {
    Couleur couleur_stylo;   // un des quatre couleur : {noir, rouge, vert, bleur}
    int quantite;            // de 0 pour vide, à 100 pour plein
    int etat;                // 0 si non, 1 si oui
} Stylo;

typedef struct quatre_couleurs{
    Stylo pencil[4];
} QuatreCouleurs;
*/


/*
[Q10] Écrire une fonction transformer_titre paramétrée par une chaine de caractère chaine qui
    modifie chaine afin que chaque mot commence par une majuscule suivi de minuscules.
    Un mot est une suite de lettres de l’alphabet délimitée par n’importe quel autre caractère (chiffre, ponctuation, espace ...).
    Par exemple, la chaine de caractères "ceCi␣n’eSt␣PAS␣rai5onN4ble" devient "Ceci␣N’Est␣Pas␣Rai5Onn4Ble".


*/
