#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "readData.h"

#ifndef taxis_h
#define taxis_h

// Structure pour un taxi
typedef struct taxi{
    int id;
    int demande;	// Combien de temps avant de pouvoir prendre en compte une demande (0: taxi prêt, sinon il faut attente "demande" secondes)
} taxi;

/**
*	Fonction créant les taxis avec createTaxis et traitant les demande avec traitement
*
*	@param head première demande
*	@param nbTaxis nombre de taxis à utiliser
*/
void traiterDemandes(demande *head, int nbTaxis);

/**
*	Fonction créant le nombre nécessaire de taxis
*
*	@param head première demande
*	@param nbTaxis nombre de taxis à utiliser
*/
void createTaxis(taxi *taxis, int nbTaxis);

/**
*	Fonction traitant toutes les demandes.
*	La demande est attribué au premier taxi non occupé qu'on trouve.
*	Si tous les taxis sont occupés, on trouve le premier qui va être libre
*	et on lui attribue la nouvelle course.
*
*	@param head première demande
*	@param nbTaxis nombre de taxis à utiliser
*/
void traitement(demande *head, taxi *taxis, int nbTaxis);

#endif