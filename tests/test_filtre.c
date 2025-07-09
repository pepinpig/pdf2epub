#include <stdio.h>
#include <stdlib.h>
#include "filtre.h"
#include "manipulation_fichier.h"
#include "matrice.h"


matrice* filtre_flou15() {
    matrice* k = matrice_nulle(15,15);
    for (int i = 0; i < 15; i++){
       for(int j=0; j<15; j++){
            k->mat[i][j]=1;
       }
    }
    
    return k;
}

int main() {
    // Créer un filtre 3x3
    matrice* filtre = filtre_flou15();
    matrice* img;
    read_matrice_from_file_dimension(&img, "page_000_dil3v1.txt"); 
    matrice* sortie = filtering(img, filtre);
    printf("\nImage filtrée :\n");
    save_matrice_to_file_dimension(sortie, "page_000_dil3v1f.txt");
    // Libération mémoire (à écrire ou utiliser si déjà implémenté)
    free_matrice(img);
    free_matrice(filtre);
    free_matrice(sortie);
    system("python3 src/txt_to_jpg.py page_000_dil3v1f.txt");
    return 0;
}
