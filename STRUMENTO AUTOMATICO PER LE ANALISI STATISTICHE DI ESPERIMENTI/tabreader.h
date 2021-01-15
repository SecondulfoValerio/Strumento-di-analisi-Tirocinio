#ifndef TABREADER_H
#define TABREADER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
#define RELEVANT 1
#define NOTRELEVANT 0

typedef char* stringa[MAX];


int numcolMat(FILE*fp); //n colonne
int numrow(FILE* fp); //n righe
int numcolSup(FILE*fp); //n colonne file supporto
char*** initmat(FILE*fp); //crea e restituisce una matrice 2x2 di array
int* initlist(FILE*fp); //crea e restituisce array che racchiude i gradi di importanza dei vari attributi
int isNumber(int elemento);
int isWord(int elemento);
int isRelevant(int elemento);
int isPrincipal(int elemento);
int isInput(int elemento);
int isOutput(int elemento);
char* getDescription(int elemento);
int getposPrincipal(FILE* fp); //restituisce posizione colonna Principale
int getposOutput(FILE* fp); //restituisce posizione colonna Output

int numcolSup(FILE*fp){ //restituisce int numero colonne per l'array del file di supporto
	if(fp==NULL){printf("File non trovato\n");return -1;}
			fseek(fp,0,SEEK_SET);
			char c;
			int col=0;
			c=fgetc(fp);
			while(c!=EOF){
				if(c==';')
					col++;
				c=fgetc(fp);
			}
			return col+1;

}

int numcolMat(FILE*fp){ //restituisce int numero colonne per la matrice del file principale

		if(fp==NULL){printf("File non trovato\n");return -1;}
		fseek(fp,0,SEEK_SET);
		char c;
		int col=0;
		while(c!=EOF){
			c=fgetc(fp);
			if(c=='\n' || c=='\r')
			return col+1;
			if(c==';')
				col++;
		}
		return col+1;
}

int numrow(FILE* fp){ //restituisce int numero righe
	int rows=0;
	if(fp==NULL){printf("File non trovato\n");return -1;}
	fseek(fp,0,SEEK_SET);
	char c;

		while(c!=EOF){
			c=fgetc(fp);
			if(c==EOF) return rows+1;
			if(c=='\n')
				rows++;
		}
	return rows+1;
}

char*** initmat(FILE*fp){

	int row= numrow(fp);
	int col= numcolMat(fp);
	char c;
	fseek(fp,0,SEEK_SET);
	char*** matrice=(char***)calloc(row, sizeof(char**)); //creazione matrice
	for(int i=0;i<row;i++){ //allocazione memoria colonne
		matrice[i]=(char**) calloc(col,sizeof(char*));
							}

	for(int i=0;i<row;i++){ //lettura righe
		for(int j=0;j<col;j++){ //lettura colonne
			matrice[i][j]=(char*)malloc(MAX * sizeof(char)); //alloco spazio singolo array contenuto in riga i colonna j
			c=fgetc(fp);
			if(c==EOF)
				return matrice;
			while(c=='\n' || c=='\r')
				c=fgetc(fp);
			if(c==';'){ //ricorda che questo ; è un secondo ';' che viene trovato dopo il ; considerato durante la scrittura della parola
				matrice[i][j]=NULL;
				continue;
			}
			if(c==' '){
				c=fgetc(fp);
				if(c==';' || c=='\n' || c=='\r' || c==EOF)
					matrice[i][j]=NULL;
				continue;
			}
			for(int x=0;x<MAX;x++){ //lettura file e inserimento in el j colonna
				matrice[i][j][x]=c;
				//printf("matrice[%d][%d][%d]=%c valore %d\n",i,j,x,c,c);
				c=fgetc(fp);
				if(c==EOF)
					return matrice; //fine FILE termino la creazione della matrice

				if(c==';' || c=='\n' || c=='\r')
					break;
			} //fine inserimento elemento in colonna
		 }//fine colonna

	}//fine riga
	return matrice;
}



int* initlist(FILE* fp){ //inizializza l'array del file di supporto
	int colonne= numcolSup(fp);
	fseek(fp,0,SEEK_SET);
	int valore=-1;
	char c;
	c=fgetc(fp);
	int* list=(int*)malloc(colonne*sizeof(int));

	while(c==' '|| c=='\n' || c=='\r')
		c=fgetc(fp);
	for(int x=0;x<colonne;x++){
		valore=0;
		if(c==EOF) return list;
		while(c!=';' && c!='\n' && c!='\r' && c!=EOF){
			if(c=='W'){
						valore+=8;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			if(c=='R'){
						valore+=4;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			if(c=='P'){
						valore+=2;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			if(c=='N'){
						valore+=0;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			if(c=='U'){
						valore+=0;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			if(c=='S'){
						valore+=0;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			if(c=='I'){
						valore+=0;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			if(c=='O'){
						valore+=1;
						//printf("colonna %d char %c valore %d\n",x+1,c,valore);
			}
			c=fgetc(fp);
		}
		list[x]=valore;
		c=fgetc(fp);
	}


	return list;
}

int isNumber(int elemento){
	if(elemento>=0 && elemento<=7)
		return 1;
	return 0;
}
int isWord(int elemento){
		if(elemento>=8 && elemento<=15)
			return 1;
		return 0;
}
int isRelevant(int elemento){
		if(elemento==4 ||elemento==5 ||elemento==6 ||elemento==7 ||elemento==12 ||elemento==13 ||elemento==14 ||elemento==15)
			return 1;
		return 0;
}
int isPrincipal(int elemento){
		if(elemento==2 ||elemento==3 ||elemento==6 ||elemento==7 ||elemento==10 ||elemento==11 ||elemento==14 ||elemento==15)
			return 1;
		return 0;
}
int isInput(int elemento){
	if(elemento==0 ||elemento==2 ||elemento==4 ||elemento==6 ||elemento==8 ||elemento==10 ||elemento==12 ||elemento==14)
		return 1;
	return 0;
}
int isOutput(int elemento){
	if(elemento==1 ||elemento==3 ||elemento==5 ||elemento==7 ||elemento==9 ||elemento==11 ||elemento==13 ||elemento==15)
		return 1;
	return 0;
}

char* getDescription(int valore){
	if(valore==0)
		return ("NUSI");
	if(valore==1)
		return ("NUSO");
	if(valore==2)
		return ("NUPI");
	if(valore==3)
		return ("NUPO");
	if(valore==4)
		return ("NRSI");
	if(valore==5)
		return ("NRSO");
	if(valore==6)
		return ("NRPI");
	if(valore==7)
		return ("NRPO");
	if(valore==8)
		return ("WUSI");
	if(valore==9)
		return ("WUSO");
	if(valore==10)
		return ("WUPI");
	if(valore==11)
		return ("WUPO");
	if(valore==12)
		return ("WRSI");
	if(valore==13)
		return ("WRSO");
	if(valore==14)
		return ("WRPI");
	if(valore==15)
		return ("WRPO");
return NULL;
}

int getposPrincipal(FILE* fp){
	fseek(fp,0,SEEK_SET);
	int pos=0;
	char c;
	c=fgetc(fp);
	while(c!=EOF){
		if(c==';')
			pos++;
		if(c=='P')
			return pos;
	c=fgetc(fp);

	}
	printf("Colonna Principale non trovata\n");
	return -1;
}

int getposOutput(FILE* fp){
	fseek(fp,0,SEEK_SET);
	int pos=0;
	char c;
	c=fgetc(fp);
	while(c!=EOF){
		if(c==';')
			pos++;
		if(c=='O')
			return pos;
	c=fgetc(fp);

	}
	printf("Colonna Output non trovata\n");
	return -1;
}




#endif
