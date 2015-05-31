void ecrire(tampon *t, FILE *f){ // écriture du tampon puis mise à jour
	fputc(t->buffer, f);
	t->buffer = 0;
	t->nb_bits_restants = siezof(element);
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
