#include "decompresser.h"


void init_tampon(tampon *t){
	t -> nb_bits_dispo = 0;
	t -> buffer = 0;
}

void decompresser(FILE* f_in, FILE* f_out){
	int TAILLE_LU = 9; // on commence sur 9 pour avoir deux infos de plus : Fin de fichier & incrémentation du nombre de bits à écrire
	int INDICE_MAX = 257; // dernier indice donné
	//int TAILLE_ECRIT = 8;
	dico dictionnaire;
	dico *table = creer_table();
	sequence *i = NULL;
	sequence *iprime = NULL; 
	sequence *a = NULL; 
	sequence *w = NULL; 
	sequence *wprime = NULL;
	int indice = 0;
	tampon bl; // Le buffer de lecture 


	init_decompression(table, &dictionnaire); 
	i = creer_sequence();
	a = creer_sequence();
	w = creer_sequence();
	iprime = creer_sequence();
	wprime = creer_sequence();
	init_tampon_lecturee(&bl);
	lecture_bits(f_in, TAILLE_LU, &bl, i);
	indice = conversion(i, TAILLE_LU);
	recupere_seq(table, indice, a); // renvoie la séquence pour aboutir à la case d'index i // antention à la fin de fichier, si table[i]==NULL soit fin de fichier -> a = EOF soit increment
	extraction_tete(a, w); // transfère dans la séquence w
	ecriture_seq(f_out, w); // nous n'utilisons pas de buffer d'écriture car nous écrivons sur un octet -> amélioration = passer par un buffer pour faire des écriture sur plus de 8 bits
	while(!est_fin_fichier(f_in)){ // vérification w  = dernier élément à tous les bits à 1 = 255
		lecture_bits(f_in, TAILLE_LU, &bl, iprime);
		indice = conversion(iprime, TAILLE_LU); // conversion d'une séquence en l'entier correspondant
		if(table[indice].racine == NULL){
			indice = conversion(i, TAILLE_LU);
			recupere_seq(table, indice, wprime);
			ajout_queue(wprime, a);
		}else{
			recupere_seq(table , indice, wprime);
		}
		ecriture_seq(f_out, wprime);
		extraction_tete(wprime, a);
		ajout_element_concat(w, a, &TAILLE_LU, &INDICE_MAX, table); // ajout l'élément w.a en mettant le reste à jour
		i = iprime;
		indice = conversion(i, TAILLE_LU);
		recupere_seq(table , indice, w);
	}
}
