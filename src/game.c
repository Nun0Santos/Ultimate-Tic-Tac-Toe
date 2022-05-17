#include "globals.h"
#include "game.h"
#include "file.h"

void game(int gameMode, bool resume){
   Board *atualBoard;
   atualBoard = boardsInitializer();
   char globalBoard[3][3];
   Plays *plays = NULL;
   char playerName[2][255];
   int joga=1, nPlays=0, won=0, nBoard, nBoardBefore=0,
       resWinner=0, flagPlayerTwo = 0, flagWinnerSection=0, section=-1,x,y;

   globalBoardInitializer(globalBoard);

   if(resume == RESUME_GAME){
      plays = loadFich("fich.bin",playerName);
   }
   else{
      nBoard = intUniformRnd(0,8);//Iniciar num board aleatório
      printf("First player name: ");
      fgets(playerName[0],sizeof(playerName[0]),stdin);
      playerName[0][strlen(playerName[0]) - 1] = '\0';
   }

   if(gameMode == 1){ //BOT_GAME

      //printf("\nComputer Plays\n");
      strcpy(playerName[1],"Computer");

      do{
         boardPrint(atualBoard);
         nBoard=botPlays(atualBoard,&plays,joga,nBoard,&nBoardBefore,&gameMode,&section,nBoard);
         while (globalBoard[nBoard / 3][nBoard % 3] != '_')
         {
            nBoard = rand() % 9;
         }
         boardPrint(atualBoard);
         ++nPlays;
         if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //bot win
            joga=2;
            resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
            if(resWinner == 1){
               printf("\n%s won board [%d] !\n",playerName[1],nBoardBefore);
               break;
            }
            joga=1;
            printf("\n%s won board [%d] !\n",playerName[1],nBoardBefore);

         }
         if(joga ==1){ 
            nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nBoard,gameMode);   
            while (globalBoard[nBoard / 3][nBoard % 3] != '_')
            {
               nBoard = rand() % 9;
            }
            ++nPlays;
            if(verifyWinner(atualBoard,nBoardBefore) == 0 ){ //Human win
               resWinner = winnerSection(atualBoard,nBoardBefore,globalBoard,joga,playerName);
               if(resWinner == 1){
                  printf("\n%s won board [%d] !\n",playerName[1],nBoardBefore);
                  break;   
               }
               joga = 1;
               printf("\n%s won board [%d] !\n",playerName[0],nBoardBefore);
            }         
         }
      }while (resWinner == 0 && nPlays < 9*9);

      boardPrint(atualBoard);

      if(joga == 1)
         printf("%s won!\n",playerName[0]);
      else
         printf("%s won!\n",playerName[1]);

   }else{ //TWO_PLAYERS
   
      if(resume == RESUME_GAME){
         
      }
      else{
         printf("Second player name: ");
         fgets(playerName[1],sizeof(playerName[1]),stdin);
         playerName[1][strlen(playerName[1]) - 1] = '\0';

      }
      do{
         boardPrint(atualBoard);
         //globalBoardPrint(globalBoard);
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays,gameMode);  
         while (globalBoard[nBoard / 3][nBoard % 3] != '_')//se ganhar o board na mesma posicao tem bug
         {
            nBoard = rand() % 9;
         }
         convertPositionBoard(nBoard,&x,&y);
         ++nPlays;
         
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

}

int choosePlays(Board *board, Plays **plays, int jogador,char namePlayers[2][255],  int nBoard,int *nBoardBefore, int *mode, int *section, int nPlays, int gameMode ){
   int pos,x,y,res,resp,k,resMenu;
   char posStr[255], respStr[255],kStr[255],posK;
   *nBoardBefore = nBoard;

   printf("\nCurrent board: [%d]",nBoard);

   if(jogador == 1){
      printf("\n%s plays:\n",namePlayers[0]);
   }
   else{
      printf("\n%s plays:\n",namePlayers[1]);
   }

	do{
      resMenu = menuGame(nPlays); //1, 2 ou 3 

      if(resMenu == 1){
         if(nPlays < 0 || nPlays == 0){
           printf("Sorry, haven't reached the minimum of moves yet\n");  
         }
         else{
            printf("Plays to see [1-10]: ");
            fgets(kStr,sizeof(kStr),stdin);
            k = atoi(kStr);
            showKPlays(*plays,k,nPlays);
         }
      }
      if(resMenu == 3){
         //pause
         pause(board,*plays,nPlays,gameMode,namePlayers);
         endGame(board,*plays);
      }
      do{
         printf("\nPosition: ");
         fgets(posStr,sizeof(posStr),stdin);
         pos = atoi(posStr);

         res = convertPosition(pos, &x,&y);

         if(pos < 0 || pos > 8 || board[nBoard].section[x][y] != '_'){
            printf("Please enter a valid input\n");
         }
      }while(pos < 0 || pos > 8 || board[nBoard].section[x][y] != '_');
      
      res = convertPosition(pos, &x,&y);

	}while(board[nBoard].section[x][y] != '_' || res == 1 || pos < 0 || pos > 8);
  
   addNodePlays(plays,nBoard,x,y,nPlays);
   //showPlays(*plays);
   
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
     
	}while(board[nBoard].section[x][y] != '_' || res == 1 || pos < 0 || pos > 9 || pos == *section );

   addNodePlays(plays,nBoard,x,y,nPlays);
   //showPlays(*plays);

   setPos(board[nBoard].section,x,y,'O');
   *mode = 1;

   return pos;
}

void rules(){
   printf("test\n");
}

int menuGame(int nPlays){
   char opStr[255];
   int op;
         
   printf(" ___________________________________\n");
   printf("|        Choose one option:         |\n");
   printf("|___________________________________|\n");
   printf("|1-Want to see previous plays?      |\n"
          "|2-Play                             |\n"
          "|3-Pause                            |\n"); 
   printf("|___________________________________|\n");
   putchar('\n');
   do{
        printf("Option: ");
        fgets(opStr,sizeof(opStr),stdin);
        op = atoi(opStr);

        if(op != 1 && op != 2 && op != 3){
            printf("Please enter a valid input [1-3]\n");
        }
    }while(op != 1 && op != 2 && op != 3);  

    return op;
}

void pause(Board *board,Plays *plays, int nPlays, int gameMode, char namePlayers[2][255]){
    FILE * fp;
    int i;
    plays->nPlays = nPlays;
    Plays *aux = plays;

    /*printf("Mode: %d\n",gameMode);
    printf("x: %d\ty: %d\tboard: %d\n",aux->x,aux->y,aux->Board);*/
   
    printf("writing game state to fich.bin...\n");

    fp = fopen("fich.bin","wb");
    if (fp == NULL) {
        perror("Failed to open file\n");
        endGame(board,plays);
    }
     else {
        if(aux == NULL){
           printf("List clean\n");
        }  
        else{
            fwrite(&gameMode,sizeof(int),1,fp); // 1-> BotGame 0-> TwoPlayers
            fwrite(&nPlays, sizeof(int),1,fp); //total
            fwrite(&namePlayers[0], sizeof(int),1,fp);
            fwrite(&namePlayers[1], sizeof(int),1,fp);

            while(aux != NULL){
               fwrite(&aux->x,sizeof(Plays),1,fp);
               fwrite(&aux->y,sizeof(Plays),1,fp);
               fwrite(&aux->Board,sizeof(Plays),1,fp);
               printf("x:%d\ty:%d\tboard:%d\n",aux->x,aux->y,aux->Board);
               aux = aux->next;
            }
         }
     }
     fclose(fp);  
}

void exportFile(Plays *plays, int nPlays){
   FILE *fp;
   Plays *aux = plays;

   char nameFile[255];

   printf("Choose file name to save the succession of all plays: ");
   fgets(nameFile,sizeof(nameFile),stdin);

   fp = fopen(nameFile,"wt");
   if (fp == NULL){
        perror("Failed to save plays to file\n");
   }
   fprintf(fp,"%d\n",nPlays);
   for(int i=0; i<nPlays; ++i){
      fprintf(fp,"Player %d made the move (%d,%d) on Board [%d]\n",aux->nPlays%2 +1,aux->x,aux->y,aux->Board);
         aux = aux->next;  
   }
   fclose(fp);
}

Plays *loadFich(char *nameFile,char namePlayers[2][255]){
   Plays *novo, *aux, *list = NULL;
   FILE *fp;
   char playerName[2][255];
   int gameMode,total;

   fp = fopen(nameFile, "rb");
   if(fp == NULL){
       perror("Failed to open file\n");
      return NULL;
   }
   
   fread(&gameMode,sizeof(int),1,fp); //ja estou a ler no fileio
   fread(&total,sizeof(int),1,fp);
   fread(&playerName[0],sizeof(int),1,fp);
   fread(&playerName[1],sizeof(int),1,fp);

   strcpy(namePlayers[0],playerName[0]);
   strcpy(namePlayers[1],playerName[1]);

   /*while( ( fread(&list,sizeof(Plays),1,fp) == 1 ) ){
         //addNodePlays(&list,list->Board,list->x,list->y,list->nPlays);
         //list = list->next;
   }*/
}


void endGame(Board *board, Plays *plays){
   //removeList(plays);
   //freeBoards(board);
   exit(0); //Skips everything and returns 0
}