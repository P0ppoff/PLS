#ifndef _GESTION_FICHIER_H_
#define _GESTION_FICHIER_H_

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

FILE* ouverture_lecture(char nom_fichier[]);
FILE* ouverture_ecriture(char nom_fichier[]);

void fermeture(FILE *fichier);

sequence* lecture_bits(FILE *fichier, int nb_bits);

int est_fin_fichier(sequence *ptr_seq);

void ecriture_indice(cellule *ptr_cell,FILE *fichier, int TAILLE_ECRIT);

void ecriture_fin(cellule *ptr_cell,FILE *fichier, int TAILLE_ECRIT);


#endif // _GESTION_FICHIER_H_
