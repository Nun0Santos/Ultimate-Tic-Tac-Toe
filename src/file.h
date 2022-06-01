#ifndef FILE_H
#define FILE_H

#include "board.h"
#include "globals.h"
#include "game.h"

void pause(Board *board,Plays *plays,int nPlays,int gameMode,char namePlayers[2][255],int joga, int nBoardBefore,int *completedBoards, int howManyBoards);
void exportFile(Plays *plays, int nPlays);
Plays *loadFich(Board *board,char *nameFile,char namePlayers[2][255], int *nBoard,int *nPlays,int *joga, int *nBoardBefore,int *completedBoards, int *itLoad);


#endif
