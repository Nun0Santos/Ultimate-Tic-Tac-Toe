#include "file.h"


void pause(Board *board,Plays *plays, int nPlays, int gameMode, char namePlayers[2][255]){
    FILE * fp;
    int i;
    plays->nPlays = nPlays;
    Plays *aux = plays;

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
            fwrite(&namePlayers[0], sizeof(namePlayers[0]),1,fp);
            fwrite(&namePlayers[1], sizeof(namePlayers[1]),1,fp);

            while(aux != NULL){
               fwrite(&aux->x,sizeof(int),1,fp);
               fwrite(&aux->y,sizeof(int),1,fp);
               fwrite(&aux->Board,sizeof(int),1,fp);
               fwrite(&aux->nPlays,sizeof(int),1,fp);
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

Plays *loadFich(Board *board,char *nameFile,char namePlayers[2][255], int *nBoard){
   Plays *list = NULL;
   Plays aux;
   FILE *fp;
   int gameMode,total;

   fp = fopen(nameFile, "rb");
   if(fp == NULL){
       perror("Failed to open file\n");
      return NULL;
   }

   fread(&gameMode,sizeof(int),1,fp); //ja estou a ler no fileio
   fread(&total,sizeof(int),1,fp);
   fread(&namePlayers[0],sizeof(namePlayers[0]),1,fp);
   fread(&namePlayers[1],sizeof(namePlayers[1]),1,fp);
   printf("%s\n",namePlayers[0]);

   while(fread(&aux.x,sizeof(int),1,fp) &&
      fread(&aux.y,sizeof(int),1,fp) &&
      fread(&aux.Board,sizeof(int),1,fp) && 
      fread(&aux.nPlays,sizeof(int),1,fp) )
      {
         //printf("x:%d\ty:%d\tboard:%d\n",aux.x,aux.y,aux.Board);
         addNodePlays(&list,aux.Board,aux.x,aux.y,total);

         *nBoard = aux.Board;

         if(aux.nPlays%2 == 0)
            board[*nBoard].section[aux.x][aux.y] = 'X';  
         else
            board[*nBoard].section[aux.x][aux.y] = 'O';  
   }
   fclose(fp);
   return list;
}
