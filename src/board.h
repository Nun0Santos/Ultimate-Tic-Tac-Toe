
typedef struct Board{
    char **section;
}Board;

//Todas as funcoes referentes ao tabuleiro

Board *boardsInitializer();
void boardPrint(Board *board);
void verifyWinner(Board board);
void freeBoards(Board *board);


void choosePlays(Board *board, int jogador);

