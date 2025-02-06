/********
 * Fichier: canevas.h
 * Auteurs: C.-A. Brunet
 * Date: 13 juin 2024 (creation)
 * Modifie par : Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date : 13 Jan 2025
 * Description: Declaration de la classe Canevas. La classe Canevas gere un 
 *    vecteur de pointeur de couches en accord avec les specifications de Graphicus.
 *    Ce fichier fait partie de la distribution de Graphicus.
********/

#ifndef CANEVAS_H
#define CANEVAS_H

#include <iostream>

//#include "graphicusGUI.h"
#include "forme.h"
#include "Vecteur.h"
#include "couche.h"

class Couche;


using namespace std;

class Canevas
{
public:
   Canevas();
   ~Canevas();
   
   bool ajouterCouche();
//   bool retirerCouche(int index);

   bool reinitialiser();
   bool reinitialiserCouche(int index);
   
   bool activerCouche(int index);
   bool desactiverCouche(int index);
   
   bool ajouterForme(Forme *p_forme);
   bool retirerForme(int index);
   
   double aire();
   bool translater(int deltaX, int deltaY);
   void afficher(ostream & s);

   Couche* retirerElement(int index);

   Informations infoCanevas;
   Vecteur<Couche*> vecteurCanevas;
   
private:   
   
   
};

#endif
