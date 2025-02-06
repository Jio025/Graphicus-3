/********
* Fichier: monInterface.cpp
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: Voir fichier d'entête pour informations.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#pragma once

#include <random>
#include <sstream>
#include "monInterface.h"
#include "Vecteur.h"
#include "canevas.h"
#include "graphicusGUI.h"

using namespace std;

MonInterface::MonInterface(const char* theName) : GraphicusGUI(theName)
{
//	reinitialiserCanevas();
//	effacerInformations();
}

//void MonInterface::reinitialiserCanevas()
//{
	/*
	ostringstream os;
	random_device r;
	default_random_engine generator(r());
	uniform_int_distribution<int> coor(0, 300), dim(20, 100);


	// On s'amuse à générer aléatoirement un canevas en format texte à chaque
	// fois que la commande de réinitialisation de canevas est choisie par l'usager.
	os << "L x" << endl;
	os << "R " << coor(generator) << " " << coor(generator) << " " << dim(generator) << " " << dim(generator) << endl;
	os << "K " << coor(generator) << " " << coor(generator) << " " << dim(generator) << endl;
	os << "L a" << endl;
	os << "K " << coor(generator) << " " << coor(generator) << " " << dim(generator) << endl;
	os << "C " << coor(generator) << " " << coor(generator) << " " << dim(generator) << endl;
	os << "L x" << endl;
	os << "R " << coor(generator) << " " << coor(generator) << " " << dim(generator) << " " << dim(generator) << endl;
	os << "C " << coor(generator) << " " << coor(generator) << " " << dim(generator) << endl;
	os << "L x" << endl;
	os << "R " << coor(generator) << " " << coor(generator) << " " << dim(generator) << " " << dim(generator) << endl;
	os << "K " << coor(generator) << " " << coor(generator) << " " << dim(generator) << endl;
	os << "C " << coor(generator) << " " << coor(generator) << " " << dim(generator) << endl;

	// Ensuite, on dessine ce qui a été généré dans Graphicus
	dessiner(os.str().c_str());
	*/
//}


Canevas canevas;

//Actions de fichiers




bool MonInterface::ouvrirFichier(const char* nom) {
	return true;
//	istream a(nom);
};

bool MonInterface::sauvegarderFichier(const char* nom) {
	return true;
//	canevas.vecteurCanevas << nom;
};

//Actions de canevas, de couches et de formes

void MonInterface::reinitialiserCanevas() {
	canevas.vecteurCanevas.viderVecteur();
};

void MonInterface::coucheAjouter() {
	canevas.ajouterCouche();
};

void MonInterface::coucheRetirer() {
	canevas.retirerElement(canevas.vecteurCanevas.indexCourant);
};

void MonInterface::coucheTranslater(int deltaX, int deltaY) {
	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->translaterCouche(deltaX, deltaY);
};

void MonInterface::ajouterCercle(int x, int y, int rayon) {
	Cercle * cercle = new Cercle(x,y,rayon);
//	Cercle cercle(x, y, rayon);
//	Cercle* ptr = &cercle;
	cout << &canevas << endl;
	cout << canevas.infoCanevas.coucheActive << endl;
	cout << canevas.vecteurCanevas[0] << endl;
//	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->ajoutForme(ptr);
};

void MonInterface::ajouterRectangle(int x, int y, int long_x, int long_y) {
	Rectangle rec(x, y, long_x, long_y);
	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->ajoutForme(&rec);
};

void MonInterface::ajouterCarre(int x, int y, int cote) {
	Carre car(x, y, cote);
	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->ajoutForme(&car);
};

void MonInterface::retirerForme() {
	canevas.retirerForme(canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->infoCouche.formeActive);
};

void MonInterface::modePileChange(bool mode){
	
};


//Actions de navigation


void MonInterface::couchePremiere() {
	canevas.infoCanevas.coucheActive = 1;
};

void MonInterface::couchePrecedente() {
	canevas.infoCanevas.coucheActive = canevas.infoCanevas.coucheActive - 1;
};

void MonInterface::coucheSuivante() {
	canevas.infoCanevas.coucheActive = canevas.infoCanevas.coucheActive + 1;
};

void MonInterface::coucheDerniere() {
	canevas.infoCanevas.coucheActive = canevas.infoCanevas.nbCouches;
};

void MonInterface::formePremiere() {
	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->vecteurCouche.contenuVecteur[1];
};

void MonInterface::formePrecedente() {
	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->infoCouche.formeActive += 1;
};

void MonInterface::formeSuivante() {
	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->infoCouche.formeActive += 1;
};

void MonInterface::formeDerniere() {
	canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->infoCouche.formeActive = canevas.vecteurCanevas.contenuVecteur[canevas.infoCanevas.coucheActive]->infoCouche.nbFormesCouche;
};


