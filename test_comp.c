#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include "comp.h"


int main(int argc, char **argv)
{
	if(argc < 2){
		fprintf(stderr, "Podaj plik wejciowy\n");
		return 1;
	}
	
	
	gener_t *g = readToGen(argv[1]);
	if(g == NULL){
                fprintf(stderr, "Brak pamieci lub zly plik\n");
                return 2;
        }
	
	if(argc < 3){
                fprintf(stderr, "Podaj liczbe generacji\n");
                return 3;
        }

	printGen(g);
	printf("\n\n");
	for(int k=0, n=atoi(argv[2]);k<n;k++)
	{	
		for(int i=0; i<g->r; i++){
			for(int j=0;j<g->c;j++)
				printf("%d ",g->next[i][j]=  isAlive8(i,j,g));
			printf("\n");
		}
		printf("\n \n");
		for(int j=0; j< g->r;j++)
                        for(int k=0; k<g->c; k++)
                                g->cont[j][k] = g->next[j][k];
		printGen(g);
	}
	freeGen(g);
	return 0;
}
