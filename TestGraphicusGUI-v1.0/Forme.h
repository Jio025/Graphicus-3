#pragma once


#include <iostream>
#include "graphicusGUI.h" //Pour le struct Coodonnee

using namespace std;

class Forme
{
public:
	Forme(int x = 0, int y = 0);
	virtual ~Forme();
	void translater(int deltaX, int deltaY);
	Coordonnee getAncrage();
	void setAncrage(Coordonnee c);
	virtual double aire() = 0;
	virtual void afficher(ostream& s) = 0;
protected:
	Coordonnee ancrage;
};
