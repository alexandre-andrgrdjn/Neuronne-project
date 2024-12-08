#include "neurone.h"

Poids* remplirListePoidsVal1(int n) {
    Poids* current = NULL;
    Poids* previous = NULL;
    Poids* tete = NULL;

    for (int i = 0; i < n; i++) {
        current = (Poids*)malloc(sizeof(Poids)); 
        if (current == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }

        current->data = 1.0f;  // Initialiser tous les poids à 1
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


void libererListePoids(Poids* tete) {
    Poids* current = tete;
    Poids* suivant = NULL;

    while (current != NULL) {
        suivant = current->suivant;
        free(current);  
        current = suivant;
    }
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

nbCouches* CreerListeTailles() {
    int nb_couches;
    printf("Entrez le nombre de couches : ");
    scanf("%d", &nb_couches);

    nbCouches* tete = NULL;
    nbCouches* courant = NULL;

    for (int i = 0; i < nb_couches; i++) {
        nbCouches* nouveau = (nbCouches*)malloc(sizeof(nbCouches));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }

        printf("Entrez le nombre de neurones pour la couche %d : ", i + 1);
        scanf("%d", &(nouveau->data));
        nouveau->suivant = NULL;

        if (tete == NULL) {
            tete = nouveau;
        } else {
            courant->suivant = nouveau;
        }
        courant = nouveau;
    }

    return tete;
}
void afficherReseau(Listecouche* reseau) {
    Listecouche* current = reseau;
    int couche_id = 1;

    while (current != NULL) {
        printf("Couche %d : %d neurones\n", couche_id, current->couche->nb_neurones);

        NoeudNeurone* neurone_courant = current->couche->neurones;
        int neurone_id = 1;
        while (neurone_courant != NULL) {
            printf("  Neurone %d :\n", neurone_id);
            
            
            Poids* poids_courant = neurone_courant->neurone.poids;
            int poids_id = 1;
            while (poids_courant != NULL) {
                printf("    Poids %d : %.2f\n", poids_id, poids_courant->data);
                poids_courant = poids_courant->suivant;
                poids_id++;
            }
            
            printf("    Biais : %.2f\n", neurone_courant->neurone.biais);

            neurone_courant = neurone_courant->suivant;
            neurone_id++;
        }

        current = current->suivant;
        couche_id++;
    }
}
Listecouche* creer_reseau_avec_neurone(Neurone neurone) {
    // Allouer la mémoire pour le réseau
    Listecouche* reseau = (Listecouche*)malloc(sizeof(Listecouche));
    if (reseau == NULL) {
        printf("Erreur d'allocation mémoire pour le réseau.\n");
        exit(1);
    }
    
    // Créer une couche
    Couche* couche = (Couche*)malloc(sizeof(Couche));
    if (couche == NULL) {
        printf("Erreur d'allocation mémoire pour la couche.\n");
        exit(1);
    }
    couche->nb_neurones = 1;
    
    // Créer un neurone
    NoeudNeurone* noeud = (NoeudNeurone*)malloc(sizeof(NoeudNeurone));
    if (noeud == NULL) {
        printf("Erreur d'allocation mémoire pour le neurone.\n");
        exit(1);
    }
    noeud->neurone = neurone;
    noeud->suivant = NULL;
    
    // Assigner le neurone à la couche
    couche->neurones = noeud;
    
    // Assigner la couche au réseau
    reseau->couche = couche;
    reseau->suivant = NULL;
    
    return reseau;
}
