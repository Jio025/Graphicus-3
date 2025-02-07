#include "FormeGeometriques.h"

const double PI = 3.141592653589793;

Rectangle::Rectangle(int x, int y, double width, double heigth) : Forme(x, y), width(width), heigth(heigth) {}
Rectangle::~Rectangle() {}
double Rectangle::aire() { return(width * heigth); }
void Rectangle::afficher(ostream& s) {
	s << "Rectangle (x = " << ancrage.x << ", y = " << ancrage.y << ", l = " << width << ", h = " << heigth << ", aire = " << aire() << ")" << endl;
}



Cercle::Cercle(int x, int y, double rayon) :Forme(x, y), rayon(rayon) {}
Cercle::~Cercle() {}
double Cercle::aire() {
	return(PI * (rayon * rayon));
}
void Cercle::afficher(ostream& s) { s << "Cercle (x = " << ancrage.x << ", y = " << ancrage.y << ", r = " << rayon << ", aire = " << aire() << ")" << endl; }



Carre::Carre(int x, int y, double width) : Forme(x, y), width(width) {};
Carre::~Carre() {};
double Carre::aire() {
	return(width * width);
}
void Carre::afficher(ostream& s) { s << "Carre (x = " << ancrage.x << ", y = " << ancrage.y << ", c = " << width << ", aire = " << aire() << ")" << endl; }

