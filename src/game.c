#include "game.h"

void game(int gameMode, bool resume){
   Board *atualBoard = NULL;
   atualBoard = boardsInitializer();
   char globalBoard[3][3] = {"", "", ""};
   Plays *plays = NULL;
   char playerName[2][255] = {"", ""};
   int joga=1, nPlays=0, won=0, nBoard = 0, nBoardBefore=0,
       resWinner=0, flagWinnerSection=0, section=-1,x = 0,y = 0;

   globalBoardInitializer(globalBoard);

   if(resume == RESUME_GAME){
      plays = loadFich(atualBoard,"fich.bin",playerName,&nBoard,&nPlays,&joga,&nBoardBefore,globalBoard);
      nBoard = nBoardBefore;
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
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays,gameMode);   
         boardPrint(atualBoard);
         ++nPlays;
         //globalBoardPrint(globalBoard);

         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //human won
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,1,playerName);
            printf("\n%s won board [%d] !\n",playerName[0],nBoardBefore);
            
         }
         else{
            if(verifyWinner(atualBoard,nBoardBefore) == 1){ //Emapte pelo human
               printf("\nDraw on the board [%d] !\n",nBoardBefore);
               checkDraw(globalBoard,nBoardBefore);
            }
         }
         if(resWinner == 1 || verifyGlobalWinner(globalBoard) == 1) //se ganhar ou se o globalBoard estiver cheio
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
         }
         else{
            if(verifyWinner(atualBoard,nBoardBefore) == 1){ //Empate pelo bot
               printf("\nDraw on the board [%d] !\n",nBoardBefore);
               checkDraw(globalBoard,nBoardBefore);
            }
         }
         if(resWinner == 1 || verifyGlobalWinner(globalBoard) == 1)
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

      if(joga == 1)
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
         //globalBoardPrint(globalBoard);
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays,gameMode);  
         convertPositionBoard(nBoard,&x,&y);
         ++nPlays;

         if(verifyWinner(atualBoard,nBoardBefore) == 0){ //verifica vitória
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
            flagWinnerSection = 1;
            section = nBoardBefore;
           
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
            }
            joga=joga%2 + 1;
         }

         if(resWinner == 1 || verifyGlobalWinner(globalBoard) == 1) //se ganhar ou se o globalBoard estiver cheio
            break;
         
         while (globalBoard[nBoard / 3][nBoard % 3] != '_' )
         {  
            nBoard = rand() % 9;
         }
      
      }while (resWinner == 0 && nPlays < 9*9 );

   boardPrint(atualBoard);
   //globalBoardPrint(globalBoard);
   
   if(verifyGlobalWinner(globalBoard) == 1){//verificar empate no final do jogo
      printf("Draw in the game!\n");
      exportFile(plays,nPlays);//Exportação das jogadas para ficheiro de texto
      endGame(atualBoard,plays);
   }
      
   if(plays->player == 1 && joga == 2) //Preciso do joga == 2 porque estou a trocar essa variavel nos if's
      printf("%s won!\n",playerName[0]);
   else
      printf("%s won!\n",playerName[1]);
   }

   exportFile(plays,nPlays);//Exportação das jogadas para ficheiro de texto
   endGame(atualBoard,plays);
}

int choosePlays(Board *board, Plays **plays, int jogador,char namePlayers[2][255],  int nBoard,int *nBoardBefore, int *mode, int *section, int nPlays, int gameMode){
   int pos,x,y,res,resp,k,resMenu,cont=0;
   char posStr[255]={" "}, respStr[255]={" "},kStr[255]={" "}, *buffer=NULL;
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
            pause(board,*plays,nPlays,gameMode,namePlayers,jogador,*nBoardBefore);
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
   char opt[255];

   printf("\n\n");
   printf("----------- Regras Ultimate Tic-Tac-Toe  -----------\n\n");
   printf("Cada número corresponde a uma posição\n");

   printf("\n\n    C0       C1        C2");
   printf("\n  +----------+---------+---------+\n");
   printf("  | 0  1  2  | _  _  _ | _  _  _ |\n");
   printf("L0| 3  4  5  | _  _  _ | _  _  _ |\n"); 
   printf("  | 6  7  8  | _  _  _ | _  _  _ |\n"); 
   printf("  |----------+---------+---------|\n");
   printf("  | _  _  _  | _  _  _ | _  _  _ |\n");
   printf("L1| _  _  _  | _  _  _ | _  _  _ |\n"); 
   printf("  | _  _  _  | _  _  _ | _  _  _ |\n"); 
   printf("  |----------+---------+---------|\n");
   printf("  | _  _  _  | _  _  _ | _  _  _ |\n");
   printf("L2| _  _  _  | _  _  _ | _  _  _ |\n"); 
   printf("  | _  _  _  | _  _  _ | _  _  _ |\n"); 
   printf("  +----------+---------+---------+\n");

   printf("\n\nObjetivo:\n"
          "\t- Ser o primeiro a construir linha/coluna/diagonal com 3 peças iguais\n\n");
   
   printf("Regras:\n"
           "\t- Os dois jogadores colocam, alternadamente, as suas peças de forma a construirem uma linha/coluna/diagonal\n" 
            "\t  com 3 peças iguais em 9 tabuleiros de 3 x 3\n\n"
           "\t- O jogador deve jogar tendo em conta as seguintes propriedades:\n"
           "\t\t- Ganhar completando a linha/coluna/diagonal;\n"
           "\t\t- Bloquer para impedir que o adeversáro complete a sua linha/coluna/diagonal;\n"
           "\t\t- Fazer jogadas tendo em consideração que o tabuleiro seguinte a jogar será decidido pela jogada atual.\n\n\n");

   do{
      printf("Do you want to start playing? (Y/N)\n");
      fgets(opt,sizeof(opt)-1,stdin);

      if( opt[0] != 'Y' && opt[0] != 'N'){
          printf("Please enter a valid input: Y(Yes) or N(No)\n");
      }
   }while( opt[0] != 'Y' && opt[0] != 'N');
   
   if( opt[0] == 'Y' )
      initializer();

   exit(EXIT_SUCCESS);
}

void endGame(Board *board, Plays *plays){
   removeList(plays);
   freeBoards(board);
   exit(EXIT_SUCCESS); 
}