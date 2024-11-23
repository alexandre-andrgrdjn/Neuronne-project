#include <stdio.h>
#include <stdlib.h>
#include "neurone.h"

int main() {
    // Initialisation d'un neurone avec 3 entrées
    int nb_entrees = 3;
    Neurone neurone = InitNeur(nb_entrees);

    // Création d'une liste d'entrées pour le neurone
    EntreeNode *Liste_entrees = NULL;
    float entree;
    printf("Entrez les %d entrées pour le neurone :\n", nb_entrees);
    for (int i = 0; i < nb_entrees; i++) {
        printf("Entree %d : ", i + 1);
        scanf("%f", &entree);
        Liste_entrees = AjouterteteEntree(Liste_entrees, entree);
    }

    // Calcul de la sortie du neurone avec la liste d'entrées
    int sortie = Outneurone(Liste_entrees, neurone);
    printf("La sortie du neurone est : %d\n", sortie);

    // Libération de la liste d'entrées
    LibererListeEntree(Liste_entrees);  // Libérer la liste d'entrées
    // Libération des poids du neurone
    LibererNeurone(neurone);

    return 0;
}
