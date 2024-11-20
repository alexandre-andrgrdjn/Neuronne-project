#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    // int *poids; faire liste chainée
    int biais;
    int nb_entrees;
} Neurone;

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
        scanf("%d", &neurone.poids[i]);//modifier
    }
    printf("Entrez le biais du neurone : ");
    scanf("%d", &neurone.biais);
    
    return neurone;
}
//Partie 2
typedef struct {
    // Neurone *neurones; faire liste chainée
    int nb_neurones;    
} Couche;

Couche InitCouche(int nb_neurones, int nb_entrees) {
    Couche couche;
    couche.nb_neurones = nb_neurones;
    couche.neurones = (Neurone *)malloc(nb_neurones * sizeof(Neurone));
    
    for (int i = 0; i < nb_neurones; i++) {
        printf("Initialisation du neurone %d\n", i+1);
        couche.neurones[i] = InitNeur(nb_entrees);//modifier
    }
    
    return couche;
}

int* OutCouche(Couche couche, float *Liste_entrees) {
 
    int *Sorties = (int*)malloc(couche.nb_neurones * sizeof(int));
    
    
    for (int i = 0; i < couche.nb_neurones; i++) {
        Sorties[i] = Outneurone(Liste_entrees, couche.neurones[i]);//modifier
    }
    
    return Sorties;
}


int main() {
    //test partie 1
  /* int n;
    printf("Combien d'entrées pour le neurone? ");
    scanf("%d", &n);

    // Initialiser le neurone avec n entrées
    Neurone neurone = InitNeur(n);
    float *entrees = (float *)malloc(neurone.nb_entrees * sizeof(float));
    
    printf("Entrez les valeurs des entrées du neurone : \n");
    for (int i = 0; i < neurone.nb_entrees; i++) {
        printf("Entrée %d: ", i + 1);
        scanf("%f", &entrees[i]);
    }
    
    // Calcul de la sortie du neurone
    int sortie = Outneurone(entrees, neurone);
    
    // Affichage de la sortie du neurone
    printf("Sortie du neurone : %d\n", sortie);
    
    // Libération de la mémoire allouée pour les poids et les entrées
    free(neurone.poids);
    free(entrees);
    */ 


   // Test de la partie 2
    int nb_neurones = 3;
    int nb_entrees = 2;
    Couche couche = InitCouche(nb_neurones, nb_entrees);
    float entrees[] = {1.0, -1.5};
    int *sorties = OutCouche(couche, entrees);
    printf("Calcul des sorties de la couche : \n");
    for (int i = 0; i < nb_neurones; i++) {
        printf("Sortie du neurone %d : %d\n", i + 1, sorties[i]);
    }
    free(sorties);
    for (int i = 0; i < nb_neurones; i++) {
        free(couche.neurones[i].poids);
    }
    free(couche.neurones); 

    return 0;
}