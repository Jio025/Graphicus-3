/********
 * Fichier: couche.cpp
 * Auteurs: C.-A. Brunet
 * Date: 13 juin 2024 (creation)
 * Modifie par : Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date : 11 Jan 2025
 * Description: Implementation des methodes des classes decrites dans
 *    couche.h. Ce fichier fait partie de la distribution de Graphicus.
********/

#pragma once

#include "couche.h"

Couche::Couche() : etat(INITIALISEE){}
Couche::~Couche(){reinitialiserCouche();}

bool Couche::ajoutForme(Forme * forme_ptr){
//	cout << forme_ptr << endl;
//	cout << this << endl;
	if(etat != ACTIVE || !forme_ptr){
		return false;
	}
	vecteurCouche += forme_ptr;
	return true;
}
Forme * Couche::retraitForme(int index_forme){
	if(nb_item == 0 || index_forme >= MAX_FORMES || index_forme < 0 || etat != ACTIVE){
	return nullptr;
	}
	Forme * forme_ptr = vecteurCouche[index_forme];
	while(index_forme < MAX_FORMES -1){
		vecteurCouche[index_forme] = vecteurCouche[index_forme + 1];
		index_forme++;
	}
	vecteurCouche[nb_item--] = nullptr;
	return forme_ptr;	
}
Forme * Couche::obtenirForme(int index_forme) const{
	if(nb_item == 0 || index_forme >= MAX_FORMES || index_forme < 0){
		return nullptr;
	}
	Forme * forme_ptr = vecteurCouche[index_forme];
	return forme_ptr;
}
double Couche::aireTotale() const{
	double aire_totale = 0.0;
	for(int i = 0; i< nb_item; i++){
		aire_totale += vecteurCouche[i]->aire();
	}
	return aire_totale;
	
}
bool Couche::translaterCouche(int delta_x, int delta_y){
	if(nb_item == 0 || etat != ACTIVE){
		return false;
	}
	for(int i = 0; i<nb_item; i++){
		vecteurCouche[i]->translater(delta_x, delta_y);
	}
	return true;
}
bool Couche::reinitialiserCouche(){
	if(nb_item == 0){
		return false;
	}
	for(int i = 0; i<nb_item; i++){
		delete vecteurCouche[i];
		vecteurCouche[i] = nullptr;
	}
	nb_item = 0;
	etat = INITIALISEE;
	return true;
}
bool Couche::changerEtat(Etat etat_nouveau){
	if(etat_nouveau != INITIALISEE && etat_nouveau != ACTIVE && etat_nouveau != INACTIVE){
		return false;
	}
	etat = etat_nouveau;
	return true;
}
void Couche::afficher(ostream & s){
	if(etat == INITIALISEE){
		s << "L i" << endl;
	}
	if(etat == ACTIVE){
		s << "L a" << endl;
	}
	
	if(etat == INACTIVE){
		s << "L x" << endl;
	}
	if(etat == ACTIVE || etat == INACTIVE){
	for(int i = 0; i<nb_item; i++){
		vecteurCouche[i]->afficher(s);
		}
	}
}
