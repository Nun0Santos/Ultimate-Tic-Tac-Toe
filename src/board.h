#include "plays.h"

typedef struct Board{
    char **section;
}Board;

//Todas as funcoes referentes ao tabuleiro

Board *boardsInitializer();
void boardPrint(Board *board);
int verifyWinner(Board *board, int nBoard);
int choosePlays(Board *board, Plays *plays, int jogador, int nBoard);

void freeBoards(Board *board);
