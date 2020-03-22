#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <png.h>
#include "pngfile.h"

#define CELL 40		//bok kwadratu (jednej komórki)

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers = NULL;

void write_png_file(FILE* fp) {
  if (!fp)
    printf("[write_png_file] png file could not be opened for writing");

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    printf("[write_png_file] png_create_write_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    printf("[write_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during init_io");

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing header");

  png_set_IHDR(png_ptr, info_ptr, width, height,
   bit_depth, color_type, PNG_INTERLACE_NONE,
   PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing bytes");

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during end of write");

  png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr,&info_ptr);	
  for (y=0; y<height; y++)
    free(row_pointers[y]);
  free(row_pointers);
}
	
void process_file( gener_t *g) {
	width = CELL *g->c;
	height = CELL * g->r;
	bit_depth = 8;
	color_type = PNG_COLOR_TYPE_GRAY;

	number_of_passes = 7;

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for (y=0; y<height; y++)
		row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);

	for (y=0; y<height/CELL; y++) {
		png_byte* row = row_pointers[y*CELL];

		for (x=0; x<width/CELL; x++) {

			//row[x*CELL] = (y+x)%2? 255 : 0;
			row[x*CELL] = g->cont[y][x] == 0? 0: 255;
			for(int i=1; i<CELL; i++)		//kopiowanie pixela CELL razy (aby utworzyć 
				row[x*CELL+i] = row[x*CELL];    // poziomy bok kwadratu)  
		}
		for(int i=0;i<CELL; i++){
			for(int j=0; j<width; j++){
				row_pointers[y*CELL +i][j] = row[j];	//'pion' kwadratu
			}
		}	
	}
}

void fPrintPng(FILE *out, gener_t *g)
{
	process_file(g);
	write_png_file(out);
}
