#include "neurone.h" 
Neurone InitNeur(int n) {

    Neurone neurone;
    neurone.nb_entrees = n;
    neurone.poids = remplirListePoids(n);//utils function
    printf("Entrez le biais du neurone : ");
    scanf("%d", &neurone.biais);
    return neurone;
}

float Outneurone(Entree* liste_entree, Neurone neurone) {
    if (liste_entree == NULL) {
        printf("Erreur : liste d'entrées est NULL.\n");
        return -1;  //error
    }
    if (neurone.poids == NULL) {
        printf("Erreur : poids du neurone sont NULL.\n");
        return -1;  //error
    }
    int somme = 0;
    Poids* current_poids = neurone.poids;
    Entree* current_entree = liste_entree;

    for (int i = 0; i < neurone.nb_entrees; i++) {

         if (current_poids == NULL || current_entree == NULL) {
            printf("Erreur : pointeur poids ou entrée manquant à l'index %d.\n", i);
            return -1;  // error
        }
        somme += current_poids->data * current_entree->data;// calculation
        current_poids = current_poids->suivant;
        current_entree = current_entree->suivant;
    }

    if (somme >= neurone.biais) { //check if the neuronne is on or off
        return 1;
    } else {
        return 0;
    }
}


//Part 2


Couche InitCouche(int nb_neurones, int nb_entrees) {
    Couche couche;
    couche.nb_neurones = nb_neurones;
    couche.neurones = NULL;
    NoeudNeurone* dernier = NULL;

    for (int i = 0; i < nb_neurones; i++) {
    printf("Neurrone %d\n", i+1);
        NoeudNeurone* nouveau = (NoeudNeurone*)malloc(sizeof(NoeudNeurone));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        nouveau->neurone = InitNeur(nb_entrees);//each elem are create with InitNeur
        nouveau->suivant = NULL;

        if (couche.neurones == NULL) { // if it's first elem, keep his adress
            couche.neurones = nouveau;
        } else {
            dernier->suivant = nouveau;
        }
        dernier = nouveau;//next elem
    
    }

    return couche; // return layer with all the elems
}



ListeSortie* OutCouche(Couche couche, Entree* liste_entrees) {
    ListeSortie* sortie_tete = NULL; //create list with all the output for each neurrones
    ListeSortie* sortie_precedente = NULL;

    NoeudNeurone* current_neurone = couche.neurones;

    while (current_neurone != NULL) {

        int sortie_neurone = Outneurone(liste_entrees, current_neurone->neurone);//each neurrone on the layer are test
        
        ListeSortie* nouvelle_sortie = (ListeSortie*)malloc(sizeof(ListeSortie));
        if (nouvelle_sortie == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        nouvelle_sortie->data = sortie_neurone;//1 or 0 link with the previous neurrone
        nouvelle_sortie->suivant = NULL;

        if (sortie_tete == NULL) {
            sortie_tete = nouvelle_sortie;// if it's first elem, keep the adress
        } else {
            sortie_precedente->suivant = nouvelle_sortie;
        }

        sortie_precedente = nouvelle_sortie;//keep to complete the "next" of the previous

        current_neurone = current_neurone->suivant;
    }

    return sortie_tete;// return the list
}

//Part 3
Listecouche* CreerResNeur(int nb_couches, nbCouches* liste_nbParCouches) {

    nbCouches* temp = liste_nbParCouches;// to move through the list
    Listecouche* couche_pre = NULL;
    Listecouche* couche_tete = NULL;

    int nb_entrees_initial;
    printf("Donnez le nombre d'entrées initiales : ");
    scanf("%d", &nb_entrees_initial);

    for (int i = 0; i < nb_couches; i++) {

        int nb_neurones = temp->data;

        Listecouche* Newcouche = (Listecouche*)malloc(sizeof(Listecouche));
        if (Newcouche == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        printf("Couche numéro %d\n", i+1);

        Couche nouvelle_couche = InitCouche(nb_neurones, nb_entrees_initial); //initcouche for each elem because each eleme are layers

        Newcouche->couche = (Couche*)malloc(sizeof(Couche));
        if (Newcouche->couche == NULL) {
            printf("Erreur d'allocation mémoire pour la couche\n");
            exit(1);
        }
        *(Newcouche->couche) = nouvelle_couche;

        Newcouche->suivant = NULL;

        if (couche_tete == NULL) { // the aim is to keep the adress for the first elem
            couche_tete = Newcouche;
        } else {
            couche_pre->suivant = Newcouche;
        }

        couche_pre = Newcouche;
        nb_entrees_initial = nb_neurones; 
        temp = temp->suivant;
    }

    return couche_tete; // return the adress from the first elem 
}
//Part 4

//network AND

float reseauET(Listecouche* reseau, Entree* entrees) {

    if (reseau == NULL || reseau->couche == NULL) { 
        printf("Erreur : réseau ou couche invalide.\n");
        return -1;
    }

    Couche* couche_principale = reseau->couche;
        
    if (couche_principale->nb_neurones != 1) {
    printf("Erreur : ce réseau contient %d neurones, mais la fonction ET nécessite exactement 1 neurone.\n", couche_principale->nb_neurones);
    return -1; 
}
NoeudNeurone* premier_neurone = couche_principale->neurones;
    
    // Vérification et initialisation du neurone
    Neurone* neurone_courant = &premier_neurone->neurone;
    if (neurone_courant->biais != neurone_courant->nb_entrees) {
        printf("Biais modifié pour être égal au nombre d'entrées (%d).\n", neurone_courant->nb_entrees);
        neurone_courant->biais = neurone_courant->nb_entrees; 
    }

    Poids* poids_courant = neurone_courant->poids;
    while (poids_courant != NULL) {
        if (poids_courant->data != 1) {
            printf("Poids différent de 1 détecté : réinitialisation à 1.\n");
            poids_courant->data = 1;
        }
        poids_courant = poids_courant->suivant;
    }

    float resultat = Outneurone(entrees, *(neurone_courant));  // Utilisation de *neurone_courant pour passer un Neurone
    
    return resultat;
}

float reseauOU(Listecouche* reseau, Entree* entrees) {

    if (reseau == NULL || reseau->couche == NULL) {
        printf("Erreur : réseau ou couche invalide.\n");
        return -1;
    }
    Couche* couche_principale = reseau->couche;
        
    if (couche_principale->nb_neurones != 1) {
        printf("Erreur : ce réseau contient %d neurones, mais la fonction OU nécessite exactement 1 neurone.\n", couche_principale->nb_neurones);
        return -1; 
    }

    NoeudNeurone* premier_neurone = couche_principale->neurones;
    Neurone* neurone_courant = &premier_neurone->neurone;

    if (neurone_courant->biais != 1) {
        printf("Biais modifié pour être égal à 1.\n");
        neurone_courant->biais = 1; 
    }

 Poids* poids_courant = neurone_courant->poids;

    while (poids_courant != NULL) {
        if (poids_courant->data != 1) {
            printf("Poids différent de 1 détecté : réinitialisation à 1.\n");
            poids_courant->data = 1;
        }
        poids_courant = poids_courant->suivant;
    }

    float resultat = Outneurone(entrees, *(neurone_courant));
    return resultat;
}

float reseauNOT(Listecouche* reseau, Entree* entrees) {

    //check all the datas 

    if (reseau == NULL || reseau->couche == NULL) {
        printf("Erreur : réseau ou couche invalide.\n");
        return -1;
    }

    Couche* couche_principale = reseau->couche;

    if (couche_principale->nb_neurones != 1) {
        printf("Erreur : ce réseau contient %d neurones, mais la fonction NOT nécessite exactement 1 neurone.\n", couche_principale->nb_neurones);
        return -1; 
    }

    NoeudNeurone* noeud_courant = couche_principale->neurones;

    if (noeud_courant == NULL) {
        printf("Erreur : aucun neurone dans la couche.\n");
        return -1;
    }

    Neurone* neurone_courant = &noeud_courant->neurone;

    if (neurone_courant->biais != 0) {
        printf("Biais modifié pour être égal à 0\n");
        neurone_courant->biais = 0; 
    }

    Poids* poids_courant = neurone_courant->poids;
    if (poids_courant == NULL) {
        printf("Erreur : aucun poids défini pour le neurone.\n");
        return -1;
    }

    if (poids_courant->data != -1) {
        printf("Poids différent de -1 détecté : réinitialisation à -1.\n");
        poids_courant->data = -1;
    }

    //calculation

    float resultat = Outneurone(entrees, *neurone_courant);
    return resultat;
}

float reseauMultiCouches(Listecouche* reseauA, Listecouche* reseauB, Listecouche* reseauC, Entree* entrees) {
   
    float sortie_A = Outneurone(entrees, reseauA->couche->neurones->neurone);
    if (sortie_A == -1) {
        printf("Erreur dans le calcul de la sortie A.\n");
        return -1;
    }
    printf("sortie_A: %f\n", sortie_A);

    float sortie_B = Outneurone(entrees, reseauB->couche->neurones->neurone);
    if (sortie_B == -1) {
        printf("Erreur dans le calcul de la sortie B.\n");
        return -1;
    }
    printf("sortie_B: %f\n", sortie_B);

    float sortie_C = Outneurone(entrees, reseauC->couche->neurones->neurone);
    if (sortie_C == -1) {
        printf("Erreur dans le calcul de la sortie C.\n");
        return -1;
    }
    printf("sortie_C: %f\n", sortie_C);

 int nb_neurones=1;
    Neurone neurone_not;
    neurone_not.nb_entrees = nb_neurones;
    neurone_not.biais = 0;
    neurone_not.poids = remplirListePoidsValnot1(nb_neurones);//utils function
    Listecouche* reseaunot = creer_reseau_avec_neurone(neurone_not);


    //mise en liste chainée des valeurs
    Entree* liste_B = NULL;
    liste_B = (Entree*)malloc(sizeof(Entree));
        if (liste_B == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
    liste_B->data=sortie_B;
    liste_B->suivant=NULL;

    Entree* liste_C = NULL;
    liste_C = (Entree*)malloc(sizeof(Entree));
        if (liste_C == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
    liste_C->data=sortie_C;
    liste_C->suivant=NULL;



    // Calcul de NOT B et NOT C

    float sortie_NOT_B = reseauNOT(reseaunot, liste_B);
    printf("sortie_NOT_B: %f\n", sortie_NOT_B);
    float sortie_NOT_C = reseauNOT(reseaunot, liste_C);
    printf("sortie_NOT_C: %f\n", sortie_NOT_C);

    // Calcul de la sortie du réseau A et du réseau C

  
    // Création du réseau ET1 avec 3 entrées

    
    Neurone neurone_et1;
    neurone_et1.nb_entrees = 3;
    neurone_et1.biais = 3;
    neurone_et1.poids = remplirListePoidsVal1(neurone_et1.nb_entrees);

   Listecouche* Reseau_ET1 = creer_reseau_avec_neurone(neurone_et1);

    // Vérifier si le réseau a été créé
    if (Reseau_ET1 == NULL) {
        printf("Erreur dans la création du réseau ET1\n");
        return -1;
    }

    // Création du réseau ET2 avec 2 entrées
    Neurone neurone_et2;
    neurone_et2.nb_entrees = 2;
    neurone_et2.biais = 2;
    neurone_et2.poids = remplirListePoidsVal1(neurone_et2.nb_entrees);

 Listecouche* Reseau_ET2 = creer_reseau_avec_neurone(neurone_et2);

    // Vérifier si le réseau a été créé
    if (Reseau_ET2 == NULL) {
        printf("Erreur dans la création du réseau ET2\n");
        return -1;
    }

    // Création des entrées pour le premier ET
    Entree* et_1 = (Entree*)malloc(sizeof(Entree));
if (et_1 == NULL) {
    printf("Erreur d'allocation mémoire pour et_1\n");
    return -1;
}
et_1->data = sortie_A;
et_1->suivant = NULL;

Entree* entree_not_B = (Entree*)malloc(sizeof(Entree));
if (entree_not_B == NULL) {
    printf("Erreur d'allocation mémoire pour entree_not_B\n");
    return -1;
}
entree_not_B->data = sortie_NOT_B;
entree_not_B->suivant = NULL;

Entree* entree_C = (Entree*)malloc(sizeof(Entree));
if (entree_C == NULL) {
    printf("Erreur d'allocation mémoire pour entree_C\n");
    return -1;
}
entree_C->data = sortie_C;
entree_C->suivant = NULL;

et_1->suivant = entree_not_B;
entree_not_B->suivant = entree_C;

    // Création des entrées pour le deuxième ET

  Entree* et_2 = (Entree*)malloc(sizeof(Entree));
if (et_2 == NULL) {
    printf("Erreur d'allocation mémoire pour et_2\n");
    return -1;
}
et_2->data = sortie_A;
et_2->suivant = NULL;

Entree* entree_not_C = (Entree*)malloc(sizeof(Entree));
if (entree_not_C == NULL) {
    printf("Erreur d'allocation mémoire pour entree_not_C\n");
    return -1;
}
entree_not_C->data = sortie_NOT_C;
entree_not_C->suivant = NULL;

et_2->suivant = entree_not_C;

    // Calcul des sorties des deux ET

    float sortie_et1 = reseauET(Reseau_ET1, et_1);
    if (sortie_et1 == -1) {
        printf("Erreur dans le calcul de la sortie du premier ET\n");
        return -1;
    }
    printf("sortie_et1: %f\n", sortie_et1);

    float sortie_et2 = reseauET(Reseau_ET2, et_2);
    if (sortie_et2 == -1) {
        printf("Erreur dans le calcul de la sortie du deuxième ET\n");
        return -1;
    }
    printf("sortie_et2: %f\n", sortie_et2);

    // Création du réseau OU avec 2 entrées
    int nb_neuronnes_ou=2;
    Neurone neurone_ou;
    neurone_ou.nb_entrees = nb_neuronnes_ou;
    neurone_ou.biais = 1;
    neurone_ou.poids = remplirListePoidsVal1(nb_neuronnes_ou);
    Listecouche* Reseau_OU = creer_reseau_avec_neurone(neurone_ou);

    // Vérifier si le réseau a été créé
    if (Reseau_OU == NULL) {
        printf("Erreur dans la création du réseau OU\n");
        return -1;
    }

    // Création des entrées pour le réseau OU
    Entree* Ou_tete = (Entree*)malloc(sizeof(Entree));
    if (Ou_tete == NULL) {
        printf("Erreur d'allocation mémoire pour Ou_tete\n");
        return -1;
    }
    Ou_tete->data = sortie_et1;
    Ou_tete->suivant = NULL;

    Entree* Ou_dernier = (Entree*)malloc(sizeof(Entree));
    if (Ou_dernier == NULL) {
        printf("Erreur d'allocation mémoire pour Ou_dernier\n");
        return -1;
    }
    Ou_dernier->data = sortie_et2;
    Ou_dernier->suivant = NULL;

    Ou_tete->suivant = Ou_dernier;


    // Retour de la sortie du réseau OU
    float result = reseauOU(Reseau_OU, Ou_tete);
    if (result == -1) {
        printf("Erreur dans le calcul de la sortie du réseau OU\n");
        return -1;
    }

    // Libération de la mémoire
    free(et_1);
    free(entree_not_B);
    free(entree_C);
    free(et_2);
    free(entree_not_C);
    free(Ou_tete);
    free(Ou_dernier);

    return result;
}
