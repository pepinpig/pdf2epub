#include "manipulation_fichier.h"

void nom_fichier(char* filename, char* matrix_name, char* image_name) {
    snprintf(filename, 256, "%s-%s.txt", matrix_name, image_name);
}

bool file_exists(const char *filename) {
    char complete_fn[256];
    snprintf(complete_fn, 256, "data/pages_txt/%s", filename);
    FILE *file = fopen(complete_fn, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}
void read_matrice_from_file_dimension(matrice** mtx, char* filename) {
    char complete_fn[256];
    snprintf(complete_fn, 256, "data/pages_txt/%s", filename);
    printf("%s\n", filename);
    FILE* fichier = fopen(complete_fn, "r");
    assert(fichier != NULL);
    int n, m;
    fscanf(fichier, "%d %d", &n, &m); 
    *mtx = matrice_nulle(n, m); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(fichier, "%lf", &((*mtx)->mat[i][j]));
        }
    }
    fclose(fichier);
    printf("Matrice lue depuis %s\n", filename);
}


void save_matrice_to_file_dimension(matrice* matrix, char* filename) {
    char complete_fn[256];
    snprintf(complete_fn, 256, "data/pages_txt/%s", filename);
    FILE* file = fopen(complete_fn, "w");
    assert(file != NULL);

    fprintf(file, "%d %d", matrix->n, matrix->m);
    fprintf(file, "\n");
    for (int i = 0; i < matrix->n; ++i) {
        for (int j = 0; j < matrix->m; ++j) {
            fprintf(file, "%lf ", matrix->mat[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Matrice enregistrée dans %s\n", filename);
}


void save_matrice_to_file(matrice *A, char* filename) {
    char complete_fn[256];
    snprintf(complete_fn, 256, "data/pages_txt/%s", filename);
    FILE *file = fopen(complete_fn, "w");
    assert(file != NULL);

    for (int i = 0; i < A->n; i++) {
        for (int j = 0; j < A->m; j++) {
            fprintf(file, "%lf ", A->mat[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Matrice enregistrée dans %s\n", filename);
}

void read_matrice_from_file(matrice* A, const char *filename) {
    char complete_fn[256];
    snprintf(complete_fn, 256, "data/pages_txt//%s", filename);
    FILE *file = fopen(complete_fn, "r");
    assert(file != NULL);

    for (int i = 0; i < A->n; i++) {
        for (int j = 0; j < A->m; j++) {
            fscanf(file, "%lf", &A->mat[i][j]);
        }
    }
    fclose(file);
    printf("Matrice lues depuis %s\n", filename);
}


void load_all_points_images(const char* filename, double* u, double*v, int n) {
    FILE *file = fopen(filename, "r");
    double ui, vi;
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf %lf", &ui, &vi);
        u[i]=ui;
        v[i]=vi;
    }
    fclose(file);
}


void load_all_points_reels(const char* filename, double* X, double* Y, double* Z, int n) {
    FILE *file = fopen(filename, "r");
    assert(file != NULL);
    double Xi, Yi, Zi;
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf %lf %lf", &Xi, &Yi, &Zi);
        X[i]=Xi;
        Y[i]=Yi;
        Z[i]=Zi;
    }
    fclose(file);
}
matrice* read_jpg(char* filename){
    char input_name[32];
    snprintf(input_name, sizeof(input_name), "%s.txt", filename);
    if (!file_exists(input_name)){
        char command[128];
        snprintf(command, sizeof(command), "python3 jpg_to_txt.py %s.jpg", filename);
        system(command);
    }
    matrice* input;
    read_matrice_from_file_dimension(&input, input_name);
    return input;
}

matrice* read_jpg_color(char* filename, char* color){
  char input_name[32];
  snprintf(input_name, sizeof(input_name), "%s_%s.txt", filename, color);
  if (!file_exists(input_name)){
      char command[128];
      snprintf(command, sizeof(command), "python3 jpg_to_txt_color.py %s.jpg", filename);
      system(command);
  }
  matrice* input;
  read_matrice_from_file_dimension(&input, input_name);
  return input;
}