#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>
#include "generation.h"
#include "comp.h"
void disHelp()
{
	printf("Prawidlowe wprowadzenie argumentow: \n");
	printf("------------------------------------\n");
	printf("./main [ilosc generacji] [liczba 4 lub 8 zaleznie od wyboru sasiedztwa] [nazwa pliku wejsciowego] [numery generacji zapisywanych w postaci plikow, opcjonalne]\n");
	printf("\n----------------------------------\n");
}
int main(int argc, char **argv)
{
	gener_t *g;
	int s;		//rodzaj sasiedztwa
	int pr[200]; 	// numery generacjii zapisywanych do plikow	

	if(argc < 1)
	{
		fprintf(stderr, "Podaj ilosc generacji\n");
		disHelp();
		return 1;
	}

	if(argc < 2 && (atoi(argv[2]) != 4 || atoi(argv[2]) != 8))
	{
		fprintf(stderr, "Wymagany 2gi argument: 4 lub 8 odp dla sasiedztwa von Neumanna i Morrea\n");
		disHelp();
		return 2;
	}
	s = atoi(argv[2]);
	FILE *in = argc > 2 ? fopen(argv[3],"r") : stdin;
	FILE *out = fopen("out.txt","w");

	if(in == NULL || out == NULL)
	{
		fprintf(stderr,"Blad zapisu lub odczytywania pliku\n");
		return 4;	
	}	
	g = readToGen(in);

	if( g == NULL)
	{
		fprintf(stderr, "Brak pamieci\n");
		disHelp();
		return 3;		
	}
	printGen(g);
	printf("\n \n");

	if(argc > 3)
	{
		for(int i=4; i<argc; i++)	// numery gen zapisów do pliku
		{
			pr[i-4] = atoi(argv[i]);	
		}
	}

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
				fPrintGen(g,out);
		printf("\n \n");
	}
	fclose(in);
	fclose(out);
	freeGen(g);
	return 0;
}
