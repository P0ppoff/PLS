#ifndef _GESTION_DONNEES_H_
#define _GESTION_DONNEES_H_

#include "types.h"
#include "gestion_memoire.h"

void init_compression (dico *dictionnaire);

void init_decompression (dico *table, dico *dictionnaire);

void recupere_seq(dico *table, int i, sequence *seq_retour);

void ajout_element (sequence *a, cellule *w, int *INDICE_MAX, int *TAILLE_ECRIT);

void ajout_queue(sequence *ptr_tete, sequence *ajout);

cellule* rechercher_dans_fils(sequence *ptr_sequence, cellule *ptr_cellule);

cellule* rechercher_dico(sequence *ptr_sequence, dico dictionnaire);

void extraction_tete(sequence *a_extraire, sequence *retour);

void ajout_element_concat(sequence *w, sequence *a, int *TAILLE_LU, int *INDICE_MAX, dico *table);

int conversion (sequence *seq, int TAILLE_LU);

#endif // _GESTION_DONNEES_H_