#include "game.h"

void game(int gameMode, bool resume){
   Board *atualBoard = NULL;
   atualBoard = boardsInitializer();
   char globalBoard[3][3] = {"", "", ""};
   Plays *plays = NULL;
   char playerName[2][255] = {"", ""};
   int joga=1, nPlays=0, won=0, nBoard = 0, nBoardBefore=0, completedBoards[9] = {0},iterator=0,itLoad=0,
       resWinner=0, flagWinnerSection=0, section=-1,x = 0,y = 0, flagEmpate=0, drawBoards[9] = {0}, indexDraw = 0;

   globalBoardInitializer(globalBoard);

   if(resume == RESUME_GAME){
      plays = loadFich(atualBoard,"fich.bin",playerName,&nBoard,&nPlays,&joga,&nBoardBefore,completedBoards,&itLoad,globalBoard,drawBoards,&indexDraw);
      nBoard = nBoardBefore;
      iterator = itLoad;
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
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays,gameMode,completedBoards,iterator,drawBoards,indexDraw);   
         boardPrint(atualBoard);
         ++nPlays;
         globalBoardPrint(globalBoard);

         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //human won
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,1,playerName);
            printf("\n%s won board [%d] !\n",playerName[0],nBoardBefore);
            completedBoards[iterator] = nBoardBefore; //Para guardar os boards que foram ganhos num array 
            ++iterator;
         }
         else{
            if(verifyWinner(atualBoard,nBoardBefore) == 1){ //Emapte pelo human
               printf("\nDraw on the board [%d] !\n",nBoardBefore);
               checkDraw(globalBoard,nBoardBefore);
               resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,1,playerName);
               drawBoards[indexDraw] = nBoardBefore; //Para guardar os boards que ficaram empatados
               ++indexDraw;
            }
         }
         if(resWinner == 1)
            break;

         joga=2;
         while (globalBoard[nBoard / 3][nBoard % 3] != '_')//Condição para que quando ganho no board 6 na posição 6 ele troque de board para um aleatório 
         {  
            nBoard = rand() % 9;
         }
         
         nBoard=botPlays(atualBoard,&plays,joga,nBoard,&nBoardBefore,&gameMode,&section,nPlays);
         ++nPlays;
         
         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //bot won
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,2,playerName);
            printf("\n%s won board [%d] !\n",playerName[1],nBoardBefore);
            completedBoards[iterator] = nBoardBefore;//Para guardar os boards que foram ganhos num array 
            ++iterator;  
         }
         else{
            if(verifyWinner(atualBoard,nBoardBefore) == 1){ //Empate pelo bot
               printf("\nDraw on the board [%d] !\n",nBoardBefore);
               checkDraw(globalBoard,nBoardBefore);
               resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,2,playerName);
               drawBoards[indexDraw] = nBoardBefore; //Para guardar os boards que ficaram empatados
               ++indexDraw;
            }
         }
         if(resWinner == 1)
            break;

         joga = 1;//para ser o jogador 1 a seguir
         while (globalBoard[nBoard / 3][nBoard % 3] != '_' )
         {  
            nBoard = rand() % 9;
         }       
      }while (resWinner == 0 && nPlays < 9*9 );

      boardPrint(atualBoard);
      //globalBoardPrint(globalBoard);

      if(verifyGlobalWinner(globalBoard) == 1){//Verificar empate no final do jogo
         printf("Draw in the game!\n");
         exportFile(plays,nPlays); //Exportação das jogadas para ficheiro de texto
         endGame(atualBoard,plays);
      }

      if(joga == 1)//joga == 1
         printf("%s won!\n",playerName[0]);
      else
         printf("%s won!\n",playerName[1]);

      exportFile(plays,nPlays); //Exportação das jogadas para ficheiro de texto
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
         globalBoardPrint(globalBoard);
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays,gameMode,completedBoards,iterator,drawBoards,indexDraw);  
         convertPositionBoard(nBoard,&x,&y);
         ++nPlays;

         if(verifyWinner(atualBoard,nBoardBefore) == 0){ //verifica vitória
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
            flagWinnerSection = 1;
            section = nBoardBefore;
            completedBoards[iterator] = section; //Para guardar os boards que foram ganhos num array 
            ++iterator;
            /*for(int i=0; i<iterator; ++i)
               printf("game CompletedBoards [%d]: %d\n",i,completedBoards[i]);*/
            if(joga == 1){
               joga = 2;
               printf("\n%s won board [%d] !\n",playerName[0],nBoardBefore);
            }
            else{
               joga = 1;
               printf("\n%s won board [%d] !\n",playerName[1],nBoardBefore); 
            }      
         }else{

            if(verifyWinner(atualBoard,nBoardBefore) == 1){//verifica empate
               printf("\nDraw on the board [%d] !\n",nBoardBefore);
               checkDraw(globalBoard,nBoardBefore);
               drawBoards[indexDraw] = nBoardBefore; //Para guardar os boards que ficaram empatados
               ++indexDraw;
            }
            joga=joga%2 + 1;
         }

         if(resWinner == 1)
            break;
         
         while (globalBoard[nBoard / 3][nBoard % 3] != '_' )
         {  
            nBoard = rand() % 9;
         }
      
      }while (resWinner == 0 && nPlays < 9*9 ); //|| nPlays < 9*9

   boardPrint(atualBoard);
   //globalBoardPrint(globalBoard);
   
   if(verifyGlobalWinner(globalBoard) == 1){//verificar empate no final do jogo
      printf("Draw in the game!\n");
      exportFile(plays,nPlays);//Exportação das jogadas para ficheiro de texto
      endGame(atualBoard,plays);
   }
      
   if(plays->player == 1)
      printf("%s won!\n",playerName[0]);
   else
      printf("%s won!\n",playerName[1]);
   }

   exportFile(plays,nPlays);//Exportação das jogadas para ficheiro de texto
   endGame(atualBoard,plays);
}

int choosePlays(Board *board, Plays **plays, int jogador,char namePlayers[2][255],  int nBoard,int *nBoardBefore, int *mode, int *section, int nPlays, int gameMode, int *completedBoards, int howManyBoards, int *drawBoards, int indexDraw){
   int pos,x,y,res,resp,k,resMenu,cont=0;
   char posStr[255]={" "}, respStr[255]={" "},kStr[255]={" "},posK, *buffer=NULL;
   *nBoardBefore = nBoard;

   printf("\nCurrent board: [%d]",nBoard);

   if(jogador == 1)
      printf("\n%s plays:\n",namePlayers[0]);
   else
      printf("\n%s plays:\n",namePlayers[1]);
   
	do{
      resMenu = menuGame(); //1 - ver jogadas, 2 - jogar, 3 - pause 

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
            /*for(int i = 0; i<howManyBoards; ++i)
               printf("PAUSE CompletedBoards [%d]: %d\n",i,completedBoards[i]);*/
            pause(board,*plays,nPlays,gameMode,namePlayers,jogador,*nBoardBefore,completedBoards,howManyBoards,drawBoards,indexDraw);
            endGame(board,*plays);
         }
      }
      do{
         printf("\nPosition: ");
         fgets(posStr,sizeof(posStr),stdin);
         pos = myAtoi(posStr);
         
         if(pos == -1){
            printf("Please enter a number!\n");
            continue;
         }
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
   
   setPos(board[nBoard].section,x,y,'O'); //Função do professor (alterada)
   *mode = 1;

   return pos;
}

int myAtoi(char *str){
   int res;

   res = atoi(str);
   if(res == 0){
      if(str[0] != '0')
         return -1;
   }
   return res;
}

void rules(){
   printf("test\n");
      
}

void endGame(Board *board, Plays *plays){
   removeList(plays);
   freeBoards(board);
   exit(EXIT_SUCCESS); 
}