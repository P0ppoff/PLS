#include "gestion_donnees.h"
#include "types.h"

void init_compression (dico *dictionnaire){
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	dictionnaire = creer_cellule();
	cellule_courante = dictionnaire;
	for (i = 0; i < 256; i++)
	{
		cellule_courante -> index = i;
		cellule_courante -> elt = i;
		cellule_courante -> frere_precedent = cellule_precedente;
		cellule_courante -> frere_suivant = creer_cellule();
		cellule_precedente = cellule_courante;
		cellule_courante = cellule_courante -> frere_suivant;
	}
}

void init_decompression (dico table[], dico *dictionnaire){
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	dictionnaire = creer_cellule();
	cellule_courante = dictionnaire;
	for (i = 0; i < 256; i++)
	{
		cellule_courante -> index = i;
		cellule_courante -> elt = i;
		table[i] = cellule_courante;
		cellule_courante -> frere_precedent = cellule_precedente;
		cellule_courante -> frere_suivant = creer_cellule();
		cellule_precedente = cellule_courante;
		cellule_courante = cellule_courante -> frere_suivant;
	}
}

dico* ajout_element (dico *dictionnaire, sequence *seq, int numero_index){
	cellule *cellule_ajoutee; //creation d'une cellule pour y inserer la sequence a ajouter
	cellule *ptr_cellule = NULL; 
	sequence *seq_copie = seq;
	cellule_ajoutee = creer_cellule(); //initialisation de la cellule
	while(seq_copie -> suite != NULL){ 
		seq_copie = seq_copie -> suite;
	}
	cellule_ajoutee -> elt = seq_copie -> elt; // ajout du dernier element de la sequence a la cellule
	cellule_ajoutee -> index = numero_index; 
	ptr_cellule = rechercher_dico(seq, dictionnaire);
	ptr_cellule -> elt = cellule_ajoutee -> elt;
	ptr_cellule -> index = cellule_ajoutee -> index;
}

void ajout_queue(sequence *ptr_tete, sequence *ptr_queue){
	sequence *seq_copie = ptr_tete;
	while(seq_copie != NULL){
		seq_copie = seq_copie -> suite;
	}
	seq_copie -> suite = seq_copie;
}


cellule* rechercher_freres(sequence *ptr_sequence, cellule *ptr_cellule){
	cellule *cellule_copie;
	sequence *sequence_copie;
	cellule_copie = ptr_cellule;
	sequence_copie = ptr_sequence;
	while(sequence_copie != NULL && cellule_copie != NULL){
		while(cellule_copie -> elt != sequence_copie -> elt){
			cellule_copie = cellule_copie -> frere_suivant;
		}
		sequence_copie = sequence_copie -> suite;
		cellule_copie = cellule_copie -> fils;
	}
	return cellule_copie;
}


cellule* rechercher_dico(sequence *ptr_sequence, dico *dictionnaire){
	cellule *cellule_copie;
	cellule_copie = dictionnaire -> racine;
	return rechercher_freres(cellule_copie);
}