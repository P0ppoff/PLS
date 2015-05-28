#ifndef _GESTION_DONNEES_H_
#define _GESTION_DONNEES_H_

void init_compression (dico *dictionnaire);

void init_decompression (dico table[], *dico dictionnaire);

//Description   :
//Parametre     :
//Retour        :   aucun
void maj_nb_bits;

//Description   :
//Parametre     :   dictionnaire
//Retour        :   dictionnaire avec le nouveau prefixe
dico * ajouter_prefixe (dico * dic, sequence seq);




#endif // _GESTION_DONNEES_H_
