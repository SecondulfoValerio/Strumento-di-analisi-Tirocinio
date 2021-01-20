#include <test.h>



int main(){

FILE* tab=fopen("nomi.txt","r");
FILE* sup=fopen("relations.txt","r");


if(tab==NULL){	printf("Il file cercato è inesistente\n"); return -1;}
if(sup==NULL){	printf("Il file cercato è inesistente\n"); return -1;}
printf("file:\n");

int colonne=numcolMat(tab);
int righe= numrow(tab);
int colonneSup=numcolSup(sup);
char*** tabella=initmat(tab);
int* relations=initlist(sup);

//TEST
printf("\n-------------TEST BASE--------------\n");
testColonneMat(tab); //TEST METODO COLONNE MATRICE
testRigheMat(tab); //TEST METODO RIGHE MATRICE
testColonneSup(sup); //TEST METODO COLONNE FILE SUPPORTO
testprintMat(tabella,righe,colonne); //TEST METODO CREA TABELLA
testprintArrSup(relations,colonneSup); //TEST METODO CREA ARRAY RELAZIONI
testElements(relations,colonneSup); //TEST RICONOSCIMENTO DELLE TIPOLOGIE DI DATO IN ARRAY RELAZIONI
printf("\n-------------FINE TEST BASE--------------\n");


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

//TEST FUMATORI
printf("\n-------------TEST FUMATORI--------------\n");
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
printf("\n-------------FINE TEST FUMATORI--------------\n");

//NEW FUMATORI
//COPIA PER NEW FUMATORI
FILE* tab3=fopen("NewFumatori.txt","r");
FILE* sup3=fopen("Fumatorisupporto.txt","r");
int colonne3=numcolMat(tab3);
int righe3= numrow(tab3);
int colonneSup3=numcolSup(sup3);
char*** tabella3=initmat(tab3);
int* relations3=initlist(sup3);
int principal2=getposPrincipal(sup3);
int output2=getposOutput(sup3);
double** matriceTest2=makeTestMatrix(tabella3,righe3,principal2,output2);
int rows2=getNumCategorie(tabella3,righe3,principal2);
int columns2=getNumCategorie(tabella3,righe3,output2);

//TEST  NEW FUMATORI
printf("\n-------------TEST NEW FUMATORI--------------\n");
testColonneMat(tab3); //TEST METODO COLONNE MATRICE
testRigheMat(tab3); //TEST METODO RIGHE MATRICE
testColonneSup(sup2); //TEST METODO COLONNE FILE SUPPORTO
testprintMat(tabella3,righe3,colonne3); //TEST METODO CREA TABELLA
testprintArrSup(relations3,colonneSup3); //TEST METODO CREA ARRAY RELAZIONI
testElements(relations3,colonneSup3); //TEST RICONOSCIMENTO DELLE TIPOLOGIE DI DATO IN ARRAY RELAZIONI
testgetNumCategorie(tabella3,righe3,0);
testgetNumCategorie(tabella3,righe3,1);
testgetNumCategorie(tabella3,righe3,2);
testgetNumCategorie(tabella3,righe3,3);
testgetCategorie(tabella3,righe3,0,getNumCategorie(tabella3,righe3,0));
testgetCategorie(tabella3,righe3,1,getNumCategorie(tabella3,righe3,1));
testgetCategorie(tabella3,righe3,2,getNumCategorie(tabella3,righe3,2));
testgetCategorie(tabella3,righe3,3,getNumCategorie(tabella3,righe3,3));
testgetposPrincipal(sup3);
testgetposOutuput(sup3);
testgetOccurence(tabella3,"Maschio","Si",principal2,output2,righe3);
testgetOccurence(tabella3,"Maschio","No",principal2,output2,righe3);
testgetOccurence(tabella3,"Donna","Si",principal2,output2,righe3);
testgetOccurence(tabella3,"Donna","No",principal2,output2,righe3);
testprintMatTest(matriceTest,rows2,columns2);
testtotalrow(matriceTest2,rows2,columns2);
testtotalcol(matriceTest2,rows2,columns2);
testtotalElements(matriceTest2,rows2,columns2);
testdegfreedom(rows,columns2);
testexpectedValue(matriceTest2,rows2,columns2);
testrowsums(matriceTest2,rows2,columns2);
testcolumnsums(matriceTest2,rows2,columns2);
testchivalue(matriceTest2,rows2,columns2);
printf("\n-------------FINE TEST NEW FUMATORI--------------\n");


//CHI TABLE
FILE* chitable=fopen("chitable.txt","r");

//TEST CHI TABLE
printf("\n-------------TEST CHI TABLE--------------\n");
testgetColumnNum(chitable);
testgetRowNum(chitable);
double sl=0.05; double sl2=0.001; double sl3=0.995; double sl4= 0.975;
testgetColPos(chitable,sl);
testgetColPos(chitable,sl2);
testgetColPos(chitable,sl3);
testgetColPos(chitable,sl4);
testgetRowPos(chitable,1);
testgetRowPos(chitable,2);
testgetRowPos(chitable,4);
testgetRowPos(chitable,6);
testgetRowPos(chitable,24);
testgetRowPos(chitable,56);
testgetRowPos(chitable,12);
testgetRowPos(chitable,32);
testgetRowPos(chitable,50);
testgetRowPos(chitable,66);
testgetCriticalValue(chitable,3,6);
testgetCriticalValue(chitable,3,6);
testgetCriticalValue(chitable,0,6);
testgetCriticalValue(chitable,-1,6);
testgetCriticalValue(chitable,200,6);
testgetCriticalValue(chitable,14,6);
testgetCriticalValue(chitable,51,6);
testgetCriticalValue(chitable,51,8);
testgetCriticalValue(chitable,51,11);
testgetCriticalValue(chitable,51,12);



printf("\n-------------FINE TEST CHI TABLE--------------\n");


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
