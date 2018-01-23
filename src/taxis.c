#include "taxis.h"

void traiterDemandes(demande *head, int nbTaxi){
	taxi* taxis;
	createTaxis(taxis, nbTaxi);
	traitement(head, taxis, nbTaxi);
}

void createTaxis(taxi *taxis, int nbTaxi){
	taxis = malloc(nbTaxi * sizeof *taxis);

    for(int i=0; i<nbTaxi; i++){
        taxis[i].demande = 0;
        taxis[i].id = i;
    }
}

void getNewTimer(int* timer, int timerSansAttente, int attente, bool taxiTrouve){
	if(!taxiTrouve){
        if(timerSansAttente > *timer){
            *timer = timerSansAttente;
        }
    }else{
        *timer += attente;
    }
}

void getMinTaxi(int* min, taxi* taxiPrenantLaDemande, taxi *taxis, int duree, int nbTaxi){
	*min = taxis[0].demande;
    taxi* minTaxi = &taxis[0];
    for(int i=0; i<nbTaxi; i++){
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

	int timer = 0;
    int previousTimer = 0;
    int timerSansAttente = 0;
    int retard;
    bool taxiTrouve = true;
    int min;
    taxi minTaxi;
    taxi taxiPrenantLaDemande;


    while(head != NULL){
    	timerSansAttente += head->attente;
    	getNewTimer(&timer, timerSansAttente, head->attente, taxiTrouve);
        taxiTrouve = false;
        for(int i=0; i<nbTaxi; i++){

            if(taxis[i].demande == 0 && taxiTrouve == false){
                taxis[i].demande = head->duree;
                taxiTrouve = true;
                taxiPrenantLaDemande = taxis[i];
            }
            else if(taxis[i].demande > 0 && taxis[i].id != minTaxi.id){
                taxis[i].demande -= (timer - previousTimer);
                if(taxis[i].demande < 0){
                    taxis[i].demande = 0;
                }
            }
        }
        minTaxi.id = -1;
        previousTimer = timer;
        if(!taxiTrouve){
        	getMinTaxi(&min, &taxiPrenantLaDemande, taxis, head->duree, nbTaxi);
        	minTaxi = taxiPrenantLaDemande;
            timer += min;
        }

        retard = timer - timerSansAttente;
        printf("Timer = %d \nLa demande %d a été prise en charge par le taxi %d (retard = %d sec) \n", timer, head->id, taxiPrenantLaDemande.id, retard);
        
        head = head->next;
    }
}