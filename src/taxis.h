#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "readData.h"

#ifndef taxis_h
#define taxis_h

typedef struct taxi{
    int id;
    int demande;
} taxi;

void traiterDemandes(demande *head, int nbTaxis);

void createTaxis(taxi *taxis, int nbTaxis);

void traitement(demande *head, taxi *taxis, int nbTaxis);

#endif