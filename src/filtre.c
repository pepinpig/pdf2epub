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
int apply_kernel(const matrice* img, int x, int y, matrice* k){
    int rn_k= k->n/2;
    int rm_k= k->m/2;
    if (est_bord(img, x, y, rn_k, rm_k)){
        return BORDS_VAL; 
    }
    else{
        int origin_x = x-rn_k;
        int origin_y = y-rm_k;
        int res=0;
        int somme = 0;
        for (int i = 0; i < k->n; i++){
            for (int j = 0; j < k->m; j++){
                res += k->mat[i][j]* img->mat[origin_x+i][origin_y+j];
                somme += k->mat[i][j];
            }
        }
        if (somme != 0) {
            res = res / somme;  // Normalisation uniquement si somme non nulle
        }
        // Sinon res inchangé (filtre passe-haut ou gradient)
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

matrice* filtre_flou() {
    matrice* k = matrice_nulle(3,3);
    for (int i = 0; i < 3; i++){
       for(int j=0; j<3; j++){
            k->mat[i][j]=1;
       }
    }
    
    return k;
}



matrice* filtre_h(){
    matrice* k = matrice_nulle(1,3);
    k->mat[0][0] =1; k->mat[0][1] = 1; k->mat[0][2] =  1;
    return k;
}

matrice* filtre_v(){
    matrice* k = matrice_nulle(3,1);
    k->mat[0][0] =1; k->mat[1][0] = 1; k->mat[2][0] =  1;
    return k;
}

matrice* filtre_v25(){
    matrice* k = matrice_nulle(25,1);
    for (int i=0; i<25; i++){
        k->mat[i][0]=1;
    }
    // for (int i=5; i<20; i++){
    //     k->mat[i][0]=0;
    // }
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
int apply_dilatation(const matrice* img, int x, int y, matrice* k) {
    int rn_k = k->n / 2;
    int rm_k = k->m / 2;
    if (est_bord(img, x, y, rn_k, rm_k)) {
        return BORDS_VAL;
    } else {
        int origin_x = x - rn_k;
        int origin_y = y - rm_k;
        int min_val = 255; // Max valeur possible pour pixel

        for (int i = 0; i < k->n; i++) {
            for (int j = 0; j < k->m; j++) {
                if (k->mat[i][j] != 0) {  // Élément structurant actif
                    int val = img->mat[origin_x + i][origin_y + j];
                    if (val < min_val) {
                        min_val = val;
                    }
                }
            }
        }
        return min_val;
    }
}
matrice* filtering_dilatation(const matrice* mat, matrice* k) {
    matrice* res = matrice_nulle(mat->n, mat->m);
    for (int i = 0; i < res->n; i++) {
        for (int j = 0; j < res->m; j++) {
            res->mat[i][j] = apply_dilatation(mat, i, j, k);
        }
    }
    return res;
}

int apply_erosion(const matrice* img, int x, int y, matrice* k) {
    int rn_k = k->n / 2;
    int rm_k = k->m / 2;
    if (est_bord(img, x, y, rn_k, rm_k)) {
        return BORDS_VAL;
    } else {
        int origin_x = x - rn_k;
        int origin_y = y - rm_k;
        int max_val = 0; // Min valeur possible pour pixel

        for (int i = 0; i < k->n; i++) {
            for (int j = 0; j < k->m; j++) {
                if (k->mat[i][j] != 0) {
                    int val = img->mat[origin_x + i][origin_y + j];
                    if (val > max_val) {
                        max_val = val;
                    }
                }
            }
        }
        return max_val;
    }
}

matrice* filtering_erosion(const matrice* mat, matrice* k) {
    matrice* res = matrice_nulle(mat->n, mat->m);
    for (int i = 0; i < res->n; i++) {
        for (int j = 0; j < res->m; j++) {
            res->mat[i][j] = apply_erosion(mat, i, j, k);
        }
    }
    return res;
}