#include "decompresser.h"
#include "types.h"

void decompresser(FILE* f_in, FILE* f_out){
	int TAILLE_LU = 9; // on commence sur 9 pour avoir deux infos de plus : Fin de fichier & incrémentation du nombre de bits à écrire
	int INDICE_MAX = 257; // dernier indice donné
	int TAILLE_ECRIT = 8;
	dico *dictionnaire;
	dico table[];
	sequence *i, *iprime, *a, *w, *wprime;
	int indice;

	init_decompression(table, dictionnaire); 
	i = lecture_bits(f_in, TAILLE_LU);
	a = recupere_seq(table, i); // renvoie la séquence pour aboutir à la case d'index i // antention à la fin de fichier, si table[i]==NULL soit fin de fichier -> a = EOF soit increment
	w = a; // transfère dans la séquence w
	ecriture_seq(f_out, w, TAILLE_ECRIT);
	while(!est_fin(w)){ // vérification w  = dernier élément à tous les bits à 1 = 255
		iprime = lecture_bits(f_in, TAILLE_LU);
		indice = conversion(iprime); // convertion d'une séquence en l'entier correspondant
		if(table[indice] == NULL){
			wprime = recupere_seq(table, i);
			ajout_queue(wprime, a);
		}else{
			wprime = recupere_seq(table , iprime);
		}
		ecriture_seq(f_out, wprime, TAILLE_ECRIT);
		a = extraction_tete(wprime);
		ajout_element(w, a, &TAILLE_LU, &INDICE_MAX, table); // ajout l'élément w.a en mettant le reste à jour
		i = iprime;
	}
}
