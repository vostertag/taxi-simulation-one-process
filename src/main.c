#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "readData.h"
#include "taxis.h"


int main(int argc, char *argv[])
{
    // L'application ne prendra qu'un argument : le nombre de taxi
    if(argc != 2){
        printf("L'application nécessite un argument");
        exit(-1);
    }

    // Début de la queue
    demande *head = NULL;

    // Nombre de taxis à utiliser
    int nbTaxi = atoi(argv[1]);

    // Le nombre de taxi doit être supérieur à 0
    if(nbTaxi > 0){
        getDemandes(&head);             // On récupère les demandes dans le fichier msgq.dat 
        traiterDemandes(head, nbTaxi);  // On traite ces demandes
    }else{
        printf("Le nombre de taxi doit être supérieur à 0 \n");
        exit(-1);
    }

    return 0;
}
