#ifndef _GESTION_DONNEES_H_
#define _GESTION_DONNEES_H_

#include "types.h"
#include "gestion_memoire.h"

void init_compression (dico *dictionnaire);

void init_decompression (dico table[], dico *dictionnaire);

//void maj_nb_bits;

dico* ajout_element (dico *dictionnaire, sequence *seq, int numero_index);

void ajout_queue(sequence *ptr_tete, sequence *ptr_queue);

cellule* rechercher_dico(sequence *ptr_sequence, dico *dictionnaire);

#endif // _GESTION_DONNEES_H_