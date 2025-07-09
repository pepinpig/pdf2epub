
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define _POSIX_C_SOURCE 200809L

#define OUTPUT_DIR "epub_out"
#define META_INF_DIR OUTPUT_DIR "/META-INF"
#define OEBPS_DIR OUTPUT_DIR "/OEBPS"

typedef enum {
    CHAPITRE_PRINCIPAL,
    INTRODUCTION,
    ANNEXE
} TypeChapitre;

typedef struct {
    char *id_note;   
    char *texte;     
} Note;

typedef struct {
    TypeChapitre type;   
    char *titre;
    char *contenu;    
    Note *notes;
    int nb_notes;
    int numero_chapitre; // -1 si non numéroté
} Chapitre;

typedef struct {
    char *titre_livre;
    char *auteur;
    Chapitre *chapitres;
    int nb_chapitres;
} Livre;

void creer_dossiers(); 
void generer_mimetype();
void generer_container_xml();
void generer_chapitre_xhtml(Chapitre *chap, int index);
void generer_content_opf(Livre *livre);
void generer_toc_ncx(Livre *livre);
void zipper_epub(const char *nom_fichier);
void generer_epub(Livre *livre);