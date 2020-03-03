#include <stdio.h>
#include <stdlib.h>

#include "generation.h"

gener_t *newGen(int r, int c){
    gener_t *g = (gener_t*) malloc( sizeof(gener_t) );
    if(g != NULL){
            g->r = r;
            g->c = c;
            g->cont = (int **) malloc( r * sizeof(int *));
            for (int i = 0; i < r; i++)
                g->cont[i] = (int *) malloc(c * sizeof(int));
            g->next = (int **) malloc( r * sizeof(int *));
            for (int i = 0; i < r; i++)
                g->next[i] = (int *) malloc(c * sizeof(int));
    }
    return g;
}

gener_t *readToGen(char *in){
    gener_t *g = NULL;
    FILE *fin = fopen(in, "r");
    if(fin != NULL){
        int r, c;
        fscanf(fin, "%d %d", &r, &c);
        g = newGen(r, c);
        if(g != NULL) {
            for (int i = 0; i < g->r; i++) {
                for (int j = 0; j < g->c; j++) {
                    fscanf(fin, "%d", &(g->cont[i][j]));
                }
            }
        }
        fclose(fin);
    }
    return g;
}

void printGen(gener_t *g){
    if(g != NULL){
        for(int i = 0; i < g->r; i++) {
            for (int j = 0; j < g->c; j++) {
                printf("%d ", g->cont[i][j]);
            }
            printf("\n");
        }
    }
}

void fPrintGen(gener_t *g, char *out){
    FILE *f_out = fopen(out, "w");
    if(f_out != NULL){
        for(int i = 0; i < g->r; i++) {
            for (int j = 0; j < g->c; j++) {
                fprintf(f_out, "%d ", g->cont[i][j]);
            }
            fprintf(f_out, "\n");
        }
        fclose(f_out);
    }
}

void freeGen(gener_t *g){
    for(int i = 0; i < g->r; i++)
        free(g->cont[i]);
    free(g->cont);
    for(int i = 0; i < g->r; i++)
        free(g->next[i]);
    free(g->next);
    free(g);
}