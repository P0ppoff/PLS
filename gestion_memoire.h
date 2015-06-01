#ifndef _GESTION_MEMOIRE_H_
#define _GESTION_MEMOIRE_H_

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void liberer_sequence (sequence *ptr_seq);

void liberer_dico (dico *ptr_dico);

void creer_sequence(sequence* ptr_seq);

void creer_cellule(cellule* ptr_cellule);

void modif_lg_table (dico table[]);

#endif // _GESTION_MEMOIRE_H_
