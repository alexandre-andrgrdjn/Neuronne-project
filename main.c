#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    int *poids;
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
        scanf("%d", &neurone.poids[i]);
    }
    printf("Entrez le biais du neurone : ");
    scanf("%d", &neurone.biais);
    
    return neurone;
}

int main() {
    int n;
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

    return 0;
}
