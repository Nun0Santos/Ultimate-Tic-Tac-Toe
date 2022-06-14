#ifndef BOARD_H
#define BOARD_H

#include "plays.h"

typedef struct Board{
    char **section;
}Board;

//All board related functions
Board *boardsInitializer();
void globalBoardInitializer(char board[3][3]);
void boardPrint(Board *board);
void globalBoardPrint(char board[3][3]);
int verifyWinner(Board *board, int nBoard);//secção
int verifyGlobalWinner(char board[3][3]);
int convertPosition(int position, int *x, int *y);//Play
int winnerSection(Board *board, int nBoard, char globalBoard[3][3], int jogador, char namePlayers[2][255]); //Mete um X ou O na posição 1 1 do board
void convertPositionBoard(int pos, int *x, int *y);//board
void checkDraw(char globalBoard[3][3], int nBoard); //Coloca um - no tabuleiro em caso de empate nesse tabuleiro

void freeBoards(Board *board);

#endif