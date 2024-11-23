#ifndef NEURONE_H 
#define NEURONE_H 

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    int *poids;
    int biais;
    int nb_entrees;
} Neurone;

typedef struct {
    Neurone *neurones;   
    int nb_neurones;    
} Couche;

//fonctions
int Outneurone(float *Liste_entrees, Neurone neurone);
Neurone InitNeur(int n);
Couche InitCouche(int nb_neurones, int nb_entrees);
int* OutCouche(Couche couche, float *Liste_entrees);


#endif 