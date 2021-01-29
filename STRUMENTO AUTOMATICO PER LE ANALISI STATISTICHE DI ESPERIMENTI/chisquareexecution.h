#ifndef CHISQUAREXECUTION_H
#define CHISQUAREXECUTION_H
#include <tabreader.h>
#include <MatrixTest.h>
#include <chisquaretest.h>
#include <chitablereader.h>
#include <filtermatrix.h>

void dotest(FILE* test,FILE*support,FILE*chitable);//Esegue tutti i test partendo da principale
void calculate();//Esegue tutti i calcoli del chi test
void doprincipal(char*** matrice,int righematrice,int colonnematrice,int posPrincipale,int posOutput,FILE*chitable); //Esegue il test per la colonna principale e di output
void dosecondary(FILE*test,FILE*chitable,char*** matrice,int* arraysecondario, int elemsecondario,int righematrice,int colonnematrice,int posInout,int posOutput);
void docombinations();//Esegue il test combinando tutte le colonne secondarie


void dotest(FILE* test,FILE*support,FILE*chitable){
printf("------ESEGUO TEST------\n");
char*** matrice=initmat(test);
int* arrsupporto=initlist(support);
int elementisupporto=numcolSup(support);
int righematrice=numrow(test);
int colonnematrice=numcolMat(test);
int posPrincipale=getposPrincipal(support);
int posOutput=getposOutput(support);

doprincipal(matrice,righematrice,colonnematrice,posPrincipale,posOutput,chitable);
dosecondary(test,chitable,matrice,arrsupporto,elementisupporto,righematrice,colonnematrice,posPrincipale,posOutput);
}

void getmatrixtestvalues(double**matriced,char*** matrice,int righematchar,int righe,int colonne,int colonnaI,int colonnaO){
	int numInput=getNumCategorie(matrice,righematchar,colonnaI);
	int numOutput=getNumCategorie(matrice,righematchar,colonnaO);
	char** catI= getCategorie(matrice,righematchar,colonnaI,numInput); //array con le categorie nella colonna Input
	char** catO= getCategorie(matrice,righematchar,colonnaO,numOutput); //array col le categorie nella colonna Output
	double totel=totalElements(matriced,righe,colonne);
	printf("righe %d colonne %d tot el=%lf\n",righe,colonne,totel);
		for(int i=0;i<numInput;i++){
			for(int j=0;j<numOutput;j++){
				int occ=getOccurence(matrice,catI[i],catO[j],colonnaI,colonnaO,righematchar);
				printf("%s %s=%lf%%\n",catI[i],catO[j],(occ/totel)*100);
			}
		}

}



void calculate(char*** matrice,int righematrice,int posPrincipale,int posOutput,FILE*chitable){
	double** matricetest= makeTestMatrix(matrice, righematrice,posPrincipale,posOutput);
		int righe=getNumCategorie(matrice,righematrice,posPrincipale);
		int colonne=getNumCategorie(matrice,righematrice,posOutput);
		if(colonne==1)
			colonne++;
		for(int i=0;i<righe;i++){ // DA TOGLIERE
			for(int c=0;c<colonne;c++)
				printf("%lf ",matricetest[i][c]);
		printf("\n");}
		printf("RIGHE %d COLONNE %d\n",righe,colonne);
		getmatrixtestvalues(matricetest,matrice,righematrice,righe,colonne,posPrincipale,posOutput);
		double chiv=chivalue(matricetest,righe,colonne);
		int df=degfreedom(righe,colonne);
		chiTestCompare(chitable,chiv,df);
}

void doprincipal(char*** matrice,int righematrice,int colonnematrice,int posPrincipale,int posOutput,FILE*chitable){
	printf("------ESEGUO PRINCIPALE------\n");
	calculate(matrice,righematrice,posPrincipale,posOutput,chitable);
	printf("------FINE PRINCIPALE------\n\n\n\n");

}

void dosecondary(FILE*test,FILE*chitable,char*** matrice,int* arraysecondario, int elemsecondario,int righematrice,int colonnamatrice,int posInput,int posOutput){
	printf("------ESEGUO SECONDARIA------\n");
	int* occorrenzesupport=secondarycol(arraysecondario,elemsecondario);

for(int i=0;i<elemsecondario;i++){
	if(occorrenzesupport[i]==0) continue;
	if(occorrenzesupport[i]==1){
		printf("Filtro per colonna %d:",i); getNameColumn(test,i); printf("\n");
		int numcategorie=getNumCategorie(matrice,righematrice,i);
		char** categorie= getCategorie(matrice,righematrice,i,numcategorie);

		for(int n=0;n<numcategorie;n++){
			printf("Per %s\n",categorie[n]);
			int catoccorrenze= getCatOccurence(matrice,righematrice,i,categorie[n]);
			char*** matricefiltrata= filtermatrix(matrice,categorie[n],catoccorrenze,i,righematrice,colonnamatrice);
			for(int r=0;r<catoccorrenze;r++){ //DA TOGLIERE
				for(int c=0;c<colonnamatrice;c++)
					printf("%s ",matricefiltrata[r][c]);
				printf("\n");

			}


				calculate(matricefiltrata,catoccorrenze,posInput,posOutput,chitable);
				printf("\n\n\n");
		}

	}
}
printf("------FINE SECONDARIA------\n");
}

/*void dosecondary(FILE*test,FILE*chitable,char*** matrice,int* arraysecondario, int elemsecondario,int righematrice,int colonnamatrice,int posInput,int posOutput){
int* occorrenzesupport=secondarycol(arraysecondario,elemsecondario);

for(int i=0;i<elemsecondario;i++){
	if(occorrenzesupport[i]==0) continue;
	if(occorrenzesupport[i]==1){
		printf("Filtro per colonna %d:",i); getNameColumn(test,i); printf("\n");
		int numcategorie=getNumCategorie(matrice,righematrice,i); printf("numero categorie: %d",numcategorie); printf("\n");
		printf("righe matrice iniziale:%d\ncolonne matrice iniziale:%d\n",righematrice,colonnamatrice);
		char** categorie= getCategorie(matrice,righematrice,i,numcategorie);
		for (int z=0;z<numcategorie;z++)
				printf("%s\n",categorie[z]);
		for(int n=0;n<numcategorie;n++){
			int catoccorrenze= getCatOccurence(matrice,righematrice,i,categorie[n]);
			printf("categoria:%s occorrenze:%d",categorie[n],catoccorrenze); printf("\n");
			printf("Per categoria:%s\n ",categorie[n]);

			char*** matricefiltrata= filtermatrix(matrice,categorie[n],catoccorrenze,i,righematrice,colonnamatrice);
			printf("--------%s--------\n",categorie[n]);
			printf("Righe:%d Colonne%d\n",catoccorrenze,colonnamatrice);
				for(int x=0;x<catoccorrenze;x++){
					for(int y=0;y<colonnamatrice;y++)
						printf("%s ",matricefiltrata[x][y]);

					printf("\n");
				}
				printf("----------------\n");
				printf("Input:%d Output:%d\n",posInput,posOutput);
				calculate(matricefiltrata,catoccorrenze,posInput,posOutput,chitable);
				int numcat1=getNumCategorie(matricefiltrata,catoccorrenze,0);
				int numcat2=getNumCategorie(matricefiltrata,catoccorrenze,1);
				int numcat3=getNumCategorie(matricefiltrata,catoccorrenze,2);
				int numcatinput=getNumCategorie(matricefiltrata,catoccorrenze,posInput);
				int numcatoutput=getNumCategorie(matricefiltrata,catoccorrenze,posOutput);
				printf("numero categorie colonna1:%d colonna2:%d colonna3:%d Input:%d Output:%d\n",numcat1,numcat2,numcat3,numcatinput,numcatoutput);
				char** catI= getCategorie(matricefiltrata,catoccorrenze,posInput,numcatinput); //array con le categorie nella colonna Input
				for(int zz=0;zz<numcatinput;zz++){
									printf("Input: %s ",catI[zz]);
								} printf("\n");
				char** catO= getCategorie(matricefiltrata,catoccorrenze,posOutput,numcatoutput); //array col le categorie nella colonna Output

				for(int zz=0;zz<numcatoutput;zz++){
					printf("Output: %s ",catO[zz]);
								}


		}

	}
}
}
 * */

#endif
