#pragma once



#include "Forme.h"



class Rectangle : public Forme {
public:
	//Constructeur: prend x y pour les points d'ancrages et width et height pour la forme
	Rectangle(int x = 0, int y = 0, double width = 1.0, double heigth = 1.0);
	//Destructeur virtuel de rectangle
	virtual ~Rectangle() override;
	double aire() override;
	void afficher(ostream& s) override;
	int getX() const { return ancrage.x; }
	int getY() const { return ancrage.y; }
	double getWidth() const { return width; }
	double getHeigth() const { return heigth; }
private:
	double width;
	double heigth;
};



class Cercle : public Forme {
public:
	//Constructeur
	Cercle(int x, int y, double rayon);
	//Destructeur
	virtual ~Cercle();
	double aire() override;
	void afficher(ostream& s) override;
	int getX() const { return ancrage.x; }
	int getY() const { return ancrage.y; }
	double getRayon() const { return rayon; }

private:
	double rayon;
};



class Carre : public Forme {
public:
	//Constructeur
	Carre(int x, int y, double width);
	//Destructeur
	virtual ~Carre() override;
	double aire() override;
	void afficher(ostream& s) override;
	int getX() const { return ancrage.x; }
	int getY() const { return ancrage.y; }
	double getWidth() const { return width; }

private:
	double width;
};