#include <stdio.h>
#include <stdlib.h>
#include "neurone.h"

// Ajouter un poids à la tête de la liste chainée des poids
Node* Ajoutertete(Node *tete, int poids) {
    Node *nouveau = (Node *)malloc(sizeof(Node));
    nouveau->poids = poids;
    nouveau->suivant = tete;
    return nouveau;
}

// Ajouter une entrée à la tête de la liste chainée des entrées
EntreeNode* AjouterteteEntree(EntreeNode *tete, float entree) {
    EntreeNode *nouveau = (EntreeNode *)malloc(sizeof(EntreeNode));
    nouveau->entree = entree;
    nouveau->suivant = tete;
    return nouveau;
}

// Libérer la liste des entrées
void LibererListeEntree(EntreeNode *tete) {
    EntreeNode *courant = tete;
    while (courant != NULL) {
        EntreeNode *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
}

// Libérer la mémoire d'un neurone
void LibererNeurone(Neurone neurone) {
    LibererListe(neurone.liste_poids);
}

// Libérer la mémoire d'une couche de neurones
void LibererCouche(Couche couche) {
    NeuroneNode *courant = couche.neurones;
    while (courant != NULL) {
        LibererNeurone(courant->neurone);
        NeuroneNode *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
}

// Initialiser un neurone avec ses poids et son biais
Neurone InitNeur(int n) {
    Neurone neurone;
    neurone.nb_entrees = n;
    neurone.liste_poids = NULL;

    printf("Entrez les %d poids du neurone :\n", n);
    for (int i = 0; i < n; i++) {
        int poids;
        printf("Poids %d: ", i + 1);
        scanf("%d", &poids);
        neurone.liste_poids = Ajoutertete(neurone.liste_poids, poids);
    }

    printf("Entrez le biais du neurone : ");
    scanf("%d", &neurone.biais);
    return neurone;
}

// Calculer la sortie d'un neurone avec les entrées passées sous forme de liste chainée
int Outneurone(EntreeNode *Liste_entrees, Neurone neurone) {
    float somme = 0;
    Node *courant_poids = neurone.liste_poids;
    EntreeNode *courant_entrees = Liste_entrees;

    for (int i = 0; i < neurone.nb_entrees; i++) {
        if (courant_poids == NULL || courant_entrees == NULL) {
            printf("Erreur : Liste des poids ou des entrées trop courte.\n");
            return 0;
        }

        somme += courant_poids->poids * courant_entrees->entree;
        courant_poids = courant_poids->suivant;
        courant_entrees = courant_entrees->suivant;
    }

    if (somme >= neurone.biais) {
        return 1;  // Activation du neurone
    } else {
        return 0;  // Pas d'activation
    }
}

// Ajouter un neurone à la couche sous forme de liste chainée
NeuroneNode* AjouterNeurone(NeuroneNode *tete, Neurone neurone) {
    NeuroneNode *nouveau = (NeuroneNode *)malloc(sizeof(NeuroneNode));
    nouveau->neurone = neurone;
    nouveau->suivant = tete;
    return nouveau;
}

// Initialiser une couche de neurones
Couche InitCouche(int nb_neurones, int nb_entrees) {
    Couche couche;
    couche.nb_neurones = nb_neurones;
    couche.neurones = NULL;

    for (int i = 0; i < nb_neurones; i++) {
        printf("Initialisation du neurone %d\n", i + 1);
        Neurone neurone = InitNeur(nb_entrees);
        couche.neurones = AjouterNeurone(couche.neurones, neurone);
    }

    return couche;
}

// Calculer les sorties d'une couche avec les entrées sous forme de liste chainée
EntreeNode* OutCouche(Couche couche, EntreeNode *Liste_entrees) {
    EntreeNode *sorties = NULL;
    NeuroneNode *courant = couche.neurones;

    while (courant != NULL) {
        int sortie = Outneurone(Liste_entrees, courant->neurone);
        sorties = AjouterteteEntree(sorties, sortie);  // Ajouter la sortie à la liste chainée
        courant = courant->suivant;
    }

    return sorties;
}
