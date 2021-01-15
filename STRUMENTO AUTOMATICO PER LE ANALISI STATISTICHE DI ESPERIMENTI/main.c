#include <test.h>



int main(){

FILE* tab=fopen("nomi.txt","r");
FILE* sup=fopen("relations.txt","r");
FILE* chitable=fopen("chitable.txt","r");

if(tab==NULL){	printf("Il file cercato è inesistente\n"); return -1;}
if(sup==NULL){	printf("Il file cercato è inesistente\n"); return -1;}
printf("file:\n");

int colonne=numcolMat(tab);
int righe= numrow(tab);
int colonneSup=numcolSup(sup);
char*** tabella=initmat(tab);
int* relations=initlist(sup);

//TEST
testColonneMat(tab); //TEST METODO COLONNE MATRICE
testRigheMat(tab); //TEST METODO RIGHE MATRICE
testColonneSup(sup); //TEST METODO COLONNE FILE SUPPORTO
testprintMat(tabella,righe,colonne); //TEST METODO CREA TABELLA
testprintArrSup(relations,colonneSup); //TEST METODO CREA ARRAY RELAZIONI
testElements(relations,colonneSup); //TEST RICONOSCIMENTO DELLE TIPOLOGIE DI DATO IN ARRAY RELAZIONI

//COPIA PER FUMATORI
FILE* tab2=fopen("Fumatori.txt","r");
FILE* sup2=fopen("Fumatorisupporto.txt","r");
int colonne2=numcolMat(tab2);
int righe2= numrow(tab2);
int colonneSup2=numcolSup(sup2);
char*** tabella2=initmat(tab2);
int* relations2=initlist(sup2);
int principal=getposPrincipal(sup2);
int output=getposOutput(sup2);
double** matriceTest=makeTestMatrix(tabella2,righe2,principal,output);
int rows=getNumCategorie(tabella2,righe2,principal);
int columns=getNumCategorie(tabella2,righe2,output);

//TEST
testColonneMat(tab2); //TEST METODO COLONNE MATRICE
testRigheMat(tab2); //TEST METODO RIGHE MATRICE
testColonneSup(sup2); //TEST METODO COLONNE FILE SUPPORTO
testprintMat(tabella2,righe2,colonne2); //TEST METODO CREA TABELLA
testprintArrSup(relations2,colonneSup2); //TEST METODO CREA ARRAY RELAZIONI
testElements(relations2,colonneSup2); //TEST RICONOSCIMENTO DELLE TIPOLOGIE DI DATO IN ARRAY RELAZIONI
testgetNumCategorie(tabella2,righe2,0);
testgetNumCategorie(tabella2,righe2,1);
testgetNumCategorie(tabella2,righe2,2);
testgetNumCategorie(tabella2,righe2,3);
testgetCategorie(tabella2,righe2,0,getNumCategorie(tabella2,righe2,0));
testgetCategorie(tabella2,righe2,1,getNumCategorie(tabella2,righe2,1));
testgetCategorie(tabella2,righe2,2,getNumCategorie(tabella2,righe2,2));
testgetCategorie(tabella2,righe2,3,getNumCategorie(tabella2,righe2,3));
testgetposPrincipal(sup2);
testgetposOutuput(sup2);
testgetOccurence(tabella2,"Maschio","Si",principal,output,righe2);
testgetOccurence(tabella2,"Maschio","No",principal,output,righe2);
testgetOccurence(tabella2,"Donna","Si",principal,output,righe2);
testgetOccurence(tabella2,"Donna","No",principal,output,righe2);
testprintMatTest(matriceTest,rows,columns);
testtotalrow(matriceTest,rows,columns);
testtotalcol(matriceTest,rows,columns);
testtotalElements(matriceTest,rows,columns);
testdegfreedom(rows,columns);
testexpectedValue(matriceTest,rows,columns);
testrowsums(matriceTest,rows,columns);
testcolumnsums(matriceTest,rows,columns);
testchivalue(matriceTest,rows,columns);


free(tabella);
free(relations);
fclose(tab);
fclose(sup);


//COPIA PER FUMATORI
free(tabella2);
free(relations2);
fclose(tab2);
fclose(sup2);
free(matriceTest);
return 0;

}
