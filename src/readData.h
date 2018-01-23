#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef readData_h
#define readData_h

typedef struct demande{
    int id;
    int attente;
    int duree;
    char client;
    struct demande  *next;
} demande;

void getDemandes(demande **premiereDemande);

void createList(FILE *file, demande **premiereDemande);

void  printList(demande **headBase);

void deleteList(demande **headBase);

#endif
