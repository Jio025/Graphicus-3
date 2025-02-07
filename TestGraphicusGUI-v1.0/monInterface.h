/********
* Fichier: monInterface.h
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: La classe MonInterface teste l'interface usager GraphicusGUI.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#pragma once
#include "graphicusGUI.h"
#include "Canevas.h"
#include <sstream>
#include <fstream>

    class MonInterface : public GraphicusGUI {
    private:
        Canevas canevas;
        Informations info;
    public:
        MonInterface(const char* theName = "GraphicusGUI");

        // Actions de fichier
        virtual bool ouvrirFichier(const char* nom) override;
        virtual bool sauvegarderFichier(const char* nom) override;

        // Actions de canevas, couches et formes
        virtual void reinitialiserCanevas() override;
        virtual void coucheAjouter() override;
        virtual void coucheRetirer() override;
        virtual void coucheTranslater(int deltaX, int deltaY) override;
        virtual void ajouterCercle(int x, int y, int rayon) override;
        virtual void ajouterRectangle(int x, int y, int long_x, int long_y) override;
        virtual void ajouterCarre(int x, int y, int cote) override;
        virtual void retirerForme() override;
        virtual void modePileChange(bool mode) override;

        // Actions de navigation
        virtual void couchePremiere() override;
        virtual void couchePrecedente() override;
        virtual void coucheSuivante() override;
        virtual void coucheDerniere() override;
        virtual void formePremiere() override;
        virtual void formePrecedente() override;
        virtual void formeSuivante() override;
        virtual void formeDerniere() override;

        //Action d'update
        void updateInformations();
};