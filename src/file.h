#ifndef FILE_H
#define FILE_H

#include "board.h"
#include "globals.h"
#include "game.h"

void pause(Board *board,Plays *plays,int nPlays,int gameMode,char namePlayers[2][255],int joga, int nBoardBefore,int *completedBoards, int howManyBoards); //Guardar no ficheiro bináro
void exportFile(Plays *plays, int nPlays); //Guarda jogadas num ficheiro de texto no final do jogo
Plays *loadFich(Board *board,char *nameFile,char namePlayers[2][255], int *nBoard,int *nPlays,int *joga, int *nBoardBefore,int *completedBoards, int *itLoad,char globalBoard[3][3]); //Carregar do ficheiro binário (constrói o board e a lista)

#endif
