#include "globals.h"
#include "board.h"


#define BOT_GAME 1
#define TWO_PLAYERS 0

void game(int gameMode);
void PLays();
int choosePlays(Board *board, Plays *plays, int jogador,char namePlayers[2][255], int nBoard, int *nBoardBefore, int *mode);
int botPlays(Board *board, pPlays plays, int jogador, int nBoard, int *nBoardBefore, int *mode);
void rules();
