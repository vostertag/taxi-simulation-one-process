#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct demande{
    int id;
    int attente;
    int duree;
    char client;
    struct demande  *next;
} demande;

typedef struct taxi{
    int id;
    int demande;
} taxi;

void createList(FILE *file, demande **premiereDemande)
{
    demande *currDemande;
    demande *premier = *premiereDemande;
    demande *fin;

    bool attente = true;
    #define VFMT " %29[^ ,\n\t]"
    int id=0;

    while(!feof(file)){
        if(attente){
            currDemande = malloc(sizeof(struct demande));
            currDemande->id = id;
            fscanf(file, "%d ", &currDemande->attente);
            id++;
            attente = false;
        }else{
            fscanf(file, "%s ;%d", &currDemande->client, &currDemande->duree);
            attente = true;
        }
        if(NULL == premier)
        {
            premier = currDemande;
            fin = currDemande;
        }
        else
        {
            fin->next = currDemande;
            fin = currDemande;
        }
    }
    fin->next = NULL;
    *premiereDemande = premier;
}

void  printList(demande **headBase)
{
    demande *tmpNode = *headBase;

    while(tmpNode->next != NULL)
    {
        printf("%s-->", &tmpNode->client);
        tmpNode = tmpNode->next;
    }
    printf("%s \n", &tmpNode->client);
}

void deleteList(demande **headBase)
{
    demande *head = *headBase;
    demande *tmp;

    while(NULL != head)
    {
        tmp = head; // Get a temp pointer
        head = head->next; // Move head pointer
        tmp->next = NULL; // break the link
        printf("<< Deleted Node: %d\n", tmp->id);
        free(tmp);
    }

    // Store the head pointer back which should be NULL
    *headBase = head;
}

int main()
{
    FILE *file;
    file = fopen("mesq.dat", "r");
    demande *head = NULL;

    createList(file, &head);

    printList(&head);

    //deleteList(&head);

    fclose(file);

    int timer = 0;
    int previousTimer = 0;
    int nbTaxi = 3;
    taxi* taxis = malloc(nbTaxi * sizeof *taxis);

    for(int i=0; i<nbTaxi; i++){
        taxis[i].demande = 0;
        taxis[i].id = i;
    }
    bool taxiTrouve = true;
    int min;
    taxi* minTaxi;
    while(head != NULL){
        if(!taxiTrouve){
            if(previousTimer + head->attente > timer){
                timer = previousTimer + head->attente;
            }
        }else{
            timer += head->attente;
        }
        printf("Timer = %d duree = %d \n", timer, head->duree);
        
        taxiTrouve = false;
        for(int i=0; i<nbTaxi; i++){

            if(taxis[i].demande == 0 && taxiTrouve == false){
                taxis[i].demande = head->duree;
                taxiTrouve = true;
                printf("J'ai pris la commande %d \n", taxis[i].id);
            }
            if(taxis[i].demande > 0){
                taxis[i].demande -= (timer - previousTimer);
                if(taxis[i].demande < 0){
                    taxis[i].demande = 0;
                }
            }
            printf("Taxi %d demande = %d \n", taxis[i].id, taxis[i].demande);
        }
        previousTimer = timer;
        if(!taxiTrouve){
            min = taxis[0].demande;
            minTaxi = &taxis[0];
            for(int i=0; i<nbTaxi; i++){
                if(taxis[i].demande < min){
                    min = taxis[i].demande;
                    minTaxi = &taxis[i];
                }
            }
            timer += min;
            minTaxi->demande = head->duree;
            printf("J'ai pris la commande en retard %d à %d \n", minTaxi->id, timer);
        }
        
        head = head->next;
    }

    return 0;
}
