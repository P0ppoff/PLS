#ifndef _GESTION_DONNEES_H_
#define _GESTION_DONNEES_H_

#include "types.h"
#include "gestion_memoire.h"
#include <math.h>

void init_compression (dico *dictionnaire);

void init_decompression (dico *table, dico *dictionnaire);

void init_tampon_lecture(tampon *t);

void init_tampon_ecriture(tampon *t);

void afficher_sequence (sequence * seq);

void recupere_seq(dico *table, int i, sequence *seq_retour);

void ajout_element (sequence *a, cellule *w, int *INDICE_MAX, int *TAILLE_ECRIT);

void ajout_queue(sequence *ptr_tete, sequence *ajout);

cellule* recherche_freres(cellule *premier_frere, sequence *seq);

cellule* rechercher_dico (dico dictionnaire, sequence *seq);

void extraction_tete(sequence *a_extraire, sequence *retour);

void ajout_element_concat(sequence *w, sequence *a, int *TAILLE_LU, int *INDICE_MAX, dico *table);

int conversion (sequence *seq, int TAILLE_LU);

#endif // _GESTION_DONNEES_H_