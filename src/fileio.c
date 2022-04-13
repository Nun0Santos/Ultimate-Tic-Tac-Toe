#include "globals.h"
#include "header.h"


char menu(){
    char op;

    printf("Choose one option:\n");
    printf("\t1-Play against person\n"
                 "\t2-Play against computer\n"
                 "\t3-Help\n"
                 "\t4-Exit\n");
    do{
        printf("Option: ");
        scanf(" %c",&op);
        //fgets(&op,sizeof(op),stdin);
        if(op != '1' && op != '2' && op != '3' && op != '4'){
            printf("Please enter a valid input [1-4]\n");
        }
    }while(op != '1' && op != '2' && op != '3' && op != '4');  
    return op;
}

void initializer(){
    int tmp=0;
    bool gameMode;
    char op = 'N';
    FILE *fp;
   
    //Verify if we have to load the jogo.bin
    if( (fp = fopen("jogo.bin","rb") ) != NULL){
        printf("A jogo.bin file with valid data has bin found, do you wish to load the previous game?(Y/N)");
        do{
            printf("Option: ");
            scanf(" %c",&op);
            if( op != 'Y' && op != 'N'){
                printf("Please enter a valid input: Y(Yes) or N(No)\n");
            }
        }while(op != 'Y' && op != 'N');
    }  
    if(op == 'Y'){
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
    if(op == 'N'){
        op = menu();
        do{
            if(op == '1')//2 jogadores
                game(TWO_PLAYERS);
            if(op == '2')//Computer
                game(BOT_GAME);
            if(op == '3')//rules 
                //rules();
                printf("test");
        }while(op == '3');
    }
}