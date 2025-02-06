/********
* Fichier: carre.h
 * Auteurs: Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date: 10 Jan 2025 (creation)
 * Description: Methodes de la classe cercle
********/
#pragma once

#include "cercle.h"
const double PI = 3.141592653589793;
Cercle::Cercle(int x, int y, double rayon):Forme(x,y),rayon(rayon){}
Cercle::~Cercle(){}
double Cercle::aire(){
	return(PI * (rayon * rayon));
}
void Cercle::afficher(ostream & s){s << "C " << ancrage.x << " " << ancrage.y << " " << rayon << endl; }
