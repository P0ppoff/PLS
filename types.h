#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t element;

typedef struct _sequence {
    struct _sequence * suite;
    element elt;
} sequence;

typedef struct _cellule {
    struct  _cellule *  parent, frere_suivant, frere_precedent, fils;  //????frere_precedent
            element     elt;      //8 bits
            int         index;    //numéro de la séquence
} cellule;


typedef struct _dico {
    cellule * racine;
} dico;



#endif // _TYPES_H_




