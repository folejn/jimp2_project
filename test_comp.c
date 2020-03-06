#include <stdio.h>
#include "generation.h"
#include "comp.h"


int main(int argc, char **argv)
{
	if(argc != 2){
		fprintf(stderr, "Podaj plik wejciowy\n");
		return 1;
	}
	
	
	gener_t *g = readToGen(argv[1]);
	if(g == NULL){
                fprintf(stderr, "Brak pamieci lub zly plik\n");
                return 2;
        }

	printGen(g);
	printf("\n\n");	
	for(int i=0; i<g->r; i++){
		for(int j=0;j<g->c;j++)
			printf("%d ", isAlive8(i,j,g));
		printf("\n");
	}
	freeGen(g);
	return 0;
}
