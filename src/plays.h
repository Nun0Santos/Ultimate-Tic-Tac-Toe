
typedef struct Plays{
    int player;
    int x;
    int y;
    int xBoard;
    int yBoard;
    int Board;
    struct Plays *prox;
}Plays;



//Todas as funcoes referentes à lista ligada (jogadas)
int showPlays(Plays *plays, int jogador);
