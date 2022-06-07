#include "game.h"

void game(int gameMode, bool resume){
   Board *atualBoard = NULL;
   atualBoard = boardsInitializer();
   char globalBoard[3][3] = {"", "", ""};
   Plays *plays = NULL;
   char playerName[2][255] = {"", ""};
   int joga=1, nPlays=0, won=0, nBoard = 0, nBoardBefore=0, completedBoards[9] = {0},iterator=0,itLoad=0,
       resWinner=0, flagPlayerTwo = 0, flagWinnerSection=0, section=-1,x = 0,y = 0;

   globalBoardInitializer(globalBoard);

   if(resume == RESUME_GAME){
      plays = loadFich(atualBoard,"fich.bin",playerName,&nBoard,&nPlays,&joga,&nBoardBefore,completedBoards,&itLoad,globalBoard);
      nBoard = nBoardBefore;
      iterator = itLoad;
      for(int i=0; i<itLoad; ++i)
         printf("boards load: %d\n",completedBoards[i]);

   }
   else{
      nBoard = intUniformRnd(0,8);//Iniciar num board aleatório
      printf("First player name: ");
      fgets(playerName[0],sizeof(playerName[0]),stdin);
      playerName[0][strlen(playerName[0]) - 1] = '\0';
   }

   if(gameMode == 1){ //BOT_GAME
      strcpy(playerName[1],"Computer");
      
      do{
         boardPrint(atualBoard);
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays,gameMode,completedBoards,iterator);   
         boardPrint(atualBoard);
         ++nPlays;

         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //human win
            joga=1;
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,1,playerName);
            printf("\n%s won board [%d] !\n",playerName[0],nBoardBefore);
            completedBoards[iterator] = nBoardBefore; 
            ++iterator;
            printf("Board human Completed %d\n",completedBoards[iterator-1]);
         }
         while (globalBoard[nBoard / 3][nBoard % 3] != '_' )//Condição para que quando ganho o board 6 na pos 6 ele troque de board
         {  
            nBoard = rand() % 9;
         }

         nBoard=botPlays(atualBoard,&plays,joga,nBoard,&nBoardBefore,&gameMode,&section,nPlays);
         ++nPlays;
         
         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //bot win
            joga = 2;
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,2,playerName);
            printf("\n%s won board [%d] !\n",playerName[1],nBoardBefore);
            completedBoards[iterator] = nBoardBefore; 
            ++iterator;
            joga =1;//para ser o jogador 1 a seguir
         }
         while (globalBoard[nBoard / 3][nBoard % 3] != '_' )
         {  
            nBoard = rand() % 9;
         }         
      }while (resWinner == 0 && nPlays < 9*9);

      boardPrint(atualBoard);
      if(joga == 1)
         printf("%s won!\n",playerName[0]);
      else
         printf("%s won!\n",playerName[1]);

      exportFile(plays,nPlays);
      endGame(atualBoard,plays);
      
   }else{ //TWO_PLAYERS
   
      if(resume == RESUME_GAME){}
      else{
         printf("Second player name: ");
         fgets(playerName[1],sizeof(playerName[1]),stdin);
         playerName[1][strlen(playerName[1]) - 1] = '\0';
      }
      do{
         boardPrint(atualBoard);
         //globalBoardPrint(globalBoard);
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays,gameMode,completedBoards,iterator);  
         for(int i = 0; i<itLoad; ++i)
            printf("a seguir ao choose completedBoards: %d\n",completedBoards[i]);
           
         convertPositionBoard(nBoard,&x,&y);
         ++nPlays;
         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
            flagWinnerSection = 1;
            section = nBoardBefore;
            completedBoards[iterator] = section; 
            ++iterator;
            for(int i=0; i<iterator; ++i)
               printf("game CompletedBoards [%d]: %d\n",i,completedBoards[i]);


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
         }
         //globalBoardPrint(globalBoard);
         while (globalBoard[nBoard / 3][nBoard % 3] != '_' )
         {  
            nBoard = rand() % 9;
         }
   }while (resWinner == 0 && nPlays < 9*9); 

   boardPrint(atualBoard);

   if(joga == 1 && flagPlayerTwo == 0 )
      printf("%s won!\n",playerName[1]);
   else
      printf("%s won!\n",playerName[0]);
   }
   //Exportação para ficheiro
   exportFile(plays,nPlays);
   /*removeList(plays); 
   showPlays(plays);*/
   endGame(atualBoard,plays);


}

int choosePlays(Board *board, Plays **plays, int jogador,char namePlayers[2][255],  int nBoard,int *nBoardBefore, int *mode, int *section, int nPlays, int gameMode, int *completedBoards, int howManyBoards ){
   int pos,x,y,res,resp,k,resMenu,cont=0;
   char posStr[255], respStr[255],kStr[255],posK;
   *nBoardBefore = nBoard;

   printf("\nCurrent board: [%d]",nBoard);

   if(jogador == 1)
      printf("\n%s plays:\n",namePlayers[0]);
   else
      printf("\n%s plays:\n",namePlayers[1]);
   
	do{
      resMenu = menuGame(); //1, 2 ou 3 

      if(resMenu == 1){
         if(nPlays < 0 || nPlays == 0){
           printf("Sorry, haven't reached the minimum of moves yet\n");  
         }
         else{
            printf("Total plays: %d\n",nPlays);
            printf("Plays to see [1-10]: ");
            fgets(kStr,sizeof(kStr),stdin);
            k = atoi(kStr);
            showKPlays(*plays,k,nPlays,&cont);cont=0;
         }
      }
      if(resMenu == 3){
         //pause
         if(nPlays == 0){
            printf("There are no plays to save, please make a play\n");
         }
         else{
            for(int i = 0; i<howManyBoards; ++i)
               printf("PAUSE CompletedBoards [%d]: %d\n",i,completedBoards[i]);
            
            pause(board,*plays,nPlays,gameMode,namePlayers,jogador,*nBoardBefore,completedBoards,howManyBoards);
            endGame(board,*plays);
         }
      }
      do{
         printf("\nPosition: ");
         fgets(posStr,sizeof(posStr),stdin);
         pos = atoi(posStr);
         res = convertPosition(pos, &x,&y);

         if(pos < 0 || pos > 8 || board[nBoard].section[x][y] != '_')
            printf("Please enter a valid input\n");
         
      }while(pos < 0 || pos > 8 || board[nBoard].section[x][y] != '_' );
      
      res = convertPosition(pos, &x,&y);

	}while(board[nBoard].section[x][y] != '_' || res == 1 || pos < 0 || pos > 8);
  
   addNodePlays(plays,nBoard,x,y,nPlays,jogador);
   
   if(jogador == 1)
      setPos(board[nBoard].section,x,y,'X');
	else
      setPos(board[nBoard].section,x,y,'O');

   //*mode = 1;
   return pos;
}

int botPlays(Board *board, Plays **plays, int jogador, int nBoard, int *nBoardBefore, int *mode, int *section, int nPlays){
   int pos,x,y,res;
   *nBoardBefore = nBoard; 

   printf("\nCurrent board: [%d]",nBoard);
	printf("\nComputer plays:\n");
	do{

		pos = intUniformRnd(0,8);
      printf("Position: %d\n",pos);
      res = convertPosition(pos, &x,&y);
     
	}while(board[nBoard].section[x][y] != '_' || res == 1 || pos < 0 || pos > 8 || pos == *section );

   addNodePlays(plays,nBoard,x,y,nPlays,2);
   //showPlays(*plays);
   
   setPos(board[nBoard].section,x,y,'O');
   *mode = 1;

   return pos;
}

void rules(){
   printf("test\n");
   
}

void endGame(Board *board, Plays *plays){
   removeList(plays);
   freeBoards(board);
   printf("plays: %lu\n",sizeof(plays));
   printf("board:%lu\n",sizeof(board));
   exit(0); 
}