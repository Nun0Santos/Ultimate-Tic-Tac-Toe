#include "plays.h"
#include "globals.h"


void showPlays(Plays *plays){
    //Shows contents of connected list
    Plays *aux = plays;
    int count=1;
    
    if(aux == NULL)
        printf("Empty list\n");

    while (aux != NULL){
        printf("Node: %d \nx=%d\ty=%d\tBoard: %d\tPlays: %d\tPlayer: %d\n",count++,aux->x,aux->y,aux->Board,aux->nPlays,aux->player);
        aux = aux->next;
    }
}

void addNodePlays(Plays **head,int board, int x, int y, int nPlays, int player){
    Plays *aux = *head;

    if(*head == NULL){
        *head = (Plays *)malloc(sizeof(Plays));
        if(*head == NULL){
            fprintf(stderr,"Error trying to allocate memory for head\n");
            exit(EXIT_FAILURE);
        }
        (*head)->x = x;
        (*head)->y = y;
        (*head)->Board = board;
        (*head)->player = player;
        (*head)->nPlays = nPlays;
        (*head)->next = NULL;
    }else{
        while(aux->next != NULL){
            aux = aux->next;//Para ir até à última posição da lista
        }
        aux->next = (Plays *)malloc(sizeof(Plays));
        if(aux->next == NULL){
            removeList(*head);
            fprintf(stderr,"Error trying to allocate memory for node of list\n");
            exit(EXIT_FAILURE);
        }
        aux = aux->next;
        aux->x = x;
        aux->y = y;
        aux->Board = board;
        aux->player = player;
        aux->nPlays = nPlays;
        aux->next = NULL;
    }
}

void removeList(Plays *head){
    Plays *aux;

    while(head != NULL){
        aux = head;
        head = head -> next;
        free(aux);
    }
}

void  showKPlays(Plays *plays, int k,int nPlays, int *cont){
    //Shows contents of connected list
    Plays *aux = plays;
  
    if(aux == NULL)
        return;
    
    showKPlays(aux->next,k,nPlays,cont);
    (*cont)++;

    if(k>=*cont && *cont <=10){
        printf("Player %d made the move (%d,%d) on Board [%d]\n",aux->player,aux->x,aux->y,aux->Board);            
       
    }
    /*if(nPlays == k || nPlays > k){
        for(int i=0; i<k; ++i){
            printf("Player %d made the move (%d,%d) on Board [%d]\n",count%2 +1,aux->x,aux->y,aux->Board);
            aux = aux->next;  
            ++count;
        }   
    }
    else{
        printf("There are not enough plays\n");
    }*/  
}
