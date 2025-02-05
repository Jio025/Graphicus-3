/********
* Fichier: monInterface.cpp
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: Voir fichier d'entête pour informations.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#include <random>
#include <sstream>
#include "monInterface.h"
#include "Vecteur.h"

using namespace std;

MonInterface::MonInterface(const char* theName) : GraphicusGUI(theName)
{
	reinitialiserCanevas();
	effacerInformations();
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




//Actions de fichiers




bool GraphicusGUI::ouvrirFichier(const char* nom) {
	nom >> vecteurCanevas;
};

bool GraphicusGUI::sauvegarderFichier(const char* nom) {
	vecteurCanevas << nom;
};

//Actions de canevas, de couches et de formes

void GraphicusGUI::reinitialiserCanevas() {
	vecteurCanevas.viderVecteur();
};

void GraphicusGUI::coucheAjouter() {
	vecteurCanevas.ajouterCouche();
};

void GraphicusGUI::coucheRetirer() {
	vecteurCanevas.retirerCouche(vecteurCanevas.indexCourant);
};

void GraphicusGUI::coucheTranslater(int deltaX, int deltaY) {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->translater(deltaX, deltaY);
};

void GraphicusGUI::ajouterCercle(int x, int y, int rayon) {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->ajouterCercle(x, y, rayon);
};

void GraphicusGUI::ajouterRectangle(int x, int y, int long_x, int long_y) {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->ajouterRectangle(x, y, long_x, long_y);
};

void GraphicusGUI::ajouterCarre(int x, int y, int cote) {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->ajouterCarre(x, y, cote);
};

void GraphicusGUI::retirerForme() {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->vecteurCouche.contenuVecteur[infoCouche.formeActive]->detruireForme();
};

void GraphicusGUI::modePileChange(bool mode){
	pile = mode;
};


//Actions de navigation


void GraphicusGUI::couchePremiere() {
	infoCanevas.coucheActive = 1;
};

void GraphicusGUI::couchePrecedente() {
	infoCanevas.coucheActive = infoCanevas.coucheActive - 1;
};

void GraphicusGUI::coucheSuivante() {
	infoCanevas.coucheActive = infoCanevas.coucheActive + 1;
};

void GraphicusGUI::coucheDerniere() {
	infoCanevas.coucheActive = infoCanevas.nbCouche;
};

void GraphicusGUI::formePremiere() {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->vecteurCouche.contenuVecteur[1];
};

void GraphicusGUI::formePrecedente() {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.formeActive = infoCouche.formeActive - 1;
};

void GraphicusGUI::formeSuivante() {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.formeActive = infoCouche.formeActive + 1;
};

void GraphicusGUI::formeDerniere() {
	vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.formeActive = infoCouche.nbFormesCouche;
};


