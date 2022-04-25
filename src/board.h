#include "plays.h"

typedef struct Board{
    char **section;
}Board;

//Todas as funcoes referentes ao tabuleiro
Board *boardsInitializer();
void boardPrint(Board *board);
int verifyWinner(char board[3][3]);
int convertPosition(int position, int *x, int *y);
int winnerSection(Board *board, int nBoard, char globalBoard[3][3], int jogador, char namePlayers[2][255]);
void freeBoards(Board *board);
int linha(Board *board, int nBoard);
int coluna(Board *board, int nBoard);
int diag(Board *board, int nBoard);
void convertPositionBoard(int pos, int *x, int *y);
void globalBoardPrint(char board[3][3]);
void globalBoardInitializer(char board[3][3]);