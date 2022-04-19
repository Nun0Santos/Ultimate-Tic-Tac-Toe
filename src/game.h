#include "globals.h"
#include "board.h"


#define BOT_GAME 1
#define TWO_PLAYERS 0

void game(int gameMode);
void PLays();
int choosePlays(Board *board, Plays *plays, int jogador, int nBoard, int *mode);
int botPlays(Board *board, pPlays plays, int jogador, int nBoard, int *mode);

void rules();
