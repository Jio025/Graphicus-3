/********
* Fichier: rectangle.h
 * Auteurs: Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date: 10 Jan 2025 (creation)
 * Description: Creation de la classe rectangle
********/
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "forme.h"
class Rectangle : public Forme{
public:
//Constructeur: prend x y pour les points d'ancrages et width et height pour la forme
	Rectangle(int x = 0, int y = 0, double width = 1.0, double heigth = 1.0);
//Destructeur virtuel de rectangle
	virtual ~Rectangle() override;
	double aire() override;
	void afficher(ostream & s) override;
private:
	double width;
	double heigth;
};
#endif // RECTANGLE_H
