#include "globals.h"
#include "game.h"

void game(int gameMode){
   Board *atualBoard;
   atualBoard = boardsInitializer();
   char globalBoard[3][3];
   pPlays plays = NULL;
   char playerName[2][255];
   int joga=1, nPlays=0, won=0, nBoard, nBoardBefore=0,
       resWinner=0, flagPlayerTwo = 0, flagWinnerSection=0, section=-1,x,y;

	nBoard = intUniformRnd(0,8);//Iniciar num board aleatório

   globalBoardInitializer(globalBoard);

   printf("First player name: ");
   fgets(playerName[0],sizeof(playerName[0]),stdin);
   playerName[0][strlen(playerName[0]) - 1] = '\0';

   if(gameMode == 1){ //BOT_GAME

      printf("\nComputer Plays\n");
      strcpy(playerName[1],"Computer");

      do{
         boardPrint(atualBoard);
         nBoard=botPlays(atualBoard,plays,joga,nBoard,&nBoardBefore,&gameMode,&section);
         boardPrint(atualBoard);
         ++nPlays;

         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //bot win
            joga=2;
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
            joga=1;
         }
         else{ 
            nBoard=choosePlays(atualBoard,plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section);   
            ++nPlays;
            if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //Human win
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
               joga = 1;
            }         
         }
      }while (resWinner == 0 && nPlays < 9*9);

      boardPrint(atualBoard);

      if(joga == 1)
         printf("%s won!\n",playerName[0]);
      else
         printf("%s won!\n",playerName[1]);

   }else{ //TWO_PLAYERS

      printf("Second player name: ");
      fgets(playerName[1],sizeof(playerName[1]),stdin);
      playerName[1][strlen(playerName[1]) - 1] = '\0';
      do{
         boardPrint(atualBoard);
         nBoard=choosePlays(atualBoard,plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section);   
         ++nPlays;
         convertPositionBoard(nBoard,&x,&y);
         
         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
            flagWinnerSection = 1;
            section = nBoardBefore;

            if(joga == 1){
               joga = 2;
               printf("\n%s won board [%d] !\n",playerName[0],nBoardBefore);
            }
            else{
               flagPlayerTwo = 2;
               joga = 1;
               printf("\n%s won board [%d] !\n",playerName[1],nBoardBefore); 
            }         
      }else{
            joga=joga%2 + 1;
            printf("else joga %d\n",joga);
      }
   }while (resWinner == 0 && nPlays < 9*9 || nBoard == atualBoard[nBoard].section[x][y]); 

   boardPrint(atualBoard);

   if(joga == 1 && flagPlayerTwo == 0 )
      printf("%s won!\n",playerName[0]);
   else
      printf("%s won!\n",playerName[1]);
   }
}

int choosePlays(Board *board, Plays *plays, int jogador,char namePlayers[2][255],  int nBoard,int *nBoardBefore, int *mode, int *section){
   int pos,x,y,res;
   char poss[255];
   *nBoardBefore = nBoard;
   
   printf("\nCurrent board: [%d]",nBoard);

   if(jogador == 1){
      printf("\n%s plays:\n",namePlayers[0]);
   }
   else{
      printf("\n%s plays:\n",namePlayers[1]);
   }

	do{
		printf("Position: ");
      fgets(poss,sizeof(pos),stdin);
      pos = atoi(poss);

      if(pos < 0 || pos > 8){
         printf("Please enter a valid input [0-9]\n");
      }
      pos = atoi(poss);
      res = convertPosition(pos, &x,&y);
      printf("x %d y %d\n",x,y);
      /*addNodePlays(plays,nBoard,x,y);
      showPlays(plays);*/

	}while(board[nBoard].section[x][y] != '_' || res == 1 || pos < 0 || pos > 9 || pos == board[nBoard].section[x][y]);
	
   if(jogador == 1)
            setPos(board[nBoard].section,x,y,'X');
		else
            setPos(board[nBoard].section,x,y,'O');
   *mode = 1;

   return pos;
}

int botPlays(Board *board, pPlays plays, int jogador, int nBoard, int *nBoardBefore, int *mode, int *section){
   int pos,x,y,res;
   *nBoardBefore = nBoard; 

   printf("\nCurrent board: [%d]",nBoard);
	printf("\nComputer plays:\n");
	do{

		pos = intUniformRnd(0,8);
      printf("Position: %d\n",pos);
      res = convertPosition(pos, &x,&y);
     

      /*addNodePlays(plays,nBoard,x,y);
      showPlays(plays);*/

	}while(board[nBoard].section[x][y] != '_' || res == 1 || pos < 0 || pos > 9 || pos == *section );

   setPos(board[nBoard].section,x,y,'O');
   *mode = 0;

   return pos;
}

void rules(){
   printf("test\n");
}

