#include "segmentation2.h"

void print_results() {
    for (int i = 0; i < num_lines; i++) {
        printf("Ligne %d : %d caractères\n", i, lines[i].count);
        for (int j = 0; j < lines[i].count; j++) {
            CharacterImage *c = &lines[i].chars[j];
            printf("  Caractère %d : [%d,%d]-[%d,%d]\n", j,
                   c->box.x_min, c->box.y_min, c->box.x_max, c->box.y_max);
        }
    }
}

int main() {

    segment_lines();
    print_results();

    return 0;
}
