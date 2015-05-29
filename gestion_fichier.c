#include "gestion_fichier.h"

FILE* ouverture_lecture(char nom_fichier[]){
	FILE* fichier = NULL;
    fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL){
        printf("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }
}

FILE* ouverture_ecriture(char nom_fichier[]){
	FILE* fichier = NULL;
    fichier = fopen(nom_fichier, "wb");
    if (fichier == NULL){
        printf("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }
}

void fermeture(FILE *fichier){
	fclose(fichier);
}

sequence* lecture_bits(FILE *fichier, int nb_bits){
    return NULL;
}

int est_fin(sequence *ptr_seq){
	if(ptr_seq == EOF ) {
		return 1;
	}
	else {
		return 0;
	}
}

void ecriture_indice(cellule *ptr_cell,FILE fichier){

}

void ecriture_fin(cellule *ptr_cell,FILE fichier){

}
