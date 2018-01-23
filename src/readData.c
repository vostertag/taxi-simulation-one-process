#include "readData.h"
// Voir le header pour plus d'informations sur les fonctions

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

    // Il y a deux étapes : une pour trouver la demande, une pour les autres informations. Ce bool permet de savoir où on en est
    bool attente = true; 
    int id=0;
    printf("Demandes : \n");
    // Tant que le fichier n'a pas été lu en entier
    while(!feof(file)){
        // Si on est à l'étape où on doit chercher une attente
        if(attente){
            // Cela signifie qu'une nouvelle demande doit être créé
            currDemande = malloc(sizeof(struct demande));
            currDemande->id = id;
            fscanf(file, "%d ", &currDemande->attente); // Et que l'int qu'on trouvera sera son attente
            id++;
            attente = false;
        // Sinon, nous devons chercher le nom du client et la duree de la demande en cours    
        }else{
            fscanf(file, "%s ;%d", &currDemande->client, &currDemande->duree);
            attente = true;
            // Affichage de la demande trouvée
            printf("Attente = %d \t  Client = %s \t  Durée = %d \n", currDemande->attente, &currDemande->client, currDemande->duree);
        }
        // Permet d'alimenter la liste des demandes en ajoutant à la fin de la demande précédente la nouvelle...
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
    fin->next = NULL;   // la dernière demande n'a pas de demande suivante...
    *premiereDemande = premier; // début de la liste
}

void  printList(demande **headBase)
{
    demande *tmpNode = *headBase;

    // On parcourt la liste tant qu'il y a des demandes et affiche ce que l'on souhaite
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
        printf("<< Demande effacee: %d\n", tmp->id);
        free(tmp);
    }

    *headBase = head;
}