CC=gcc
CFLAGS=

all: Lwf

#Lwf: lwf.o gestion_fichier.o compresser.o decompresser.o
Lwf: lwf.o gestion_fichier.o compresser.o gestion_donnees.o gestion_memoire.o
	$(CC) $^ -o Lwf

#lwf.o: lwf.c compresser.h decompresser.h gestion_fichier.h
lwf.o: lwf.c compresser.h gestion_fichier.h

compresser.o: compresser.c compresser.h types.h gestion_donnees.h gestion_fichier.h
#decompresser.o: decompresser.c decompresser.h types.h
gestion_donnees.o: gestion_donnees.c gestion_donnees.h types.h gestion_memoire.h

%.o: %.c %.h types.h

clean:
	rm -f Lwf *.o