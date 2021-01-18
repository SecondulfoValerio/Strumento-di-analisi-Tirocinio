#ifndef CHITABLEREADER_H
#define CHITABLEREADER_H
#include <tabreader.h>

#define MAXNUM 10
int getColumnNum(FILE* fp); // RITORNA NUMERO DI COLONNE CHAR TABLE
int getRowNum(FILE* fp); //RITORNA NUMERO DI RIGHE CHAR TABLE
int getColPos(FILE* fp,double sl); //RITORNA POSIZIONE IN COLONNA DI VALORE SL
int getRowPos(FILE* fp,int df); //RITORNA POSIZIONE IN RIGA DI DF

int getColumnNum(FILE* fp){
	if(fp==NULL){printf("File non trovato\n"); return -1;}
	int num=0;
	fseek(fp,0,SEEK_SET);
	char el;
	el=fgetc(fp);
	while(el!=EOF){
		if(el==9)
			num++;
		if(el=='\n' || el=='\r')
			break;
		el=fgetc(fp);
	}
	return num+1;
}

int getRowNum(FILE* fp){
	if(fp==NULL){printf("File non trovato\n"); return -1;}
		int num=0;
		fseek(fp,0,SEEK_SET);
		char el;
		el=fgetc(fp);
		while(el!=EOF){
			if(el=='\n')
				num++;
			el=fgetc(fp);
		}
		return num+1;
}

int getColPos(FILE* fp,double sl){ //RITORNA POSIZIONE COLONNA DELL'ELEMENTO CON VALORE SL, -1 IN CASO DI ERRORE
	if(fp==NULL){printf("File non trovato\n"); return -1;}
	fseek(fp,0,SEEK_SET);
	int pos=0;
	int arrpos=0;
	char temp[20];
	char c;
	c=fgetc(fp);
	while(c!=EOF){
		if(c!='\n' && c!='\r')
		while(c!=9){ //CICLO PER COPIARE IL NUMERO IN I-COLONNA IN ARRAY
			if(arrpos<20){
				temp[arrpos]=c;
				arrpos+=1;}
			c=fgetc(fp);
		}
		if(c==9){
			if(	atof(temp)==sl)
				return pos+1;
			arrpos=0;
			memset(temp, 0, sizeof(temp));
			c=fgetc(fp);
			pos++;
				}
		if(c=='\n' || c=='\r')
			break;
	}
	printf("Valore non trovato\n"); return -1;
}


int getRowPos(FILE* fp,int df){ //RITORNA POSIZIONE RIGA DELL'ELEMENTO CON VALORE SL, -1 IN CASO DI ERRORE
	if(fp==NULL){printf("File non trovato\n"); return -1;}
	fseek(fp,0,SEEK_SET);
	int pos=0;
	int arrpos=0;
	char temp[20];
	char c;
	c=fgetc(fp);

	while(c!=EOF){
		if(c!=9 && c!='\n' && c!='\r'){ //CICLO PER COPIARE IL NUMERO NELLA PRIMA COLONNA IN ARRAY
			if(arrpos<20){
				temp[arrpos]=c;
				arrpos+=1;
			}
			else{printf("Valore df troppo grande. Non supportato\n");return -1;}
			c=fgetc(fp);
			}
		if(c==9){
			if(atof(temp)==df){
				return pos+1;}
			arrpos=0;
			memset(temp, 0, sizeof(temp));
			c=fgetc(fp);
		}
		if(c=='\n' || c=='\r'){
			arrpos=0;
			memset(temp, 0, sizeof(temp));
			pos++;
			c=fgetc(fp);
			if(c=='\n' || c=='\r')
				c=fgetc(fp);
		}
	}
	printf("Valore %d non trovato\n",df); return -1;
}









/*
double getCriticalValue(FILE* fp,double sl, int df){ //RITORNA VALORE CRITICO PER DF GRADI DI LIBERTA' E SL SIGNIFICANCE LEVEL, -1 IN CASO DI ERRORE
	if(fp==NULL){printf("File non trovato\n"); return -1;}
	double crit=-1;
			fseek(fp,0,SEEK_SET);
	char*elemento[20];
	char c;
	int arrpos=0;
	c=fgetc(fp);
	while(c!=EOF){		//PRIMA SI CONTROLLA LA POSIZIONE SULLA RIGA
		while(c!='9'){
			if(arrpos<20)
				elemento[arrpos]=c;
				c=fgetc(fp);
			arrpos++;
		}











	}

}















char*** initmat2(FILE*fp){

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





*/














#endif
