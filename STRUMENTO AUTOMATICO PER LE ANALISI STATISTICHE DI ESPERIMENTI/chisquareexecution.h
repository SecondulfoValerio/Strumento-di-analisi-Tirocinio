#ifndef CHISQUAREXECUTION_H
#define CHISQUAREXECUTION_H
#include <tabreader.h>
#include <MatrixTest.h>
#include <chisquaretest.h>
#include <chitablereader.h>
#include <filtermatrix.h>
#include <definitions.h>

void dotest(FILE* test,FILE*support,FILE*chitable);//Esegue tutti i test partendo da principale
void calculate();//Esegue tutti i calcoli del chi test
void doprincipal(char*** matrice,int righematrice,int colonnematrice,int posPrincipale,int posOutput,FILE*chitable,FILE*test); //Esegue il test per la colonna principale e di output
void dofiltered(FILE*test,FILE*chitable,char*** matrice,int* arraysecondario, int elemsecondario,int righematrice,int colonnematrice,int posInout,int posOutput); //Esegue il test filtrando per ogni categoria di ogni colonna secondaria
void docombinations(FILE*test,FILE*chitable,char*** matrice,int* arraysecondario, int elemsecondario,int righematrice,int colonnematrice,int posInout,int posOutput);//Esegue il test combinando tutte le colonne secondarie
void getmatrixtestvalues(double**matriced,char*** matrice,int righematchar,int righe,int colonne,int colonnaI,int colonnaO);//Stampa in output % delle categorie Principale e Output partecipanti al test


void dotest(FILE* test,FILE*support,FILE*chitable){
if(verbose==1)
	printf("------ESEGUO TEST------\n");
char*** matrice=initmat(test);
int* arrsupporto=initlist(support);
int elementisupporto=numcolSup(support);
int righematrice=numrow(test);
int colonnematrice=numcolMat(test);
int posPrincipale=getposPrincipal(arrsupporto,elementisupporto);
int posOutput=getposOutput(arrsupporto,elementisupporto);
//int posPrincipale=getposPrincipal(support);
//int posOutput=getposOutput(support);
if(verbose==1)
	printf("------INIZIO PRINCIPALE------\n");
doprincipal(matrice,righematrice,colonnematrice,posPrincipale,posOutput,chitable,test);
if(verbose==1)
	printf("------FINE PRINCIPALE------\n");
if(verbose==1)
	printf("------INIZIO FILTRAGGIO------\n");
dofiltered(test,chitable,matrice,arrsupporto,elementisupporto,righematrice,colonnematrice,posPrincipale,posOutput);
if(verbose==1)
	printf("------FINE FILTRAGGIO------\n");
if(verbose==1)
	printf("------INIZIO COMBINAZIONI------\n");
docombinations(test,chitable,matrice,arrsupporto,elementisupporto,righematrice,colonnematrice,posPrincipale,posOutput);
if(verbose==1)
	printf("------FINE COMBINAZIONI------\n");
}

void getmatrixtestvalues(double**matriced,char*** matrice,int righematchar,int righe,int colonne,int colonnaI,int colonnaO){
	int numInput=getNumCategorie(matrice,righematchar,colonnaI);
	int numOutput=getNumCategorie(matrice,righematchar,colonnaO);
	char** catI= getCategorie(matrice,righematchar,colonnaI,numInput); //array con le categorie nella colonna Input
	char** catO= getCategorie(matrice,righematchar,colonnaO,numOutput); //array col le categorie nella colonna Output
	double totrow;

	for(int i=0;i<numInput;i++){
		totrow=totalrow(matriced,i,numOutput);
		for(int j=0;j<numOutput;j++){
			int occ=getOccurence(matrice,catI[i],catO[j],colonnaI,colonnaO,righematchar);
			if(verbose==1){
				printf("(%s+%s)/%s=%lf%%\n",catI[i],catO[j],catI[i],(occ/totrow)*100);
			}
			else{
				printf("(%s+%s)/%s=%.2lf%%\n",catI[i],catO[j],catI[i],(occ/totrow)*100);

			}
			}
		}

}



void calculate(char*** matrice,int righematrice,int posPrincipale,int posOutput,FILE*chitable,FILE*test){
	double** matricetest= makeTestMatrix(matrice, righematrice,posPrincipale,posOutput);
		int righe=getNumCategorie(matrice,righematrice,posPrincipale);
		int colonne=getNumCategorie(matrice,righematrice,posOutput);
		if(colonne==1)
			colonne++;
		if(verbose==1){
		for(int i=0;i<righe;i++){
			for(int c=0;c<colonne;c++)
				printf("%lf ",matricetest[i][c]);
		printf("\n");}
		}
		if(verbose==1)
			printf("RIGHE %d COLONNE %d\n",righe,colonne);
		getmatrixtestvalues(matricetest,matrice,righematrice,righe,colonne,posPrincipale,posOutput);
		double chiv=chivalue(matricetest,righe,colonne);
		int df=degfreedom(righe,colonne);
		if(verbose==0){
			printf("Prob("); getNameColumn(test,posPrincipale); printf("=>"); getNameColumn(test,posOutput); printf(") = ");
		}
		chiTestCompare(chitable,chiv,df);
}

void doprincipal(char*** matrice,int righematrice,int colonnematrice,int posPrincipale,int posOutput,FILE*chitable,FILE*test){
	calculate(matrice,righematrice,posPrincipale,posOutput,chitable,test);
	printf("\n\n\n");

}

void dofiltered(FILE*test,FILE*chitable,char*** matrice,int* arraysecondario, int elemsecondario,int righematrice,int colonnamatrice,int posInput,int posOutput){
	int* occorrenzesupport=secondarycol(arraysecondario,elemsecondario);

for(int i=0;i<elemsecondario;i++){
	if(occorrenzesupport[i]==0) continue;
	if(occorrenzesupport[i]==1){
		if(verbose==1){
			printf("Filtro per colonna %d:",i); getNameColumn(test,i); printf("\n");
		}
		int numcategorie=getNumCategorie(matrice,righematrice,i);
		char** categorie= getCategorie(matrice,righematrice,i,numcategorie);

		for(int n=0;n<numcategorie;n++){
			printf("Per "); getNameColumn(test,i); printf("=%s\n",categorie[n]);
			int catoccorrenze= getCatOccurence(matrice,righematrice,i,categorie[n]);
			char*** matricefiltrata= filtermatrix(matrice,categorie[n],catoccorrenze,i,righematrice,colonnamatrice);
			if(verbose==1){
				for(int r=0;r<catoccorrenze;r++){
					for(int c=0;c<colonnamatrice;c++)
						printf("%s ",matricefiltrata[r][c]);
					printf("\n");
				}
			}


				calculate(matricefiltrata,catoccorrenze,posInput,posOutput,chitable,test);
				printf("\n\n\n");
		}

	}
}
}

void docombinations(FILE*test,FILE*chitable,char*** matrice,int* arraysecondario, int elemsecondario,int righematrice,int colonnematrice,int posInput,int posOutput){
	int* occorrenzesupport=secondarycol(arraysecondario,elemsecondario);
	int ultimosecondario=-1;
	for(int i=0;i<elemsecondario;i++){
		if(occorrenzesupport[i]==1)
			ultimosecondario=i;
	}
	for(int i=0;i<elemsecondario;i++){
		if(i==ultimosecondario)
			break;
		if(occorrenzesupport[i]==0) continue;
		if(occorrenzesupport[i]==1){
			if(verbose==1){
				printf("Filtro per colonna %d:",i); getNameColumn(test,i); printf("\n");
			}

			int numcategorie=getNumCategorie(matrice,righematrice,i);
			char** categorie= getCategorie(matrice,righematrice,i,numcategorie);

			for(int n=0;n<numcategorie;n++){
				int catoccorrenze= getCatOccurence(matrice,righematrice,i,categorie[n]);
				char*** matricefiltrata= filtermatrix(matrice,categorie[n],catoccorrenze,i,righematrice,colonnematrice);

			for(int x=i+1;x<elemsecondario;x++){
				if(occorrenzesupport[x]==0) continue;
				if(occorrenzesupport[x]==1){
					if(verbose==1){
						printf("Filtro per colonna %d:",x); getNameColumn(test,x); printf("\n");
					}

					int numcategorief=getNumCategorie(matricefiltrata,catoccorrenze,x);
					char** categorief= getCategorie(matricefiltrata,catoccorrenze,x,numcategorief);

					for(int y=0;y<numcategorief;y++){

						int catoccorrenzef= getCatOccurence(matricefiltrata,catoccorrenze,x,categorief[y]);
						char*** matricefiltrata2= filtermatrix(matricefiltrata,categorief[y],catoccorrenzef,x,catoccorrenze,colonnematrice);

					printf("Filtro:");getNameColumn(test,i); printf("=%s,",categorie[n]); getNameColumn(test,x); printf("=%s\n",categorief[y]);

					if(verbose==1){ //STAMPA ELEMENTI MATRICE
												for(int rf=0;rf<catoccorrenzef;rf++){
													for(int cf=0;cf<colonnematrice;cf++)
														printf("%s ",matricefiltrata2[rf][cf]);
													printf("\n");
														}
											}

					calculate(matricefiltrata2,catoccorrenzef,posInput,posOutput,chitable,test);
					printf("\n\n\n");
			}

		}
	}


			}
		}
	}








}



#endif
