#include <stdio.h>

#include "generation.h"

int main(int argc, char **argv){
	gener_t *g = readToGen(argv[1]);
	printGen(g);
	fPrintGen(g, argv[2]);
	freeGen(g);
	return 0;
}
