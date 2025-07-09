#include "segmentation.h"
#include "manipulation_fichier.h"
#include "matrice.h"
int main(){
    matrice* img;
    read_matrice_from_file_dimension(&img, "page_000.txt"); 
    process_image(img);
}