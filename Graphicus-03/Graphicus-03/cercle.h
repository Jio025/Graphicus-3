/********
* Fichier: carre.h
 * Auteurs: Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date: 10 Jan 2025 (creation)
 * Description: Creation de la classe cercle
********/
#ifndef CERCLE_H
#define CERCLE_H
#include "forme.h"
class Cercle : public Forme{
public:
//Constructeur
	Cercle(int x, int y, double rayon);
//Destructeur
	virtual ~Cercle();
	double aire() override;
	void afficher(ostream & s) override;
	
private:
double rayon;
};
#endif
