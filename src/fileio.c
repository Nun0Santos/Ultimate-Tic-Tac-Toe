#include "globals.h"
#include "header.h"


int menu(){
    char opStr[255];
    int op;
    printf(" __________________________\n");
    printf("|    Choose one option:    |\n");
    printf("|__________________________|\n");
    printf("|1-Play against person     |\n"
           "|2-Play against computer   |\n"
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

void initializer(){
    int tmp=0,op,opF;
    bool gameMode;
    char opStr = 'N';
    char opStrF[255];
    FILE *fp;
    
    //Verify if we have to load the jogo.bin
    fp = fopen("fich.bin","rb");
    if( fp != NULL){
        printf("A jogo.bin file with valid data has bin found, do you wish to load the previous game?(Y/N)");
        
        do{
            printf("Option: ");
            fgets(opStrF,sizeof(opStrF),stdin);
            opF = atoi(opStrF);

            if( opF != 1 && opF != 0){
                printf("Please enter a valid input: Y(Yes) or N(No)\n");
            }

        }while( opF != 1 && opF != 0);
    }  
    if(opF == 1){
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
