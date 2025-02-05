#include <iostream>
#include "Vecteur.h"

using namespace std;

Vecteur::Vecteur() : taille(0), capacite(1), indexCourrant(0) {
    contenuVecteur = new T[capacite];
    for (int i = 0; i < capacite; i++) {
        contenuVecteur[i] = nullptr;
    }
}

Vecteur::~Vecteur() {
    viderVecteur();
    delete[] contenuVecteur;
}

void Vecteur::viderVecteur() {
    for (int i = 0; i < taille; ++i) {
        delete contenuVecteur[i];
        contenuVecteur[i] = nullptr;
    }
    taille = 0;
}

void Vecteur::doublerCapaciteVecteur() {
    int nouvelleCapacite = capacite * 2;
    T* nouveau = new T[nouvelleCapacite];

    for (int i = 0; i < taille; ++i) {
        nouveau[i] = contenuVecteur[i];
    }
    for (int i = taille; i < nouvelleCapacite; ++i) {
        nouveau[i] = nullptr;
    }

    delete[] contenuVecteur;
    contenuVecteur = nouveau;
    capacite = nouvelleCapacite;
}

bool Vecteur::ajouterCouche(Couche* couche) {
    if (!couche) return false;

    if (taille >= capacite) {
        doublerCapaciteVecteur();
    }
    contenuVecteur[taille++] = couche;
    return true;
}

Couche* Vecteur::retirerCouche(int index) {
    if (index < 0 || index >= taille) return nullptr;

    Couche* couche = contenuVecteur[index];

    for (int i = index; i < taille - 1; i++) {
        contenuVecteur[i] = contenuVecteur[i + 1];
    }

    contenuVecteur[taille--] = nullptr;
    return couche;
}

Couche* Vecteur::obtenirCouche(int index) {
    if (index < 0 || index >= taille) return nullptr;
    return contenuVecteur[index];
}

void Vecteur::afficherVecteur(ostream& s) {
    for (int i = 0; i < taille; i++) {
        if (contenuVecteur[i]) {
            contenuVecteur[i]->afficherCouche(s);
        }
    }
}

bool Vecteur::estVide() {
    return taille == 0;
}

int Vecteur::capaciteVecteur() {
    return capacite;
}

int Vecteur::tailleVecteur() {
    return taille;
}