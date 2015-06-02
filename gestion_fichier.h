#ifndef _GESTION_FICHIER_H_
#define _GESTION_FICHIER_H_

#include <stdlib.h>
#include <stdio.h>

#include "gestion_memoire.h"
#include "types.h"

FILE* ouverture_lecture(char nom_fichier[]);

FILE* ouverture_ecriture(char nom_fichier[]);

void fermeture(FILE *fichier);

void lecture_bits(FILE *fichier, int nb_bits_a_lire, tampon *t, sequence *seq);

int est_fin_fichier(FILE *fichier);

void ecriture_indice(cellule *cell_w, FILE *f_out, int TAILLE_ECRIT, tampon *t);

void ecriture_fin(FILE *fichier, int TAILLE_ECRIT, tampon *t);

void ecriture_seq(FILE *fichier, sequence *seq); 

#endif // _GESTION_FICHIER_H_
