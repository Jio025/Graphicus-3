/********
* Fichier: carre.cpp
 * Auteurs: Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date: 10 Jan 2025 (creation)
 * Description: Methodes de la classe carre
********/
#include "carre.h"
Carre::Carre(int x, int y, double width) : Forme(x,y), width(width){};
Carre::~Carre(){};
double Carre::aire(){
return(width * width);}
void Carre::afficher(ostream & s){s << "K " << ancrage.x << " " << ancrage.y << " " << width << endl; }



