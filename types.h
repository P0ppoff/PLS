#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct _cellule {
    struct _cellule * parent, frere, fils;
    uint8_t element;
} cellule;


typedef struct _dico {
    cellule * racine;
} dico;



#endif // _TYPES_H_




