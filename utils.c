#include "neurone.h"

Poids* remplirListePoids(int n) {
    Poids* current = NULL;
    Poids* previous = NULL;
    Poids* tete = NULL;

    for (int i = 0; i < n; i++) {
        current = (Poids*)malloc(sizeof(Poids)); 
        if (current == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }

        printf("Poids %d: ", i + 1);
        scanf("%f", &current->data);
        current->suivant = NULL;  

        if (tete == NULL) {
            tete = current;  
        } else {
            previous->suivant = current;  
        }

        previous = current;  
    }

    return tete;  
}

Entree* remplirListeEntree(int n) {
    Entree* current = NULL;
    Entree* previous = NULL;
    Entree* tete = NULL;

    for (int i = 0; i < n; i++) {
        current = (Entree*)malloc(sizeof(Entree));
        if (current == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }

        printf("Entree %d: ", i + 1);
        scanf("%f", &current->data);
        current->suivant = NULL;

        if (tete == NULL) {
            tete = current;
        } else {
            previous->suivant = current;
        }

        previous = current;
    }

    return tete;
}

NoeudNeurone* remplirCouche(int nb_neurones, int nb_entrees) {
    NoeudNeurone* tete = NULL;
    NoeudNeurone* previous = NULL;

    for (int i = 0; i < nb_neurones; i++) {
        NoeudNeurone* current = (NoeudNeurone*)malloc(sizeof(NoeudNeurone));
        if (current == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }

        *current = (NoeudNeurone){InitNeur(nb_entrees), NULL};

        if (tete == NULL) {
            tete = current;
        } else {
            previous->suivant = current;
        }

        current->suivant = NULL;
        previous = current;
    }

    return tete;
}

