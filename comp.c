#include <stdio.h>
#include "generation.h"
int isInFrame(int r, int c, gener_t *g)
{
	int rg = g->r, cg = g->c;
	if((r >= 0 && r < rg) && (c >= 0 && c < cg))
		return 1;
	return 0; 
}
int isAlive4(int r, int c, gener_t *g)
{
	int alNeigh = 0;
	
	if(isInFrame(r,c-1,g))
		if(g->cont[r][c-1] == 1)
			alNeigh++;
	if(isInFrame(r,c+1,g))
		if(g->cont[r][c+1] == 1)
                      alNeigh++;
	if(isInFrame(r-1,c,g))
		if(g->cont[r-1][c] == 1)
                        alNeigh++;
	if(isInFrame(r+1,c,g))
		if(g->cont[r+1][c] == 1)
                        alNeigh++;
	if(g->cont[r][c] == 0 && alNeigh == 3)  
		return 1;

	if(g->cont[r][c] == 1 && ( alNeigh == 2 || alNeigh == 3))
		return 1;
	return 0;
}
int isAlive8(int r, int c, gener_t *g)
{
        int alNeigh = 0;

        if(isInFrame(r,c-1,g))
                if(g->cont[r][c-1] == 1)
                        alNeigh++;
        if(isInFrame(r,c+1,g))
                if(g->cont[r][c+1] == 1)
                      alNeigh++;
        if(isInFrame(r-1,c,g))
                if(g->cont[r-1][c] == 1)
                        alNeigh++;
        if(isInFrame(r+1,c,g))
                if(g->cont[r+1][c] == 1)
                        alNeigh++;
	if(isInFrame(r+1,c+1,g))
                if(g->cont[r+1][c+1] == 1)
                        alNeigh++;
	if(isInFrame(r-1,c-1,g))
                if(g->cont[r-1][c-1] == 1)
                        alNeigh++;
	if(isInFrame(r+1,c-1,g))
                if(g->cont[r+1][c-1] == 1)
                        alNeigh++;
	if(isInFrame(r-1,c+1,g))
                if(g->cont[r-1][c+1] == 1)
                        alNeigh++;
        if(g->cont[r][c] == 0 && alNeigh == 3)
                return 1;

        if(g->cont[r][c] == 1 && ( alNeigh == 2 || alNeigh == 3))
                return 1;
        return 0;
}

