#pragma once
#include "matrice.h"
// détermine si le pixel (i,j) est sur un bord de res(pas assez de pixel pour appliquer le kernel de rayon rn_k*rm_k)
bool est_bord(const matrice* res,int i ,int j, int rn_k, int rm_k); 

// calcul la valeur du pixel de coordonnée x,y sur img
int apply_kernel(const matrice* img,int x ,int y, matrice* k);

//Gaussienn 
matrice* filtre_gaussien();

// Filtre passe-haut (renforcement des contours)
matrice* filtre_contours(); 

// renvoie une copie de mat en ayant appliqué le filtre de kernel k
matrice* filtering(const matrice* mat, matrice* k);
