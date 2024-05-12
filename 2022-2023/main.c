/*
    Préparé par MUNAITPASOV M.
    Université Gustave Eiffel

    Pour trouver la question souhaitée, cherchez par [Qn], avec n = {1, ..., 16}
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
[Q1] Lister les éventuels effets de bords et donner la valeur de l’expression
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
[Q2] En supposant que y est un identificateur de variable de type float *,
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
[Q3] En supposant que x est un identificateur de variable de type int** et y un identificateur de
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
*/
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



/*
[Q10] Écrire une fonction transformer_titre paramétrée par une chaine de caractère chaine qui
    modifie chaine afin que chaque mot commence par une majuscule suivi de minuscules.
    Un mot est une suite de lettres de l’alphabet délimitée par n’importe quel autre caractère (chiffre, ponctuation, espace ...).
    Par exemple, la chaine de caractères "ceCi n’eSt PAS rai5onN4ble" devient "Ceci N’Est Pas Rai5Onn4Ble".


*/

char to_upper(char c){
    if ('a' <= c && c <= 'z'){
        return c - 'a' + 'A';
    }
    return c;    /* rien a faire si c'est pas une lettre minuscule */
}

char to_lower(char c){
    if ('A' <= c && c <= 'Z'){
        return c - 'A' + 'a';
    }
    return c;    /* rien a faire si c'est pas une lettre majuscule */
}

/*
    On suppose que chaine est `char []`
    Sinon on ne peut rien changer
*/
void transformer_titre(char chaine[]){
    int espace = 1;    /* pour la premiere fois*/
    int i = 0;
    for (i = 0; chaine[i]; ++i){
        if (espace){
            chaine[i] = to_upper(chaine[i]);
            espace = 0;
        }
        if (chaine[i] == ' '){     /* si c'est un espace */
            espace = 1;
        }
        chaine[i] = to_lower(chaine[i]);
    }
}


/*
[Q11] Écrire une fonction melange paramétrée par un tableau de chaines de caractères et renvoie
    une nouvelle chaine de caractères construite en prenant successivement les premiers caractères de
    chaque chaine, puis les deuxièmes caractères et ainsi de suite jusqu’à ce qu’il n’y ait plus de lettre.
    Par exemple, le résultat sur le tableau de chaines de caractères {"aeik", "bf", "cg", "", "dhj"}
    est la chaine "abcdefghijk".

*/

/* équivalent à strlen() de string.h */
int longueur(char *mot){
    int i = 0;
    while (*mot++) ++i;
    return i;
}


char *melange(char *tab[], size_t taille){
    char *result = NULL;
    int i = 0, curr_idx = 0, new_taille = 0, result_idx = 0;
    
    for (i = 0; i < taille; ++i)
        new_taille += longueur(tab[i]);
    
    /* sizeof(*result) == sizeof(char) */
    result = malloc(sizeof(*result) * (new_taille + 1));    /* new_taille + 1, il faut ajouter '\0' à la fin */
    if ( !(result) ){
        fprintf(stderr, "Pas de memoire\n");
        return NULL;
    }

    while (result_idx < new_taille + 1){
        for (i = 0; i < taille; ++i){
            if (curr_idx < longueur(tab[i])){    /* si l'indice est valide, alors tout est bon! */
                result[result_idx] = tab[i][curr_idx];
                ++result_idx;
            }
        }
        curr_idx++;
    }
    
    result[result_idx] = '\0';
    return result;
}

/*
Si vous voulez vérifier si cette fonction fonctionne, vous pouvez tester avec ça:
int main(void){
    char *tab[] = {"aeik", "bf", "cg", "", "dhj"};
    int taille = 5;
    char *result = melange(tab, taille);
    printf("result: %s, taille: %d\n", result, longueur(result));
    return 0;
}
*/


/*
[Q12] Écrire une fonction compte_lettre_a à gestion d’erreur paramétrée par un nom de fichier nom
    et qui renvoie le nombre d’occurences de la lettre ’a’ dans le fichier.
*/

int compte_lettre_a(char *nom_fichier){
    int count = 0, c = 0;
    FILE *fptr = fopen(nom_fichier, "r");
    if (!fptr){
        fprintf(stderr, "Le fichier n'est pas trouver\n");
        return 0;
    }
    while ( (c = fgetc(fptr)) != EOF ){
        if (c == 'a') ++count;
    }
    return count;
}



/*
[Q13] Écrire une fonction combine_tabs paramétrée par deux tableaux de même taille d’entiers de
    type int et un pointeur sur une fonction f à type de retour int et à deux paramètres de type int.
    La fonction renvoie un nouveau tableau de la même taille que ses arguments et dont l’élémént d’indice
    `i` est le résultat de l’application de f aux deux éléments d’indices i des tableaux en paramètre.
*/


int *combine_tabs(int *tab_un, int *tab_deux, size_t taille, int (*f)(int, int)){
    int i = 0;
    for (i = 0; i < taille; ++i){
        tab_un[i] = f(tab_un[i], tab_deux[i]);
    }
    return tab_un;
}

/*
On n'est pas obligé d'allouer dynamiquement la mémoire pour un nouveau tableau,
mais si on veut l'ajouter, il faut faire ça:

int *combine_tabs(int *tab_un, int *tab_deux, size_t taille, int (*f)(int, int)){
    int i = 0;
    int *new_tableau = malloc(sizeof(*new_tableau) * taille);
    if (!new_tableau){
        fprintf(stderr, "Pas de memoire pour nouveau tableau\n");
        return NULL;
    }
    for (i = 0; i < taille; ++i){
        new_tableau[i] = f(tab_un[i], tab_deux[i]);
    }
    return new_tableau;
}
*/


/*
[Q14] Écrire une fonction equiv_rotation paramétrée par deux nombres de 64 bits (non signés) et
    renvoie 1 si les bits du premier nombre sont les mêmes que ceux du second à rotation près et renvoie
    0 sinon. Par exemple sur 8 bits, les nombres 01110010 et 01001110 sont les mêmes par une rotation
    de 3 bits vers la droite : 01110010 -> 01001110
*/
typedef unsigned long long ull;

ull reverse_bits(ull chiffre) {
    ull result = 0;
    int i = 0;
    int decaler = 0, bit_poids_faible = 0;
    for (i = 0; i < 64; ++i) {
        decaler = 63 - i;
        bit_poids_faible = (chiffre >> i) & 1;

        /* logique `ou` pour avoir le bit poidsfaible à la position du bit de poids fort */
        result |= bit_poids_faible << decaler;  
    }
    return result;
}

int equiv_rotation(ull a, ull b){
    return reverse_bits(a) == b;
}

/*
[Q15] Écrire une fonction plus_long_suffixe paramétrée par deux nombres de 64 bits (non signés)
    et qui renvoie la taille du plus long suffixe commun dans l’écriture binaire des deux nombres.
    Par exemple, les nombres 0...0100110 et 0....0101110 ont comme plus grand suffixe commun les 3 bits 110.
*/


int plus_long_suffixe(ull a, ull b){
    int count = 0, i = 0;
    int bit_faible_a = 0, bit_faible_b = 0;
    for (i = 0; i < 64; ++i){
        bit_faible_a = (a >> i) & 1;
        bit_faible_b = (b >> i) & 1;

        /* si l'un d'entre est different, on renvoie la réponse*/
        if (bit_faible_a ^ bit_faible_b) {
            return count;
        }
        ++count;
    }
    return count;
}



/*
    [Q16] Donner en justifiant les erreurs présentes dans cet extrait de code de la fonction main :

                                                                              // problème numéro 0)    au début de la feuille, on n'a pas inclus <string.h>
                                                                              // problème numéro 1)    on doit être sur que main a (`argc` et `argv`) pour pouvoir les utiliser plus tard
                                                                              // problème numéro 2)    il vaut mieux changer (argc == 4) à (argc >= 4)
    if (argc == 4 && argv[1] == "compare") {                                  // problème numéro 3)    une mauvaise comparaison (la correction en bas)
        int different = (strlen(argv[2]) != strlen(argv[3]));                 // problème numéro 4)    la valeur n'est pas accessible après (la correction en bas)
                                                                              // problème numéro 5)    la valeur de `different` après avoir vérifié la longueur n'est pas utilisée
        for (int i = 0; i < strlen(argv[2]) && i < strlen(argv[3]); i++) {    // problème numéro 6)    les calculs inutiles
            if (argv[2][i] != argv[3][i])                                     // problème numéro 7)    les accolades oubliées
                different = 1;
                break;
        }
    }
    if (different) printf("%s␣et␣%s␣sont␣différents\n", argv[2], argv[3]);      // la conséquence de problème 4)
                                                                              // problème numéro 8) (complémentaire) il faut renvoie 0   
*/



/* le main correcte: */

/* il faut l'inclure pour pouvoir utiliser les fonctions: strlen(), strcmp()... */
#include <string.h>

int main(int argc, char *argv[]){    /* un bon prototype */

    /* un autre erreur fait dans main, n'est pas accessible, car la valeur est parti de la pile */
    int different = 0;    
    
    /* d'abord il faut verifier si nous avons au moins 4 arguments
        (notre programme fonctionne également s'il y a plus de 4 arguments) */
    if (argc >= 4){
        /*
            il est interdit de faire argv[1] == "compare", car vous faites la comparaison de argv[1][0] == 'c'
            donc on utilise la fonction strcmp()
        */
        if ( !strcmp(argv[1], "compare") ){

            /*  problème suivant: dans les boucle il vaut mieux ne pas appeler les fonctions qui parcours la chaine
                Vous empirez la complexité, donc faites les calculs de la longueur avant. */
            int longueur_un = strlen(argv[2]);
            int longueur_deux = strlen(argv[3]);

            /* on n'utilise pas la valeur de `different` après avoir vérifié la longueur
                donc j'ajoute cette condition dans boucle for */
            different = longueur_un != longueur_deux;
            for (int i = 0; i < longueur_un && i < longueur_deux && !different; i++){
                if (argv[2][i] != argv[3][i]){    /* il faut pas oublier qu'il faut ajouter les accolades, s'il y a plus d'une instruction */
                    different = 1;
                    break;
                }
            }
            /* de plus il faut l'ajouter cette vérification à l'intérieur de premier if
            car sinon c'est segfault (vous n'avez pas droit d'accéder à argv[2] ou argv[3]) */
            if (different) printf("%s et %s sont différents\n", argv[2], argv[3]);
        }

    }
    /* il ne faut pas oublier de renvoie 0 à la fin */
    return 0;
}

/* sinon, si c'était moi qui je le faisais, je le ferais comme ça :
    Ce petit programme vérifie juste si c'est bien

#include <stdio.h>    // pour printf()
#include <string.h>   // pour strcmp()

int main(int argc, char *argv[]){
    if (argc < 4) return 1;    // pas assez d'arguments 
    
    // première condition vérifie si c'est la mode de comparaison
    // deuxième condition vérifie si strcmp() renvoie une valeur différente de 0 (donc n'est pas égale)
    if ( !strcmp(argv[1], "compare") && strcmp(argv[2], argv[3]) ){
        printf("%s et %s sont différents\n", argv[2], argv[3]);
    }
    return 0;
}
*/
