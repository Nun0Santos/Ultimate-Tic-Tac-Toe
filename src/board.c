#include "board.h"
#include "globals.h"
#include "matdin.h"

Board *boardsInitializer(){
    Board *board;
    
    board = malloc(sizeof(Board) * 9); //Principal
    if(board == NULL){
       printf("Error trying to allocate memory for global board\n");
       exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 9; ++i){
        board[i].section = malloc(sizeof(char *) * 3); //linhas
        if(board[i].section == NULL){
            fprintf(stderr, "Error trying to allocate memory for section of Board [%d]\n",i);
            //libertar
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 3; j++){
            board[i].section[j] = malloc(sizeof(char) * 3); //colunas
            if (board[i].section[j] == NULL){
                fprintf(stderr, "Error trying to allocate memory for section[%d] of Board [%d]\n",j,i);
                //libertar
                exit(EXIT_FAILURE);
            }
        }
    }
    int i,j;
    for(int k = 0; k < 9; ++k)
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
                board[k].section[i][j] = '_';

    return board;
}

void boardPrint(Board *board){
   printf("\n\n      C0       C1     C2");
   printf("\n  +------------------------+\n");

   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[0].section[0][0], board[0].section[0][1], board[0].section[0][2],
   board[1].section[0][0],board[1].section[0][1], board[1].section[0][2],
   board[2].section[0][0],board[2].section[0][1],board[2].section[0][2]);
   printf("L0| %c %c %c  | %c %c %c | %c %c %c |\n",board[0].section[1][0], board[0].section[1][1], board[0].section[1][2],
   board[1].section[1][0],board[1].section[1][1], board[1].section[1][2],
   board[2].section[1][0],board[2].section[1][1],board[2].section[1][2]); 
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[0].section[2][0], board[0].section[2][1], board[0].section[2][2],
   board[1].section[2][0],board[1].section[2][1], board[1].section[2][2],
   board[2].section[2][0],board[2].section[2][1],board[2].section[2][2]); 
   printf("  |--------+-------+-------|\n");
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[3].section[0][0], board[3].section[0][1], board[3].section[0][2],
   board[4].section[0][0],board[4].section[0][1], board[4].section[0][2],
   board[5].section[0][0],board[5].section[0][1],board[5].section[0][2]);
   printf("L1| %c %c %c  | %c %c %c | %c %c %c |\n",board[3].section[1][0], board[3].section[1][1], board[3].section[1][2],
   board[4].section[1][0],board[4].section[1][1], board[4].section[1][2],
   board[5].section[1][0],board[5].section[1][1],board[5].section[1][2]); 
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[3].section[2][0], board[3].section[2][1], board[3].section[2][2],
   board[4].section[2][0],board[4].section[2][1], board[4].section[2][2],
   board[5].section[2][0],board[5].section[2][1],board[5].section[2][2]); 
   printf("  |--------+-------+-------|\n");
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[6].section[0][0], board[6].section[0][1], board[6].section[0][2],
   board[7].section[0][0],board[7].section[0][1], board[7].section[0][2],
   board[8].section[0][0],board[8].section[0][1],board[8].section[0][2]);
   printf("L2| %c %c %c  | %c %c %c | %c %c %c |\n",board[6].section[1][0], board[6].section[1][1], board[6].section[1][2],
   board[7].section[1][0],board[7].section[1][1], board[7].section[1][2],
   board[8].section[1][0],board[8].section[1][1],board[8].section[1][2]); 
   printf("  | %c %c %c  | %c %c %c | %c %c %c |\n",board[6].section[2][0], board[6].section[2][1], board[6].section[2][2],
   board[7].section[2][0],board[7].section[2][1], board[7].section[2][2],
   board[8].section[2][0],board[8].section[2][1],board[8].section[2][2]); 
   printf("  +------------------------+\n");
}
int linha(Board *board, int nBoard)
{
	int i=0,j=0;
    int line = 1;
	//Test Lines:
    for (i = 0; i < 3; i++){
        for (j = 1; j < 3; j++){
            if(board[nBoard].section[i][j] == board[nBoard].section[i][j-1] && board[nBoard].section[i][j]!='_'){
                line++;
            }
        }
        if (line==3)
            return 0;
        line=1;
    }

}

int coluna(Board *board, int nBoard)
{
	int i=0,j=0;
    int line = 1;
	for (i = 0; i < 3; i++){
        for (j = 1; j <3; j++){
            if(board[nBoard].section[j][i] == board[nBoard].section[j-1][i] && board[nBoard].section[j][i]!='_'){
                line++;
            }
        }
        if (line==3)
            return 0;
        line=1;
    }
}


int diag(Board *board, int nBoard)
{
	int i=0,j=0;
    int line = 1;
	j = 1;  
    if (3 == 3){
        for (i = 1; i < 3; i++){
            if(board[nBoard].section[i][i] == board[nBoard].section[i-1][i-1] && board[nBoard].section[i][i]!='_'){
                line++;     //Left to Right Diagonals
            }
            if(board[nBoard].section[i][3-1-i] == board[nBoard].section[i-1][3-i] && board[nBoard].section[i][3-1-i]!='_'){
                j++;        //Right to Left Diagonals
            }
        }
        if (line==3 || j==3)
            return 0;
    }
}

int verifyWinner(char board[3][3]){
    int i=0,j=0;
    int line = 1;

     //Test Lines:
    for (i = 0; i < 3; i++){
        for (j = 1; j < 3; j++){
            if(board[i][j] == board[i][j-1] && board[i][j]!= '_'){
                line++;
            }
        }
        if (line==3)
            return 0;
        line=1;
    }
    //Test Columns:
    /*for (i = 0; i < 3; i++){
        for (j = 1; j <3; j++){
            if(board[nBoard].section[j][i] == board[nBoard].section[j-1][i] && board[nBoard].section[j][i]!='_'){
                line++;
            }
        }
        if (line==3)
            return 0;
        line=1;
    }
    //Diagonals
    j = 1;  
    if (3 == 3){
        for (i = 1; i < 3; i++){
            if(board[nBoard].section[i][i] == board[nBoard].section[i-1][i-1] && board[nBoard].section[i][i]!='_'){
                line++;     //Left to Right Diagonals
            }
            if(board[nBoard].section[i][3-1-i] == board[nBoard].section[i-1][3-i] && board[nBoard].section[i][3-1-i]!='_'){
                j++;        //Right to Left Diagonals
            }
        }
        if (line==3 || j==3)
            return 0;
    }*/
}

int convertPosition(int position, int *x, int *y){
    switch (position)
    {
    case 0:
        *x=0; *y=0;
        break;
    case 1:
        *x=0; *y=1;
        break;
    case 2:
        *x=0; *y=2;
        break;
    case 3:
        *x=1; *y=0;
        break;
    case 4:
        *x=1; *y=1;
        break;
    case 5:
        *x=1; *y=2;
        break;
    case 6:
        *x=2; *y=0;
        break;
     case 7:
        *x=2; *y=1;
        break;
    case 8:
        *x=2; *y=2;
        break;
    default:
        return 1;
        break;
        
    }
    return 0;
}
int winnerSection(Board *board, int nBoard, char globalBoard[3][3], int jogador, char namePlayers[2][255]){
    int i,j,aux;
    int x,y,res;

        convertPositionBoard(nBoard,&x,&y);
        if(jogador == 1){
            globalBoard[x][y] = 'X';
            if( (lin(globalBoard) ) == 0){
                res = 1;
                return res;
            }
        }
        else{
            globalBoard[x][y] = 'O';
             if( (lin(globalBoard) ) == 0){
                res = 1;
                return res;
            }
            res = 0;
            return res;
        }
        
}

void convertPositionBoard(int pos, int *x, int *y){
    if(pos == 0){
        *x=0;*y=0;
    }
    if(pos == 1){
        *x=0;*y=1;
    }
    if(pos == 2){
        *x=0;*y=2;
    }
    if(pos == 3){
        *x=1;*y=0;
    }
    if(pos == 4){
        *x=1;*y=1;
    }
    if(pos == 5){
        *x=1;*y=2;
    }
    if(pos == 6){
        *x=2;*y=0;
    }
    if(pos == 7){
        *x=2;*y=1;
    }
    if(pos == 8){
        *x=2;*y=2;
    }
}

void freeBoards(Board *board){
    for(int i = 0; i < 10; i++){
        free(board[i].section);
    }
    free(board);
}

int lin(char board[3][3])
{
	int i=0,j=0;
    int line = 1;
	//Test Lines:
    for (i = 0; i < 3; i++){
        for (j = 1; j < 3; j++){
            if(board[i][j] == board[i][j-1] && board[i][j]!='_'){
                line++;
            }
        }
        if (line==3)
            return 0;
        line=1;
    }

}
