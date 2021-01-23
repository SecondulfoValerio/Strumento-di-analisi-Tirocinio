#ifndef TEST_H
#define TEST_H
#include <tabreader.h>
#include <MatrixTest.h>
#include <chisquaretest.h>
#include <chitablereader.h>

/*DEFINIZIONI*/
void testColonneMat(FILE* fp);
void testRigheMat(FILE* fp);
void testColonneSup(FILE* fp);
void testprintMat(char*** tabella,int righe,int colonne);
void testprintArrSup(int* relations,int colonne);
void testElements(int* relations,int colonne);
void testgetNumCategorie(char*** tabella,int righe,int pos);
void testgetCategorie(char*** matrice,int righe, int pos, int catnum);
void testprintMatTest(double** matrice,int righe,int colonne);
void testgetposPrincipal(FILE* fp);
void testgetposOutuput(FILE* fp);
void testtotalElements(double** matrice, int row, int col);
void testdegfreedom(int row,int col);
void testexpectedValue(double** matrice, int row,int col);
void printrowsumsarray(double** matrice, int row,int col);
void printcolumnsumsarray(double** matrice, int row,int col);
void testchivalue(double**matrice,int row,int col);
void testgetColumnNum(FILE* fp);
void testgetRowNum(FILE* fp);
void testgetColPos(FILE* fp,double sl);
void testgetRowPos(FILE* fp, int df);
void testgetCriticalValue(FILE* fp,int sl,int df);
void testgetChiTestResult(double y1,double y2,double  x1,double x2,double chiv);
void testgetSignificanceLevel(FILE*fp,int pos);
void testchiTestCompare(FILE* fp, double chivalue,int df);

/*FUNZIONI*/

//STAMPA COLONNE MATRICE
void testColonneMat(FILE* fp){
	printf("Colonne Matrice:%d\n",numcolMat(fp));
	return;
}
//STAMPA RIGHE MATRICE
void testRigheMat(FILE* fp){
	printf("Righe Matrice:%d\n",numcolMat(fp));
	return;
}
//STAMPA COLONNE FILE SUPPORTO
void testColonneSup(FILE* fp){
	printf("Colonne file supporto:%d\n",numcolSup(fp));
	return;
}

//STAMPA MATRICE
void testprintMat(char*** tabella,int righe,int colonne){
	for(int i=0;i<righe;i++){
		printf("Riga %d ",i);
		for(int g=0;g<colonne;g++)
			printf("%s ",tabella[i][g]);
		printf("\n");
	}
	return;
}

//STAMPA ARRAY DI SUPPORTO
void testprintArrSup(int* relations,int colonne){
	printf("\n");
	for(int i=0;i<colonne;i++)
		printf("Importanza el %d:%d\n",i+1,relations[i]);
	return;
}
//VERIFICA ELEMENTI SUPPORTO
void testElements(int* relations,int colonne){
	printf("Lista supporto\n");
	for(int i=0;i<colonne;i++){
		printf("elemento[%d]:E' parola?=%d E' numero?=%d E' rilevante?=%d E' principale?=%d E' output?=%d E' input?=%d Descrizione:%s Valore:%d\n",
				i,isWord(relations[i]),
				isNumber(relations[i]),isRelevant(relations[i]),isPrincipal(relations[i]),
				isOutput(relations[i]),isInput(relations[i]),
				getDescription(relations[i]),relations[i]);

	}
return;
}

//NUMERO CATEGORIE IN COLONNA MATRICE
void testgetNumCategorie(char*** tabella,int righe,int pos){
	printf("Ci sono %d categorie in %s\n",getNumCategorie(tabella,righe,pos),tabella[0][pos]);
}

//STAMPA ARRAY CATEGORIE
void testgetCategorie(char*** matrice,int righe, int pos, int catnum){
	char** categorie= getCategorie(matrice,righe,pos,catnum);
	printf("\nCATEGORIE TROVATE IN %s\n",matrice[0][pos]);
	for(int i=0;i<catnum;i++)
		printf("%s\n",categorie[i]);
	printf("---------------------------------\n");
}

//STAMPA MATRICE PER IL TEST
void testprintMatTest(double** matrice,int righe,int colonne){
	printf("----------------------------------------\n");
	printf("Matrice per il Test\n");
	for(int i=0;i<righe;i++){
		for(int j=0;j<colonne;j++)
			printf("%lf ",matrice[i][j]);
		printf("\n");
	}
	printf("----------------------------------------\n");
}

//STAMPA POSIZIONE COLONNA PRINCIPALE
void testgetposPrincipal(FILE* fp){
	printf("La colonna Principale è la %da\n",getposPrincipal(fp)+1);

}
//STAMPA POSIZIONE COLONNA OUTUPUT
void testgetposOutuput(FILE* fp){
	printf("La colonna Outuput è la %da\n",getposOutput(fp)+1);
}
//STAMPA LE OCCORRENZE DI VALORE A IN COLONNA 1 E VALORE B IN COLONNA 2
void testgetOccurence(char*** matrice,char* nomeA, char* nomeB, int posA, int posB, int righe){
	printf("Numero di occorrenze di %s %s=%d\n",nomeA,nomeB,getOccurence(matrice,nomeA,nomeB,posA,posB,righe));
}
//STAMPA LA SOMMATORIA GLI ELEMENTI PER OGNI RIGA DELLA MATRICE
void testtotalrow(double** matrice, int row, int col){
	for(int i=0;i<row;i++)
		printf("Totale riga %d: %lf\n",i+1,totalrow(matrice,i,col));
}
//STAMPA LA SOMMATORIA GLI ELEMENTI PER OGNI COLONNA DELLA MATRICE
void testtotalcol(double** matrice, int row, int col){
	for(int i=0;i<col;i++)
		printf("Totale colonna %d: %lf\n",i+1,totalcol(matrice,row,i));
}
//STAMPA LA SOMMATORIA DEGLI ELEMENTI DELLA MATRICE
void testtotalElements(double** matrice, int row, int col){
	printf("Totale elementi matrice=%f \n",totalElements(matrice,row,col));
}
//STAMPA I GRADI DI LIBERTA' DELLA MATRICE
void testdegfreedom(int row,int col){
	printf("Gradi di libertà= %d\n",degfreedom(row,col));
}
//STAMPA L'EXPECTED VALUE PER OGNI VALORE DELLA MATRICE
void  testexpectedValue(double** matrice, int row,int col){
	double tot= totalElements(matrice,row,col);
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			printf("Expected Value riga %d colonna %d: %lf = %lf\n",i+1,j+1,matrice[i][j],expectedValue(totalrow(matrice,i,col),totalcol(matrice,row,j),tot));
									}
//STAMPA GLI ELEMENTI DELL'ARRAY CHE CONTIENE LE SOMME DEGLI ELEMENTI PER OGNI RIGA DELLA MATRICE
void testrowsums(double** matrice, int row,int col){
	double* rowsum= rowsums(matrice,row,col);
	for(int i=0;i<row;i++)
		printf("Sommatoria riga %d = %lf\n",i+1,rowsum[i]);
}
//STAMPA GLI ELEMENTI DELL'ARRAY CHE CONTIENE LE SOMME DEGLI ELEMENTI PER OGNI COLONNA DELLA MATRICE
void testcolumnsums(double** matrice, int row,int col){
	double* colsum= columnsums(matrice,row,col);
		for(int i=0;i<col;i++)
			printf("Sommatoria colonna %d = %lf\n",i+1,colsum[i]);
}
//STAMPA CHI VALUE MATRICE
void testchivalue(double**matrice,int row,int col){
	printf("Chi value= %lf\n",chivalue(matrice,row,col));
}
//STAMPA NUMERO RIGHE CHI TABLE
void testgetColumnNum(FILE* fp){
	printf("Numero colonne ChiTable:%d\n",getColumnNum(fp));
}
//STAMPA NUMERO COLONNE CHI TABLE
void testgetRowNum(FILE* fp){
	printf("Numero righe ChiTable:%d\n",getRowNum(fp));
}
//STAMPA POSIZIONE SL IN CHI TABLE
void testgetColPos(FILE* fp,double sl){
	printf("Elemento %lf in colonna %d\n",sl,getColPos(fp,sl));
}
//STAMPA POSIZIONE DF IN CHI TABLE
void testgetRowPos(FILE* fp, int df){
	printf("Elemento %d in riga %d\n",df,getRowPos(fp,df));
}
//STAMPA CRITICAL VALUE IN CHI TABLE
void testgetCriticalValue(FILE* fp,int df,int sl){
	printf("Elemento DF= %d SL= %d=%lf\n",df,sl,getCriticalValue(fp,df,sl));
}
//STAMPA RISULTATO CHI TEST (DA TOGLIERE POI)
/*void testchiTestCompare(double cv,double chiv){
	chiTestCompare(cv,chiv);
} */
//STAMPA RISULTATO CHI TEST NUOVO METODO
void testgetChiTestResult(double y1,double y2,double  x1,double x2,double chiv){
	 getChiTestResult( y1, y2,  x1, x2, chiv);
}
//STAMPA SL IN POSIZIONE POS IN CHI TABLE
void testgetSignificanceLevel(FILE*fp,int pos){
	printf("Significance Level:%lf\n",getSignificanceLevel(fp,pos));
}
//STAMPA RISULTATO CHI TEST
void testchiTestCompare(FILE* fp, double chivalue,int df){
	chiTestCompare(fp,chivalue,df);
}

#endif
