/********
 * Fichier: couche.h
 * Auteurs: C.-A. Brunet
 * Date: 13 juin 2024 (creation)
 * Modifie par : Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date : 11 Jan 2025
 * Description: Declaration de la classe pour une couche dans un
 *    canevas. La classe gere un tableau de formes en accord avec 
 *    les specifications de Graphicus. Ce fichier fait partie de 
 *    la distribution de Graphicus.
********/

#ifndef COUCHE_H
#define COUCHE_H

#include "forme.h"
#include "graphicusGUI.h"
#include "Vecteur.h"

const int MAX_FORMES = 5;
enum Etat {INITIALISEE, ACTIVE, INACTIVE};

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

	Vecteur <Forme*> vecteurCouche;
	Informations infoCouche;
	Etat etat;

private:
	//Tableau de poiteurs de formes
	
	int nb_item = 0;
	

};

#endif
