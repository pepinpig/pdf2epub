# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I$(SRC_DIR)
PYTHON = python3

# Répertoires
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
DATA_DIR = data

# Liste des fichiers source
SRC_FILES = matrice manipulation_fichier filtre

# Génère automatiquement les objets dans $(BUILD_DIR)
OBJ = $(patsubst %, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Cible de compilation principale pour test_filtre
test_filtre: $(OBJ) $(TEST_DIR)/test_filtre.c
	$(CC) $(CFLAGS) -g $(OBJ) $(TEST_DIR)/test_filtre.c -o $@ -lm

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
all: test_filtre
