#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "segmentation2.h"

#define CHAR_SIZE 16
#define MAX_DATASET_SIZE 1000
#define K_NEIGHBORS 3

typedef struct {
    unsigned char image[CHAR_SIZE][CHAR_SIZE];
    char label; // caractère reconnu
} LabeledCharacter;

typedef struct {
    LabeledCharacter data[MAX_DATASET_SIZE];
    int size;
} Dataset;

extern int num_lines; // défini dans le fichier de segmentation
extern LineCharacters lines[MAX_LINES]; // défini dans le fichier de segmentation
