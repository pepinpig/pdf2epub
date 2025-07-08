#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "epub.h"

#define OUTPUT_DIR "epub_out"
#define META_INF_DIR OUTPUT_DIR "/META-INF"
#define OEBPS_DIR OUTPUT_DIR "/OEBPS"

// --- Structures déjà définies comme dans ta question ---

void creer_dossiers() {
    mkdir(OUTPUT_DIR, 0755);
    mkdir(META_INF_DIR, 0755);
    mkdir(OEBPS_DIR, 0755);
}

void generer_mimetype() {
    FILE *f = fopen(OUTPUT_DIR "/mimetype", "w");
    fprintf(f, "application/epub+zip");
    fclose(f);
}

void generer_container_xml() {
    FILE *f = fopen(META_INF_DIR "/container.xml", "w");
    fprintf(f,
        "<?xml version=\"1.0\"?>\n"
        "<container version=\"1.0\" xmlns=\"urn:oasis:names:tc:opendocument:xmlns:container\">\n"
        "  <rootfiles>\n"
        "    <rootfile full-path=\"OEBPS/content.opf\" media-type=\"application/oebps-package+xml\"/>\n"
        "  </rootfiles>\n"
        "</container>\n");
    fclose(f);
}

void generer_chapitre_xhtml(Chapitre *chap, int index) {
    char filename[256];
    sprintf(filename, OEBPS_DIR "/chapitre%d.xhtml", index + 1);

    FILE *f = fopen(filename, "w");
    if (!f) { perror("fopen chapitre"); exit(1); }

    fprintf(f,
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
        "<!DOCTYPE html>\n"
        "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
        "<head><title>%s</title></head>\n"
        "<body>\n"
        "<h1>%s</h1>\n"
        "%s\n",
        chap->titre, chap->titre, chap->contenu);

    // Génération des notes de bas de page
    if (chap->nb_notes > 0) {
        fprintf(f, "<hr/><ol>\n");
        for (int i = 0; i < chap->nb_notes; ++i) {
            fprintf(f, "<li id=\"%s\">%s</li>\n", chap->notes[i].id_note, chap->notes[i].texte);
        }
        fprintf(f, "</ol>\n");
    }

    fprintf(f, "</body></html>\n");
    fclose(f);
}

void generer_content_opf(Livre *livre) {
    FILE *f = fopen(OEBPS_DIR "/content.opf", "w");
    fprintf(f,
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<package xmlns=\"http://www.idpf.org/2007/opf\" version=\"2.0\" unique-identifier=\"BookId\">\n"
        "<metadata xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n"
        "<dc:title>%s</dc:title>\n"
        "<dc:creator>%s</dc:creator>\n"
        "<dc:language>fr</dc:language>\n"
        "<dc:identifier id=\"BookId\">urn:uuid:12345</dc:identifier>\n"
        "</metadata>\n"
        "<manifest>\n",
        livre->titre_livre, livre->auteur);

    for (int i = 0; i < livre->nb_chapitres; ++i) {
        fprintf(f, "<item id=\"chap%d\" href=\"chapitre%d.xhtml\" media-type=\"application/xhtml+xml\"/>\n", i + 1, i + 1);
    }

    fprintf(f,
        "<item id=\"ncx\" href=\"toc.ncx\" media-type=\"application/x-dtbncx+xml\"/>\n"
        "</manifest>\n<spine toc=\"ncx\">\n");

    for (int i = 0; i < livre->nb_chapitres; ++i) {
        fprintf(f, "<itemref idref=\"chap%d\"/>\n", i + 1);
    }

    fprintf(f,
        "</spine>\n</package>\n");
    fclose(f);
}

void generer_toc_ncx(Livre *livre) {
    FILE *f = fopen(OEBPS_DIR "/toc.ncx", "w");
    fprintf(f,
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<ncx xmlns=\"http://www.daisy.org/z3986/2005/ncx/\" version=\"2005-1\">\n"
        "<head>\n"
        "<meta name=\"dtb:uid\" content=\"urn:uuid:12345\"/>\n"
        "</head>\n"
        "<docTitle><text>%s</text></docTitle>\n"
        "<navMap>\n",
        livre->titre_livre);

    for (int i = 0; i < livre->nb_chapitres; ++i) {
        fprintf(f,
            "<navPoint id=\"nav%d\" playOrder=\"%d\">\n"
            "<navLabel><text>%s</text></navLabel>\n"
            "<content src=\"chapitre%d.xhtml\"/>\n"
            "</navPoint>\n",
            i + 1, i + 1, livre->chapitres[i].titre, i + 1);
    }

    fprintf(f, "</navMap>\n</ncx>\n");
    fclose(f);
}


void zipper_epub(const char *nom_fichier) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "cd " OUTPUT_DIR " && "
        "zip -X0 %s mimetype > /dev/null && "
        "zip -Xr9D %s META-INF OEBPS > /dev/null",
        nom_fichier, nom_fichier);

    int res = system(cmd);
    if (res != 0) {
        fprintf(stderr, "Erreur lors de la compression EPUB (zip).\n");
        exit(1);
    } else {
        printf("EPUB généré : %s/%s\n", OUTPUT_DIR, nom_fichier);
    }
}

void generer_epub(Livre *livre, const char *nom_fichier_epub) {
    creer_dossiers();
    generer_mimetype();
    generer_container_xml();

    for (int i = 0; i < livre->nb_chapitres; ++i) {
        generer_chapitre_xhtml(&livre->chapitres[i], i);
    }

    generer_content_opf(livre);
    generer_toc_ncx(livre);

    zipper_epub(nom_fichier_epub);
}
