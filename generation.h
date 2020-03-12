#ifndef GENERATION_H
#define GENERATION_H


// program przechowuje liste generacji, na podstawie biezacej gener 
typedef struct gener
{
    int r, c;	// ilosc wierszy i kolumn
    int **cont;	// zawartosc macierzy
    int **next;
}gener_t;

gener_t *readToGen(FILE *fin); //wpisuje dane z pliku zrodlowego
//gener_t *readToGenTxt(FILE *fin); //wpisuje dane z pliku zrodlowego
void printGen(gener_t *g);	// wyswietla generacje na stdout
void fPrintGen(gener_t *g, FILE *f_out);	// wypisuje generacje do piku (na razie proponuje txt)
void freeGen(gener_t *g);		// uwalnia pamiec

#endif
