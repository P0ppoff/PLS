#include "gestion_donnees.h"
#include "gestion_memoire.h"

void init_compression (dico *dictionnaire){ // initialisation du dictionnaire pour la compression
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	dictionnaire->racine = creer_cellule(); //creation de la première cellule
	cellule_courante = dictionnaire->racine;
	for (i = 0; i < 256; i++){ //On remplit 256 cellules
		cellule_courante -> index = i; //mise a jour de l'index
		cellule_courante -> elt = i; // mise a jour du contenu
		cellule_courante -> frere_precedent = cellule_precedente; //chainage des cellules
		cellule_courante -> frere_suivant = creer_cellule(); //creation de la suite des cellules
		cellule_precedente = cellule_courante; // on avance d'une cellule
		cellule_courante = cellule_courante -> frere_suivant;
	}
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
}

void ajout_element (sequence *a, cellule *w, int *INDICE_MAX, int *TAILLE_ECRIT){
	cellule *courante;
	cellule *nouvelle_cell;
	nouvelle_cell = creer_cellule(); //allocation d'une cellule
	//maj de l'indice
	(*INDICE_MAX) ++;
	if (2 ^ (*TAILLE_ECRIT) <= (*INDICE_MAX)){
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

void ajout_queue(sequence *ptr_tete, sequence *ptr_queue){
	sequence *seq_copie = ptr_tete;
	while(seq_copie != NULL){
		seq_copie = seq_copie -> suite; //on parcours la sequence jusqu'a la fin
	}
	seq_copie -> suite = ptr_queue; //on place la queue a la fin
}


void rechercher_fils(sequence *ptr_sequence, cellule *ptr_cellule, cellule *cellule_copie){
	sequence *sequence_copie;
	cellule_copie = ptr_cellule;
	sequence_copie = ptr_sequence;
	// on parcours les sequences jusqu'a avoir les memes ou une finie
	while(sequence_copie != NULL && cellule_copie != NULL){
		while(cellule_copie -> elt != sequence_copie -> elt){
			cellule_copie = cellule_copie -> frere_suivant;
		}
		sequence_copie = sequence_copie -> suite;
		cellule_copie = cellule_copie -> fils;
	}
}


void rechercher_dico(sequence *ptr_sequence, dico *dictionnaire, cellule *cellule_recherche){
	cellule_recherche = dictionnaire -> racine;
	rechercher_fils(ptr_sequence,dictionnaire -> racine, cellule_recherche);
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
	seq_retour = NULL;
	while(courante != NULL){
		nouvelle_seq = creer_sequence();
		nouvelle_seq -> elt = courante -> elt;
		inserer_tete(nouvelle_seq,seq_retour);
		courante = courante -> parent;
	}
}

void extraction_tete(sequence *a_extraire, sequence *retour){
	retour = creer_sequence();
	retour -> elt = a_extraire -> elt;
}

void ajout_element_concat(sequence *w, sequence *a, int *TAILLE_LU, int *INDICE_MAX, dico *table){
	cellule *ptr_cell;
	rechercher_dico(w, table, ptr_cell);
	ajout_element(a, ptr_cell, INDICE_MAX, TAILLE_LU);
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
