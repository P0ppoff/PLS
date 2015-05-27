#include <stdio.h>

//#include "compresser.h"
//#include "decompresser.h"

/* Notre programme principal doit permettre de choisir entre :
 * une compression de fichier et 
 * une décompression d'un fichier compressé par notre programme.
 * Dans ce dernier cas, nous devons vérifier l'extension que nous avons ajoutée.
 * Notre allons donc procéder à une vérification des arguments.
 */

/* Fonction permettant de vérifier l'écriture d'une option et de retourner cette option
 * L'option doit être d'un caractère seulement
 */
char choix(char* champs_option){
 	if(champs_option[0] != '-' || champs_option[2] != '\0'){
 		return 0;
 	}else{
 		return champs_option[1];
 	}
}

int main (int argc, char** argv) {

	char option = 0; // équivalent à option = '\0'

	if(argc != 3){
		printf("\n\tUtilisation : ./Lwf -[c/e] fichier\n\n");
		return 1;
	}else{
		option = choix(argv[1]);
		if(option == 'c'){
			printf("\n\tCompression\n\n");
		}else if(option == 'e'){
			printf("\n\tExtraction\n\n");
		}else{		
			printf("\n\tUtilisation : ./Lwf -[c/e] fichier\n\n");
			return 1;
		}
	}
	return 0;
}
