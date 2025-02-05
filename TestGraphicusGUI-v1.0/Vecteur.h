#pragma once
#include <ostream>
#include <istream>
template <typename T>
class Vecteur {
public:

    Vecteur() : taille(0), capacite(1), indexCourant(0) {
        contenuVecteur = new T[capacite];
    }

    ~Vecteur() {
        viderVecteur();
        delete[] contenuVecteur;
    }

    T& operator[](int index) {
        if (index < 0 || index >= taille) {
            trow std::out_of_range("Index hors limite !")
        }
        return contenuVecteur[index];
    }

    T& operator +=(const T& donnees) {
        if (taille >= capacite) {
            doublerCapaciteVecteur();
        }
        contenuVecteur[taille++] = donnees;
        return *this; // For chaining
    }

    friend std::ostream& operator <<(std::ostream& os, const Vecteur<T>& v){
        for (int i = 0; i < v.taille; i++) {
            os << v.contenuVecteur[i] << " ";
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Vecteur<T>&) {
        T valeur;
        is >> valeur;
        v += valeur;
        return is;
    }
    Vecteur<T>& operator++() {
        if (indexCourant < taille - 1) {
            ++indexCourant;
        }
        return this*;
    }
    Vecteur<T>& operator--() {
        if (indexCourant > 0) {
            --indexCourant;
        }
        return this*;
    }
    /*void viderVecteur() {
        for (int i = 0; i < taille; ++i) {
            delete contenuVecteur[i];
            contenuVecteur[i] = nullptr;
        }
        taille = 0;
    }
    bool ajouterCouche(Couche* couche) {
        if (!couche) return false;

        if (taille >= capacite) {
            doublerCapaciteVecteur();
        }
        contenuVecteur[taille++] = couche;
        return true;
    }
    Couche* retirerCouche(int index) {
        if (index < 0 || index >= taille) return nullptr;

        Couche* couche = contenuVecteur[index];

        for (int i = index; i < taille - 1; i++) {
            contenuVecteur[i] = contenuVecteur[i + 1];
        }

        contenuVecteur[taille--] = nullptr;
        return couche;
    }
    Couche* obtenirCouche(int index) {
        if (index < 0 || index >= taille) return nullptr;
        return contenuVecteur[index];
    }
    void afficherVecteur(ostream& s) {
        for (int i = 0; i < taille; i++) {
            if (contenuVecteur[i]) {
                contenuVecteur[i]->afficherCouche(s);
            }
        }
    }*/
    bool estVide() {
        return taille == 0;
    }
    int capaciteVecteur() {
        return capacite;
    }
    int tailleVecteur() {
        return taille;
    }
private:
    void doublerCapaciteVecteur() {
        int nouvelleCapacite = capacite * 2;
        T* nouveau = new T[nouvelleCapacite];

        for (int i = 0; i < taille; ++i) {
            nouveau[i] = contenuVecteur[i];
        }

        delete[] contenuVecteur;
        contenuVecteur = nouveau;
        capacite = nouvelleCapacite;
    }
    int taille;
    int capacite;
    int indexCourant;
    T* contenuVecteur; // 1 is default value
};
