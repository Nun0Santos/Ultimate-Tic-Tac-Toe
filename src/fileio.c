#include "globals.h"
#include "header.h"


int menu(){
    char opStr[255];
    int op;

    printf("Choose one option:\n");
    printf("\t1-Play against person\n"
                 "\t2-Play against computer\n"
                 "\t3-Help\n"
                 "\t4-Exit\n");
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

void initializer(){
    int tmp=0,op;
    bool gameMode;
    char opStr = 'N';
    FILE *fp;
    
    //Verify if we have to load the jogo.bin
    fp = fopen("jogo.txt","rt");
    if( fp != NULL){
        printf("A jogo.bin file with valid data has bin found, do you wish to load the previous game?(Y/N)");
        
        do{
            printf("Option: ");
            fgets(&opStr,sizeof(opStr),stdin);
          
            if( opStr != 'Y' && opStr != 'N'){
                printf("Please enter a valid input: Y(Yes) or N(No)\n");
            }

        }while(opStr != 'Y' && opStr != 'N');
    }  
    if(opStr == 'Y'){
        fread(&gameMode,sizeof(bool),1,fp);
        fclose(fp);

        if(gameMode == BOT_GAME)
            game(gameMode); //Computador (Resumir)
        else
            game(gameMode); //2 Players (Resumir)
    }
    else{//Option == N
       //fclose(fp);
    }
    
    if(opStr == 'N'){
        op = menu();

        do{
            if(op == 1)//2 jogadores
                game(TWO_PLAYERS);
            if(op == 2)//Computer
                game(BOT_GAME);
            if(op == 3)//rules 
                rules();
        }while(op == 3);
    }
}
