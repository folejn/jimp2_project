CFLAGS = -c -std=c99
LIBS = -lpng

all: main.o generation.o comp.o pngfile.o
	@cc main.o pngfile.o comp.o generation.o $(LIBS) -o main
	@rm -f *.o
main.o: main.c comp.h generation.h pngfile.h
	@cc $(CFLAGS) main.c -o main.o 

comp.o: comp.c comp.h generation.h
	@cc $(CFLAGS) comp.c -o comp.o
generation.o: generation.c generation.h
	@cc $(CFLAGS) generation.c -o generation.o
pngfile.o: pngfile.c pngfile.h
	@cc $(CFLAGS) pngfile.c -o pngfile.o
