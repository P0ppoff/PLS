#-------------------------------------------------
#                    VARIABLES
#-------------------------------------------------
CC=gcc
#CFLAGS=-g -Wall -pedantic -I../include -DDEBUG -DINT16
CFLAGS=-g -Wall
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

lwf.o: lwf.c compresser.h decompresser.h gestion_fichier.h
compresser.o: compresser.c compresser.h types.h gestion_donnees.h gestion_fichier.h
decompresser.o: decompresser.c decompresser.h types.h gestion_donnees.h gestion_fichier.h
gestion_donnees.o: gestion_donnees.c gestion_donnees.h types.h gestion_memoire.h

%.o: %.c %.h types.h

#-------------------------------------------------
#                     CLEANING
#-------------------------------------------------
clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(EXEC)

.PHONY: mrproper clean
