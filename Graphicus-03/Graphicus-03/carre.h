/********
* Fichier: carre.h
 * Auteurs: Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date: 10 Jan 2025 (creation)
 * Description: Creation de la classe carre
********/
#ifndef CARRE_H
#define CARRE_H
#include "forme.h"
class Carre : public Forme{
public:
//Constructeur
	Carre(int x, int y, double width);
//Destructeur
	virtual ~Carre() override;
	double aire() override;
	void afficher(ostream & s) override;
	
	
private:
double width;
};
#endif
