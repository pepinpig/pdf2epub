#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "matrice.h"
#define MAX_FILENAME 256

//Teste l'existence du fichier filename
bool file_exists(const char *filename);

//Enregistre la matrice dans un fichier texte <matrix_name>-<image_name>.txt avec ses dimensions sur la première ligne
void save_matrice_to_file_dimension(matrice* matrix, char* filename);

//Enregsitre la matrice dans un fichier texte <matrix_name>-<image_name>.txt
void save_matrice_to_file(matrice* matrix, char* filename);

//Lis la matrice dans filename avec les dimension sur le première ligne et fait pointer vers mtx
void read_matrice_from_file_dimension(matrice** mtx, char* filename);

//Lis la matrice dans filename et fait pointer vers mtx
void read_matrice_from_file(matrice *A, const char *filename);
//Créer chaine de caractère <matrix_name>-<image_name>.txt
void nom_fichier(char* filename, char* matrix_name, char* image_name);

matrice* read_jpg(char* filename);

matrice* read_jpg_color(char* filename, char* color);