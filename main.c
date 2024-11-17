#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    int *poids;
    int biais;
    int nb_entrees;
} Neurone;


int Outneurone(double *ei, Neurone neurone) {
    double somme = 0;

    for (int i = 0; i < neurone.nb_entrees; i++) {
        somme += neurone.poids[i] * ei[i];
    }

    somme += neurone.biais;  
    if (somme >= neurone.biais) {
        return 1;
    } else {
        return 0;
    }
}

Neurone InitNeur(int n) {
    Neurone neurone;

    neurone.nb_entrees = n;

    neurone.poids = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        neurone.poids[i] = (rand() % 21) - 10;
    }

    neurone.biais = (rand() % 21) - 10;

    return neurone;
}

int main() {
   srand(time(NULL));

    int n = 5;
    Neurone neurone = InitNeur(n);

    for (int i = 0; i < n; i++) {
        printf("Poids %d: %d\n", i, neurone.poids[i]);
    }
    printf("Biais: %d\n", neurone.biais);

    double entrees[] = {1.5, -2.3, 0.8, 1.0, -1.7};  // Exemple d'entrées
    int sortie = Outneurone(entrees, neurone);

    printf("Sortie du neurone : %d\n", sortie);

    free(neurone.poids);

    return 0;
}
