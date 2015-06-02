#-------------------------------------------------
#                    VARIABLES
#-------------------------------------------------
CC=gcc
CFLAGS=-g -Wall -lm -Iinclude
LDFLAGS=
LIBRARIES=

SRCS=lwf.c compresser.c decompresser.c gestion_fichier.c gestion_donnees.c gestion_memoire.c
OBJS=${SRCS:.c=.o}
EXEC=Lwf

#-------------------------------------------------
#                     LINKINGS
#-------------------------------------------------
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@ 

lwf.o: lwf.c include/compresser.h include/decompresser.h include/gestion_fichier.h
compresser.o: compresser.c include/compresser.h include/gestion_donnees.h include/gestion_fichier.h
decompresser.o: decompresser.c include/decompresser.h include/gestion_donnees.h include/gestion_fichier.h
gestion_donnees.o: gestion_donnees.c include/gestion_donnees.h include/gestion_memoire.h
gestion_fichier.o: gestion_fichier.c include/gestion_fichier.h include/gestion_memoire.h

%.o: %.c include/%.h types.h

#-------------------------------------------------
#                     CLEANING
#-------------------------------------------------
clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(EXEC)

.PHONY: mrproper clean
