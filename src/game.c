#include "globals.h"
#include "game.h"


void game(bool gameMode){
   Board *atualBoard;
   atualBoard = boardsInitializer();
   char globalBoard[3][3];
   Plays *plays;
   char playerNameOne[25], playerNameTwo[25];
   int joga=1,nPlays=0,won=0,nBoard=0;

   printf("First player name: ");
   //fgets(playerNameOne,sizeof(playerNameOne),stdin);
   scanf("%s",playerNameOne);
   if(gameMode == 1){ //BOT_GAME
      

   }else{ //TWO_PLAYERS
      printf("Second player name: ");
      //fgets(playerNameTwo,sizeof(playerNameTwo),stdin);
      scanf("%s",playerNameTwo);
   }         
  
   do{
      boardPrint(atualBoard);
      nBoard=choosePlays(atualBoard,plays,joga,nBoard);
      ++nPlays;

      if(verifyWinner(atualBoard,nBoard) == 1){
         won=joga;
      }
      else{
         joga=joga%2 + 1;
         
      }



   }while (won == 0 && nPlays < 9);
   
   boardPrint(atualBoard);


   

  



}

