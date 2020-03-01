#ifndef GENERATION_H
#define GENERATION_H


// program przechowuje liste generacji, na podstawie biezacej gener 
typedef struct gener
{
	int r, c;	// ilosc wierszy i kolumn
	char **cont;	// zawartosc macierzy
	gener *next;
}gener;

gener *newGen(gener *list, int r, int c);
void printGen(gener *g);	// wyswietla generacje na stdout
void fprintGen(gener *g);	// wypisuje generacje do piku (na razie proponuje txt)
void freeGen(gener *g);		// uwalnia pamiec

#endif
