/********
* Fichier: monInterface.h
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: La classe MonInterface teste l'interface usager GraphicusGUI.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#ifndef MONINTERFACE_H
#define MONINTERFACE_H

#include "graphicusGUI.h"
#include "Vecteur.h"

const int MAX_FORMES = 5;
enum Etat { INITIALISEE, ACTIVE, INACTIVE };

struct Coordonnee {
	int x;
	int y;
};

class Forme {
	public:
		Forme(int x = 0, int y = 0);
		virtual ~Forme();
		void translater(int deltaX, int deltaY);
		Coordonnee getAncrage();
		void setAncrage(Coordonnee c);
		virtual double aire() = 0;
		virtual void afficher(ostream & s) = 0;
	protected:
		Coordonnee ancrage;
};

class Rectangle : public Forme {
public:
	//Constructeur: prend x y pour les points d'ancrages et width et height pour la forme
	Rectangle(int x = 0, int y = 0, double width = 1.0, double heigth = 1.0);
	//Destructeur virtuel de rectangle
	virtual ~Rectangle() override;
	double aire() override;
	void afficher(ostream& s) override;
private:
	double width;
	double heigth;
};

class Carre : public Forme {
public:
	//Constructeur
	Carre(int x, int y, double width);
	//Destructeur
	virtual ~Carre() override;
	double aire() override;
	void afficher(ostream& s) override;


private:
	double width;
};

class Cercle : public Forme {
public:
	//Constructeur
	Cercle(int x, int y, double rayon);
	//Destructeur
	virtual ~Cercle();
	double aire() override;
	void afficher(ostream& s) override;

private:
	double rayon;
};


class Couche
{
public:
	Couche();
	virtual ~Couche();
	bool ajoutForme(Forme* forme_ptr);
	Forme* retraitForme(int index_forme);
	Forme* obtenirForme(int index_forme) const;
	double aireTotale()const;
	bool translaterCouche(int delta_x, int delta_y);
	bool reinitialiserCouche();
	bool changerEtat(Etat etat_nouveau);
	void afficherCouche(ostream& s);

private:
	//Tableau de poiteurs de formes
	Vecteur<Forme*> formes;
	int nb_item = 0;
	Etat etat;

};

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

	double aire();
	bool translater(int deltaX, int deltaY);
	void afficher(ostream& s);

	Couche* retirerElement(int index) {
		if (index < 0 || index >= vecteur_forme.tailleVecteur()) return nullptr;

		Couche* couche = vecteur_forme[index];

		for (int i = index; i < vecteur_forme.tailleVecteur() - 1; i++) {
			vecteur_forme[i] = vecteur_forme[i + 1];
		}

		vecteur_forme[vecteur_forme.tailleVecteur() - 1] = nullptr;
		return couche;
	}

private:
	Vecteur<Couche*> vecteur_forme;

};

class MonInterface : public GraphicusGUI
{
public:
	MonInterface(const char *theName = nullptr);
	virtual void reinitialiserCanevas();
};

#endif // MONINTERFACE_H
