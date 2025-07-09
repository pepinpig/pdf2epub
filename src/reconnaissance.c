#include "reconnaissance.h"

void flatten_image(unsigned char image[CHAR_SIZE][CHAR_SIZE], unsigned char *out) {
    for (int i = 0; i < CHAR_SIZE; i++) {
        for (int j = 0; j < CHAR_SIZE; j++) {
            out[i * CHAR_SIZE + j] = image[i][j];
        }
    }
}
double euclidean_distance(unsigned char *a, unsigned char *b, int len) {
    double sum = 0.0;
    for (int i = 0; i < len; i++) {
        double d = (double)a[i] - (double)b[i];
        sum += d * d;
    }
    return sqrt(sum);
}
typedef struct {
    double dist;
    char label;
} Neighbor;

int compare_neighbors(const void *a, const void *b) {
    Neighbor *na = (Neighbor *)a;
    Neighbor *nb = (Neighbor *)b;
    return (na->dist > nb->dist) - (na->dist < nb->dist);
}

char knn_classify(Dataset *dataset, unsigned char image[CHAR_SIZE][CHAR_SIZE]) {
    unsigned char input_vec[CHAR_SIZE * CHAR_SIZE];
    flatten_image(image, input_vec);

    Neighbor neighbors[MAX_DATASET_SIZE];

    for (int i = 0; i < dataset->size; i++) {
        unsigned char ref_vec[CHAR_SIZE * CHAR_SIZE];
        flatten_image(dataset->data[i].image, ref_vec);

        neighbors[i].dist = euclidean_distance(input_vec, ref_vec, CHAR_SIZE * CHAR_SIZE);
        neighbors[i].label = dataset->data[i].label;
    }

    qsort(neighbors, dataset->size, sizeof(Neighbor), compare_neighbors);

    // Compter les fréquences parmi les K plus proches voisins
    int freq[256] = {0};
    for (int i = 0; i < K_NEIGHBORS; i++) {
        unsigned char c = (unsigned char)neighbors[i].label;
        freq[c]++;
    }

    // Trouver le caractère le plus fréquent
    int max_freq = 0;
    char best = '?';
    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            best = (char)i;
        }
    }

    return best;
}
void recognize_text_from_segments(Dataset *dataset, char *output, int max_len) {
    int pos = 0;
    for (int l = 0; l < num_lines; l++) {
        for (int c = 0; c < lines[l].count; c++) {
            if (pos < max_len - 1) {
                char ch = knn_classify(dataset, lines[l].chars[c].data);
                output[pos++] = ch;
            }
            // if (lines[l].chars[c].is_space && pos < max_len - 1){
            //     output[pos++] = ' ';
            // }

        }
        if (pos < max_len - 1) {
            output[pos++] = '\n'; // nouvelle ligne
        }
    }
    output[pos] = '\0';
}
void clean_hyphenation(char *text) {
    int len = strlen(text);
    char cleaned[8192];
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (text[i] == '-' && text[i + 1] == '\n') {
            // ignorer le tiret et la coupure
            i++; // saute '\n'
        } else {
            cleaned[j++] = text[i];
        }
    }
    cleaned[j] = '\0';
    strcpy(text, cleaned);
}
