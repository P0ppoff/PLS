#include "gestion_donnees.h"
#include "gestion_memoire.h"

void init_compression (dico *dictionnaire){
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	creer_cellule(dictionnaire->racine);
	cellule_courante = dictionnaire->racine;
	for (i = 0; i < 256; i++){
		cellule_courante -> index = i;
		cellule_courante -> elt = i;
		cellule_courante -> frere_precedent = cellule_precedente;
		creer_cellule(cellule_courante -> frere_suivant);
		cellule_precedente = cellule_courante;
		cellule_courante = cellule_courante -> frere_suivant;
	}
}

void init_decompression (dico table[], dico *dictionnaire){
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	creer_cellule(dictionnaire->racine);
	cellule_courante = dictionnaire->racine;
	for (i = 0; i < 256; i++){
		cellule_courante -> index = i;
		cellule_courante -> elt = i;
		table[i].racine = cellule_courante;
		cellule_courante -> frere_precedent = cellule_precedente;
		creer_cellule(cellule_courante -> frere_suivant);
		cellule_precedente = cellule_courante;
		cellule_courante = cellule_courante -> frere_suivant;
	}
}

void ajout_element (sequence *a, cellule *w, int *INDICE_MAX, int *TAILLE_ECRIT){
	cellule *courante;
	cellule *nouvelle_cell;
	creer_cellule(nouvelle_cell);
	//maj de l'indice
	(*INDICE_MAX) ++;
	if (2 ^ (*TAILLE_ECRIT) <= (*INDICE_MAX)){
		(*TAILLE_ECRIT) ++;
	}
	nouvelle_cell -> elt = a -> elt;
	nouvelle_cell -> index = (*INDICE_MAX);
	nouvelle_cell -> parent = w;
	courante = w->fils;
	if (courante==NULL){
		w -> fils = nouvelle_cell;
	}else {
		while(courante -> frere_suivant != NULL) {
			courante = courante -> frere_suivant;
		}
		courante -> frere_suivant = nouvelle_cell;
		nouvelle_cell -> frere_precedent = courante;
	}

}

void ajout_queue(sequence *ptr_tete, sequence *ptr_queue){
	sequence *seq_copie = ptr_tete;
	while(seq_copie != NULL){
		seq_copie = seq_copie -> suite;
	}
	seq_copie -> suite = seq_copie;
}


void rechercher_fils(sequence *ptr_sequence, cellule *ptr_cellule, cellule *cellule_copie){
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


void rechercher_dico(sequence *ptr_sequence, dico *dictionnaire, cellule *cellule_recherche){
	cellule_recherche = dictionnaire -> racine;
	return rechercher_fils(ptr_sequence,cellule_recherche, cellule_copie);
}

void inserer_tete(sequence *seq_ajout,sequence *ptr_seq) {
	if(ptr_seq == NULL){
		ptr_seq = seq_ajout;
	}else{
		seq_ajout -> suite = ptr_seq;
		ptr_seq = seq_ajout;
	}
}

void recupere_seq(dico *table, int i, sequence *seq_retour){
	sequence *nouvelle_seq;
	cellule *courante = table[i].racine;
	while(courante != NULL){
		creer_sequence(nouvelle_seq);
		nouvelle_seq -> elt = courante -> elt;
		inserer_tete(nouvelle_seq,seq_retour);
		courante = courante -> parent;
	}
}

void extraction_tete(sequence *a_extraire, sequence *retour){
	creer_sequence(retour);
	retour -> elt = a_extraire -> elt;
}

void ajout_element_concat(sequence *w, sequence *a, int *TAILLE_LU, int *INDICE_MAX, dico *table){
	cellule *ptr_cell;
	ptr_cell = rechercher_dico(w,table);
	ajout_element(a, ptr_cell, &INDICE_MAX, &TAILLE_ECRIT);
}


int conversion ( sequence *seq, int TAILLE_LU){
	int i,somme = 0;
	sequence *copie = seq;
	while (copie  != NULL){
		somme <<= sizeof(element);
		somme += (int)(copie->elt);
		copie = (copie->suite);
	}
	//décalage vers la droite pour corriger le remplissage de 0
	somme >>= sizeof(element) - (TAILLE_LU % sizeof(element));
	return somme;
}
