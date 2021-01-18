#ifndef CHISQUARETEST_H
#define CHISQUARETEST_H

double totalrow(double** matrice, int row, int col); //RESTITUISCE SOMMA DELLE RIGHE NELLA COLONNA col
double totalcol(double** matrice, int row, int col); //RESTITUISCE SOMMA DELLE COLONNE NELLA RIGA row
double totalElements(double** matrice, int row, int col); //RESTITUISCE SOMMA DI TUTTI GLI ELEMENTI DELLA MATRICE
int degfreedom(int row,int col); //RESTITUISCE I GRADI DI LIBERTA' DELLA MATRICE
double* rowsums(double** matrice,int row,int col); //RESTITUISCE ARRAY CON I VALORI DELLE SOMMATORIE DELLE RIGHE DELLA MATRICE
double* columnsums(double** matrice,int row,int col); //RESTITUISCE ARRAY CON I VALORI DELLE SOMMATORIE DELLE COLONNE DELLA MATRICE
double expectedValue(double rowtot,double coltot, double eltot); //RESTITUISCE VALORE DI EXPECTED VALUE
double chivalue(double**matrice,int row,int col); //RESTITUISCE CHI-VALUE MATRICE

double totalrow(double** matrice, int row, int col){

	double tot=0;
	for(int i=0;i<col;i++)
		tot+= matrice[row][i];
	return tot;
}

double totalcol(double** matrice, int row, int col){
	double tot=0;
	for(int i=0;i<row;i++)
		tot+=matrice[i][col];
	return tot;
}

double totalElements(double** matrice, int row, int col){
	double tot=0;
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			tot+=matrice[i][j];
	return tot;
}

int degfreedom(int row,int col){
	return (row-1)*(col-1);
}


double* rowsums(double** matrice,int row,int col){
double* somme=(double*) calloc(row,sizeof(double));
for(int i=0;i<row;i++)
	somme[i]=totalrow(matrice,i,col);
return somme;
}

double* columnsums(double** matrice,int row,int col){
double* somme=(double*) calloc(col,sizeof(double));
for(int i=0;i<col;i++)
	somme[i]=totalcol(matrice,row,i);
return somme;
}

double expectedValue(double rowtot,double coltot, double eltot){
	return (rowtot*coltot)/eltot;
}


double chivalue(double**matrice,int row,int col){
	double tot=0;
	double* sumrows=rowsums(matrice,row,col);
	double* sumcol=columnsums(matrice,row,col);
	double  totalElements=0;
	double temp=0;
	int matrixelements=row*col;
	for(int i=0;i<row;i++)
		totalElements+=sumrows[i];
	for(int x=0;x<matrixelements;x++){
		for(int r=0;r<row;r++)
			for(int c=0;c<col;c++){
				temp=((matrice[r][c]- expectedValue(sumrows[r],sumcol[c],totalElements)));
				tot+=temp*temp/totalElements;
			}
	}
	return tot;
}












#endif
