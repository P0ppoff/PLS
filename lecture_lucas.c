void inserer_tampon(sequence *seq, tampon *t, int nb_bits_restants, int nb_de_bits_a_remplir){ // nb = nombre de bits à mettre dans la séquence qui sont dans le tampon
    element masque = ~0;
    int taille = 8*sizeof(element); // Car sizeof donne la taille en OCTET.... 
    masque >>= (taille - (t -> nb_bits_dispo)); // si j'ai si bits disponible par exemple je veux 0011 1111.
    masque >>= ((t -> nb_bits_dispo) - nb_de_bits_a_remplir); // apres cette opération on a par exemple 00000111 pour nb_de_bits_a_remplir = 3
    //                                                                                                  00000001 pour nb_de_bits_a_remplir = 1
    //                                                                                                  00111111 pour nb_de_bits_a_remplir = 6
    //On note que (0 < nb_de_bits_a_remplir <= nb_bits_dispo) dans tout les appel de inserer_tampon (QUEL HASARD !!!!)

    masque <<= ((t -> nb_bits_dispo) - nb_de_bits_a_remplir); // apres cette opération on a par exemple 00111000 pour nb_de_bits_a_remplir = 3
    //                                                                                                  00100000 pour nb_de_bits_a_remplir = 1
    //                                                                                                  00111111 pour nb_de_bits_a_remplir = 6

    masque &= (t -> buffer);                                  // apres cette opération on a par exemple 00XXX000 pour nb_de_bits_a_remplir = 3
    //                                                                                                  00X00000 pour nb_de_bits_a_remplir = 1
    //                                                                                                  00XXXXXX pour nb_de_bits_a_remplir = 6
    // A priori maintenant on veut savoir ou coller cette merde dans la sequence. on utilise nb_bits_restants pour ça. (ingénieux!)
    if (nb_bits_restants <= (t -> nb_bits_dispo)){

        masque >>= ((t -> nb_bits_dispo) - nb_bits_restants);
    }
    else {

        masque <<= (nb_bits_restants - (t -> nb_bits_dispo));
    }

    (sequence -> elt) |= masque;
}

void lecture_bits(FILE *fichier, int nb_bits_a_lire, tampon *t, sequence *seq){
    //nb_bits_restants correspond au nombre de bit dans la séquence courante qui n'ont pas été modifié ainsi nb_bits_restant doit etre compris entre 0 et 8 
    //si nb_bits_restants = 0 alors la séquence est PLEINE et si nb_bits_restants = 8 la séquence est VIDE.
    //Comme on rempli les poid fort en premier, les bits non valide et qu'il faut modifier lorsque (nb_bits_restant != 0) sont les nb_bits_restants bits de poid faible (logique)

    //nb_bits_a_lire correspond au nombre de bits qu'il reste à lire en tout (logique)
    //nb_bits_dispo correspond aux nombre de bits de poids faible du buffer qui n'on pas encore été utilisé et qui son donc disponible (logique)
    sequence *courante = seq;
    int nb_bits_restants = 0;
    while (n != 0){ // ON regarde si on a encore des bits a lire.
        if ((t -> nb_bits_dispo) != 0){ // On regarde si le tampon est vide.

            if ((t -> nb_bits_dispo) <= nb_bits_restants){ // On regarde si il faut inserer tout les bits du tampon ou simplement une partie.

                if((t -> nb_bits_dispo) <= nb_bits_a_lire){ // Cas ou l'on doit videz les dernier bits disponible du buffer car on doit en lire plus qu'il n'y en a et que l'on peux en lire plus qu'il n'y en a sans avoir a chainé une sequence supplémentaire

                    inserer_tampon(courante, t, nb_bits_restants, (t -> nb_bits_dispo)); // insere les nb_bits_dispo bits du buffer t dans la sequence seq sachant qu'il reste nb_bits_restant bit a compléter dans seq
                    nb_bits_a_lire = nb_bits_a_lire - (t -> nb_bits_dispo); // on met a jour le nombre total de bit a lire puisque logiquement on vien d'en lire nb_bits-dispo.
                    nb_bits_restants = nb_bits_restants - (t -> nb_bits_dispo); // On met le nombre de bits restant à jour.
                    //On peut noter que dans le cas dans lequel on se trouve nb_bits_a_lire et nb_bits_restant reste positif car nb_bits_dispo est inferieur à ces deux valeurs.
                    (t -> nb_bits_dispo) = 0; // Enfin on met le nombre de bits disponible du buffer a 0 (logique car on vient de le vider)
                }
                else { //Ici on est dans le cas ou (nb_bits_a_lire < nb_bits_dispo <= nb_bits_restant)

                    inserer_tampon(courante, t, nb_bits_restants, nb_bits_a_lire); //Car nb_bits_a_lire est le plus petit.
                    nb_bits_restants = nb_bits_restants - nb_bits_a_lire;
                    (t -> nb_bits_dispo) = (t -> nb_bits_dispo) - nb_bits_a_lire;
                    //On peut encore noter que les resultat sont positif
                    nb_bits_a_lire = 0; // Enfin on met le nombre de bits a lire a 0 car on a lu tout ce qu'on voulais.
                }
            }
            else { // Cas ou il y a plus de bits dispo dans le tampon que de bit a modifier dans une unique sequence.

                if(nb_bits_a_lire <= nb_bits_restants){ //Cas ou nb_bits_a_lire <= nb_bits_restants < nb_bits_dispo

                    inserer_tampon(courante, t, nb_bits_restants, nb_bits_a_lire); //Car nb_bits_a_lire est le plus petit.
                    nb_bits_restants = nb_bits_restants - nb_bits_a_lire;
                    (t -> nb_bits_dispo) = (t -> nb_bits_dispo) - nb_bits_a_lire;
                    //On peut encore noter que les resultat sont positif
                    nb_bits_a_lire = 0; // Enfin on met le nombre de bits a lire a 0 car on a lu tout ce qu'on voulais.   


                } 
                else { // Dans ce cas nb_bits_restants est le plus petit donc il faut finir de le remplir et crerer une autre case pour la sequence.

                    inserer_tampon(courante, t, nb_bits_restants, nb_bits_restants);
                    nb_bits_a_lire = nb_bits_a_lire - nb_bits_restants;
                    (t -> nb_bits_dispo) = (t -> nb_bits_dispo) - nb_bits_restants;
                    courante -> suite) = creer_sequence(); // On doit créer une nouvelle case car on viens de remplir l'ancienne.
                    courante = (courante -> suite); // Ensuite on fait pointer le pointeur courant vers cette nouvelle case afin de faire les prochaine modification sur cette nouvelle case
                    nb_bits_restants = 8; // On vien de créer une nouvelle case donc elle est vide, Ainsi on let nb_bits_restants a 8.
                }
            }
        }
        else {
            (t -> buffer) = fgetc(fichier);
            (t -> nb_bits_restants) = 8;
        }
    }
}