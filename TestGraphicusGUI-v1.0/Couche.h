#pragma once


#include "forme.h"
#include "Vecteur.h"

enum Etat { INITIALISEE, ACTIVE, INACTIVE };

class Couche
{
public:
    Couche();
    virtual ~Couche();
    bool ajoutForme(Forme* forme_ptr);
    Forme* retraitForme(int index_forme);
    Forme* obtenirForme(int index_forme) const;
    double aireTotale()const;
    bool translaterCouche(int delta_x, int delta_y);
    bool reinitialiserCouche();
    bool changerEtat(Etat etat_nouveau);
    void afficherCouche(std::ostream& s) const;
    Etat getEtat() const;
    int getNbFormes() const;
    int getActiveFormeIndex() const;
    bool setActiveFormeIndex(int index);

private:
    //Tableau de poiteurs de formes
    Vecteur<Forme*> vecteur_forme;
    int nb_item = 0;
    Etat etat;
    int activeFormeIndex;

};