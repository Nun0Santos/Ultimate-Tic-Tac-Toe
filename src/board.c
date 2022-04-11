#include "board.h"
#include "globals.h"
#include "matdin.h"

Board *boardsInitializer(){
    Board *board;
    board = criaMat(3,3);

    return board;
}
void boardPrint(int lin, int col, Board board[][col]){
    int i,j,aux;
    //int lin=3, col=3;

    printf("    ");
    for(i=0; i<col; ++i)
        if(i+1!=col)
            printf("----");
        else
            printf("-----");
        putchar('\n');
        
    for(i=0; i<lin; ++i){
        printf("  %d ",i+1);
        putchar('|'); 
        for(j=0; j<col; ++j)
            printf(" %c %c",board.squares[i][j],'|');
            printf("\n    ");
        for(aux=0; aux<col; ++aux)
            if(aux+1!=col)
                printf("----");
            else
                printf("-----");
        putchar('\n');
    }
    printf("      ");
    for(i=0; i<col; ++i)
        printf("%d   ",i+1);

}


void freeBoards(Board *board){
    for(int i = 0; i < 10; i++){
        free(board[i].squares);
    }
    free(board);
}
