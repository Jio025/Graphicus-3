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

    void viderVecteur() {
        for (int i = 0; i < taille; ++i) {
            delete contenuVecteur[i];
            contenuVecteur[i] = T();
        }
        taille = 0;
    }

    T& operator[](int index) {
        if (index < 0 || index >= taille) {
            throw std::out_of_range("Index hors limite !");
        }
        return contenuVecteur[index];
    }
    const T& operator[](int index) const {
        if (index < 0 || index >= taille) {
            throw std::out_of_range("Index hors limite !");
        }
        return contenuVecteur[index];
    }

    Vecteur<T>& operator +=(const T & donnees) {
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
    friend std::istream& operator>>(std::istream& is, Vecteur<T>& v) {
        T valeur;
        is >> valeur;
        v += valeur;
        return is;
    }
    Vecteur<T>& operator++() {
        if (indexCourant < taille - 1) {
            ++indexCourant;
        }
        return *this;
    }
    Vecteur<T>& operator--() {
        if (indexCourant > 0) {
            --indexCourant;
        }
        return *this;
    }


    bool estVide(){
        return taille == 0;
    }
    int capaciteVecteur(){
        return capacite;
    }
    int tailleVecteur(){
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
