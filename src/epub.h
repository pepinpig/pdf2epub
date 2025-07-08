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
