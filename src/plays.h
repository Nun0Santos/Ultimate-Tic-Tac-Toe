#ifndef PLAYS_H
#define PLAYS_H

typedef struct Plays{
    int player;
    int x;
    int y;
    int Board;
    int nPlays;
    struct Plays *next;
}Plays;

//All functions related to the linked list 
void showPlays(Plays *plays);
void addNodePlays(Plays **head, int board, int x, int y, int nPlays, int palyer);
void removeList(Plays *head);//Destroy list
void showKPlays(Plays *plays, int k, int nPlays,int *cont);

#endif
