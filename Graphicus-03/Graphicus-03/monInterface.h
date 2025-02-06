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

class MonInterface : public GraphicusGUI
{
public:
	MonInterface(const char *theName = nullptr);
	
	virtual void reinitialiserCanevas();
	virtual void coucheAjouter();
	virtual bool ouvrirFichier(const char* nom);
	virtual bool sauvegarderFichier(const char* nom);
	virtual void coucheRetirer();
	virtual void coucheTranslater(int deltaX, int deltaY);
	virtual void ajouterCercle(int x, int y, int rayon);
	virtual void ajouterRectangle(int x, int y, int long_x, int long_y);
	virtual void ajouterCarre(int x, int y, int cote);
	virtual void retirerForme();
	virtual void modePileChange(bool mode);
	virtual void couchePremiere();
	virtual void couchePrecedente();
	virtual void coucheSuivante();
	virtual void coucheDerniere();
	virtual void formePremiere();
	virtual void formePrecedente();
	virtual void formeSuivante();
	virtual void formeDerniere();
};

#endif // MONINTERFACE_H