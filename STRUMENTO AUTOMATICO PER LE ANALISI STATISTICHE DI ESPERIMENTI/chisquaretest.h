#ifndef CHISQUARETEST_H
#define CHISQUARETEST_H

double totalrow(double** matrice, int row, int col); //RESTITUISCE SOMMA DELLE RIGHE NELLA COLONNA col
double totalcol(double** matrice, int row, int col); //RESTITUISCE SOMMA DELLE COLONNE NELLA RIGA row
double totalelements(double** matrice, int row, int col); //RESTITUISCE SOMMA DI TUTTI GLI ELEMENTI DELLA MATRICE



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

double totalelements(double** matrice, int row, int col){
	double tot=0;
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			tot+=matrice[i][j];
	return tot;

}








#endif
