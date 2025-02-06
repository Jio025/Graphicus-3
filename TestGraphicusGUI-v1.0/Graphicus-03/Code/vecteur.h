/********
 * Fichier: vecteur.h
 * Auteurs: Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date: 10 janvier 2024 (creation)
 * Modification : 13 janvier 2024
 * Description: Creation de la classe Vecteur
********/


#ifndef VECTEUR_H
#define VECTEUR_H

#include "couche.h"

using namespace std;

class Vecteur
{
    public:
        Vecteur();
        virtual ~Vecteur();
        int capaciteVecteur();
        int tailleVecteur();
        void doublerCapaciteVecteur();
        void viderVecteur();
        bool ajouterCouche(Couche * couche);
        Couche * retirerCouche(int index);
        Couche * obtenirCouche(int index);
        void afficherVecteur(ostream & s);
        bool estVide();

    private:
        int taille;
        int capacite;
        Couche** contenuVecteur; // 1 est la valeur par defaut
};
#endif
