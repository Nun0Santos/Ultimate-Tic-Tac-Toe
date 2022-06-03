#ifndef PLAYS_H
#define PLAYS_H

typedef struct Plays{
    int player;
    int x;
    int y;
    int Board;
    int nPlays;
    struct Plays *next;

    /* int xBoard;
    int yBoard;*/
}Plays;

//Todas as funcoes referentes à lista ligada (jogadas)
void showPlays(Plays *plays);
void addNodePlays(Plays **head, int board, int x, int y, int nPlays, int palyer);
void removeList(Plays *head);
void showKPlays(Plays *plays, int k, int nPlays,int *cont);

#endif
