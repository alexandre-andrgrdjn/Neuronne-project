
#include "neurone.h"

/*

// Test part 1 (check)

int main() {
    int n;
    Entree* liste_entree = NULL;

    printf("Combien d'entrées pour le neurone? ");
    scanf("%d", &n);

    Neurone neurone = InitNeur(n); //test InitNeur
    liste_entree = remplirListeEntree(n); //utils function

    int sortie = Outneurone(liste_entree, neurone);//test OutNeurone
    printf("Sortie du neurone : %d\n", sortie);

    free(neurone.poids);

    return 0;
}



// Test part 2 (check)

int main() {
    int nb_neurones, nb_entrees;

    printf("Entrez le nombre de neurones dans la couche : ");
    scanf("%d", &nb_neurones);

    printf("Entrez le nombre d'entrées pour chaque neurone : ");
    scanf("%d", &nb_entrees);

    Couche couche = InitCouche(nb_neurones, nb_entrees);

    Entree* liste_entrees = remplirListeEntree(nb_entrees);

    ListeSortie* liste_sorties = OutCouche(couche, liste_entrees);

    printf("Sorties de la couche :\n");
    ListeSortie* current_sortie = liste_sorties;
    while (current_sortie != NULL) {
        printf("%d ", current_sortie->data);
        current_sortie = current_sortie->suivant;
    }
    printf("\n");

    return 0;
}


//Test Part 3 (check)

int main() {
    nbCouches* liste_tailles = CreerListeTailles();

    int nb_couches = 0;
    nbCouches* temp = liste_tailles;
    while (temp != NULL) {
        nb_couches++;
        temp = temp->suivant;
    }
    
    Listecouche* reseau = CreerResNeur(nb_couches, liste_tailles);
    printf("Réseau de neurones créé :\n");
    afficherReseau(reseau); //utils function

    return 0;
}
//Test network AND (check)

int main() {
    int nb_neurones, nb_entrees;
    printf("Entrez le nombre de neurones dans la couche : ");
    scanf("%d", &nb_neurones);
    printf("Entrez le nombre d'entrées pour chaque neurone : ");
    scanf("%d", &nb_entrees);
    Couche couche = InitCouche(nb_neurones, nb_entrees);
    Entree* liste_entrees = remplirListeEntree(nb_entrees);
    ListeSortie* liste_sorties = OutCouche(couche, liste_entrees);
    printf("Sorties de la couche :\n");//just to check the answers
    ListeSortie* current_sortie = liste_sorties;
    while (current_sortie != NULL) {
        printf("%d ", current_sortie->data);
        current_sortie = current_sortie->suivant;
    }
    printf("\n");

 //create neurone "neurone_et"
    Neurone neurone_et;
    neurone_et.nb_entrees = nb_neurones;
    neurone_et.biais = nb_entrees;
    neurone_et.poids = remplirListePoidsVal1(nb_neurones);//utils function

    Listecouche* reseau = creer_reseau_avec_neurone(neurone_et);//put in network
    Entree* liste_entrees_converties = convertirListeSortieEnEntree(liste_sorties);//mandatory to be use in reseauET

    float resultat = reseauET(reseau, liste_entrees_converties);
    if (resultat != -1) {
        printf("Le résultat du réseau ET est : %.f\n", resultat);
    }

//free memory part

    Entree* temp_entree;
    while (liste_entrees != NULL) {
        temp_entree = liste_entrees->suivant;
        free(liste_entrees);
        liste_entrees = temp_entree;
    }

    ListeSortie* temp_sortie;
    while (liste_sorties != NULL) {
        temp_sortie = liste_sorties->suivant;
        free(liste_sorties);
        liste_sorties = temp_sortie;
    }

    NoeudNeurone* noeud_courant = reseau->couche->neurones;
    while (noeud_courant != NULL) {
        NoeudNeurone* temp_noeud = noeud_courant->suivant;
        free(noeud_courant->neurone.poids);
        free(noeud_courant);
        noeud_courant = temp_noeud;
    }

    free(reseau->couche);
    free(reseau);

    return 0;
}



// Test OR network(check)

int main() {
    
     int nb_neurones, nb_entrees;
    printf("Entrez le nombre de neurones dans la couche : ");
    scanf("%d", &nb_neurones);
    printf("Entrez le nombre d'entrées pour chaque neurone : ");
    scanf("%d", &nb_entrees);
    Couche couche = InitCouche(nb_neurones, nb_entrees);
    Entree* liste_entrees = remplirListeEntree(nb_entrees);
    ListeSortie* liste_sorties = OutCouche(couche, liste_entrees);
    printf("Sorties de la couche :\n");//just to check the answers

    ListeSortie* current_sortie = liste_sorties;
    while (current_sortie != NULL) {
        printf("%d ", current_sortie->data);
        current_sortie = current_sortie->suivant;
    }
    printf("\n");

 //create neurone "neurone_ou"
    Neurone neurone_ou;
    neurone_ou.nb_entrees = nb_neurones;
    neurone_ou.biais = 1;
    neurone_ou.poids = remplirListePoidsVal1(nb_neurones);//utils function

    Listecouche* reseau = creer_reseau_avec_neurone(neurone_ou);//put in network
    Entree* liste_entrees_converties = convertirListeSortieEnEntree(liste_sorties);//mandatory to be use in reseauOU

    float resultat = reseauOU(reseau, liste_entrees_converties);
    if (resultat != -1) {
        printf("Le résultat du réseau OU est : %.f\n", resultat);
    }

//free memory part

    Entree* temp_entree;
    while (liste_entrees != NULL) {
        temp_entree = liste_entrees->suivant;
        free(liste_entrees);
        liste_entrees = temp_entree;
    }

    ListeSortie* temp_sortie;
    while (liste_sorties != NULL) {
        temp_sortie = liste_sorties->suivant;
        free(liste_sorties);
        liste_sorties = temp_sortie;
    }

    NoeudNeurone* noeud_courant = reseau->couche->neurones;
    while (noeud_courant != NULL) {
        NoeudNeurone* temp_noeud = noeud_courant->suivant;
        free(noeud_courant->neurone.poids);
        free(noeud_courant);
        noeud_courant = temp_noeud;
    }

    free(reseau->couche);
    free(reseau);

    return 0;
}

//test NOT network (check)

int main() {

    int n;
    Entree* liste_entree = NULL;

    printf("Combien d'entrées pour le neurone? ");
    scanf("%d", &n);

    Neurone neurone = InitNeur(n); 
    liste_entree = remplirListeEntree(n); 

    float sortie = Outneurone(liste_entree, neurone);
    printf("Sortie du neurone : %f\n", sortie);

    Entree* listesortie = NULL;
    listesortie = (Entree*)malloc(sizeof(Entree));
        if (listesortie == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
    listesortie->data=sortie;
    listesortie->suivant=NULL;


    free(neurone.poids);

    //create neurone "neurone_not"
    int nb_neurones=1;
    Neurone neurone_not;
    neurone_not.nb_entrees = nb_neurones;
    neurone_not.biais = 0;
    neurone_not.poids = remplirListePoidsValnot1(nb_neurones);//utils function
    Listecouche* reseau = creer_reseau_avec_neurone(neurone_not);

     float resultat = reseauNOT(reseau,listesortie);

    if (resultat != -1) {
        printf("Le résultat du réseau NOT est : %.f\n", resultat);
    }

    //free part

     free(neurone_not.poids);
    free(reseau->couche->neurones);
    free(reseau->couche);
    free(reseau);
    free(listesortie);
    free(liste_entree);
    return 0;
}
*/
//test reseau

int main() {

    int nb_entrees=0, nb_neuronnes =1;
    printf("Combien d'entrées voulez-vous dans le réseau ? ");
    scanf("%d", &nb_entrees); 
     Entree* entrees = remplirListeEntree(nb_entrees);

    Listecouche* reseauA = (Listecouche*)malloc(sizeof(Listecouche));

    if (reseauA == NULL) {
        printf("Erreur d'allocation mémoire pour le réseau.\n");
        return -1;
    }
    reseauA->couche = (Couche*)malloc(sizeof(Couche));
    if (reseauA->couche == NULL) {
        printf("Erreur d'allocation mémoire pour la couche.\n");
        return -1;
    }
    printf("\ncouche du premier reseau\n");
    printf("combien de neuronne pour le premier reseau ?\n");
    scanf("%d",&nb_neuronnes);
    *reseauA->couche = InitCouche(nb_neuronnes, nb_entrees);


    Listecouche* reseauB = (Listecouche*)malloc(sizeof(Listecouche));

    if (reseauB == NULL) {
        printf("Erreur d'allocation mémoire pour le réseau.\n");
        return -1;
    }
    reseauB->couche = (Couche*)malloc(sizeof(Couche));
    if (reseauB->couche == NULL) {
        printf("Erreur d'allocation mémoire pour la couche.\n");
        return -1;
    }
    printf("\ncouche du deuxieme reseau \n");
    printf("combien de neuronne pour le deuxieme reseau ?\n");
    scanf("%d",&nb_neuronnes);
    *reseauB->couche = InitCouche(nb_neuronnes, nb_entrees);
    Listecouche* reseauC = (Listecouche*)malloc(sizeof(Listecouche));

    if (reseauC == NULL) {
        printf("Erreur d'allocation mémoire pour le réseau.\n");
        return -1;
    }
    reseauC->couche = (Couche*)malloc(sizeof(Couche));
    if (reseauC->couche == NULL) {
        printf("Erreur d'allocation mémoire pour la couche.\n");
        return -1;
    }
    printf("\ncouche du troisieme reseau \n");
    printf("combien de neuronne pour le troisieme reseau ?\n");
    scanf("%d",&nb_neuronnes);
    *reseauC->couche = InitCouche(nb_neuronnes, nb_entrees);

    float resultat = reseauMultiCouches(reseauA,reseauB,reseauC, entrees);

     if (resultat != -1) {
        printf("Le résultat du réseau Multicouches est : %.2f\n", resultat);
    }

    //free part

     Entree* temp;
    while (entrees != NULL) {
        temp = entrees;
        entrees = entrees->suivant;
        free(temp);
    }
    NoeudNeurone* noeud_courant1 = reseauA->couche->neurones;
    while (noeud_courant1 != NULL) {
        NoeudNeurone* temp = noeud_courant1;
        noeud_courant1 = noeud_courant1->suivant;
        free(temp->neurone.poids);
        free(temp);
    }
    free(reseauA->couche);
    free(reseauA);

     NoeudNeurone* noeud_courant2 = reseauB->couche->neurones;
    while (noeud_courant2 != NULL) {
        NoeudNeurone* temp = noeud_courant2;
        noeud_courant2 = noeud_courant2->suivant;
        free(temp->neurone.poids);
        free(temp);
    }
    free(reseauB->couche);
    free(reseauB);

 NoeudNeurone* noeud_courant3 = reseauC->couche->neurones;
    while (noeud_courant3 != NULL) {
        NoeudNeurone* temp = noeud_courant3;
        noeud_courant3 = noeud_courant3->suivant;
        free(temp->neurone.poids);
        free(temp);
    }
    free(reseauC->couche);
    free(reseauC);


    return 0;
}



