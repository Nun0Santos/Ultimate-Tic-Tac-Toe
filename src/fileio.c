#include "globals.h"
#include "header.h"

int menu(){
    char opStr[255];
    int op;
    printf(" __________________________\n");
    printf("|    Choose one option:    |\n");
    printf("|__________________________|\n");
    printf("|1-Multiplayer             |\n"
           "|2-Singleplayer            |\n"
           "|3-Help                    |\n"
           "|4-Exit                    |\n"
           "|__________________________|\n");

    putchar('\n');
    
    do{
        printf("Option: ");
        fgets(opStr,sizeof(opStr),stdin);
        op = atoi(opStr);

        if(op != 1 && op != 2 && op != 3 && op != 4){
            printf("Please enter a valid input [1-4]\n");
        }

    }while(op != 1 && op != 2 && op != 3 && op != 4);  

    return op;
}

int menuGame(){
   char opStr[255];
   int op;
         
   printf(" ___________________________________\n");
   printf("|        Choose one option:         |\n");
   printf("|___________________________________|\n");
   printf("|1-Previous plays                   |\n"
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

void initializer(){
    int tmp=0,op,opF;
    bool gameMode;
    char opStr = 'N';
    char loadopt = 'N';
    char loadoptStr[255];
    FILE *fp = NULL;
    Plays *plays = NULL;
    
    //Verify if we have to load the jogo.bin
    fp = fopen("fich.bin","rb");
    if( fp != NULL){
        printf("A jogo.bin file with valid data has bin found, do you wish to load the previous game?(Y/N)\n");
        
        do{
            printf("Option: ");
            fgets(loadoptStr,sizeof(loadoptStr) - 1,stdin);
            
            if( loadoptStr[0] != 'Y' && loadoptStr[0] != 'N'){
                printf("Please enter a valid input: Y(Yes) or N(No)\n");
            }

        }while( loadoptStr[0] != 'Y' && loadoptStr[0] != 'N');

        if(loadoptStr[0] == 'Y'){
            fread(&gameMode,sizeof(bool),1,fp);
            fclose(fp);

            if(gameMode == BOT_GAME)
                game(gameMode,RESUME_GAME); //Computador (Resume)
            else
                game(gameMode,RESUME_GAME); //2 Players (Resume)
        }
        else{//Option == N
         fclose(fp);
         remove("fich.bin");
        }
    }  
    
    if(opStr == 'N' && loadopt == 'N'){
        op = menu();

        do{
            if(op == 1)//Two_Players
                game(TWO_PLAYERS,NEW_GAME);
            if(op == 2)//Computer
                game(BOT_GAME,NEW_GAME);
            if(op == 3)//rules 
                rules();
        }while(op == 3);
    }
}

