#define WIDTH  512
#define HEIGHT 512
#define MAX_LINES 100
#define MAX_CHARS_PER_LINE 100
#define CHAR_SIZE 16 // Taille normalisée pour KNN

typedef struct {
    int x_min, y_min, x_max, y_max;
} BoundingBox;

typedef struct {
    unsigned char data[CHAR_SIZE][CHAR_SIZE]; // Image redimensionnée
    BoundingBox box;
} CharacterImage;

typedef struct {
    CharacterImage chars[MAX_CHARS_PER_LINE];
    int count;
} LineCharacters;

LineCharacters lines[MAX_LINES];
int num_lines = 0;

unsigned char image[HEIGHT][WIDTH]; // Image binaire (0=caractère, 255=fond)
