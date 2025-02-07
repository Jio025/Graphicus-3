#include <iostream>
#include "Couche.h"

Couche::Couche() : etat(INITIALISEE), activeFormeIndex(-1) {}
Couche::~Couche() { reinitialiserCouche(); }

Etat Couche::getEtat() const {
	return etat;
}

int Couche::getNbFormes() const {
	return nb_item;
}

int Couche::getActiveFormeIndex() const {
	return activeFormeIndex;
}

bool Couche::setActiveFormeIndex(int index) {
	// Validate the index: it must be between 0 and nb_item-1.
	if (index < 0 || index >= nb_item) {
		return false;
	}
	activeFormeIndex = index;
	return true;
}

bool Couche::ajoutForme(Forme* forme_ptr) {
	if (etat != ACTIVE || !forme_ptr) {
		return false;
	}
	vecteur_forme += forme_ptr;
	nb_item++;
	return true;
}

Forme* Couche::retraitForme(int index_forme) {
	if (nb_item == 0 || index_forme < 0 || etat != ACTIVE) {
		return nullptr;
	}
	Forme* forme_ptr = vecteur_forme[index_forme];
	for (int i = index_forme; i < nb_item - 1; i++) {
		vecteur_forme[i] = vecteur_forme[i + 1];
	}
	vecteur_forme[nb_item--] = nullptr;
	return forme_ptr;
}

Forme* Couche::obtenirForme(int index_forme) const {
	if (nb_item == 0 || index_forme < 0) {
		return nullptr;
	}
	return vecteur_forme[index_forme];
}

double Couche::aireTotale() const {
	double aire_totale = 0.0;
	for (int i = 0; i < nb_item; i++) {
		if (vecteur_forme[i]) {
			aire_totale += vecteur_forme[i]->aire();
		}
	}
	return aire_totale;
}

bool Couche::translaterCouche(int delta_x, int delta_y) {
	if (nb_item == 0 || etat != ACTIVE) {
		return false;
	}
	for (int i = 0; i < nb_item; i++) {
		if (vecteur_forme[i]) {
			vecteur_forme[i]->translater(delta_x, delta_y);
		}
	}
	return true;
}

bool Couche::reinitialiserCouche() {
	if (nb_item == 0) {
		return false;
	}
	for (int i = 0; i < nb_item; i++) {
		delete vecteur_forme[i];
		vecteur_forme[i] = nullptr;
	}
	nb_item = 0;
	vecteur_forme.viderVecteur();
	activeFormeIndex = -1;
	etat = INITIALISEE;
	return true;
}

bool Couche::changerEtat(Etat etat_nouveau) {
	if (etat_nouveau != INITIALISEE && etat_nouveau != ACTIVE && etat_nouveau != INACTIVE) {
		return false;
	}
	etat = etat_nouveau;
	return true;
}

void Couche::afficherCouche(std::ostream& s) const {
	if (etat == INITIALISEE) {
		s << 'i' << std::endl;
	}
	else if (etat == ACTIVE) {
		s << 'a' << std::endl;
	}
	else if (etat == INACTIVE) {
		s << 'x' << std::endl;
	}

	// Only display the forms if the layer is active or inactive.
	if (etat == ACTIVE || etat == INACTIVE) {
		for (int i = 0; i < nb_item; i++) {
			if (vecteur_forme[i]) {
				vecteur_forme[i]->afficher(s);
			}
		}
	}
}

