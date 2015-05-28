CC=gcc

all: Lwf

Lwf: lwf.o compresser.o decompresser.o
	gcc lwf.o compresser.o decompresser.o -o Lwf

lwf.o: lwf.c compresser.h decompresser.h

compresser.o: compresser.c compresser.h
decompresser.o: decompresser.c decompresser.h

clean:
	rm Lwf *.o