#include "neurone.h"

// Prototypes des fonctions
void creerNeurone();
void creerCouche();
void creerReseau();
void testerReseauxLogiques();
void testerReseauMultiCouches();
void afficherMenu();

int main() {
    int choix;

    do {
        afficherMenu();
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creerNeurone();
                break;
            case 2:
                creerCouche();
                break;
            case 3:
                creerReseau();
                break;
            case 4:
                testerReseauxLogiques();
                break;
            case 5:
                testerReseauMultiCouches();
                break;
            case 0:
                printf("Quitter le programme. Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 0);

    return 0;
}

void afficherMenu() {
    printf("\n=== Menu Principal ===\n");
    printf("1. Crer un Neurone\n");
    printf("2. Creer une Couche\n");
    printf("3. Creer un Reseau de Neurones\n");
    printf("4. Tester les Reseaux Logiques (ET, OU, NOT)\n");
    printf("5. Tester un Reseau Multi-Couches\n");
    printf("0. Quitter\n");
}

void creerNeurone() {
    printf("\n=== Creation d'un Neurone ===\n");

    int n;
    printf("Combien d'entrees pour le neurone ? ");
    scanf("%d", &n);

    Neurone neurone = InitNeur(n);

    Entree* liste_entree = remplirListeEntree(n);
    int sortie = Outneurone(liste_entree, neurone);
    printf("Sortie du neurone : %d\n", sortie);

    libererListePoids(neurone.poids);
    while (liste_entree != NULL) {
        Entree* temp = liste_entree->suivant;
        free(liste_entree);
        liste_entree = temp;
    }
}

void creerCouche() {
    printf("\n=== Creation d'une Couche ===\n");

    int nb_neurones, nb_entrees;
    printf("Entrez le nombre de neurones dans la couche : ");
    scanf("%d", &nb_neurones);
    printf("Entrez le nombre d'entrees pour chaque neurone : ");
    scanf("%d", &nb_entrees);

    Couche couche = InitCouche(nb_neurones, nb_entrees);
    Entree* liste_entrees = remplirListeEntree(nb_entrees);
    ListeSortie* liste_sorties = OutCouche(couche, liste_entrees);

    printf("Sorties de la couche :\n");
    ListeSortie* current = liste_sorties;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->suivant;
    }
    printf("\n");

    // Libération mémoire
    while (liste_entrees != NULL) {
        Entree* temp = liste_entrees->suivant;
        free(liste_entrees);
        liste_entrees = temp;
    }
    while (liste_sorties != NULL) {
        ListeSortie* temp = liste_sorties->suivant;
        free(liste_sorties);
        liste_sorties = temp;
    }

    NoeudNeurone* current_neurone = couche.neurones;
    while (current_neurone != NULL) {
        NoeudNeurone* temp = current_neurone->suivant;
        libererListePoids(current_neurone->neurone.poids);
        free(current_neurone);
        current_neurone = temp;
    }
}

void creerReseau() {
    printf("\n=== Creation d'un Reseau de Neurones ===\n");

    nbCouches* liste_tailles = CreerListeTailles();
    int nb_couches = 0;
    nbCouches* temp = liste_tailles;

    while (temp != NULL) {
        nb_couches++;
        temp = temp->suivant;
    }

    Listecouche* reseau = CreerResNeur(nb_couches, liste_tailles);
    printf("Réseau de neurones créé :\n");
    afficherReseau(reseau);

    // Libération mémoire
    Listecouche* current_couche = reseau;
    while (current_couche != NULL) {
        Listecouche* temp_couche = current_couche->suivant;
        NoeudNeurone* current_neurone = current_couche->couche->neurones;

        while (current_neurone != NULL) {
            NoeudNeurone* temp_neurone = current_neurone->suivant;
            libererListePoids(current_neurone->neurone.poids);
            free(current_neurone);
            current_neurone = temp_neurone;
        }

        free(current_couche->couche);
        free(current_couche);
        current_couche = temp_couche;
    }
}

void testerReseauxLogiques() {
    printf("\n=== Tests des Reseaux Logiques ===\n");
    printf("Choisissez un reseau à tester :\n");
    printf("1. Reseau AND\n2. Reseau OR\n3. Reseau NOT\n");
    int choix;
    scanf("%d", &choix);

    switch (choix) {
        case 1: {
            printf("Test Reseau AND\n");
            int n;
            printf("Combien d'entrees pour le reseau AND ? ");
            scanf("%d", &n);

            Entree* entrees = remplirListeEntree(n);
            Neurone neurone_et = {remplirListePoidsVal1(n), n, n};
            Listecouche* reseau = creer_reseau_avec_neurone(neurone_et);

            float resultat = reseauET(reseau, entrees);
            printf("Resultat Reseau AND : %.0f\n", resultat);

            libererListePoids(neurone_et.poids);
            free(reseau->couche->neurones);
            free(reseau->couche);
            free(reseau);
            break;
        }
        case 2: {
            printf("Test Reseau OR\n");
            int n;
            printf("Combien d'entrees pour le reseau OR ? ");
            scanf("%d", &n);

            Entree* entrees = remplirListeEntree(n);
            Neurone neurone_ou = {remplirListePoidsVal1(n), 1, n};
            Listecouche* reseau = creer_reseau_avec_neurone(neurone_ou);

            float resultat = reseauOU(reseau, entrees);
            printf("Resultat Reseau OR : %.0f\n", resultat);

            libererListePoids(neurone_ou.poids);
            free(reseau->couche->neurones);
            free(reseau->couche);
            free(reseau);
            break;
        }
        case 3: {
            printf("Test Reseau NOT\n");
            float entree;
            printf("Entrez une valeur pour le reseau NOT (0 ou 1) : ");
            scanf("%f", &entree);

            Entree* liste_entree = (Entree*)malloc(sizeof(Entree));
            liste_entree->data = entree;
            liste_entree->suivant = NULL;

            Neurone neurone_not = {remplirListePoidsValnot1(1), 0, 1};
            Listecouche* reseau = creer_reseau_avec_neurone(neurone_not);

            float resultat = reseauNOT(reseau, liste_entree);
            printf("Resultat Réseau NOT : %.0f\n", resultat);

            libererListePoids(neurone_not.poids);
            free(reseau->couche->neurones);
            free(reseau->couche);
            free(reseau);
            free(liste_entree);
            break;
        }
        default:
            printf("Choix invalide.\n");
    }
}

void testerReseauMultiCouches() {
    printf("\n=== Test d'un Reseau Multi-Couches ===\n");

    int nb_entrees, nb_neurones;
    printf("Combien d'entrees voulez-vous dans le reseau ? ");
    scanf("%d", &nb_entrees);
    Entree* entrees = remplirListeEntree(nb_entrees);

    // Création des trois réseaux
    Listecouche* reseauA = (Listecouche*)malloc(sizeof(Listecouche));
    Listecouche* reseauB = (Listecouche*)malloc(sizeof(Listecouche));
    Listecouche* reseauC = (Listecouche*)malloc(sizeof(Listecouche));

    if (reseauA == NULL || reseauB == NULL || reseauC == NULL) {
        printf("Erreur d'allocation memoire pour les reseaux.\n");
        return;
    }

    printf("\n=== Réseau A ===\n");
    printf("Combien de neurones pour le reseau A ? ");
    scanf("%d", &nb_neurones);
    reseauA->couche = (Couche*)malloc(sizeof(Couche));
    *reseauA->couche = InitCouche(nb_neurones, nb_entrees);

    printf("\n=== Réseau B ===\n");
    printf("Combien de neurones pour le reseau B ? ");
    scanf("%d", &nb_neurones);
    reseauB->couche = (Couche*)malloc(sizeof(Couche));
    *reseauB->couche = InitCouche(nb_neurones, nb_entrees);

    printf("\n=== Réseau C ===\n");
    printf("Combien de neurones pour le reseau C ? ");
    scanf("%d", &nb_neurones);
    reseauC->couche = (Couche*)malloc(sizeof(Couche));
    *reseauC->couche = InitCouche(nb_neurones, nb_entrees);

    float resultat = reseauMultiCouches(reseauA, reseauB, reseauC, entrees);
    if (resultat != -1) {
        printf("Le resultat du reseau Multi-Couches est : %.2f\n", resultat);
    }

    // Libération mémoire
    Entree* temp;
    while (entrees != NULL) {
        temp = entrees;
        entrees = entrees->suivant;
        free(temp);
    }

    NoeudNeurone* noeud_courant;
    Listecouche* reseaux[] = {reseauA, reseauB, reseauC}; // Tableau des réseaux
    for (int i = 0; i < 3; i++) {
        Listecouche* reseau = reseaux[i];
        NoeudNeurone* noeud_courant = reseau->couche->neurones;

        while (noeud_courant != NULL) {
            NoeudNeurone* temp_noeud = noeud_courant->suivant;
            libererListePoids(noeud_courant->neurone.poids);
            free(noeud_courant);
            noeud_courant = temp_noeud;
        }

        free(reseau->couche);
        free(reseau);
    }

}
