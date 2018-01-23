#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "readData.h"
#include "taxis.h"


int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("L'application nécessite un argument");
        exit(-1);
    }

    demande *head = NULL;

    int nbTaxi = atoi(argv[1]);

    if(nbTaxi > 0){
        getDemandes(&head);
        traiterDemandes(head, nbTaxi);    
    }else{
        printf("Le nombre de taxi doit être supérieur à 0 \n");
        exit(-1);
    }

    return 0;
}
