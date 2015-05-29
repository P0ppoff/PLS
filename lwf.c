#include <stdio.h>

#include "compresser.h"
//#include "decompresser.h"
#include "gestion_fichier.h"

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

void extention(char *original, char *sortie){
	int i = 0;
	int change = 0;
	while(!change && (original[i] != '\0')){
		if(!change && (original[i] == '.')){
			sortie[i] = original[i];
			sortie[i+1] = 'l';
			sortie[i+2] = 'w';
			sortie[i+3] = 'f';
			sortie[i+4] = '\0';
			change = 1;
		}
		if(!change){
			sortie[i] = original[i];
		}
		i++;
	}
	if(!change){
		sortie[i]   = '.';
		sortie[i+1] = 'l';
		sortie[i+2] = 'w';
		sortie[i+3] = 'f';
		sortie[i+4] = '\0';
	}
}

void extraire_nom(char *original, char *sortie){
	int i = 0;
	int change = 0;
	while(!change && (original[i] != '\0')){
		if(!change && (original[i] == '.')){
			change = 1;
		}
		if(!change){
			sortie[i] = original[i];
		}
		i++;
	}
	sortie[i] = '\0';
}

int main(int argc, char **argv) {

	char option = 0; // équivalent à option = '\0'

	char *sortie;

	FILE *f_in, *f_out;

	if(argc != 3){
		printf("\n\tUtilisation : ./Lwf -[c/e] fichier\n\n");
		return 1;
	}else{
		option = choix(argv[1]);
		if(option == 'c'){
			printf("\n\tCompression\n\n");
			extention(argv[2], sortie);
			f_in = ouverture_lecture(argv[2]);
			f_out = ouverture_ecriture(sortie);
			compresser(f_in,f_out);
			fermeture(f_in);
			fermeture(f_out);
		}else if(option == 'e'){
			printf("\n\tExtraction\n\n");
			extraire_nom(argv[2], sortie);
			printf("%s\n", sortie);
			// f_in = ouverture_lecture(argv[2]);
			// f_out = ouverture_ecriture(sortie);
			// decompresser(f_in,f_out);
			// fermeture(f_in);
			// fermeture(f_out);
		}else{		
			printf("\n\tUtilisation : ./Lwf -[c/e] fichier\n\n");
			return 1;
		}
	}
	return 0;
}
