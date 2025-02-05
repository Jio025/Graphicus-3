/********
* Fichier: graphicusGUI.h
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: La classe GraphicusGUI offre une interface graphique sous
*   forme de librairie afin visualiser les opérations de canevas de la
*   problématique GIF241.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#ifndef GRAPHICUSGUI_H
#define GRAPHICUSGUI_H

#include <QMainwindow>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QToolButton>

#include "centralWidget.h"

using namespace std;

struct Informations
{
	// Canevas
	int nbCouches;       // Nombre total de couches
	int nbFormesCanevas; // Nombre total de formes
	int coucheActive;    // la couche active, si < 0, pas de couche active
	double aireCanevas;  // Aire totale
	// Pour la couche active du canevas, s'il y en a une
	int nbFormesCouche;  // Nombre de formes de la couche
	char etatCouche[20]; // État de la couche en format libre
	double aireCouche;   // Aire totale de la couche
	int formeActive;     // la forme active, si < 0, pas de forme active
	// Pour la forme active de la couche active, s'il y en a une
	int coordX, coordY;  // Coordonnées de la forme
	double aireForme;    // Aire de la forme
	char informationForme[50]; // Informations format libre: rayon, etc.
};

class GraphicusGUI : public QMainWindow
{
	Q_OBJECT
public:
	GraphicusGUI(const char* titre = 0);
	virtual ~GraphicusGUI();
	void dessiner(const char*);
	void effacer();
	void setInformations(Informations);
	void effacerInformations();
	bool getModePile();
	bool getSurlignage();
	void message(const char*);
	void messageErreur(const char*);
	void afficher(ostream& os);

	virtual bool ouvrirFichier(const char*);
	virtual bool sauvegarderFichier(const char*);
	virtual void coucheTranslater(int deltaX, int deltaY);
	virtual void ajouterCercle(int x, int y, int rayon);
	virtual void ajouterRectangle(int x, int y, int long_x, int long_y);
	virtual void ajouterCarre(int x, int y, int cote);
	virtual void modePileChange(bool mode);
public slots:
	// Menu Canevas
	virtual void reinitialiserCanevas();
	virtual void coucheAjouter();
	virtual void coucheRetirer();
	// Menu Formes
	virtual void retirerForme();
	// Menu navigation
	virtual void couchePremiere();
	virtual void couchePrecedente();
	virtual void coucheSuivante();
	virtual void coucheDerniere();
	virtual void formePremiere();
	virtual void formePrecedente();
	virtual void formeSuivante();
	virtual void formeDerniere();
private slots:
	void ouvrir();
	void sauvegarder();
	void sauvegarderSous();
	void quitter();
	void afficher();
	void coucheTranslater();
	void ajouterForme();
	void formeChoisie(int index);
	void surligner();
	void modePile();
	void informations();
private:
	bool surlignage, pile, infos;
	QString canevasTexte;
	QString nomFichier;
	CentralWidget* widget;
	QAction* v1Action, * v2Action;
	QComboBox* comboBox;
	QLabel* canevasLabel, * coucheLabel, * formeLabel;
	QSpinBox* xSpin, * ySpin, * v1Spin, * v2Spin, * dxSpin, * dySpin;
	QToolButton* surlignageButton, * pileButton, * infoButton;
};

#endif //GRAPHICUSGUI_H
