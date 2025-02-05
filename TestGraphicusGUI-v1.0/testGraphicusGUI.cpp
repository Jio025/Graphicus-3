/********
* Fichier: testGraphicusGUI.cpp
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: Ce programme teste l'interface usager GraphicusGUI.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#include <QApplication>
#include "monInterface.h"

int main( int argc, char ** argv )
{
	QApplication app(argc, argv);
	MonInterface gui("TestGraphicusGUI 1.0");
	return app.exec();
}
