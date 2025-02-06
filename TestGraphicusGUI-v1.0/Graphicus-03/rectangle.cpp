/********
* Fichier: rectangle.cpp
 * Auteurs: Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date: 10 Jan 2025 (creation)
 * Descrpition: Methodes de la classe rectangle
********/
#include "rectangle.h"
Rectangle::Rectangle(int x, int y, double width, double heigth) : Forme(x,y), width(width),heigth(heigth){}
Rectangle::~Rectangle(){}
double Rectangle::aire(){return(width * heigth);}
void Rectangle::afficher(ostream & s){
	s << "R " << ancrage.x << " " << ancrage.y << " " << width << " " << heigth << endl;
}
