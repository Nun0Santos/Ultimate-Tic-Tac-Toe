#include "plays.h"
#include "globals.h"


void showPlays(Plays **plays){
    //Shows contents of connected list

    int count=1;
    
    if(*plays == NULL){
        printf("Esta vazia\n");
    }
    while (plays != NULL){
        printf("struct : %d \nx=%d\ty=%d\n",count++,(*plays)->x,(*plays)->y);
        (*plays) = (*plays)->next;
    }
}
void addNodePlays(Plays **head,int board, int x, int y){
    Plays *aux;

    printf("Dentro do add x = %d y = %d\n",x,y);

    if(*head == NULL){
        *head = (Plays *)malloc(sizeof(Plays));
        if(*head == NULL){
            fprintf(stderr,"Error trying to allocate memory for head\n");
            exit(EXIT_FAILURE);
        }
        (*head)->x = x;
        (*head)->y = y;
        (*head)->Board = board;
        (*head)->next = NULL;
    }else{
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = (Plays *)malloc(sizeof(Plays));
        if(aux->next == NULL){
            removeList(*head);
            fprintf(stderr,"Error trying to allocate memory for node of list\n");
            exit(EXIT_FAILURE);
        }
        aux->next->x = x;
        aux->next->y = y;
        aux->next->Board = board;
        aux->next->next = NULL;
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
