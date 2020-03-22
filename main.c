#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generation.h"
#include "comp.h"
#include "pngfile.h"
void disHelp()
{
	printf("Prawidlowe wprowadzenie argumentow: \n");
	printf("------------------------------------\n");
	printf("./main N S filename.txt [a1] [a2] [a3] ... [an]\n");
	printf("Gdzie: N-ilosc zadanych generacji\n");
	printf("S = 4 lub S = 8,( 4 dla sasiedzztwa von Neumanna, 8 dla Moorea)\n");
	printf("filename.txt- nazwa pliku wejsciowego\n");
	printf("a1 - ai -an: numery generacji przekazywanych do plikow png o nazwie out[i].png (opcjonalne)\n");
	printf("Liczba tych numerow nie moze przekraczac 200!\n");
	printf("\n----------------------------------\n");
}
int main(int argc, char **argv)
{
	gener_t *g;
	int s;		//rodzaj sasiedztwa
	int pr[200]; 	// numery generacjii zapisywanych do plikow
	char png_out[30];/*bufor na nazwę pliku wyjściowego png (może ich być <0,200>) nazwa="out"+ 7cyfr					 + ".png" */	
	
	if (argc > 204)
	{
		fprintf(stderr, "Nie można przekazac wiecej niz 200 generacji do plikow\n");
		disHelp();
		return 1;
	}
	if(argc < 2)
	{
		if(atoi(argv[1]) < 1)
			fprintf(stderr,"Liczba generacji musi byc wieksza od 0\n");
		fprintf(stderr, "Podaj ilosc generacji\n");
		disHelp();
		return 1;
	}

	if(argc < 3)
	{
		fprintf(stderr, "Wymagany 2gi argument: 4 lub 8 odp dla sasiedztwa von Neumanna i Morrea\n");
		disHelp();
		return 2;
	}
	if(atoi(argv[2]) != 4 && atoi(argv[2]) != 8)
	{
		fprintf(stderr, "Wymagany 2gi argument: 4 lub 8 odp dla sasiedztwa von Neumanna i Morrea\n");
                disHelp();
                return 2;
	}

	s = atoi(argv[2]);
	FILE *in = argc > 3 ? fopen(argv[3],"rb") : stdin;

	if(!in)
	{
		fprintf(stderr,"Blad zapisu lub odczytywania pliku\n");
		return 4;	
	}	
	g = readToGenTxt(in);
	if(!g)
	{
		fprintf(stderr, "Brak pamieci\n");
		disHelp();
		return 3;		
	}
	printGen(g);
	printf("\n \n");
	
	if(argc > 4)
		for(int i=4; i<argc; i++)	// numery gen zapisów do pliku
			pr[i-4] = atoi(argv[i]);	

	for(int i=0, n = atoi(argv[1]); i<n; i++)
	{
		for(int j=0; j<g->r; j++)
			for(int k=0; k<g->c; k++)
			{
				if(s == 4)
					g->next[j][k] = isAlive4(j,k,g);
				else if (s == 8)
					g->next[j][k] = isAlive8(j,k,g);
				else return 2;
			}
		for(int j=0; j< g->r;j++)
			for(int k=0; k<g->c; k++)
				g->cont[j][k] = g->next[j][k];
		printGen(g);
		
		for(int j=0; j<argc -4; j++)	// które generacje zostaną zapisane do pliku
			if(pr[j] == i + 1)	// numery generacji są liczone od 1
			{
				strcpy(png_out,"out");				// tworzenie nazwy out[i].png
				sprintf(png_out +strlen(png_out),"%d",pr[j]);	// nazwa pliku wyjsciowego
				strcpy(png_out + strlen(png_out), ".png");	//
				FILE *out = fopen(png_out,"wb");

				if(!out)
				{
					fprintf(stderr, "Blad otwarcia pliku %s\n",png_out);
					return 4;
				}
				//fPrintGen(g,out);
				fPrintPng(out,g);

				fclose(out);
			}
		printf("\n \n");
	}
	FILE *outTxt = fopen("out.txt","w");	// zapis koncowej generacji do out.txt
	if(!outTxt)
		fprintf(stderr,"Blad zapisu do pliku txt\n");
	else fPrintGen(g,outTxt);
	
	fclose(outTxt);
	fclose(in);
	freeGen(g);
	return 0;
}
