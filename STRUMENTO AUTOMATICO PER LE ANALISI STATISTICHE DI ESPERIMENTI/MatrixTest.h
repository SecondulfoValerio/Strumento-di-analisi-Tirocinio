#ifndef MATRIXTEST_H
#define MATRIXTEST_H
#include <tabreader.h>

/*DEFINIZIONI FUNZIONI*/
int getNumCategorie(char*** matrice,int righe,int pos); //RESTITUISCE IL NUMERO DI ELEMENTI DIVERSI NELL'ARRAY (NUM. DI CATEGORIE)
char** getCategorie(char*** matrice, int righe,int pos,int catnum); //RESTIUISCE UN ARRAY DI STRINGHE CON LE CATEGORIE
int getOccurence(char*** matrice,char* nomeA, char* nomeB, int posA, int posB, int righe);//RESTITUISCE NUMERI DI OCCORRENZE DI ELEMENTO NOME1=A NOME2=B NELLA MATRICE
double** makeTestMatrix(char*** matrice,int righe,int colonnaI,int colonnaO);//CREA E RESTITUISCE LA MATRICE CON I DATI PER IL TEST
int getCatOccurence(char*** matrice,int rows,int col,char* categoria); //RITORNA NUMERO DI OCCORRENZE DI UNA CATEGORIA IN COL

/*FUNZIONI*/


int getNumCategorie(char*** matrice,int righe,int pos){
int numcategorie=0;

		for(int a=2;a<righe;a++){
			int b=0;
			if(matrice[a][pos]==NULL)
				continue;
			for(b=1;b<a;b++){
				if( matrice[b][pos]==NULL)
					continue;
				if(strcmp(matrice[b][pos],matrice[a][pos])==0)
					break;
			}
			if(a==b)
				numcategorie++;
		}
return numcategorie+1;
}

char** getCategorie(char*** matrice, int righe,int pos,int catnum){
	char** categorie=(char**)calloc(catnum,sizeof(char*));
	int el=0;
	if(righe==1){
		categorie[el]=matrice[1][pos];
		return categorie;}
	categorie[el]=matrice[1][pos];
	el++;
	while(el<catnum){
		for(int a=2;a<righe;a++){
					int b=0;
					if(matrice[a][pos]==NULL)
						continue;
					for(b=1;b<a;b++){
						if( matrice[b][pos]==NULL)
							continue;
						if(strcmp(matrice[b][pos],matrice[a][pos])==0)
							break;
					}
					if(a==b){
						categorie[el]=matrice[a][pos];
						el++;
					}
		}

	}
	return categorie;
}


int getOccurence(char*** matrice,char* nomeA, char* nomeB, int posA, int posB, int righe){
	int occ=0;
	for(int i=0;i<righe;i++){
		if(matrice[i][posA]==NULL)
				continue;
		if( strcmp(matrice[i][posA],nomeA)==0){
			if(matrice[i][posB]==NULL)
				continue;
			if( strcmp(matrice[i][posB],nomeB)==0)
				occ++;
		}
	}
	return occ;
}


double** makeTestMatrix(char*** matrice,int righe,int colonnaI,int colonnaO){
	int rows= getNumCategorie(matrice,righe,colonnaI); //numero di categorie nella colonna Input
	int col= getNumCategorie(matrice,righe,colonnaO); //numero di categorie nella colonna Output
	char** catI= getCategorie(matrice,righe,colonnaI,rows); //array con le categorie nella colonna Input
	char** catO= getCategorie(matrice,righe,colonnaO,col); //array col le categorie nella colonna Output
	double** testmatrix= (double**)calloc(rows,sizeof(double*));
	if(rows==0 || col==0){ //TEST
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				testmatrix[i][j]=0;
		return testmatrix;
	}

	if(col==1){
		for(int i=0;i<rows;i++){
				testmatrix[i]=(double*)calloc(col,sizeof(double));
				for(int j=0;j<col-1;j++)
					testmatrix[i][j]= getOccurence(matrice,catI[i],catO[j],colonnaI,colonnaO,righe);
			}
		for(int i=0;i<rows;i++){
			testmatrix[i][col-1]=0;
		}
		for(int i=0;i<rows;i++)
			for(int j=0;j<col;j++)
		return testmatrix;
	}
	for(int i=0;i<rows;i++){
		testmatrix[i]=(double*)calloc(col,sizeof(double));
		for(int j=0;j<col;j++)
			testmatrix[i][j]= getOccurence(matrice,catI[i],catO[j],colonnaI,colonnaO,righe);
	}
	return testmatrix;


}

int getCatOccurence(char*** matrice,int rows,int col,char* categoria){
	if(matrice==NULL){printf("Matrice non creata\n");return -1;}
	int occ=0;
	for(int i=0;i<rows;i++){
		if(matrice[i][col]==NULL)
			continue;
		if(strcmp(matrice[i][col],categoria)==0)
			occ++;
	}
	return occ;


}




#endif
