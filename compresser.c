#include "compresser.h"

void compresser(FILE* f_in, FILE* f_out){
	int TAILLE_ECRIT = 9; // on commence sur 9 pour avoir deux infos de plus : Fin de fichier & incrémentation du nombre de bits à écrire
	int INDICE_MAX = 257; // dernier indice donné
	int TAILLE_LU = 8;
	dico *dictionnaire;
	cellule *cell_w = NULL;
	cellule *cell_s = NULL;
	sequence *w, *a;
	tampon bl, be; // Les deux buffers de lecture et écriture

	init_compression(dictionnaire);
	w = lecture_bits(f_in, TAILLE_LU, &bl);
	while(!est_fin(w)){ // vérification w  = dernier élément à tous les bits à 1 = 255
		a = lecture_bits(f_in, TAILLE_LU, &bl);
		cell_w = rechercher_dico(w, dictionnaire); 
		cell_s = rechercher_fils(a, cell_w); // pramatère : le parent
		if(cell_s != NULL){ // w.a appartient au dictionnaire
			ajout_queue(w,a); // création de la sequence à rechercher
		}else{
			ecriture_indice(cell_w, f_out, TAILLE_ECRIT, &be);
			ajout_element(a, cell_w, &INDICE_MAX, &TAILLE_ECRIT); // on met a jour avant donc on envoie INDICE_MAX en tant que int (on le modifie pas dans cette fonction)
			w -> elt = a -> elt;
			w -> suite = NULL;
		}
	}
	ecriture_fin(cell_w, f_out, TAILLE_ECRIT, &be); // fichier vide ou pas 
}

