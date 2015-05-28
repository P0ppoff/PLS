#include "compresser.h"
#include "types.h"

void compresser(FILE* f_in, FILE* f_out){
	dico *dictionnaire;
	cellule *cell_w = NULL;
	cellule *cell_s = NULL;
	init_compression(dictionnaire);
	sequence *w, *s, *a;

	w = lecture_bits(f_in,8);
	while(!est_fin(w)){ 
		a = lecture_bits(f_in,8);
		cell_w = rechercher_dico(w,dictionnaire);
		cell_s = rechercher_freres(a,cell_w);
		if(cell_s == NULL){
			s = ajout_queue(w,a); // création de la sequence à rechercher
			w = s;
		}else{
			ecriture_indice(cell_w,f_out);
			ajout_element(a,cell_w);
			w = {NULL,a};
		}
	}
	ecriture_fin(cell_w,f_out); // fichier vide ou pas 
}

