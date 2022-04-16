
typedef struct Board{
    char **section;
}Board;

//Todas as funcoes referentes ao tabuleiro

Board *boardsInitializer();
void boardPrint(Board *board);
int verifyWinner(Board *board);
void choosePlays(Board *board, int jogador);

void freeBoards(Board *board);
