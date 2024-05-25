/*
    Préparé par MUNAITPASOV M.
    Université Gustave Eiffel

    Pour trouver la question souhaitée, cherchez par [Qn], avec n = {1, ..., 15}
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
    [Q1] Pour chaque ligne du programme de gauche, lister les éventuels effets secondaires
        et donner la valeur et le type de l'expression sous-jacente (s'il y en a une).
        Indiquer en justifiant si les fonctions définies à droite sont à effets secondaires.

    1. int a, *p, t[5];                                 1. int *index(int *x, int y){
    2. if (plus5(2) < 6){                               2.     return &x[y];
    3.   a = 4;                                         3. }
    4. } else {                                         4. int plus5(int a){
    5.   a = 2;                                         5.     int b;
    6. }                                                6.     b = 5;
    7. p = index(t, a);                                 7.     return a + b;
    8. p[1] = 0;                                        8. }

*/

/*
    TO DO
*/

/*
    [Q2] Donner les erreurs présentes dans cet extrait de code, indiquer s'il compile et proposer une correction.
    Justifier chauqe réponse.

    1. // Renvoie le tableau des sommes cumulées des éléments du tableau passé en paramétre
    2. // exemple: [1, 4, 6] -> [1, 5 (1+4), 11 (1+4+5)]
    3. int *sommes_cumulees(int tab[]){
    4.     int resultat[TAILLE_MAX];    // Tableau des résultats
    5.     int taille = sizeof(tab);    // Taille de tab
    6.     
    7.     assert(taille < TAILLE_MAX);
    8.     
    9.     resultat[0] = tab[0];
    10.    for (int i = 1; i != taille; i++) {
    11.        resultat[i] = resultat[i-1] * tab[i];
    12.    }
    13.    return resultat;
    14. }
*/


/*
    La réponse:

    Je vous invite à faire vous même et après voir ma solution




    1) Le commentaire était mal écrit: `paramétre` au lieu de `paramètre`
    2) Dans le prototype de fonction il nous manque la taille du tableau
    3) On ne sait rien à propos de TAILLE_MAX
    4) la taille est mal calculée (il ne faut pas faire ça)
    5) i != taille c'est absurde car boucle for ne va pas commencer
    6) le nom de la fonction et le commentaire nous indique qu'on calcule la somme et ne pas le produit ...
    7) on renvoie le tableau d'entier local ce qu'il faut jamais faire


    La fonction correcte:
    1. // Renvoie le tableau des sommes cumulées des éléments du tableau passé en paramétre
    2. // exemple: [1, 4, 6] -> [1, 5 (1+4), 11 (1+4+5)]
    3. int *sommes_cumulees(int tab[], int taille){
    4.    assert(taille > 0);   // taille doit être supérieur à 0
    5.
    6.    for (int i = 1; i < taille; i++) {
    7.        tab[i] += tab[i-1];
    8.    }
    9.    return tab;
    10.}
*/


/*
    [Q3] Soit un projet constitué de quatre modules A, B, C, D et d'un module principal Main.
        Il figure dans ce projet les inclusion suivante :
        - Main.c inclut B.h C.h     - A.H inclut C.h et D.h     - A.c inclut D.h
        - C.h inclut B.h     - B.h inclut D.h
        - B.c inclut C.h     - D.h inclut C.h

    Tracer le graphe d'inclusion (étendues) du projet.
*/

/*
    Je pense que vous êtes capable de le faire!
*/


/*
    [Q4] Expliquer si le projet contient une ou plusieurs incohérences/erreurs

    Erreur:
        le projet contient un boucle d'inclusion entre A.h, C.h et D.h 

    Incohérence:
        De plus, module A est inutile, car il n'est jamais utilisé

*/



/*
    [Q5] Ecrire un Makefile simple pour compiler le projet selon les bonnes pratiques du cours
        (on suppose ici que le projet ne présente aucune incohérence)
    
    CC = gcc
    CFALGS = -std=c17
    OBJ = main.o A.o B.o C.o D.o
    EXEC = executable

    $(EXEC) : $(OBJ)
        $(CC) $(CFLAGS) -o $@ $^
    
    main.o : main.c B.h C.h
    A.o : A.c A.h C.h D.h
    B.o : B.c B.h D.h
    C.o : C.c C.h B.h
    D.o : D.c D.h C.h

    %.o : %.o
        $(CC) $(CFLAGS) -c -o $@ $<
*/



/*
    [Q6] Après une compilation (qu'on supposera sans erreur), on modifie le fichier B.h,
        quels sont les fichiers à produire à nouveau à l'aide de gcc/clang? Justifier.
    
    Makefile va recompiler tous les fichiers qui dépendent de module B,
    dans notre cas c'est tous les fichiers: main.o, A.o, C.o, D.o
*/



/*
    [Q7] Ecrire une fonction nom_base paramétrée par une chaine de caractères correspondant au chemin d'accès d'un fichier.
    La fonction renvoie l'adresse de la sous-chaine de caractères correspondant au nom du fichier.
    Par exemple, avec le paramètre "/home/padawan/perfc/tp1.c", la fonction renvoie
    l'adresse de la sous-chaine "tp1.c".
    Si le chemin est vide ou termine par un '/', la fonction renvoie l'adresse de la sous-chaine vide "".
*/


char *nom_base(char *chemin){
    if ( !chemin || !*chemin ) { return ""; }

    char *res = NULL, *ptr = NULL;

    for (ptr = chemin; *ptr != '\0'; ++ptr) {   // Parcourir la chaîne pour trouver le dernier '/'
        if (*ptr == '/') { res = ptr; }
    }

    // '/' est trouvé
    if (res) {
        
        // Si le dernier caractère est '/', retourner une chaîne vide
        if (*(res + 1) == '\0') { return ""; }
        
        // Retourner l'adresse du caractère après le dernier '/'
        return res + 1;
    }
    return chemin;
}


/*
    [Q8] Ecrire une fonction compte_suite_aB à gestion d'erreur paramétrée par un nom de fichier
        `nom` et qui renvoie le nombre d'occurences de la suite de lettres `aB` dans le fichier.
        Documenter la fonction.
*/


int compte_suite_aB(char *nom_fichier){
    FILE *f_ptr = fopen(nom_fichier, "r");
    if (!f_ptr){
        fprintf(stderr, "On ne peut pas ouvrire le fichier %s\n", nom_fichier);
        return 0;
    }
    int count = 0;
    int last = 0, curr = 0;
    while ( !(curr = fgetc(f_ptr)) ){  // si c != EOF
        if (last == 'a' && curr == 'B'){
            count++;
        }
        last = curr;
    }
    fclose(f_ptr);
    return count;
}


/*
    [Q9] Ecrire une fonction `miroir_8bit` paramétrée par un nom de fichier nom et qui renvoie
        le miroir bit à bit sur 8 bits.
        Par exemple, la fonction appelée avec le nombre `01011000` renvoie le nombre `00011010`
*/

typedef unsigned char u8;

u8 miroir_8bit(u8 num){
    u8 res = 0;     // 00000000
    int i = 0;
    unsigned int bit = 0;
    for (i = 0; i < 8; ++i){
        bit = (num >> i) & 1U;
        res |= (bit << (8-1-i));
    }
    return res;
}


/*
    [Q10] SANS UTILISER DE BOUCLE!!!!!!!!!!!!!!!!!!!!!!!!
        Ecrire une fonction bits_consecutifs paramétrée par un nombre de 64 bits et renvoie un nombre de 64 bits
        dont chaque bit en position `i` vaut 1 si tous les bits en position i et i+1 sont de même valeur et 0 sinon.
        Par exemple, la fonction appelée avec le nombre `11...1101100` renvoie le nombre `01...0100101`.
*/

typedef unsigned long long ull;

ull bits_consecutifs(ull num){
    // bouger le num à gauche une fois
    ull decalage = num >> 1;

    // on compare si les bits en position i sont les mêmes (xor renvoie 0, si les bits sont équivalents)
    ull xor_res = (num ^ decalage);

    return ~(xor_res);  // renverser les bits
}


/*
    [Q11] Déclarer un pointeur f_1 sur une fonction paramétrée par deux caractères et qui renvoie un entier.
        Déclarer un pointeur f_2 sur une fonction par deux entiers et qui renvoie
        un pointeur sur une fonction de même prototype que celui de f_1.
        Donner une expression ou une instruction correcte utilisant f_1 et f_2.
*/

typedef int (*f_1)(char, char);

typedef f_1 (*f_2)(int, int);

int test(f_2 var){
    return var(1, 2)('a', 'b');
}



/*
    [Q12] Ecrire une fonction `separe` paramétrée par un tableau d'entiers de type `int` et
        un pointeur sur une fonction `test` à type de retour `int` et à un paramètre de type `int`.
        La fonction renvoie un tableau dont les premiers éléments sont les éléments
        pour lesquels `test` renvoie 0, et les derniers sont les autres éléments.

*/

int *separe(int tab[], int taille, int (*test)(int)){
    int *arr = calloc(taille, sizeof(int));
    if (!arr){
        fprintf(stderr, "Problème de mémoire\n");
        return NULL;
    }
    int i = 0;
    int idx = 0;
    for (i = 0; i < taille; ++i){
        if ( !test(tab[i]) ){
            arr[idx] = tab[i];
            ++idx;
        }
    }

    for (i = 0; i < taille; ++i){
        if ( test(tab[i]) ){
            arr[idx] = tab[i];
            ++idx;
        }
    }

    /*
        Il y a deux choix:
        1) on peut renvoyer directement `arr` et c'est tout
        2) on peut recopier tous les éléments dans `tab` et libérer `arr`
    */

    /*  1)
        return arr;
    */
    
    // 2)
    for (i = 0; i < taille; ++i) { tab[i] = arr[i]; }

    free(arr);
    return tab;
}



















































int main(int argc, char *argv[]){
    return 0;
}
