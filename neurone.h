
#ifndef NEURONE_H
#define NEURONE_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//partie 1
typedef struct Poids {
    float data;
    struct Poids* suivant;
} Poids;

typedef struct Entree {
    float data;
    struct Entree* suivant;
} Entree;

typedef struct Neurone {
    Poids* poids;
    float biais;
    int nb_entrees;
} Neurone;

//partie 2
typedef struct NoeudNeurone {
    Neurone neurone;
    struct NoeudNeurone* suivant;
} NoeudNeurone;

typedef struct Couche {
    NoeudNeurone* neurones;
    int nb_neurones;
} Couche;

typedef struct ListeSortie {
    int data;
    struct ListeSortie* suivant;
} ListeSortie;


// Fonctions du projet

//partie 1
int Outneurone(Entree* liste_entree, Neurone neurone);
Neurone InitNeur(int n);

//partie 2
Couche InitCouche(int nb_neurones, int nb_entrees);
ListeSortie* OutCouche(Couche couche, Entree* liste_entrees);

// Fonctions utilitaires
Poids* remplirListePoids(int n);
Entree* remplirListeEntree(int n);


#endif
