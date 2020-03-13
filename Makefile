CFLAGS = -std=c99

all: main.o generation.o comp.o
	@cc main.o comp.o generation.o -o main
	@rm -f *.o main
main.o: main.c comp.h generation.h
	@cc -c $(CFLAGS) main.c -o main.o 

comp.o: comp.c comp.h generation.h
	@cc -c $(CFLAGS) comp.c -o comp.o
generation.o: generation.c generation.h
	@cc -c $(CFLAGS) generation.c -o generation.o
