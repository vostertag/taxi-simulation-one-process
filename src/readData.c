#include "readData.h"

void getDemandes(demande **premiereDemande){
	FILE *file;
    file = fopen("data/mesq.dat", "r");
    createList(file, premiereDemande);
    fclose(file);
    printf("\n \n \n");
}

void createList(FILE *file, demande **premiereDemande)
{
    demande *currDemande;
    demande *premier = *premiereDemande;
    demande *fin;

    bool attente = true;
    int id=0;
    printf("Demandes : \n");
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
            printf("Attente = %d \t  Client = %s \t  Durée = %d \n", currDemande->attente, &currDemande->client, currDemande->duree);
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
        tmp = head; 
        head = head->next; 
        tmp->next = NULL; 
        printf("<< Deleted Node: %d\n", tmp->id);
        free(tmp);
    }

    *headBase = head;
}