#include "compresser.h"

void init_tampon(tampon *t){
	t -> nb_bits_dispo = 0;
	t -> buffer = 0;
}

void afficher_sequence (sequence * seq){
	sequence * courante = seq;
	printf("le pointeur de cette séquence est %p\n", seq);
	printf("l'élément de la séquence vaut %x ", courante -> elt);
	while (courante -> suite != NULL){
		courante = courante -> suite;
		printf("%x ", courante -> elt);
	}
	printf("\n");
}

void compresser(FILE* f_in, FILE* f_out){
	int TAILLE_ECRIT = 9; // on commence sur 9 pour avoir deux infos de plus : Fin de fichier & incrémentation du nombre de bits à écrire
	int INDICE_MAX = 257; // dernier indice donné
	int TAILLE_LU = 8;
	dico dictionnaire;
	cellule *cell_w = NULL;
	cellule *cell_s = NULL;
	sequence *w = NULL;
	sequence *a = NULL;
	tampon bl, be; // Les deux buffers de lecture et écriture

	init_compression(&dictionnaire);
	init_tampon(&bl);
	w = creer_sequence();
	lecture_bits(f_in, TAILLE_LU, &bl, w);
	afficher_sequence(w);
	//while(!est_fin_fichier(w)){ // vérification w  = dernier élément à tous les bits à 1 = 255
		a = creer_sequence();
		lecture_bits(f_in, TAILLE_LU, &bl, a);
		afficher_sequence(a);
		cell_w = rechercher_dico(w, dictionnaire);
		cell_s = rechercher_dans_fils(a, cell_w); // pramatère : le parent
		if(cell_s != NULL){ // w.a appartient au dictionnaire
			ajout_queue(w,a); // création de la sequence à rechercher
		}else{
			ecriture_indice(cell_w, f_out, TAILLE_ECRIT, &be);
			ajout_element(a, cell_w, &INDICE_MAX, &TAILLE_ECRIT); // on met a jour avant donc on envoie INDICE_MAX en tant que int (on le modifie pas dans cette fonction)
			w -> elt = a -> elt;
			w -> suite = NULL;
		}
	//}
	ecriture_fin(f_out, TAILLE_ECRIT, &be); // fichier vide ou pas
}

