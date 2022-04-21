#include "plays.h"
#include "globals.h"


void showPlays(pPlays plays){
    //Shows contents of connected list
    int count=1;
    
    if(plays == NULL){
        printf("Esta vazia\n");
    }
    while (plays != NULL){
        printf("struct : %d \nx=%d, y=%d\n",count++,(*plays).x,(*plays).y);
        plays = plays->prox;
    }
}
pPlays addNodePlays(pPlays plays,int board, int x, int y){
    pPlays new;

    printf("Dentro do add x = %d y = %d\n",x,y);
    
    if((new = malloc(sizeof(Plays))) == NULL)
        printf("Erro na alocacao de memoria\n");

    else{
        new->x = x;
        new->y = y;
        new->Board = board;
        new->prox = plays;
        plays = new;
    }
    return plays;

}