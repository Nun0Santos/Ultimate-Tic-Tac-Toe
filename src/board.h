#include "plays.h"

typedef struct Board{
    char **section;
}Board;

//Todas as funcoes referentes ao tabuleiro
Board *boardsInitializer();
void boardPrint(Board *board);
//int verifyWinner(Board *board, int nBoard);
int convertPosition(int position, int *x, int *y);
void winnerSection(Board *board, int nBoard,int jogador);
void freeBoards(Board *board);
int linha(Board *board, int nBoard);
int coluna(Board *board, int nBoard);
int diag(Board *board, int nBoard);