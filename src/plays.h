
typedef struct Plays Plays, *pPlays;
struct Plays{
    int player;
    int x;
    int y;
    int Board;
    pPlays prox;

    //struct Plays *prox;
    /* int xBoard;
    int yBoard;*/
};

//Todas as funcoes referentes à lista ligada (jogadas)
void showPlays(pPlays plays);
pPlays addNodePlays(pPlays plays, int board, int x, int y);