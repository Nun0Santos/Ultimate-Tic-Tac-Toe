#include "globals.h"
#include "game.h"
#include "file.h"

void game(int gameMode){
   Board *atualBoard;
   atualBoard = boardsInitializer();
   char globalBoard[3][3];
   Plays *plays = NULL;
   char playerName[2][255];
   int joga=1, nPlays=0, won=0, nBoard, nBoardBefore=0,
       resWinner=0, flagPlayerTwo = 0, flagWinnerSection=0, section=-1,x,y;

	nBoard = intUniformRnd(0,8);//Iniciar num board aleatório

   globalBoardInitializer(globalBoard);
   
   printf("First player name: ");
   fgets(playerName[0],sizeof(playerName[0]),stdin);
   playerName[0][strlen(playerName[0]) - 1] = '\0';

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
            nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nBoard);   
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

      printf("Second player name: ");
      fgets(playerName[1],sizeof(playerName[1]),stdin);
      playerName[1][strlen(playerName[1]) - 1] = '\0';

      do{
         boardPrint(atualBoard);
         //globalBoardPrint(globalBoard);
         nBoard=choosePlays(atualBoard,&plays,joga,playerName,nBoard,&nBoardBefore,&gameMode,&section,nPlays);  
         while (globalBoard[nBoard / 3][nBoard % 3] != '_')
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
      printf("%s won!\n",playerName[0]);
   else
      printf("%s won!\n",playerName[1]);
   }
   //Exportação para ficheiro
   exportFile(plays);

}

int choosePlays(Board *board, Plays **plays, int jogador,char namePlayers[2][255],  int nBoard,int *nBoardBefore, int *mode, int *section, int nPlays){
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
      resMenu = menuGame(nPlays); //1 ou 2

      if(resMenu == 1){
         if(nPlays < 0 || nPlays  > 10 || nPlays == 0){
           printf("Sorry, haven't reached the minimum of moves yet\n");  
         }
         else{
            printf("Plays to see [1-10]: ");
            fgets(kStr,sizeof(kStr),stdin);
            k = atoi(kStr);
            showKPlays(*plays,k,nPlays);
         }
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

   *mode = 1;
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
   *mode = 0;

   return pos;
}

void rules(){
   printf("test\n");
}

int menuGame(int nPlays){
   char opStr[255];
   int op;

   printf("Choose one option:\n");
   printf("\t1-Want to see previous plays?\n"
          "\t2-Play\n");
   do{
        printf("Option: ");
        fgets(opStr,sizeof(opStr),stdin);
        op = atoi(opStr);

        if(op != 1 && op != 2){
            printf("Please enter a valid input [1-2]\n");
        }
    }while(op != 1 && op != 2);  

    return op;
}

/*void pause(Board *board,Plays play){
    FILE * fp;
    int i;
    
    printf("writing game state to fich.bin...");
    fp = fopen("fich.bin","wb");
    
    if (fp == NULL) {
        fclose(fp);
        //end_game(ptable,list);
    };
    if (play==NULL){
        i=0;
        fwrite(&i,sizeof(int),1,fp); //To indicate that there is no data to read
        printf("no game data to save, aborting\n");
    } else {
        i=1;
        fwrite(&i,sizeof(int),1,fp); //To indicate that there is data to read
       /* fwrite(&robot1,sizeof(robot1),1,fp);
        fwrite(&initdim,sizeof(initdim),1,fp);*/
        //show(list);
        /*while (play != NULL){
            fwrite(play,sizeof(Plays),1,fp);
            play = play->next;
        }
    }*/
    //Binary save:  
    //[Int flag wether there's valid data, 0 or 1][robot1][initdim][pmaxplays)][linked list]
    //fclose(fp);
    //end_game(ptable,list);
//}*/

void exportFile(Plays *plays){
   FILE *fp;
   char nameFile[255];

   printf("Choose file name to save the succession of all plays: ");
   fgets(nameFile,sizeof(nameFile),stdin);

   fp = fopen(nameFile,"wt");
   if (fp == NULL){
        perror("Failed to save plays to file\n");
   }
   printf("%d\n",plays->nPlays);
   fwrite(&plays->nPlays,sizeof(plays->nPlays),1,fp);
    

   fclose(fp);
}