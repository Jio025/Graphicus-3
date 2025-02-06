/********
* Fichier: centralWidget.h
* Auteurs: C.-A. Brunet
* Date: 10 janvier 2024
* Description: La classe CentralWidget est le widget central de
*   GraphicusGUI. Elle fait l'affichage graphique des formes géométriques.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>

class CentralWidget : public QGraphicsView
{
	Q_OBJECT
public:
	CentralWidget(QWidget* parent = 0);
	virtual ~CentralWidget();
	void effacer();
	bool dessiner(const char*, bool surlignage);
private:
	QGraphicsScene* scene;
};

#endif // CENTRALWIDGET_H
