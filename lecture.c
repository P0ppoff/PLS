sequence* lecture_bits(FILE *fichier, int nb_bits, tampon * t){
    sequence * seq = creer_sequence();
    int n = nb_bits; // creation d'un entier qu'on modifieras (est utils car on ne veux pas modifier nb_bits qui n'est qu'une valeur d'entré )
    while (n != 0){ // ON regarde si on a encore des bits a lire.
        if ((t -> nb_bits_restants) != 0){ // On regarde si le tampon est vide.
            if (n >= (t -> nb_bits_restants)){ // On regarde si il faut inserer tout les bits du tampon ou simplement une partie.
                inserer_tampon (seq, t, (t -> nb_bits_restants)); // fonction qui insere nb_bits_restants bits de poid faible du buffer dans la sequence.
                n = n - (t -> nb_bits_restants); // Maj du nombre de bits lire restant car on vide le tampon dans se cas.
                (t -> nb_bits_restants) = 0; // On vien de vider le tampon donc le nombre de bit lisible dans  
            }
            else { // Cas ou il y a plus de bits lisible dans le tampon que de bit a lire.
                inserer_tampon (seq, t, n);
                (t -> nb_bits_restants) = (t -> nb_bits_restants) - n; //maj du nombre de bit encore non lu dans le tampon pour la prochaine utilisation de la fonction car ici 
                n = 0; // Comme il y avais plus de bit lisible que de bit a lire et qu'on les a inseré il faut mettre le nombre de bit a lire a 0 car le traitement est fini.
            }
        }
        else {
            (t -> buffer) = fgetc(fichier);
            (t -> nb_bits_restants) = 8;
        }
    }

    return seq;
}