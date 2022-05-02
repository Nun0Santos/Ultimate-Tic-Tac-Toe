#include "plays.h"
#include "globals.h"


void showPlays(Plays *plays){
    //Shows contents of connected list
    Plays *aux = plays;
    int count=1;
    
    if(aux == NULL){
        printf("Empty list\n");
    }
    while (aux != NULL){
        printf("Node: %d \nx=%d\ty=%d\tBoard: %d\tPlays: %d\tPlayer : %d\n",count++,aux->x,aux->y,aux->Board,aux->nPlays,aux->nPlays%2 +1);
        aux = aux->next;
    }
}
void addNodePlays(Plays **head,int board, int x, int y, int nPlays){
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
        (*head)->nPlays = nPlays;
        (*head)->next = NULL;
    }else{
        while(aux->next != NULL){
            aux = aux->next;// saber a posicao onde alocar
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
        aux->nPlays = nPlays;
        aux->next = NULL;
    }
}

void removeList(Plays *head){
    Plays *aux = head;

    while(aux){
        head = aux;
        aux = aux -> next;
        free(head);
    }
}

void  showKPlays(Plays *plays, int k,int nPlays){
    //Shows contents of connected list
    Plays *aux = plays;
    int count=1;
    puts("\n");
    if(aux == NULL){
        printf("Empty list\n");
    }
    if(nPlays == k || nPlays > k){
        for(int i=0; i<k; ++i){
            printf("Player %d made the move (%d,%d) on Board [%d]\n",aux->nPlays%2 +1,aux->x,aux->y,aux->Board);
            aux = aux->next;  
        }
    }
    else{
        printf("There are not enough plays\n");
    }
    
}
