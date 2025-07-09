#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "manipulation_fichier.h"

#define WIDTH 512
#define HEIGHT 512
#define MAX_BLOBS 10000
#define MAX_ITER 100
#define K 5 // nombre de clusters globaux


typedef struct {
    int label;
    int min_x, min_y, max_x, max_y;
    int count;
    float cx, cy;
} Blob;

extern Blob blobs[MAX_BLOBS];

int label_components(matrice* img, matrice* labels);

int extract_blobs(matrice* img, matrice* labels,int num_labels);

typedef struct {
    float cx, cy;
} Centroid;


extern int kmeans_labels[MAX_BLOBS];

void kmeans(Blob *blobs, int n_blobs, int k);

void process_image(matrice* img);




