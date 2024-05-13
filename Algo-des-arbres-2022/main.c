/*
                        L2 Algorithmique des arbres
                              Durée 2 heures.
                Notes de cours, de TD et de TP autorisées.

    • Les différentes parties sont indépendantes et peuvent être traitées dans n'importe quel ordre.
    • On veillera à minimiser la complexité des fonctions.
    • On pourra écrire des fonctions annexes, si l'utilisation de paramètres supplémentaires est nécessaire.
*/


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
    new_arbre = alloueNoeud(a->val);
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




















































