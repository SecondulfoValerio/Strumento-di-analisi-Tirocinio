#ifndef FILTERMATRIX_H
#define FILTERMATRIX_H
#include <tabreader.h>

int* secondarycol(int* support,int el);//PRENDE IN INPUT L'ARRAY INT DEL FILE SUPPORTO E RITORNA UN ARRAY CON LE VARIE COLONNE SECONDARY RELEVANT
char*** filtermatrix(char*** matrix,char* categoria, int occorrenze,int colonna,int righemat,int colonnemat);/*PARTE DALLA MATRICE INIALE
 E CREA UNA MATRICE FILTRANDO SOLO LE RIGHE AVENTI LA CATEGORIA SPECIFICIATA IN COLONNA */


/*
int* secondarycol(int* support,int el){
	int* secrel=(int*)calloc(el,sizeof(int));
	for(int i=0;i<el;i++){
		if(isRelevant(support[i])==1 && isPrincipal(support[i])==0)
			secrel[i]=1;
		else
			secrel[i]=0;
	}
	return secrel;
}
*/

int* secondarycol(int* support,int el){
	int* secrel=(int*)calloc(el,sizeof(int));
	for(int i=0;i<el;i++){
		if(isRelevant(support[i])==1 && isSecondary(support[i])==1)
			secrel[i]=1;
		else
			secrel[i]=0;
	}
	return secrel;
}


char*** filtermatrix(char*** matrix,char* categoria, int occorrenze,int colonna,int righemat,int colonnemat){
	char*** matrixfiltered=(char***)calloc(occorrenze, sizeof(char**));
	int pos=0;
	for(int i=0;i<righemat;i++){
		if(strcmp(matrix[i][colonna],categoria)==0){
			matrixfiltered[pos]=(char**)calloc(colonnemat,sizeof(char*));
			for(int n=0;n<colonnemat;n++){
				matrixfiltered[pos][n]=(char*)malloc(MAX * sizeof(char));
				strcpy(matrixfiltered[pos][n],matrix[i][n]);
			}
			pos++;
		}
	}
	return matrixfiltered;
}

















































#endif
