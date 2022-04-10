#include "header.h"

char menu(){
    welcome();
    char op;

    printf("Choose one option:\n");
    printf("\t1-Play against person\n"
                 "\t2-Play against computer\n"
                 "\t3-Help\n"
                 "\t4-Exit\n");
    do{
        printf("Option: ");
        scanf(" %c",&op);
        
        if(op != '1' && op != '2' && op != '3' && op != '4'){
            printf("Please enter a valid input [1-4]\n");
        }
    }while(op != '1' && op != '2' && op != '3' && op != '4');  
    return op;
}

void initializer(){
    int tmp=0;
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
        fread(&tmp,sizeof(int),1,fp);
        fclose(fp);
    }
    else{//Option == N
       //fclose(fp);

    }
    if(op == 'N'){
        op = menu();
        do{
            if(op == '1'){
            //2 jogadores
            }
            if(op == '2'){
            //Computer
            }
            if(op == '3'){
            //rules     
            }

        }while(op == '3');

    }
}