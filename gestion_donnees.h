#ifndef _GESTION_DONNEES_H_
#define _GESTION_DONNEES_H_

#include "types.h"
#include "gestion_memoire.h"

void init_compression (dico *dictionnaire);

void init_decompression (dico table[], dico *dictionnaire);

sequence* recupere_seq(dico *table,int i);

void ajout_element (sequence *a, cellule *w, int *INDICE_MAX, int *TAILLE_ECRIT);

void ajout_queue(sequence *ptr_tete, sequence *ptr_queue);

cellule* rechercher_fils(sequence *ptr_sequence, cellule *ptr_cellule);

cellule* rechercher_dico(sequence *ptr_sequence, dico *dictionnaire);

#endif // _GESTION_DONNEES_H_