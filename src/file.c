#include "file.h"


void pause(Board *board,Plays *plays, int nPlays, int gameMode, char namePlayers[2][255],int joga, int nBoardBefore,int *completedBoards, int howManyBoards,int *drawBoards, int indexDraw){
    FILE * fp = NULL;
    Plays *aux = plays;

    plays->nPlays = nPlays;
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
            fwrite(&namePlayers[0], sizeof(char),255,fp);
            fwrite(&namePlayers[1], sizeof(char),255,fp);
            fwrite(&joga,sizeof(int),1,fp); //de quem dá pause
            fwrite(&nBoardBefore,sizeof(int),1,fp);
        
            while(aux != NULL){
               fwrite(&aux->x,sizeof(int),1,fp);
               fwrite(&aux->y,sizeof(int),1,fp);
               fwrite(&aux->Board,sizeof(int),1,fp);
               fwrite(&aux->nPlays,sizeof(int),1,fp);
               fwrite(&aux->player,sizeof(int),1,fp);
               //printf("x:%d\ty:%d\tboard:%d\tPlayer: %d\n",aux->x,aux->y,aux->Board,aux->nPlays%2 +1);
               aux = aux->next;
            }
         }
      fclose(fp); 
     } 
}

void exportFile(Plays *plays, int nPlays){
   FILE *fp = NULL;
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
      fprintf(fp,"Player %d made the move (%d,%d) on Board [%d]\n",aux->player,aux->x,aux->y,aux->Board);
         aux = aux->next;  
   }
   fclose(fp);
}

Plays *loadFich(Board *board,char *nameFile,char namePlayers[2][255], int *nBoard,int *nPlays, int *joga, int *nBoardBefore,int *completedBoards, int *itLoad,char globalBoard[3][3], int *drawBoards, int *indexDraw){
   Plays *list = NULL;
   Plays aux;
   FILE *fp = NULL;
   int gameMode,total,jogador,nBoardbefore,x=0,y=0, xWhile=0,O=0;
   int count=0;

   fp = fopen(nameFile, "rb");
   if(fp == NULL){
      perror("Failed to open file\n");
      return NULL;
   }

   fread(&gameMode,sizeof(int),1,fp); 
   fread(&total,sizeof(int),1,fp);
   *nPlays = total;
   fread(&namePlayers[0],sizeof(namePlayers[0]),1,fp);
   fread(&namePlayers[1],sizeof(namePlayers[1]),1,fp);
   fread(&jogador,sizeof(int),1,fp);
   fread(&nBoardbefore,sizeof(int),1,fp);
   *joga= jogador;
   *nBoardBefore = nBoardbefore;

   while(fread(&aux.x,sizeof(int),1,fp) &&
      fread(&aux.y,sizeof(int),1,fp) &&
      fread(&aux.Board,sizeof(int),1,fp) && 
      fread(&aux.nPlays,sizeof(int),1,fp) &&
      fread(&aux.player,sizeof(int),1,fp) )
   {
      //printf("x:%d\ty:%d\tboard:%d\tnplays:%d\tjogador:%d\n",aux.x,aux.y,aux.Board,aux.nPlays,aux.player);
      addNodePlays(&list,aux.Board,aux.x,aux.y,aux.nPlays,aux.player);
      *nBoard = aux.Board;

      if(count%2 == 0 ){//Ou aux.player == 1
         board[*nBoard].section[aux.x][aux.y] = 'X'; 
         if(verifyWinner(board,aux.Board)  == 0 ){
            winnerSection(board,aux.Board,globalBoard,1,namePlayers);
            xWhile++;
         }
      }
      else{
         board[*nBoard].section[aux.x][aux.y] = 'O';  
         if(verifyWinner(board,aux.Board)  == 0 ){
            winnerSection(board,aux.Board,globalBoard,2,namePlayers);
            xWhile++;
         }
      }
      if(verifyWinner(board,aux.Board) == 1){//Empate
         convertPosition(aux.Board,&x,&y);
         globalBoard[x][y] = '.';
      }
      ++count;
   }
   //showPlays(list);
   fclose(fp);
   return list;
}
