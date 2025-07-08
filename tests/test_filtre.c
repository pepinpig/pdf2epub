#include <stdio.h>
#include <stdlib.h>
#include "filtre.h"
#include "manipulation_fichier.h"
#include "matrice.h"


// Exemple de filtre
matrice* creer_filtre() {
    matrice* k=matrice_nulle(3,3);
    k->mat[0][0]=0; k->mat[0][1]=-1; k->mat[0][2]=0;
    k->mat[1][0]=-1; k->mat[1][1]=5; k->mat[1][2]=-1;
    k->mat[2][0]=0; k->mat[2][1]=-1; k->mat[2][2]=0;
    return k;
}

int main() {
    // Créer un filtre 3x3
    matrice* filtre = filtre_gaussien();
    matrice* img;
    read_matrice_from_file_dimension(&img, "page_000.txt"); 
    matrice* sortie = filtering(img, filtre);
    printf("\nImage filtrée :\n");
    save_matrice_to_file_dimension(sortie, "page_000_moyenne.txt");
    // Libération mémoire (à écrire ou utiliser si déjà implémenté)
    free_matrice(img);
    free_matrice(filtre);
    free_matrice(sortie);

    return 0;
}
