#pragma once
#include "Forme.h"
#include "FormeGeometriques.h"
#include "Couche.h"
#include "Vecteur.h"

using namespace std;

class Canevas
{
public:
	Canevas();
	~Canevas();

	bool ajouterCouche();
	bool retirerCouche(int index);

	bool reinitialiser();
	bool reinitialiserCouche(int index);

	bool activerCouche(int index);
	bool desactiverCouche(int index);

	bool ajouterForme(Forme* p_forme);
	bool retirerForme(int index);

	double aire() const;
	bool translater(int deltaX, int deltaY);
	void afficher(ostream& s)const;

	int getNbCouches() const;
	int getActiveCoucheIndex() const;
	int getNbFormes() const;
	int getNbFormesInActiveCouche() const;
	int getActiveFormeIndex() const;
	double getAireTotale() const;
	double getAireActiveCouche() const;
	std::string toString() const;
	bool charger(const char* filename);

	bool couchePremiere();
	bool coucheDerniere();
	bool couchePrecedente();
	bool coucheSuivante();

	bool formePremiere();
	bool formeDerniere();
	bool formePrecedente();
	bool formeSuivante();

private:
	Vecteur<Couche*> vecteur_couche;

};