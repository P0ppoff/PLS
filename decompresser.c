#include "decompresser.h"

void decompresser(FILE* f_in, FILE* f_out){
	int TAILLE_LU = 9; // on commence sur 9 pour avoir deux infos de plus : Fin de fichier & incrémentation du nombre de bits à écrire
	int INDICE_MAX = 257; // dernier indice donné
	int TAILLE_ECRIT = 8;
	dico *dictionnaire;
	dico *table;
	sequence *i, *iprime, *a, *w, *wprime;
	int indice;
	tampon bl, be; // Les deux buffers de lecture et écriture


	init_decompression(table, dictionnaire); 
	lecture_bits(f_in, TAILLE_LU, &bl, i);
	recupere_seq(table, i, a); // renvoie la séquence pour aboutir à la case d'index i // antention à la fin de fichier, si table[i]==NULL soit fin de fichier -> a = EOF soit increment
	w = a; // transfère dans la séquence w
	ecriture_seq(f_out, w, TAILLE_ECRIT);
	while(!est_fin_fichier(w)){ // vérification w  = dernier élément à tous les bits à 1 = 255
		lecture_bits(f_in, TAILLE_LU, iprime);
		indice = conversion(iprime); // conversion d'une séquence en l'entier correspondant
		if(table[indice] == NULL){
			recupere_seq(table, i, wprime);
			ajout_queue(wprime, a);
		}else{
			recupere_seq(table , iprime, wprime);
		}
		ecriture_seq(f_out, wprime, TAILLE_ECRIT);
		extraction_tete(wprime, a);
		ajout_element_concat(w, a, &TAILLE_LU, &INDICE_MAX, table); // ajout l'élément w.a en mettant le reste à jour
		i = iprime;
	}
}
