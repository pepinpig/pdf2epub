#pragma once
#include "matrice.h"

#define WINDOW 4
#define SEUIL_SELECTION 500

//Calcul d'une variance statistique locale pour le pixel de coordonnées (x, y) dans la direction (dx, dy)
double variance(matrice* image, int x, int y, int dx, int dy);

//Application de l'algorithme de selection a chaque pixel de l'image
int selection(matrice* image_input, matrice* image_output);

// Minimum entre 4 entiers 
int min4(int un, int deux, int trois, int quatre);