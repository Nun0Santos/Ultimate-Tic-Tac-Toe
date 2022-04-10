#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Board{
    int jogadador;
    char internalBoard[9][3][3]; //9 mini-tabuleiros
    char externalBoard[3][3];
}Board;

typedef struct Plays{
    int x;
    int y;
    int board;
    struct Plays *prox;
}Plays;