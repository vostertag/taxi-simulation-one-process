#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef readData_h
#define readData_h

// Structure d'une demande
typedef struct demande{
    int id;
    int attente;			// temps d'attente en secondes
    int duree;				// duree de la course en secondes
    char client;			// nom du client
    struct demande  *next;	// demande suivante
} demande;

/**
*	Fonction ouvrant le fichier des demandes et faisant appel à createList pour créer
*	la liste de demandes
*
*	@param premiereDemande premiere demande (début de notre liste de demandes)
*/
void getDemandes(demande **premiereDemande);

/**
*	Fonction lisant un fichier de demandes et en ressortant toutes les infos utiles pour
*	créer une nouvelle demande et alimenter notre liste de demandes.
*
*	Le fichier .dat doit être de la forme : attente \n nom du client ;duree de la course
*
*	@param file fichier à lire
*	@param premiereDemande premiere demande (début de notre liste de demandes)
*/
void createList(FILE *file, demande **premiereDemande);

/**
*	Fonction permettant d'afficher la liste des demandes
*
*	@param headBase début de la liste
*/
void  printList(demande **headBase);

/**
*	Fonction permettant de supprimer la liste de demandes
*
*	@param headBase début de la liste
*/
void deleteList(demande **headBase);

#endif
