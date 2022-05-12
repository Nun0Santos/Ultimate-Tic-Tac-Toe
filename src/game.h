#include "globals.h"
#include "board.h"

#define BOT_GAME 1
#define TWO_PLAYERS 0

void game(int gameMode);
//void Plays();
int choosePlays(Board *board, Plays **plays, int jogador,char namePlayers[2][255], int nBoard, int *nBoardBefore, int *mode, int *section,int nPlays, int gameMode);
int botPlays(Board *board, Plays **plays, int jogador, int nBoard, int *nBoardBefore, int *mode, int *section, int nPlays);
void rules();
int menuGame(int nPlays);
void endGame(Board *board, Plays *plays);
void exportFile(Plays *plays, int nPlays);
void pause(Board *board,Plays *plays,int nPlays,int gameMode);