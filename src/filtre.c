#include "filtre.h"
#define BORDS_VAL 255
bool est_bord(const matrice* img,int i ,int j, int rn_k, int rm_k){
    bool res = false; 
    res= (i<rn_k) ? true : res; 
    res= (j<rm_k) ? true : res; 
    res= (img->n-i-1<rn_k) ? true : res; 
    res= (img->m-j-1<rm_k)? true : res;
    return res; 
}

// Convolutions
int apply_kernel(const matrice* img, int x , int y, matrice* k){
    int rn_k= k->n/2;
    int rm_k= k->m/2;
    if (est_bord(img, x, y, rn_k, rm_k)){
        return BORDS_VAL; 
    }
    else{
        int origin_x = x-rn_k;
        int origin_y = y-rm_k;
        int res=0; 
        for (int i = 0; i < k->n; i++){
            for (int j = 0; j < k->m; j++){
                res+= k->mat[i][j]* img->mat[origin_x+i][origin_y+j];
            }
        }
        return res; 
    }
}

matrice* filtre_gaussien() {
    matrice* k = matrice_nulle(3,3);
    k->mat[0][0] = 1; k->mat[0][1] = 2; k->mat[0][2] = 1;
    k->mat[1][0] = 2; k->mat[1][1] = 4; k->mat[1][2] = 2;
    k->mat[2][0] = 1; k->mat[2][1] = 2; k->mat[2][2] = 1;
    // Normalisation : diviser la convolution par 16
    return k;
}

matrice* filtre_contours() {
    matrice* k = matrice_nulle(3,3);
    k->mat[0][0] =  0; k->mat[0][1] = -1; k->mat[0][2] =  0;
    k->mat[1][0] = -1; k->mat[1][1] =  4; k->mat[1][2] = -1;
    k->mat[2][0] =  0; k->mat[2][1] = -1; k->mat[2][2] =  0;
    return k;
}


matrice* filtering(const matrice* mat, matrice* k){
    matrice* res=matrice_nulle(mat->n, mat->m); 
    for (int i = 0; i < res->n; i++){
        for (int j = 0; j < res->m; j++){
            res->mat[i][j]= apply_kernel(mat, i, j, k);
        }
    }
    return res;     
}



int comparer(const void* a, const void* b) {
    double da = *(double*)a;
    double db = *(double*)b;
    return (da > db) - (da < db);
}
