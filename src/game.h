#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "board.h"
#include "file.h"
#include "header.h"

#define BOT_GAME 1
#define TWO_PLAYERS 0

#define RESUME_GAME 1
#define NEW_GAME 0

void game(int gameMode, bool resume);
//void Plays();
int choosePlays(Board *board, Plays **plays, int jogador,char namePlayers[2][255], int nBoard, int *nBoardBefore, int *mode, int *section,int nPlays, int gameMode);
int botPlays(Board *board, Plays **plays, int jogador, int nBoard, int *nBoardBefore, int *mode, int *section, int nPlays);
void rules();
void endGame(Board *board, Plays *plays);


#endif

