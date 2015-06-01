#include "gestion_fichier.h"

#define FIN 256

FILE* ouverture_lecture(char nom_fichier[]){
	FILE* fichier = NULL;
    fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL){
        printf("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }
}

FILE* ouverture_ecriture(char nom_fichier[]){
	FILE* fichier = NULL;
    fichier = fopen(nom_fichier, "wb");
    if (fichier == NULL){
        printf("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }
}

void fermeture(FILE *fichier){
	fclose(fichier);
}

void inserer_tampon(sequence *seq, tampon *t, int nb, int *nb_bits_remplis){ // nb = nombre de bits à mettre dans la séquence qui sont dans le tampon
    sequence *courante;
    int indice_liste;
    int index_last_full;
    int i;
    int nb_lus;
    element masque;

    indice_liste = *nb_bits_remplis / sizeof(element); // Permet de savoir de combien d'élément est la liste donnée en argument
    index_last_full = *nb_bits_remplis % sizeof(element); // On récupère l'indice du dernier bit valide dans le dernier élément de la liste
    courante = seq; // On récupère la première case
    for(i=0; i<indice_liste; i++){
        courante = courante -> suite; // on avance dans la liste pour trouver la dernière case occupée
    }
    if(nb != 0){ // Savoir s'il reste des trucs à lire dans le tampon
        masque = 0;
        masque = ~masque;
        masque >>= t -> nb_bits_restants; // On décale vers la droite pour avoir les 1 sur les bits de points faibles
        masque &= t -> buffer; // on récupère ici les bits non utilisés dans le buffer
        masque >>= t -> nb_bits_restants - nb; // On continue de décaler pour avoir seulement les bits souhaités
        nb_lus = index_last_full - nb; // Calcul du nombre de bits que 'on va pouvoir placer dans le dernier élément de la liste
        courante -> elt |= (masque >> nb_lus); // mise en place des bits
        *nb_bits_remplis += nb_lus;
        if(nb_lus != nb){ // Nous avons rempli le dernier élément sans lire tous les bits voulus
            creer_sequence(courante -> suite); // On doit créer une nouvelle case
            masque <<= index_last_full; //on efface les bits déja lus du masque et on place les autres en poid fort
            courante -> elt = masque; // On ajoute les derniers bits à lire dans les poids forts de ntre nouvelle case
            nb_lus = sizeof(element) - index_last_full;
            *nb_bits_remplis += nb_lus;
        }
    }
}

void lecture_bits(FILE *fichier, int nb_bits_a_lire, tampon *t, sequence *seq){
    creer_sequence(seq);
    int nb_bits_remplis = 0;
    int n = nb_bits_a_lire; // creation d'un entier qu'on modifieras (est utils car on ne veux pas modifier nb_bits qui n'est qu'une valeur d'entrée )
    while (n != 0){ // ON regarde si on a encore des bits a lire.
        if ((t -> nb_bits_restants) != 0){ // On regarde si le tampon est vide.
            if (n >= (t -> nb_bits_restants)){ // On regarde si il faut inserer tout les bits du tampon ou simplement une partie.
                n = n - (t -> nb_bits_restants); // Maj du nombre de bits lire restant car on vide le tampon dans se cas.
                inserer_tampon (seq, t, (t -> nb_bits_restants), &nb_bits_remplis); // fonction qui insere nb_bits_restants bits de poid faible du buffer dans la sequence.
            }else{ // Cas ou il y a plus de bits lisible dans le tampon que de bit a lire.
                inserer_tampon (seq, t, n, &nb_bits_remplis);
                (t -> nb_bits_restants) = (t -> nb_bits_restants) - n; //maj du nombre de bit encore non lu dans le tampon pour la prochaine utilisation de la fonction car ici
                n = 0; // Comme il y avais plus de bit lisible que de bit a lire et qu'on les a inseré il faut mettre le nombre de bit a lire a 0 car le traitement est fini.
            }
        }
        else{
            (t -> buffer) = fgetc(fichier);
            (t -> nb_bits_restants) = 8;
        }
    }
}

int est_fin_fichier(sequence *ptr_seq){
	if(ptr_seq->elt == EOF ) {
		return 1;
	}
	else {
		return 0;
	}
}

void ecrire(tampon *t, FILE *f){ // écriture du tampon puis mise à jour
    fputc(t->buffer, f);
    t->buffer = 0;
    t->nb_bits_restants = sizeof(element);
}

void ecriture_indice(cellule *cell_w, FILE *f_out, int TAILLE_ECRIT, tampon *t){
    if(TAILLE_ECRIT <= t->nb_bits_restants){
        t->buffer |= ((element)(cell_w->index)) << (t->nb_bits_restants - TAILLE_ECRIT);
        t->nb_bits_restants -= TAILLE_ECRIT;
        if(t->nb_bits_restants == 0){ // le tampon est plein on doit l'écrire pour faire de la place
            ecrire(t, f_out);
        }
    }else{
        t->buffer |= (element) ((cell_w->index) >> (TAILLE_ECRIT - t->nb_bits_restants));
        TAILLE_ECRIT -= t->nb_bits_restants; // Mise à jour du nombre de bits qu'il reste à écrire
        ecrire(t, f_out); // écriture du tampon car il est plein
        ecriture_indice(cell_w, f_out, TAILLE_ECRIT, t); // Finalement la TAILLE_ECRIT correspond aussi aunombre de bits qu'il reste à écrire
    }
}

void ecriture_fin(FILE *fichier, int TAILLE_ECRIT, tampon *t){
    int code;
    int nb_bits; // représente le nombre de bits à écrire dans l'entier code
    int decalage;

    code = t -> buffer; // on récupère le buffer sur un grand nombre
    code <<= TAILLE_ECRIT - (t -> nb_bits_restants); // on décale pour faire de la place au code de fin
    code |= FIN;
    nb_bits = TAILLE_ECRIT + 8 - (t -> nb_bits_restants);
    while(nb_bits > 0){ // tant qu'il reste des bits à écrire
        if(nb_bits >= 8){ // on peut encore écrire un octet plein
            decalage = nb_bits % 8; // on enlève les derniers bits non multiples de 8
            decalage += 8 * ((decalage / 8) - 1); // on supprime le nombre d'octets total qu'il reste moins 1
            fputc(code >> decalage, fichier); // on écrit donc l'octet de poids fort qui nous interresse
        }else{
            decalage = 8 - nb_bits; // trouve combien de zéro je dois ajouter pour que les bits voulus soit en poids forts de l'octet
            fputc(code << decalage, fichier);
        }
        nb_bits -= 8; // on vient d'écrire un octet alors on enlève 8 au nombre de bits à écrire
    }
}

void ecriture_seq(FILE *fichier, sequence *seq){ // permet d'écrire la liste d'éléments dans le fichier suivante la taille d'écriture courante
    sequence *courante;

    courante = seq;
    while(courante != NULL){
        fputc(courante -> elt, fichier);
        courante = courante -> suite;
    }
}
