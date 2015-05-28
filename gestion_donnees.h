#ifndef _GESTION_DONNEES_H_
#define _GESTION_DONNEES_H_

void init_compression (dico *dictionnaire);

void init_decompression (dico table[], *dico dictionnaire);

void maj_nb_bits;

dico* ajout_element (dico * dic, sequence seq);

sequence* ajout_queue(sequence* ptr_tete, sequence ptr_queue);

cellule* rechercher_dico(sequence* ptr_sequence, dico* dictionnaire);

cellule* rechercher_freres(sequence* ptr_sequence, cellule* ptr_cellule);






#endif // _GESTION_DONNEES_H_
