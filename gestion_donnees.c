#include "gestion_donnees.h"
#include "types.h"

void init_compression (dico *dictionnaire){
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	dictionnaire = creer_cellule();
	cellule_courante = dictionnaire;
	for (i = 0; i < 258; i++)
	{
		cellule_courante -> index = i;
		cellule_courante -> elt = i;
		cellule_courante -> frere_precedent = cellule_precedente;
		cellule_courante -> frere_suivant = creer_cellule();
		cellule_precedente = cellule_courante;
		cellule_courante = cellule_courante -> frere_suivant;
	}
}

void init_decompression (dico table[], *dico dictionnaire){
	int i;
	cellule *cellule_precedente = NULL;
	cellule *cellule_courante;
	dictionnaire = creer_cellule();
	cellule_courante = dictionnaire;
	for (i = 0; i < 258; i++)
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
