/********
 * Fichier: couche.cpp
 * Auteurs: C.-A. Brunet
 * Date: 13 juin 2024 (creation)
 * Modifie par : Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date : 11 Jan 2025
 * Description: Implementation des methodes des classes decrites dans
 *    couche.h. Ce fichier fait partie de la distribution de Graphicus.
********/

#include "couche.h"

Couche::Couche() : etat(INITIALISEE){}
Couche::~Couche(){reinitialiserCouche();}

bool Couche::ajoutForme(Forme * forme_ptr){
	if(nb_item >= MAX_FORMES || etat != ACTIVE || !forme_ptr){
		return false;
	}
	formes[nb_item] = forme_ptr;
	nb_item++;
	return true;
}
Forme * Couche::retraitForme(int index_forme){
	if(nb_item == 0 || index_forme >= MAX_FORMES || index_forme < 0 || etat != ACTIVE){
	return nullptr;
	}
	Forme * forme_ptr = formes[index_forme];
	while(index_forme < MAX_FORMES -1){
		formes[index_forme] = formes[index_forme + 1];
		index_forme++;
	}
	formes[nb_item--] = nullptr;
	return forme_ptr;	
}
Forme * Couche::obtenirForme(int index_forme) const{
	if(nb_item == 0 || index_forme >= MAX_FORMES || index_forme < 0){
		return nullptr;
	}
	Forme * forme_ptr = formes[index_forme];
	return forme_ptr;
}
double Couche::aireTotale() const{
	double aire_totale = 0.0;
	for(int i = 0; i< nb_item; i++){
		aire_totale += formes[i]->aire();
	}
	return aire_totale;
	
}
bool Couche::translaterCouche(int delta_x, int delta_y){
	if(nb_item == 0 || etat != ACTIVE){
		return false;
	}
	for(int i = 0; i<nb_item; i++){
		formes[i]->translater(delta_x, delta_y);
	}
	return true;
}
bool Couche::reinitialiserCouche(){
	if(nb_item == 0){
		return false;
	}
	for(int i = 0; i<nb_item; i++){
		delete formes[i];
		formes[i] = nullptr;
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
		formes[i]->afficher(s);
		}
	}
}
