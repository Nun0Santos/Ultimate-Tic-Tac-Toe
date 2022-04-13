#include "globals.h"
#include "game.h"


void game(bool gameMode){
   Board *atualBoard;
   atualBoard = boardsInitializer();
   char globalBoard[3][3];
   Plays *plays;
   char playerNameOne[25], playerNameTwo[25];
   int joga=1,nJogadas=0;

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
      choosePlays(atualBoard,joga);

   }while (nJogadas < 9);
   
   boardPrint(atualBoard);


   

  



}

