#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TWO_PLAYER_GAME 0 
#define NEW_GAME 0

typedef struct Board{
    int jogadador;
    char internalBoard[9][3][3]; //9 mini-tabuleiros
    char externalBoard[3][3]; // tabuleiro geral
}Board;

typedef struct Plays{
    int x;
    int y;
    int board;
    char playerName;
    struct Plays *prox;
}Plays;