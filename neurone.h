// neurone.h

#ifndef NEURONE_H
#define NEURONE_H

// Définition des structures de données pour la liste chainée des poids et des entrées

typedef struct Node {
    int poids;
    struct Node *suivant;
} Node;

typedef struct EntreeNode {
    float entree;
    struct EntreeNode *suivant;
} EntreeNode;

typedef struct {
    Node *liste_poids;  // Liste chainée des poids
    int biais;
    int nb_entrees;
} Neurone;

// Liste chainée de neurones dans une couche
typedef struct NeuroneNode {
    Neurone neurone;
    struct NeuroneNode *suivant;
} NeuroneNode;

typedef struct {
    int nb_neurones;
    NeuroneNode *neurones;
} Couche;

Node* Ajoutertete(Node *tete, int poids);
EntreeNode* AjouterteteEntree(EntreeNode *tete, float entree);
Neurone InitNeur(int n);
int Outneurone(EntreeNode *Liste_entrees, Neurone neurone);
NeuroneNode* AjouterNeurone(NeuroneNode *tete, Neurone neurone);
Couche InitCouche(int nb_neurones, int nb_entrees);
EntreeNode* OutCouche(Couche couche, EntreeNode *Liste_entrees);
void LibererListe(Node *tete);
void LibererNeurone(Neurone neurone);
void LibererCouche(Couche couche);

#endif
