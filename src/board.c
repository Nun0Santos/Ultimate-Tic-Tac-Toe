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
    for(int i = 0; i < 9; ++i){
        board[i].section = malloc(sizeof(char *) * 3); //linhas
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
    int i,j;
    for(int k = 0; k < 9; ++k)
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
                board[k].section[i][j] = '_';

    return board;
}

void boardPrint(Board *board){
   printf("\n\n      C0       C1     C2");
   printf("\n  +------------------------+\n");

   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[0].section[0][0], board[0].section[0][1], board[0].section[0][2],
   board[1].section[0][0],board[1].section[0][1], board[1].section[0][2],
   board[2].section[0][0],board[2].section[0][1],board[2].section[0][2]);
   printf("L0| %c %c %c  | %c %c %c | %c %c %c |\n",board[0].section[1][0], board[0].section[1][1], board[0].section[1][2],
   board[1].section[1][0],board[1].section[1][1], board[1].section[1][2],
   board[2].section[1][0],board[2].section[1][1],board[2].section[1][2]); 
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[0].section[2][0], board[0].section[2][1], board[0].section[2][2],
   board[1].section[2][0],board[1].section[2][1], board[1].section[2][2],
   board[2].section[2][0],board[2].section[2][1],board[2].section[2][2]); 
   printf("  |--------+-------+-------|\n");
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[3].section[0][0], board[3].section[0][1], board[3].section[0][2],
   board[4].section[0][0],board[4].section[0][1], board[4].section[0][2],
   board[5].section[0][0],board[5].section[0][1],board[5].section[0][2]);
   printf("L1| %c %c %c  | %c %c %c | %c %c %c |\n",board[3].section[1][0], board[3].section[1][1], board[3].section[1][2],
   board[4].section[1][0],board[4].section[1][1], board[4].section[1][2],
   board[5].section[1][0],board[5].section[1][1],board[5].section[1][2]); 
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[3].section[2][0], board[3].section[2][1], board[3].section[2][2],
   board[4].section[2][0],board[4].section[2][1], board[4].section[2][2],
   board[5].section[2][0],board[5].section[2][1],board[5].section[2][2]); 
   printf("  |--------+-------+-------|\n");
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[6].section[0][0], board[6].section[0][1], board[6].section[0][2],
   board[7].section[0][0],board[7].section[0][1], board[7].section[0][2],
   board[8].section[0][0],board[8].section[0][1],board[8].section[0][2]);
   printf("L2| %c %c %c  | %c %c %c | %c %c %c |\n",board[6].section[1][0], board[6].section[1][1], board[6].section[1][2],
   board[7].section[1][0],board[7].section[1][1], board[7].section[1][2],
   board[8].section[1][0],board[8].section[1][1],board[8].section[1][2]); 
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[6].section[2][0], board[6].section[2][1], board[6].section[2][2],
   board[7].section[2][0],board[7].section[2][1], board[7].section[2][2],
   board[8].section[2][0],board[8].section[2][1],board[8].section[2][2]); 
   printf("  +------------------------+\n");
}

void verifyWinner(Board board){
    

}
void freeBoards(Board *board){
    for(int i = 0; i < 10; i++){
        free(board[i].section);
    }
    free(board);
}

void choosePlays(Board *board, int jogador){

}

