#include "header.h"

char menu(){
    //welcome();
    char op;

    printf("Choice one option:\n");
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
    char op,c,loadopt = 'N';

   //Verify if we have to load the jogo.bin
   //FILE  *fp = fopen("jogo.bin","rb");
   /*if(fp == NULL){
       perror("Error ");
       exit(0);
   }*/
   //fread(&tmp,sizeof(int),1,fp);
   if(tmp == 1){
       printf("A jogo.bin file with valid data has bin found, do you wish to load the previous game?(Y/N)");
       tmp = 0;
       do{
            if (tmp != 0){
                printf("Error in input\n");
                scanf("%c",&loadopt);
                while((c = getchar()) != '\n' && c != EOF) ;
                tmp=1;
            }
        }while(loadopt != 'Y' && loadopt != 'N');
    }
    if(loadopt=='Y'){   //Load jogo.bin:
    
    }else {//loadopt ==N
        //fclose(fp);
        //remove ("jogo.bin")
    }

    op = menu();

}