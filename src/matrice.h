#pragma once
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
//#include "filtre.h"

#define EPSILON 0.0001

typedef struct matrice_s{
    int n;
    int m;
    double** mat;
} matrice;


//Créer un pointeur vers une matrice nulle de taille n*m
matrice* matrice_nulle(int n, int m);

//Martice (x y 1)^T
matrice* coo_vect(double x, double y);

// Crée une matrice identité de taille n*n
matrice* matrice_identite(int n);

//Copie la matrice old dans new
void copie_matrice(matrice* old, matrice* new);

// Calcule la norme d'un vecteur (colonne de la matrice)
double norme_vecteur(matrice* a, int colonne);

//Affiche la matrice a
void print_matrice (matrice* a);

//Teste l'égalité entre les matrice a et b, renvoie true si les matrices sont egales, false sinon
bool matrice_egale (matrice* a, matrice* b);

//Libère la mémoire allouer pour la matrice a
void free_matrice(matrice* a);

//Renvoie une nouvelle matrice, somme des matrices a et b
matrice* somme(matrice* a, matrice* b);

//effectue le produit scalaire entre deux vecteur colonnes
double produit_scalaire(matrice* l, matrice* X2);

//Renvoie une nouvelle matrice, produit des matrices a et b
matrice* produit(matrice* a, matrice* b);

void multiplication_scalaire(matrice* a, double lambda);

//Renvoie une nouvelle matrice, transposée de la matrice a
matrice *transposee(matrice* a);

// Concatènae deux matrices a b horizontalement
matrice *concatenation2(matrice* a, matrice* b) ;

// Concatène trois matrices a b c horizontalement
matrice *concatenation3(matrice* a, matrice* b, matrice* c) ;

// Concatène trois matrices a b c verticalement
matrice* concatenationv2(matrice* a, matrice* b);

// Concatène trois matrices a b c verticalement
matrice* concatenationv3(matrice* a, matrice* b, matrice* c);

void echange_ligne(matrice* a, int i, int j);

void multiplication_ligne(matrice* a, int i, double lambda);

void ajout_ligne(matrice* a, int i, int j, double lambda);

void set_colonne(matrice *target, int col_idx, matrice* column_vector);

// Fonction pour extraire la i-ème colonne de la matrice A
matrice *matrice_colonne(matrice* A, int i);

int choix_pivot_partiel(matrice *a, int i);

matrice* inverser_matrice(matrice* a);

matrice* produit_vectoriel(matrice* a, matrice* b);
