#include "segmentation.h"

// ------------------------ UNION-FIND POUR COMPOSANTES ------------------------

static int parent[MAX_BLOBS];
static int rank[MAX_BLOBS];

static int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

static void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx == ry) return;
    if (rank[rx] < rank[ry])
        parent[rx] = ry;
    else {
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) rank[rx]++;
    }
}


int label_components(matrice* img, matrice* labels) {
    int next_label = 1;
    for (int i = 0; i < MAX_BLOBS; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int y = 0; y < img->m; y++) {
        for (int x = 0; x < img->n; x++) {
            if (img->mat[y][x] < 128) { // pixel noir
                int left = (x > 0) ? labels->mat[y][x - 1] : 0;
                int top = (y > 0) ? labels->mat[y - 1][x] : 0;

                if (left && top) {
                    labels->mat[y][x] = left;
                    unite(left, top);
                } else if (left || top) {
                    labels->mat[y][x] = left ? left : top;
                } else {
                    labels->mat[y][x] = next_label++;
                }
            }
        }
    }

    for (int y = 0; y < img->n; y++) {
        for (int x = 0; x < img->m; x++) {
            if (labels->mat[y][x])
                labels->mat[y][x] = find(labels->mat[y][x]);
        }
    }

    return next_label;
}

// ------------------------ DESCRIPTION DES BLOBS ------------------------
Blob blobs[MAX_BLOBS];
int extract_blobs(matrice* img, matrice* labels,int num_labels) {
    for (int i = 0; i < num_labels; i++) {
        blobs[i].label = i;
        blobs[i].min_x = img->m; blobs[i].min_y = img->n;
        blobs[i].max_x = 0; blobs[i].max_y = 0;
        blobs[i].count = 0;
    }

    for (int y = 0; y < img->n; y++) {
        for (int x = 0; x < img->m; x++) {
            int l = labels->mat[y][x];
            if (l > 0) {
                if (x < blobs[l].min_x) blobs[l].min_x = x;
                if (x > blobs[l].max_x) blobs[l].max_x = x;
                if (y < blobs[l].min_y) blobs[l].min_y = y;
                if (y > blobs[l].max_y) blobs[l].max_y = y;
                blobs[l].count++;
            }
        }
    }

    int count_valid = 0;
    for (int i = 1; i < num_labels; i++) {
        if (blobs[i].count > 10) { // filtrer les petits bruits
            blobs[i].cx = (blobs[i].min_x + blobs[i].max_x) / 2.0f;
            blobs[i].cy = (blobs[i].min_y + blobs[i].max_y) / 2.0f;
            blobs[count_valid++] = blobs[i];
        }
    }
    return count_valid;
}

// ------------------------ K-MEANS CLUSTERING ------------------------
int kmeans_labels[MAX_BLOBS];
void kmeans(Blob *blobs, int n_blobs, int k) {
    Centroid centroids[K];
    for (int i = 0; i < k; i++) {
        centroids[i].cx = blobs[i].cx;
        centroids[i].cy = blobs[i].cy;
    }

    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Affectation
        for (int i = 0; i < n_blobs; i++) {
            float best_dist = 1e9;
            int best_k = 0;
            for (int j = 0; j < k; j++) {
                float dx = blobs[i].cx - centroids[j].cx;
                float dy = blobs[i].cy - centroids[j].cy;
                float dist = dx * dx + dy * dy;
                if (dist < best_dist) {
                    best_dist = dist;
                    best_k = j;
                }
            }
            kmeans_labels[i] = best_k;
        }

        // Mise à jour
        float sum_x[K] = {0}, sum_y[K] = {0};
        int count[K] = {0};
        for (int i = 0; i < n_blobs; i++) {
            int c = kmeans_labels[i];
            sum_x[c] += blobs[i].cx;
            sum_y[c] += blobs[i].cy;
            count[c]++;
        }
        for (int j = 0; j < k; j++) {
            if (count[j] > 0) {
                centroids[j].cx = sum_x[j] / count[j];
                centroids[j].cy = sum_y[j] / count[j];
            }
        }
    }
}   

matrice* afficher_blobs(matrice* labels, int num_labels) {
    matrice* resultat = matrice_nulle(labels->n, labels->m);

    // Génère une couleur (valeur entre 1 et 255) unique par label
    unsigned char couleurs[MAX_BLOBS] = {0};
    for (int i = 1; i < num_labels; i++) {
        couleurs[i] = (i * 37) % 255 + 1; // Valeurs pseudo-aléatoires entre 1 et 255
    }

    for (int y = 0; y < labels->n; y++) {
        for (int x = 0; x < labels->m; x++) {
            int l = labels->mat[y][x];
            if (l > 0) {
                resultat->mat[y][x] = couleurs[l];
            } else {
                resultat->mat[y][x] = 0; // fond
            }
        }
    }

    return resultat;
}


// ------------------------ UTILISATION ------------------------
void process_image(matrice* img) {
    matrice* labels=matrice_nulle(img->n, img->m);
    int num_labels = label_components(img, labels);
    int n_blobs = extract_blobs(img, labels, num_labels);
    kmeans(blobs, n_blobs, K);
    printf("%d\n", n_blobs);
    matrice* sortie= afficher_blobs(labels, num_labels);
    save_matrice_to_file_dimension(sortie, "blob.txt");
}
