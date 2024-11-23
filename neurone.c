#include "neurone.h" 

int Outneurone(float *Liste_entrees, Neurone neurone) {
    float somme = 0;
    
    for (int i = 0; i < neurone.nb_entrees; i++) {
        somme += neurone.poids[i] * Liste_entrees[i];  
    }
    
    if (somme >= neurone.biais) {
        return 1;  // Activation du neurone
    } else {
        return 0;  // Pas d'activation
    }
}

Neurone InitNeur(int n) {
    Neurone neurone;
    neurone.nb_entrees = n;
    neurone.poids = (int *)malloc(n * sizeof(int));
    printf("Entrez les %d poids du neurone :\n", n);
    for (int i = 0; i < n; i++) {
        printf("Poids %d: ", i + 1);
        scanf("%d", &neurone.poids[i]);
    }
    printf("Entrez le biais du neurone : ");
    scanf("%d", &neurone.biais);
    
    return neurone;
}
//Partie 2


Couche InitCouche(int nb_neurones, int nb_entrees) {
    Couche couche;
    couche.nb_neurones = nb_neurones;
    couche.neurones = (Neurone *)malloc(nb_neurones * sizeof(Neurone));
    
    for (int i = 0; i < nb_neurones; i++) {
        printf("Initialisation du neurone %d\n", i+1);
        couche.neurones[i] = InitNeur(nb_entrees);
    }
    
    return couche;
}

int* OutCouche(Couche couche, float *Liste_entrees) {
 
    int *Sorties = (int*)malloc(couche.nb_neurones * sizeof(int));
    
    
    for (int i = 0; i < couche.nb_neurones; i++) {
        Sorties[i] = Outneurone(Liste_entrees, couche.neurones[i]);
    }
    
    return Sorties;
}
