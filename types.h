#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

typedef uint8_t element;

typedef struct _sequence {
	struct _sequence *suite;
	element elt;
} sequence;

typedef struct _cellule {
	struct _cellule *parent;
	struct _cellule *frere_suivant;
	struct _cellule *frere_precedent; //????frere_precedent
	struct _cellule *fils;
	element elt;      //8 bits
	int index;    //numéro de la séquence
} cellule;


typedef struct _dico {
	cellule* racine;
} dico;

#endif //_TYPES_H_

