#include "taxis.h"
// Plus d'informations sur les fonctions dans le header

void traiterDemandes(demande *head, int nbTaxi){
	taxi* taxis;
	createTaxis(taxis, nbTaxi);
	traitement(head, taxis, nbTaxi);
}

void createTaxis(taxi *taxis, int nbTaxi){
	taxis = malloc(nbTaxi * sizeof *taxis);
    //Création du bon nombre de taxis
    for(int i=0; i<nbTaxi; i++){
        taxis[i].demande = 0;   // A la base, tous les taxis sont prêts à recevoir des demandes
        taxis[i].id = i;
    }
}

// Fonction auxiliaire pour trouver si le temps qu'un taxi soit libre est plus long que le temps d'attente normal
// Puis mise à jour du timer en fonction de cela.
void getNewTimer(int* timer, int timerSansAttente, int attente, bool taxiTrouve){
	if(!taxiTrouve){
        if(timerSansAttente > *timer){
            *timer = timerSansAttente;
        }
    }else{
        *timer += attente;
    }
}

// Fonction auxiliaire permettant de trouver le taxi qui sera libre en premier
void getMinTaxi(int* min, taxi* taxiPrenantLaDemande, taxi *taxis, int duree, int nbTaxi){
	*min = taxis[0].demande;
    taxi* minTaxi = &taxis[0];
    // on parcourt les taxis
    for(int i=0; i<nbTaxi; i++){
        // Si le temps d'attente est inférieur à celui stocké, ce taxi est le minimum
        if(taxis[i].demande < *min){
            *min = taxis[i].demande;
            minTaxi = &taxis[i];
        }
    }
    minTaxi->demande = duree;
    *taxiPrenantLaDemande = *minTaxi;
}

void traitement(demande *head, taxi *taxis, int nbTaxi){
	printf("Début du traitement \n");

	int timer = 0;                 // Timer
    int previousTimer = 0;         // Timer de l'étape précédente
    int timerSansAttente = 0;      // Timer s'il n'avait jamais fallu attendre un seul taxi (pour connaître le retard)
    int retard;                    // Retard (sera égal à timer - timerSansAttendre)
    bool taxiTrouve = true;        // Nous indiquera si un taxi est disponible ou non
    int min;                       // Temps minimum à attendre avant qu'un futur taxi soit disponible
    taxi minTaxi;                  // Taxi à nouveau disponible le plus rapidement 
    taxi taxiPrenantLaDemande;     // Taxi qui prend la demande en cours


    // Tant qu'on a pas fait toutes les demandes...
    while(head != NULL){
        // Update du timer
        timerSansAttente += head->attente;
    	getNewTimer(&timer, timerSansAttente, head->attente, taxiTrouve);
        taxiTrouve = false;
        // On parcourt les taxis
        for(int i=0; i<nbTaxi; i++){

            // Si aucun taxi n'a pris la demande et que ce taxi est disponible, il prendra cette demande
            if(taxis[i].demande == 0 && taxiTrouve == false){
                taxis[i].demande = head->duree;
                taxiTrouve = true;
                taxiPrenantLaDemande = taxis[i];
            }
            // Sinon on update son temps d'indisponibilités en fonction du temps qui s'est écoulé entre 2 étapes
            // Si le taxi précédent a pris la commande précédente avec du retard, il ne faut pas mettre à jour son
            // temps d'indisponibilité vu que 0 secondes se sont écoulés pour lui
            else if(taxis[i].demande > 0 && taxis[i].id != minTaxi.id){
                taxis[i].demande -= (timer - previousTimer);
                if(taxis[i].demande < 0){
                    taxis[i].demande = 0;   // Le temps d'attente ne peut pas être négatif...
                }
            }
        }
        minTaxi.id = -1;
        previousTimer = timer;
        // Si aucun taxi trouvé, on cherche celui qui sera le plus rapidement disponible
        if(!taxiTrouve){
        	getMinTaxi(&min, &taxiPrenantLaDemande, taxis, head->duree, nbTaxi);
        	minTaxi = taxiPrenantLaDemande;
            timer += min;
        }

        retard = timer - timerSansAttente;
        
        // Affichage du taxi qui prend la commande actuelle
        printf("Timer = %d \nLa demande %d a été prise en charge par le taxi %d (retard = %d sec) \n", timer, head->id, taxiPrenantLaDemande.id, retard);
        
        head = head->next;
    }
}