#include "globals.h"
#include "game.h"


void game(bool gameMode){
   Board *globalBoard;
   Board *atualBoard;
   globalBoard = boardsInitializer();
   atualBoard = boardsInitializer();
   Plays *plays;
   char playerNameOne[25], playerNameTwo[25];

   printf("First player name: ");
   fgets(playerNameOne,sizeof(playerNameOne),stdin);
  

   if(gameMode == 1){ //BOT_GAME

   }else{ //TWO_PLAYERS
      printf("Second player name: ");
      fgets(playerNameTwo,sizeof(playerNameTwo),stdin);
   }         



   boardPrint(atualBoard);

  



}

