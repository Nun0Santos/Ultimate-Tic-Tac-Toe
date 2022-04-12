#include "board.h"
#include "globals.h"
#include "matdin.h"

Board *boardsInitializer(){
    Board *board;
    
    board = malloc(sizeof(Board) * 9); //Principal
    if(board == NULL){
       printf("Error trying to allocate memory for global board\n");
       exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 3; ++i){
        board[i].section = malloc(sizeof(char) * 3); //linhas
        if(board[i].section == NULL){
            fprintf(stderr, "Error trying to allocate memory for section of Board [%d]\n",i);
            //libertar
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 3; j++){
            board[i].section[j] = malloc(sizeof(char) * 3); //colunas
            if (board[i].section[j] == NULL){
                fprintf(stderr, "Error trying to allocate memory for section[%d] of Board [%d]\n",j,i);
                //libertar
                exit(EXIT_FAILURE);
            }
        }
    }
    return board;
}

void boardPrint(Board *board){
   int i=0,j=0;

    putchar('\n');
    printf("  ");

    for(i=0;i<3;i++)
        printf("  C%d ",i);
    putchar('\n');

    printf("   ");
    for(i=0;i<3;i++)
        if(i!=2)
            printf("----");
        else 
            printf("------");
    putchar('\n');

        for(i=0;i<3;i++){
            printf("L%d|",i);
            for(j=0;j<2;j++){
                printf(" %c   |",board->section[i][j]);
            }
            printf(" %c   |\n",board->section[i][j]);

            if(i!=2){
                printf("  |");
                for(j=0;j<2;j++)
                    printf("----|");
                printf("----|\n");
            }
        }
    printf("   ");
    for(i=0;i<3;i++)
        if(i!=1)
            printf("----");
        else 
            printf("------");
    putchar('\n');
}

void verifyWinner(Board board){
    

}
void freeBoards(Board *board){
    for(int i = 0; i < 10; i++){
        free(board[i].section);
    }
    free(board);
}
