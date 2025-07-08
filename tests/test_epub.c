#include "epub.h"

Livre creer_livre_de_test() {
    Livre livre;

    livre.titre_livre = strdup("Exemple de Livre");
    livre.auteur = strdup("Jean Testeur");
    livre.nb_chapitres = 2;
    livre.chapitres = malloc(sizeof(Chapitre) * livre.nb_chapitres);

    // --- Chapitre 1 : Introduction ---
    livre.chapitres[0].type = INTRODUCTION;
    livre.chapitres[0].titre = strdup("Introduction");
    livre.chapitres[0].contenu = strdup(
        "Bienvenue dans ce livre de test.<sup><a href=\"#n1\">1</a></sup><br/>"
        "Il a pour but de démontrer la génération d’un EPUB.<sup><a href=\"#n2\">2</a></sup>");
    livre.chapitres[0].nb_notes = 2;
    livre.chapitres[0].notes = malloc(sizeof(Note) * 2);
    livre.chapitres[0].notes[0].id_note = strdup("n1");
    livre.chapitres[0].notes[0].texte = strdup("Ceci est la première note.");
    livre.chapitres[0].notes[1].id_note = strdup("n2");
    livre.chapitres[0].notes[1].texte = strdup("Ceci est la deuxième note.");
    livre.chapitres[0].numero_chapitre = 0;

    // --- Chapitre 2 : Chapitre principal ---
    livre.chapitres[1].type = CHAPITRE_PRINCIPAL;
    livre.chapitres[1].titre = strdup("Chapitre 1");
    livre.chapitres[1].contenu = strdup(
        "Voici le premier chapitre.<sup><a href=\"#c1\">1</a></sup><br/>"
        "Encore un exemple de note.<sup><a href=\"#c2\">2</a></sup>");
    livre.chapitres[1].nb_notes = 2;
    livre.chapitres[1].notes = malloc(sizeof(Note) * 2);
    livre.chapitres[1].notes[0].id_note = strdup("c1");
    livre.chapitres[1].notes[0].texte = strdup("Note dans le chapitre 1.");
    livre.chapitres[1].notes[1].id_note = strdup("c2");
    livre.chapitres[1].notes[1].texte = strdup("Autre note dans le chapitre.");
    livre.chapitres[1].numero_chapitre = 1;

    return livre;
}
int main() {
    Livre livre = creer_livre_de_test();
    generer_epub(&livre, "test.epub");
    return 0;
}
