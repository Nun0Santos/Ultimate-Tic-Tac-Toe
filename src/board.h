
typedef struct Board{
    //char internalBoard[9][3][3]; //9 mini-tabuleiros
    //char externalBoard[3][3]; // tabuleiro geral
    char squares[3][3];
}Board;

//Todas as funcoes referentes ao tabuleiro


void boardPrint(int lin, int col, Board board[][col]);
Board *boardsInitializer();
void verifyWinner(Board board);
void freeBoards(Board *board);



