
void liberer_dico (dico * ptr_dico){
    free(ptr_dico);
    ptr_dico = NULL;
}

void liberer_sequence (sequence * ptr_seq){
    free(ptr_seq);
    ptr_seq = NULL;
}

void liberer_cellule (cellule * ptr_cell){
    free(ptr_cell);
    ptr_cell = NULL;
}


dico * creer_dico {
    dico * ptr_dico = malloc(sizeof(dico));
    if (ptr_dico == NULL) {
        printf("Allocation dictionnaire impossible\n");
        exit(EXIT_FAILURE);
    }
    return ptr_dico;
}

sequence * creer_sequence {
    sequence * ptr_seq = malloc(sizeof(sequence));
    if (ptr_seq == NULL) {
        printf("Allocation sequence impossible\n");
        exit(EXIT_FAILURE);
    }
    return ptr_seq;
}

cellue * creer_cellule {
    cellule * ptr_cellule = malloc(sizeof(cellule));
    if (ptr_cellule == NULL) {
        printf("Allocation cellule impossible\n");
        exit(EXIT_FAILURE);
    }
    return ptr_cellule;
}

void modif_lg_table (dico[] table){
    table[0] = (dico *) realloc(table[0],2*sizeof(table));
}
