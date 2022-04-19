#include "globals.h"
#include "game.h"

void game(int gameMode){
   Board *atualBoard;
   atualBoard = boardsInitializer();
   char globalBoard[3][3];
   pPlays plays = NULL;
   char playerNameOne[25], playerNameTwo[25];
   int joga=1,nPlays=0,won=0,nBoard=0;

   printf("First player name: ");
   //fgets(playerNameOne,sizeof(playerNameOne),stdin);
   scanf("%s",playerNameOne);
   if(gameMode == 1){ //BOT_GAME
      printf("Computer Plays\n");
      strcpy(playerNameTwo,"Computer");
      do{
         boardPrint(atualBoard);
         nBoard=botPlays(atualBoard,plays,joga,nBoard, &gameMode);
         ++nPlays;
         boardPrint(atualBoard);
         if(verifyWinner(atualBoard,nBoard) == 1){
            //won=joga;
            printf("ganhou o jogador : %s\n",playerNameTwo);
            joga=2;
             winnerSection(atualBoard,nBoard,joga);
         }
         else{
            nBoard=choosePlays(atualBoard,plays,joga,nBoard, &gameMode);   
            if(verifyWinner(atualBoard,nBoard) == 1){
               winnerSection(atualBoard,nBoard,joga);
               //won=joga;
               printf("ganhou o jogador : %s\n",playerNameOne);
               joga = 1;
               winnerSection(atualBoard,nBoard,joga);
            }         
         }
      }while (won == 0 && nPlays < 9*8);         
      boardPrint(atualBoard);
   
   }else{ //TWO_PLAYERS
      printf("Second player name: ");
      //fgets(playerNameTwo,sizeof(playerNameTwo),stdin);
      scanf("%s",playerNameTwo);
      do{
         boardPrint(atualBoard);
         nBoard=choosePlays(atualBoard,plays,joga,nBoard, &gameMode);   
         ++nPlays;
         if(verifyWinner(atualBoard,nBoard) == 1){
         won=joga;
      }
      else{
         joga=joga%2 + 1;
      }
   }while (won == 0 && nPlays < 9*8);         
   boardPrint(atualBoard);
   }
}

int choosePlays(Board *board, Plays *plays, int jogador, int nBoard, int *mode){
    int pos,x,y,res;
    
	printf("\nÉ a vez do jogador %d\n", jogador);
	do{
		printf("Posição: ");
		scanf(" %d", &pos);

      res = convertPosition(pos, &x,&y);
      addNodePlays(plays,nBoard,x,y);
      showPlays(plays);

	}while(board[nBoard].section[x][y] != '_' || res == 1 || pos < 0 || pos > 9 );
	
   if(jogador == 1)
            setPos(board[nBoard].section,x,y,'X');
		else
            setPos(board[nBoard].section,x,y,'O');
   *mode = 1;
   return pos;
}

int botPlays(Board *board, pPlays plays, int jogador, int nBoard, int *mode){
   int pos,x,y,res;
    
	printf("\nComputer:\n");
	do{
		pos =intUniformRnd(0,8);
      res = convertPosition(pos, &x,&y);
      printf("pos=%d\n",pos);
      addNodePlays(plays,nBoard,x,y);
      showPlays(plays);

	}while(board[nBoard].section[x][y] != '_' || x < 0 || y > 9 );

   setPos(board[nBoard].section,x,y,'O');
   *mode = 0;
   return pos;
}


