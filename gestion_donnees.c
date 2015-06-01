#include "gestion_donnees.h"
#include "gestion_memoire.h"

void init_compression (dico *dictionnaire){ // initialisation du dictionnaire pour la compression
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	dictionnaire->racine = creer_cellule(); //creation de la première cellule
	cellule_courante = dictionnaire->racine;
	for (i = 0; i < 255; i++){ //On remplit 256 cellules
		cellule_courante -> index = i; //mise a jour de l'index
		cellule_courante -> elt = i; // mise a jour du contenu
		cellule_courante -> frere_precedent = cellule_precedente; //chainage des cellules
		cellule_courante -> frere_suivant = creer_cellule(); //creation de la suite des cellules
		cellule_precedente = cellule_courante; // on avance d'une cellule
		cellule_courante = cellule_courante -> frere_suivant;
	}
	cellule_courante -> index = i; //mise a jour de l'index
	cellule_courante -> elt = i; // mise a jour du contenu
	cellule_courante -> frere_precedent = cellule_precedente; //chainage des cellules
}

void init_decompression (dico *table, dico *dictionnaire){ // Initialisation du dico et de la table pour la decompression
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	dictionnaire->racine = creer_cellule();
	cellule_courante = dictionnaire->racine; 
	for (i = 0; i < 256; i++){ 
		cellule_courante -> index = i;
		cellule_courante -> elt = i;
		table[i].racine = cellule_courante;
		cellule_courante -> frere_precedent = cellule_precedente;
		cellule_courante -> frere_suivant = creer_cellule();
		cellule_precedente = cellule_courante;
		cellule_courante = cellule_courante -> frere_suivant;
	}
	cellule_courante -> index = i;
	cellule_courante -> elt = i;
	table[i].racine = cellule_courante;
	cellule_courante -> frere_precedent = cellule_precedente;
}

void ajout_element (sequence *a, cellule *w, int *INDICE_MAX, int *TAILLE_ECRIT){
	cellule *courante;
	cellule *nouvelle_cell;
	nouvelle_cell = creer_cellule(); //allocation d'une cellule
	//maj de l'indice
	(*INDICE_MAX) ++;
	if ((2 ^ (*TAILLE_ECRIT)) <= (*INDICE_MAX)){
		(*TAILLE_ECRIT) ++;
	}
	//fin maj de l'indice
	nouvelle_cell -> elt = a -> elt; //maj de l'element
	nouvelle_cell -> index = (*INDICE_MAX); //maj de l'index
	nouvelle_cell -> parent = w; //maj du parent
	courante = w->fils; //courante prend comme valeur le 1er fils de w
	if (courante==NULL){ // si w n'a pas de fils
		w -> fils = nouvelle_cell;	//alors nouvelle_cell est son 1er fils
	}else { //sinon
		while(courante -> frere_suivant != NULL) {
			courante = courante -> frere_suivant; // on parcours les freres jusqu'au dernier
		}
		courante -> frere_suivant = nouvelle_cell; //on place nouvelle_cell apres le dernier frere
		nouvelle_cell -> frere_precedent = courante;
	}

}

void ajout_queue(sequence *ptr_tete, sequence *ajout){
	sequence *seq_copie = ptr_tete;
	if (seq_copie != NULL) {
		while(seq_copie -> suite != NULL){
			seq_copie = seq_copie -> suite; //on parcours la sequence jusqu'a la fin
		}
		seq_copie -> suite  = ajout ; //on place la queue a la fin
	}
	else {
		ptr_tete = creer_sequence();
		ptr_tete  = ajout;
	}
}

//on recherche la sequence dans les freres de la cellule
cellule* rechercher_dans_fils(sequence *ptr_sequence, cellule *ptr_cellule){
	cellule *cellule_courante;
	sequence *sequence_courante = ptr_sequence;
	if (ptr_cellule != NULL) {
		cellule_courante = ptr_cellule -> fils;
		do {
			while (cellule_courante != NULL && cellule_courante -> elt != sequence_courante -> elt){
				cellule_courante = cellule_courante -> frere_suivant;
			}
			if (cellule_courante != NULL) {
				sequence_courante = sequence_courante -> suite;
				cellule_courante = cellule_courante -> fils;
			}		
		} while (cellule_courante != NULL);
	}
	return cellule_courante;
}

//on recherche la sequence dans les freres de la cellule
cellule* rechercher_dans_freres(sequence *ptr_sequence, cellule *ptr_cellule){
	cellule *cellule_courante = ptr_cellule;
	sequence *sequence_courante = ptr_sequence;
	printf("\t%p\n",cellule_courante);
	if (ptr_cellule != NULL) {
		do {
			while (cellule_courante != NULL && cellule_courante -> elt != sequence_courante -> elt){
				cellule_courante = cellule_courante -> frere_suivant;
				printf("\t%p\n",cellule_courante);
			}
			if (cellule_courante != NULL) {
				sequence_courante = sequence_courante -> suite;
				cellule_courante = cellule_courante -> fils;
				printf("\t%p\n",cellule_courante);
			}		
		} while (cellule_courante != NULL);
	}
	printf("\t%p\n",cellule_courante);
	return cellule_courante;
}


cellule* rechercher_dico(sequence *ptr_sequence, dico dictionnaire){
	cellule *cellule_recherche;
	cellule_recherche = rechercher_dans_freres(ptr_sequence, dictionnaire.racine);
	return cellule_recherche;
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
	sequence *nouvelle_seq = NULL;
	cellule *courante = table[i].racine;
	seq_retour = NULL;
	while(courante != NULL){
		nouvelle_seq = creer_sequence();
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
	cellule *ptr_cell = NULL;
	 ptr_cell = rechercher_dico(w, table[0]);
	ajout_element(a, ptr_cell, INDICE_MAX, TAILLE_LU);
}


int conversion (sequence *seq, int TAILLE_LU){
	int somme = 0;
	sequence *copie = seq;
	while (copie  != NULL){
		somme <<= 8;
		somme += (int)(copie->elt);
		copie = (copie->suite);
	}
	//décalage vers la droite pour corriger le remplissage de 0
	somme >>= 8 - (TAILLE_LU % 8);
	return somme;
}
