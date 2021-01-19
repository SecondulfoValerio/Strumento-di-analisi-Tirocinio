#ifndef CHITABLEREADER_H
#define CHITABLEREADER_H
#include <tabreader.h>

#define MAXNUM 10
int getColumnNum(FILE* fp); // RITORNA NUMERO DI COLONNE CHAR TABLE
int getRowNum(FILE* fp); //RITORNA NUMERO DI RIGHE CHAR TABLE
int getColPos(FILE* fp,double sl); //RITORNA POSIZIONE IN COLONNA DI VALORE SL
int getRowPos(FILE* fp,int df); //RITORNA POSIZIONE IN RIGA DI DF
double getCriticalValue(FILE* fp,int df,int sl); //RITORNA CRITICAL VALUE DALLA CHI TABLE
void chiTestCompare(double cv,double chiv); //STAMPA IL RISULTATO DEL TEST

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


int getRowPos(FILE* fp,int df){ //RITORNA POSIZIONE RIGA DELL'ELEMENTO CON VALORE D, -1 IN CASO DI ERRORE
	if(fp==NULL){printf("File non trovato\n"); return -1;}
	fseek(fp,0,SEEK_SET);
	int pos=0;
	int arrpos=0;
	char temp[20];
	char c;
	c=fgetc(fp);
	while(c!=EOF){
		if(c!=9){
			if(arrpos<20){
				temp[arrpos]=c;
				arrpos++;
			}
			c=fgetc(fp);
		}
		if(c==9){
			if(atof(temp)==df)
				return pos+1;
			else{
				arrpos=0;
				memset(temp, 0, sizeof(temp));
				while(c!='\r' && c!=EOF)
					c=fgetc(fp);
				pos++;
			}
		}
		if(c=='\n'){
			pos++;
			arrpos=0;
			memset(temp, 0, sizeof(temp));
			c=fgetc(fp);
		}
		if(c=='\r'){
			c=fgetc(fp);
		}
	}
	printf("Valore %d non trovato\n",df); return -1;
}

double getCriticalValue(FILE* fp,int df,int sl){
	if(fp==NULL){printf("File non trovato\n"); return -1;}
	fseek(fp,0,SEEK_SET);
	char temp[20];
	int tempos=0;
	char c;
	int row=0;
	int col=0;
	c=fgetc(fp);
	if(df==0 || df <0 || df>51){
		printf("Valore Degrees of Freedom DF invalido"); return -1;
	}
	if(sl==0 || sl< 0 || sl >12){
			printf("Valore Degrees of Freedom DF invalido"); return -1;
		}
		while(row<df || c!=EOF){
			c=fgetc(fp);
			if(c=='\n')
				row+=1;
			if(row==df-1)
				break;
		}
   		while(col<sl || c!=EOF || c!='\n' || c!='\r'){
				if(c==9)
					col++;
				c=fgetc(fp);
				if(col==sl-1)
					break;
		}

		while(c!=9 || c!='\n' || c!='\r' || c!=EOF ){
			if(tempos<20){
				temp[tempos]=c;
				tempos++;
			}
			c=fgetc(fp);
			if(c==9 || c==EOF)
				return (atof(temp));
		}
	printf("Errore valore non trovato\n"); return -1;
}


void chiTestCompare(double cv,double chiv){
	if(cv>chiv){
		printf("Il valore Chi Value: %lf è inferiore rispetto al valore critico %lf\nL'ipotesi nulla non può essere rifiutata...\n",chiv,cv);
	}
	if(cv<chiv){
			printf("Il valore Chi Value: %lf è uguale rispetto al valore critico %lf\nL'ipotesi nulla non può essere rifiutata...\n",chiv,cv);
		}
	if(cv<chiv){
				printf("Il valore Chi Value: %lf è maggiore rispetto al valore critico %lf\nL'ipotesi nulla può essere rifiutata...\n",chiv,cv);
			}
}



















#endif
