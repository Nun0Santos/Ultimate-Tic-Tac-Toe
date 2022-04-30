
typedef struct Plays{
    int player;
    int x;
    int y;
    int Board;
    struct Plays *next;

    /* int xBoard;
    int yBoard;*/
}Plays;

//Todas as funcoes referentes à lista ligada (jogadas)
void showPlays(Plays **plays);
void addNodePlays(Plays **head, int board, int x, int y);
void removeList(Plays *head);