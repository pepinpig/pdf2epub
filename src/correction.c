#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 50000
#define MAX_WORD_LEN 64

char *dictionary[MAX_WORDS];
int dict_size = 0;

void load_dictionary(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Dictionnaire introuvable");
        exit(1);
    }

    char line[MAX_WORD_LEN];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0'; // retirer \n
        dictionary[dict_size] = strdup(line);
        dict_size++;
        if (dict_size >= MAX_WORDS) break;
    }

    fclose(f);
}
int levenshtein(const char *s, const char *t) {
    int ls = strlen(s), lt = strlen(t);
    int **d = malloc((ls+1) * sizeof(int*));
    for (int i = 0; i <= ls; i++)
        d[i] = malloc((lt+1) * sizeof(int));

    for (int i = 0; i <= ls; i++) d[i][0] = i;
    for (int j = 0; j <= lt; j++) d[0][j] = j;

    for (int i = 1; i <= ls; i++) {
        for (int j = 1; j <= lt; j++) {
            int cost = (s[i-1] == t[j-1]) ? 0 : 1;
            d[i][j] = fmin(fmin(
                d[i-1][j] + 1,
                d[i][j-1] + 1),
                d[i-1][j-1] + cost
            );
        }
    }

    int dist = d[ls][lt];
    for (int i = 0; i <= ls; i++) free(d[i]);
    free(d);
    return dist;
}
const char *suggest_correction(const char *word) {
    int min_dist = 1000;
    const char *best = word;

    for (int i = 0; i < dict_size; i++) {
        int dist = levenshtein(word, dictionary[i]);
        if (dist < min_dist) {
            min_dist = dist;
            best = dictionary[i];
            if (dist == 0) break;
        }
    }

    return best;
}
void correct_text_with_dictionary(char *text) {
    char *result = malloc(strlen(text) * 2);
    result[0] = '\0';

    char *token = strtok(text, " \n\t");
    while (token) {
        const char *correction = suggest_correction(token);
        strcat(result, correction);
        strcat(result, " ");
        token = strtok(NULL, " \n\t");
    }

    strcpy(text, result);
    free(result);
}
