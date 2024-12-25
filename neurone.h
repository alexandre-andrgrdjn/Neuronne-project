
#ifndef NEURONE_H
#define NEURONE_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//partie 1
typedef struct Poids {
    int data;
    struct Poids* suivant;
} Poids;

typedef struct Entree {
    float data;
    struct Entree* suivant;
} Entree;

typedef struct Neurone {
    Poids* poids;
    int biais;
    int nb_entrees;
} Neurone;



//partie 2

typedef struct NoeudNeurone {
    Neurone neurone;
    struct NoeudNeurone* suivant;
} NoeudNeurone;

typedef struct ListeSortie {
    int data;
    struct ListeSortie* suivant;
} ListeSortie;

typedef struct Couche {
    NoeudNeurone* neurones;
    int nb_neurones;
} Couche;

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
float Outneurone(Entree* liste_entree, Neurone neurone);
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
Listecouche* creer_reseau_avec_neurone(Neurone neurone);
Poids* remplirListePoidsVal1(int n) ;
Entree* convertirListeSortieEnEntree(ListeSortie* liste_sorties);

//Partie 3
Listecouche* CreerResNeur(int nb_couches, nbCouches* liste_nbParCouches) ;
//Partie4
float reseauET(Listecouche* reseau, Entree* entrees);
float reseauOU(Listecouche* reseau, Entree* entrees);
float reseauNOT(Listecouche* reseau, Entree* entrees);
float reseauMultiCouches(Listecouche* reseauA, Listecouche* reseauB, Listecouche* reseauC, Entree* entrees) ;
#endif
