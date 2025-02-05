#pragma once
template <typename T>
class Vecteur {
public:
    Vecteur();
    virtual ~Vecteur();
    int capaciteVecteur();
    int tailleVecteur();
    void viderVecteur();
    bool ajouterCouche(T* couche);
    T* retirerCouche(int index);
    T* obtenirCouche(int index);
    void afficherVecteur(ostream& s);
    bool estVide();

private:
    void doublerCapaciteVecteur();
    int taille;
    int capacite;
    T* contenuVecteur; // 1 is default value
};