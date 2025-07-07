#pragma once

#include "matrice.h"

double variance(matrice* image, int x, int y, int dx, int dy);
int selection(matrice* image_input, matrice* image_output);
int selection_arr(matrice* image_input, int*** detected);
int min4(int un, int deux, int trois, int quatre);