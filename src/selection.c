#include "selection.h"

// Calcul de la variance pour une direction donnée
double variance(matrice* image, int x, int y, int dx, int dy) {
    int count = 0; int sum = 0; int sumSq = 0;
    for (int i = -Window; i <= Window; ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < image->m && ny >= 0 && ny < image->n) {
            int val = image->mat[ny][nx];
            sum += val;
            sumSq += val * val;
            count++;
        }
    }
    return (count > 0) ? (sumSq - (sum * sum) / count) : 0;
}

int min4(int un, int deux, int trois, int quatre){
    int min=un;
    min= (deux<min) ? deux : min; 
    min= (trois<min) ? trois : min; 
    min= (quatre<min) ? quatre : min; 
    return min
}

int selection(matrice* image_input, matrice* image_output) {
    int count=0;
    for (int y = 1; y < image_input->n - 1; y++) {
        for (int x = 1; x < image_input->m - 1; x++) {
            int var0 = variance(image_input, x, y, 0, 1);  // Verticale
            int var1 = variance(image_input, x, y, 1, 0);  // Horizontale
            int var2 = variance(image_input, x, y, 1, 1);  // Diagonale bas gauche haut droite
            int var3 = variance(image_input, x, y, 1, -1); // Diagonale haut gauche bas droite 
            int score = min4(var0, var1, var2, var3);
            if (score > Seuil_selection) {
                image_output->mat[y][x] = 1;  // Coin détecté
                count++;
            } else {
                image_output->mat[y][x] = 0;  // Pas de coin
            }
        }
    }
    return count;
}