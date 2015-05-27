#ifndef _GESTION_FICHIER_H_
#define _GESTION_FICHIER_H_

#include "types.h"


//Description   :
//Parametre     :   a definir
//Retour        :   8 bits
element lecture_element;


//Description   :
//Parametre     :   8 bits
//Retour        :   aucun
void ecriture_element (element elt);

//Description   :
//Parametre     :   aucun
//Retour        :   8 bits
element element_suivant;

//Description   :
//Parametre     :
//Retour        :   booleen
int est_fin;

void ouverture;

void fermeture;

#endif // _GESTION_FICHIER_H_
