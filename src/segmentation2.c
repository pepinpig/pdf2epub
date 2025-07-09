
#include "segmentation2.h"

void compute_horizontal_projection(int *proj) {
    for (int y = 0; y < HEIGHT; y++) {
        int sum = 0;
        for (int x = 0; x < WIDTH; x++) {
            if (image[y][x] == 0) sum++;
        }
        proj[y] = sum;
    }
}

void compute_vertical_projection(int y_min, int y_max, int *proj) {
    for (int x = 0; x < WIDTH; x++) {
        int sum = 0;
        for (int y = y_min; y <= y_max; y++) {
            if (image[y][x] == 0) sum++;
        }
        proj[x] = sum;
    }
}

void resize_char_image(unsigned char src[HEIGHT][WIDTH], BoundingBox box, unsigned char dest[CHAR_SIZE][CHAR_SIZE]) {
    int w = box.x_max - box.x_min + 1;
    int h = box.y_max - box.y_min + 1;

    for (int i = 0; i < CHAR_SIZE; i++) {
        for (int j = 0; j < CHAR_SIZE; j++) {
            int src_x = box.x_min + j * w / CHAR_SIZE;
            int src_y = box.y_min + i * h / CHAR_SIZE;
            if (src_x >= WIDTH) src_x = WIDTH - 1;
            if (src_y >= HEIGHT) src_y = HEIGHT - 1;
            dest[i][j] = src[src_y][src_x];
        }
    }
}


void segment_characters_in_line(int y_min, int y_max, LineCharacters *line_chars) {
    int vertical_proj[WIDTH];
    compute_vertical_projection(y_min, y_max, vertical_proj);

    int in_char = 0, x_start = 0;
    line_chars->count = 0;

    for (int x = 0; x < WIDTH; x++) {
        if (!in_char && vertical_proj[x] > 0) {
            in_char = 1;
            x_start = x;
        } else if (in_char && vertical_proj[x] == 0) {
            in_char = 0;
            int x_end = x - 1;

            if (line_chars->count < MAX_CHARS_PER_LINE) {
                CharacterImage *ci = &line_chars->chars[line_chars->count];
                ci->box.x_min = x_start;
                ci->box.x_max = x_end;
                ci->box.y_min = y_min;
                ci->box.y_max = y_max;

                resize_char_image(image, ci->box, ci->data);
                line_chars->count++;
            }
        }
        int previous_right = -1;

    }
}
void segment_lines() {
    int proj[HEIGHT];
    compute_horizontal_projection(proj);

    int in_line = 0, y_start = 0;
    num_lines = 0;

    for (int y = 0; y < HEIGHT; y++) {
        if (!in_line && proj[y] > 0) {
            in_line = 1;
            y_start = y;
        } else if (in_line && proj[y] == 0) {
            in_line = 0;
            int y_end = y - 1;

            if (num_lines < MAX_LINES) {
                segment_characters_in_line(y_start, y_end, &lines[num_lines]);
                num_lines++;
            }
        }
    }
}
