#ifndef _GESTION_MEMOIRE_H_
#define _GESTION_MEMOIRE_H_

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void liberer_sequence (sequence *ptr_seq);

void liberer_dico (dico *ptr_dico);

sequence* creer_sequence();

cellule* creer_cellule();

dico* creer_table();

void modif_lg_table (dico table[]);

#endif // _GESTION_MEMOIRE_H_
