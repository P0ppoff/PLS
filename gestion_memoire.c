#include "gestion_memoire.h"

void liberer_sequence (sequence *ptr_seq){
    sequence *courant;
    while(ptr_seq != NULL){
        courant = ptr_seq;
        ptr_seq = ptr_seq->suite;
        free(courant);
        courant = NULL;
    }
}

void liberer_cellule (cellule *ptr_cell);
void liberer_frere (cellule *ptr_cell);
void liberer_fils (cellule *ptr_cell);

void liberer_frere (cellule *ptr_cell) {
    liberer_cellule(ptr_cell->frere_suivant);
}

void liberer_fils (cellule *ptr_cell) {
    liberer_cellule(ptr_cell->fils);
}

void liberer_cellule (cellule *ptr_cell){
    liberer_frere(ptr_cell);
    liberer_fils(ptr_cell);
    free(ptr_cell);
    ptr_cell = NULL;
}

void liberer_dico (dico *ptr_dico){
    liberer_cellule(ptr_dico->racine);
    ptr_dico->racine = NULL;
    free(ptr_dico);
    ptr_dico = NULL;
}

sequence* creer_sequence() {
    sequence* ptr_seq = malloc(sizeof(sequence));
    if (ptr_seq == NULL) {
        printf("Allocation sequence impossible\n");
        exit(EXIT_FAILURE);
    }
    ptr_seq->suite = NULL;
    ptr_seq->elt = 0;
    return ptr_seq;
}

cellule* creer_cellule() {
    cellule* ptr_cellule = malloc(sizeof(cellule));
    if (ptr_cellule == NULL) {
        printf("Allocation cellule impossible\n");
        exit(EXIT_FAILURE);
    }
    ptr_cellule->parent = NULL;
    ptr_cellule->frere_suivant = NULL;
    ptr_cellule->frere_precedent = NULL;
    ptr_cellule->fils = NULL;
    ptr_cellule->elt = 0;
    ptr_cellule->index = 0;
    return ptr_cellule;
}

void modif_lg_table (dico *table){
    table = (dico*) realloc(table,2*sizeof(table));
}
