#include "plays.h"

typedef struct Board{
    char **section;
}Board;

//Todas as funcoes referentes ao tabuleiro
Board *boardsInitializer();
void globalBoardInitializer(char board[3][3]);
void boardPrint(Board *board);
void globalBoardPrint(char board[3][3]);
int verifyWinner(Board *board, int nBoard);//secção
int verifyGlobalWinner(char board[3][3]);
int convertPosition(int position, int *x, int *y);
int winnerSection(Board *board, int nBoard, char globalBoard[3][3], int jogador, char namePlayers[2][255]);
void convertPositionBoard(int pos, int *x, int *y);
void freeBoards(Board *board);
