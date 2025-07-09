# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -I$(SRC_DIR)
PYTHON = python3

# Répertoires
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
DATA_DIR = data

SRC_FILES1 = matrice manipulation_fichier filtre
OBJ1 = $(patsubst %, $(BUILD_DIR)/%.o, $(SRC_FILES1))
test_filtre: $(OBJ1) $(TEST_DIR)/test_filtre.c
	$(CC) $(CFLAGS) -g $(OBJ1) $(TEST_DIR)/test_filtre.c -o $@ -lm

SRC_FILES2 = matrice manipulation_fichier epub
OBJ2 = $(patsubst %, $(BUILD_DIR)/%.o, $(SRC_FILES2))
test_epub: $(OBJ2) $(TEST_DIR)/test_epub.c
	$(CC) $(CFLAGS) -g $(OBJ2) $(TEST_DIR)/test_epub.c -o $@ -lm

SRC_FILES3 = matrice manipulation_fichier segmentation
OBJ3 = $(patsubst %, $(BUILD_DIR)/%.o, $(SRC_FILES3))
test_segmentation_bloc: $(OBJ3) $(TEST_DIR)/test_segmentation_bloc.c
	$(CC) $(CFLAGS) -g $(OBJ3) $(TEST_DIR)/test_segmentation_bloc.c -o $@ -lm




# Règle générique pour compiler les .o dans build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -g -c $< -o $@ -lm


# Extrait les pages du PDF (argument PDF=...)
extract:
ifndef PDF
	$(error Vous devez spécifier un PDF avec PDF=nom_du_fichier.pdf)
endif
	$(PYTHON) $(SRC_DIR)/pdf_to_jpg.py $(DATA_DIR)/$(PDF)

# Convertit les images en fichiers texte
convert:
	$(PYTHON) $(SRC_DIR)/jpg_to_txt.py

reconstruct:
ifndef TXT
	$(error Vous devez spécifier un txt avec TXT=nom_du_fichier.pdf)
endif
	$(PYTHON) $(SRC_DIR)/txt_to_jpg.py $(TXT)

# Exécution du pipeline complet
pipeline:
ifndef PDF
	$(error Vous devez spécifier un PDF avec PDF=nom_du_fichier.pdf)
endif
	$(PYTHON) $(SRC_DIR)/pdf_to_jpg.py $(DATA_DIR)/$(PDF)
	$(PYTHON) $(SRC_DIR)/jpg_to_txt.py

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)/*.o test_filtre
	rm -rf $(DATA_DIR)/pages_jpg $(DATA_DIR)/pages_txt


# Alias pratiques
.PHONY: matrice.o manipulation_fichier.o filtre.o all clean extract convert pipeline reconstruct

matrice.o: $(BUILD_DIR)/matrice.o
manipulation_fichier.o: $(BUILD_DIR)/manipulation_fichier.o
filtre.o: $(BUILD_DIR)/filtre.o
reconnaissance.o: $(BUILD_DIR)/reconnaissance.o
segmentation.o: $(BUILD_DIR)/segmentation.o
epub.o: $(BUILD_DIR)/epub.o
all: test_filtre test_epub
