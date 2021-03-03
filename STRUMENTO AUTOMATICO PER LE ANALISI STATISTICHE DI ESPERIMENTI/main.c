#include <test.h>
#include <chisquareexecution.h>


int main(int argc,char*argv[]){
//PROGRAMMA

if(argc<4){printf("Troppo pochi argomenti\n");return 0;}
if(argc>4){printf("Troppo argomenti\n");return 0;}


verbose=atoi(argv[3]);
if(verbose!=1 && verbose!=0){
	printf("Flag invalido\n"); return 0;
}
//FILE* chitable=fopen("chitable.txt","r"); if(chitable==NULL){printf("File chitable inesistente\n");return 0;}
FILE* chitable=fopen("chitablemax.txt","r"); if(chitable==NULL){printf("File chitable inesistente\n");return 0;}
FILE* filetest=fopen(argv[1],"r"); if(filetest==NULL){printf("File test inesistente\n");return 0;}
FILE* filesupport=fopen(argv[2],"r"); if(filesupport==NULL){printf("File supporto inesistente\n");return 0;}
int verbose=atoi(argv[3]);
dotest(filetest,filesupport,chitable);


//PER I TEST. DA TOGLIERE A FINE PROGRAMMA
/*verbose=0;
FILE* chitabletest=fopen("chitable.txt","r");
FILE* filefumatori3=fopen("testfumatori3.txt","r");
FILE* filesupfumatori3=fopen("testfumatorisupporto3.txt","r");
dotest(filefumatori3,filesupfumatori3,chitabletest);
*/




//fclose(chitabletest);
//fclose(filefumatori3);
//fclose(filesupfumatori3);
fclose(chitable);
fclose(filetest);
fclose(filesupport);

return 0;

}
