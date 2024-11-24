
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
    float data;
    struct ListeSortie* suivant;
} ListeSortie;

//partie 3

typedef struct Listecouche {
    Couche* couche;
    struct Listecouche* suivant;
} Listecouche;

typedef struct nbCouches {
    int data;
    struct nbCouches* suivant;
} nbCouches;


// Fonctions du projet

//partie 1
int Outneurone(Entree* liste_entree, Neurone neurone);
Neurone InitNeur(int n);

//partie 2
Couche InitCouche(int nb_neurones, int nb_entrees);
ListeSortie* OutCouche(Couche couche, Entree* liste_entrees);

// Fonctions utilitaires
Poids* remplirListePoids(int n);
void libererListePoids(Poids* tete);
Entree* remplirListeEntree(int n);
nbCouches* CreerListeTailles();
void afficherReseau(Listecouche* reseau);

//Partie 3
Listecouche* CreerResNeur(int nb_couches, nbCouches* liste_nbParCouches) ;

#endif
