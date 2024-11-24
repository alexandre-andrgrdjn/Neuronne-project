
#include "neurone.h"


/*
    // Test de la partie 1
    /* 
    int n;
    Entree* liste_entree = NULL;

    printf("Combien d'entrées pour le neurone? ");
    scanf("%d", &n);

    Neurone neurone = InitNeur(n);
    liste_entree = remplirListeEntree(n);

    int sortie = Outneurone(liste_entree, neurone);
    printf("Sortie du neurone : %d\n", sortie);

    free(neurone.poids);

    return 0;
}
*/


   // Test de la partie 2
 
/*
int main() {
    int nb_neurones, nb_entrees;

    printf("Entrez le nombre de neurones dans la couche : ");
    scanf("%d", &nb_neurones);

    printf("Entrez le nombre d'entrées pour chaque neurone : ");
    scanf("%d", &nb_entrees);

    Couche couche = InitCouche(nb_neurones, nb_entrees);

    Entree* liste_entrees = remplirListeEntree(nb_entrees);

    ListeSortie* liste_sorties = OutCouche(couche, liste_entrees);

    printf("Sorties de la couche :\n");
    ListeSortie* current_sortie = liste_sorties;
    while (current_sortie != NULL) {
        printf("%d ", current_sortie->data);
        current_sortie = current_sortie->suivant;
    }
    printf("\n");

    return 0;
}
*/

//Test de la Partie 3

int main() {
    nbCouches* liste_tailles = CreerListeTailles();

    int nb_couches = 0;
    nbCouches* temp = liste_tailles;
    while (temp != NULL) {
        nb_couches++;
        temp = temp->suivant;
    }
    
    Listecouche* reseau = CreerResNeur(nb_couches, liste_tailles);
    printf("Réseau de neurones créé :\n");
    afficherReseau(reseau);

    return 0;
}

