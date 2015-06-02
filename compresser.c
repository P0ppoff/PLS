#include "compresser.h"

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
	init_tampon_lecture(&bl);
	init_tampon_ecriture(&be);
	w = creer_sequence();
	lecture_bits(f_in, TAILLE_LU, &bl, w);
	//afficher_sequence(w);
	while(!est_fin_fichier(f_in)){ // vérification w  = dernier élément à tous les bits à 1 = 255
		a = creer_sequence();
		lecture_bits(f_in, TAILLE_LU, &bl, a);
		//printf("\nsequence a:\n ");
		//afficher_sequence(a);
		cell_w = rechercher_dico(dictionnaire,w);
		cell_s = recherche_freres(cell_w->fils,a); // pramatère : le parent
		if(cell_s != NULL){ // w.a appartient au dictionnaire
			ajout_queue(w,a); // création de la sequence à rechercher
		}else{
			printf("\tTAILLE_ECRIT = %i\n", TAILLE_ECRIT);
			ecriture_indice(cell_w, f_out, TAILLE_ECRIT, &be);
			ajout_element(a, cell_w, &INDICE_MAX, &TAILLE_ECRIT); // on met a jour avant donc on envoie INDICE_MAX en tant que int (on le modifie pas dans cette fonction)
			w -> elt = a -> elt;
			w -> suite = NULL;
			//printf("JE PASSE DANS LE ELSE \n");
		}
	//printf("\nsequence w:\n ");
	//afficher_sequence(w);
	}
	ecriture_fin(f_out, TAILLE_ECRIT, &be); // fichier vide ou pas
}

