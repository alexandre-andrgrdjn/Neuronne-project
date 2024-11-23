

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