/********
* Fichier: monInterface.cpp
* Auteurs: Guillaume Dumas
* Date: 05 fevrier 2025
* Description: Voir fichier d'entête pour informations.
*
* Copyright 2024 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#include <random>
#include <sstream>
#include "monInterface.h"

using namespace std;

MonInterface::MonInterface(const char* theName) : GraphicusGUI(theName)
{
	reinitialiserCanevas();
	effacerInformations();
}

void MonInterface::reinitialiserCanevas()
{
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
}

// Formes
Forme::Forme(int x1, int y1)
{
	ancrage.x = x1;
	ancrage.y = y1;
}

Forme::~Forme()
{
}

void Forme::translater(int deltaX, int deltaY)
{
	ancrage.x += deltaX;
	ancrage.y += deltaY;
}

Coordonnee Forme::getAncrage()
{
	return ancrage;
}

void Forme::setAncrage(Coordonnee c)
{
	ancrage = c;
}

Rectangle::Rectangle(int x, int y, double width, double heigth) : Forme(x, y), width(width), heigth(heigth) {}
Rectangle::~Rectangle() {}
double Rectangle::aire() { return(width * heigth); }
void Rectangle::afficher(ostream& s) {
    s << "Rectangle (x = " << ancrage.x << ", y = " << ancrage.y << ", l = " << width << ", h = " << heigth << ", aire = " << aire() << ")" << endl;
}

Carre::Carre(int x, int y, double width) : Forme(x, y), width(width) {};
Carre::~Carre() {};
double Carre::aire() {
    return(width * width);
}
void Carre::afficher(ostream& s) { s << "Carre (x = " << ancrage.x << ", y = " << ancrage.y << ", c = " << width << ", aire = " << aire() << ")" << endl; }

const double PI = 3.141592653589793;
Cercle::Cercle(int x, int y, double rayon) :Forme(x, y), rayon(rayon) {}
Cercle::~Cercle() {}
double Cercle::aire() {
    return(PI * (rayon * rayon));
}
void Cercle::afficher(ostream& s) { s << "Cercle (x = " << ancrage.x << ", y = " << ancrage.y << ", r = " << rayon << ", aire = " << aire() << ")" << endl; }

// Couches
Couche::Couche() : etat(INITIALISEE) {}
Couche::~Couche() { reinitialiserCouche(); }

vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->vecteurCouche.contenuVecteur[vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.formeActive]->detruireForme();

bool Couche::ajoutForme(Forme* forme_ptr) {
	if (nb_item >= MAX_FORMES || etat != ACTIVE || !forme_ptr) {
		return false;
	}
	formes += forme_ptr;
	nb_item++;
	return true;
}
Forme* Couche::retraitForme(int index_forme) {
	if (nb_item == 0 || index_forme >= MAX_FORMES || index_forme < 0 || etat != ACTIVE) {
		return nullptr;
	}
	Forme* forme_ptr = formes[index_forme];
	while (index_forme < MAX_FORMES - 1) {
		formes[index_forme] = formes[index_forme + 1];
		index_forme++;
	}
	formes[nb_item--] = nullptr;
	return forme_ptr;
}
Forme* Couche::obtenirForme(int index_forme) const {
	if (nb_item == 0 || index_forme >= MAX_FORMES || index_forme < 0) {
		return nullptr;
	}
	Forme* forme_ptr = formes[index_forme];
	return forme_ptr;
}
double Couche::aireTotale() const {
	double aire_totale = 0.0;
	for (int i = 0; i < nb_item; i++) {
		aire_totale += formes[i]->aire();
	}
	return aire_totale;

}
bool Couche::translaterCouche(int delta_x, int delta_y) {
	if (nb_item == 0 || etat != ACTIVE) {
		return false;
	}
	for (int i = 0; i < nb_item; i++) {
		formes[i]->translater(delta_x, delta_y);
	}
	return true;
}
bool Couche::reinitialiserCouche() {
	if (nb_item == 0) {
		return false;
	}
	for (int i = 0; i < nb_item; i++) {
		delete formes[i];
		formes[i] = nullptr;
	}
	nb_item = 0;
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
void Couche::afficherCouche(ostream& s) {
	if (etat == INITIALISEE) {
		s << "Etat: initialisee" << endl;
		s << "Couche: vide" << endl;
	}
	if (etat == ACTIVE) {
		s << "Etat: active" << endl;
	}

	if (etat == INACTIVE) {
		s << "Etat: inactive" << endl;
	}
	if (etat == ACTIVE || etat == INACTIVE) {
		for (int i = 0; i < nb_item; i++) {
			formes[i]->afficher(s);
		}
	}
}

Canevas::Canevas() {
}

Canevas::~Canevas() {
    reinitialiser();
}

bool Canevas::ajouterCouche() {
    Couche* nouvelle_couche = new Couche();

    bool aucune_couche_active = true;
    for (int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme[i];
        if (couche) {
            // We can try to change the state to ACTIVE - if it fails, 
            // it means the layer is already active
            if (couche->changerEtat(ACTIVE)) {
                // If we successfully changed it to active, change it back
                couche->changerEtat(INACTIVE);
            }
            else {
                // If we couldn't change it to active, it means it was already active
                aucune_couche_active = false;
                break;
            }
        }
    }

    if (aucune_couche_active) {
        nouvelle_couche->changerEtat(ACTIVE);
    }
    else {
        nouvelle_couche->changerEtat(INITIALISEE);
    }

    vecteur_forme += nouvelle_couche;
    return true;
}


bool Canevas::retirerCouche(int index) {
    if (index < 0 || index >= vecteur_forme.tailleVecteur())
        return false;

    Couche* couche = vecteur_forme[index];
    if (!couche) return false;

    Couche* couche_retiree = retirerElement(index);
    if (couche_retiree) {
        couche_retiree->reinitialiserCouche();  // Do this before deleting
        delete couche_retiree;
        return true;
    }
    return false;
}

bool Canevas::reinitialiser() {
    while (!vecteur_forme.estVide()) {
        retirerCouche(vecteur_forme.tailleVecteur() - 1);
    }
    return true;
}

bool Canevas::reinitialiserCouche(int index) {
    if (index < 0 || index >= vecteur_forme.tailleVecteur()) {
        return false;
    }

    Couche* couche = vecteur_forme[index];
    if (!couche) { return false; }

    couche->reinitialiserCouche();
    return true;
}

bool Canevas::activerCouche(int index) {
    if (index < 0 || index >= vecteur_forme.tailleVecteur())
        return false;

    Couche* couche = vecteur_forme[index];
    if (!couche) return false;

    for (int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* c = vecteur_forme[i];
        if (c && i != index) {
            c->changerEtat(INACTIVE);
        }
    }

    return couche->changerEtat(ACTIVE);
}

bool Canevas::desactiverCouche(int index) {
    if (index < 0 || index >= vecteur_forme.tailleVecteur())
        return false;

    Couche* couche = vecteur_forme[index];
    if (!couche) return false;

    return couche->changerEtat(INACTIVE);
}

bool Canevas::ajouterForme(Forme* p_forme) {
    if (!p_forme) return false;

    for (int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme[i];
        if (couche) {
            if (couche->ajoutForme(p_forme)) {
                return true;
            }
        }
    }
    delete p_forme;
    return false;
}

bool Canevas::retirerForme(int index) {
    for (int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme[i];
        if (couche) {
            Forme* forme = couche->retraitForme(index);
            if (forme) {
                delete forme;
                return true;
            }
        }
    }
    return false;
}

double Canevas::aire() {
    double aire_totale = 0.0;
    for (int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme[i];
        if (couche) {
            aire_totale += couche->aireTotale();
        }
    }
    return aire_totale;
}

bool Canevas::translater(int deltaX, int deltaY) {
    bool translate = false;
    for (int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme[i];
        if (couche) {
            if (couche->translaterCouche(deltaX, deltaY)) {
                translate = true;
            }
        }
    }
    return translate;
}

void Canevas::afficher(ostream& s) {
    if (vecteur_forme.estVide()) {
        s << "--- Aucune couche ---" << endl;
    }
    else {
        for (int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
            s << "--- Couche " << i << " ---" << endl;
            Couche* couche = vecteur_forme[i];
            if (couche) {
                couche->afficherCouche(s);
            }
            else {
                s << "Couche inexistante" << endl;
            }
        }
    }
}

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
void GraphicusGUI::modePileChange(bool mode) {
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
    infoCanevas.coucheActive = infoCanevas.nbCouches;
};
void GraphicusGUI::formePremiere() {
    vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->vecteurCouche.contenuVecteur[1];
};
void GraphicusGUI::formePrecedente() {
    vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.formeActive = infoCouche.formeActive += 1;
};
void GraphicusGUI::formeSuivante() {
    vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.formeActive = infoCouche.formeActive += 1;
};
void GraphicusGUI::formeDerniere() {
    vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.formeActive = vecteurCanevas.contenuVecteur[infoCanevas.coucheActive]->infoCouche.nbFormesCouche;
};
