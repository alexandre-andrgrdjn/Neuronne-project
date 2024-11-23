#include "neurone.h" 
Neurone InitNeur(int n) {
    Neurone neurone;
    neurone.nb_entrees = n;
    neurone.poids = remplirListePoids(n);
    printf("Entrez le biais du neurone : ");
    scanf("%f", &neurone.biais);
    return neurone;
}

int Outneurone(Entree* liste_entree, Neurone neurone) {
    float somme = 0;
    Poids* current_poids = neurone.poids;
    Entree* current_entree = liste_entree;

    for (int i = 0; i < neurone.nb_entrees; i++) {
        somme += current_poids->data * current_entree->data;
        current_poids = current_poids->suivant;
        current_entree = current_entree->suivant;
    }

    if (somme >= neurone.biais) {
        return 1;
    } else {
        return 0;
    }
}
//Partie 2


Couche InitCouche(int nb_neurones, int nb_entrees) {
    Couche couche;
    couche.nb_neurones = nb_neurones;
    couche.neurones = NULL;
    NoeudNeurone* dernier = NULL;

    for (int i = 0; i < nb_neurones; i++) {
        NoeudNeurone* nouveau = (NoeudNeurone*)malloc(sizeof(NoeudNeurone));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        nouveau->neurone = InitNeur(nb_entrees);
        nouveau->suivant = NULL;

        if (couche.neurones == NULL) {
            couche.neurones = nouveau;
        } else {
            dernier->suivant = nouveau;
        }
        dernier = nouveau;
    }

    return couche;
}

ListeSortie* OutCouche(Couche couche, Entree* liste_entrees) {
    ListeSortie* sortie_tete = NULL;
    ListeSortie* sortie_precedente = NULL;

    NoeudNeurone* current_neurone = couche.neurones;

    while (current_neurone != NULL) {
        int sortie_neurone = Outneurone(liste_entrees, current_neurone->neurone);
        
        ListeSortie* nouvelle_sortie = (ListeSortie*)malloc(sizeof(ListeSortie));
        if (nouvelle_sortie == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        nouvelle_sortie->data = sortie_neurone;
        nouvelle_sortie->suivant = NULL;

        if (sortie_tete == NULL) {
            sortie_tete = nouvelle_sortie;
        } else {
            sortie_precedente->suivant = nouvelle_sortie;
        }

        sortie_precedente = nouvelle_sortie;

        current_neurone = current_neurone->suivant;
    }

    return sortie_tete;
}

