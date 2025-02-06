/********
 * Fichier: canevas.cpp
 * Auteurs: C.-A. Brunet 
 * Date: 13 juin 2024 (creation)
 * Modifie par : Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date : 13 Jan 2025
 * Description: Implementation des methodes des classes decrites dans
 *    canevas.h. Ce fichier fait partie de la distribution de Graphicus.
********/

#include "canevas.h"

Canevas::Canevas() {
    infoCanevas.aireCanevas = 0;
    infoCanevas.aireCouche = 0;
    infoCanevas.aireForme = 0;
    infoCanevas.coordX = 0;
    infoCanevas.coordY = 0;
    infoCanevas.coucheActive = 1;
    infoCanevas.etatCouche = "INITIALISEE";
    infoCanevas.formeActive = -1;
    infoCanevas.informationForme = " ";
    infoCanevas.nbCouches = 1;
    infoCanevas.nbFormesCanevas = 0;
    infoCanevas.nbFormesCouche = 0;
}

Canevas::~Canevas() {
    reinitialiser();
}

bool Canevas::ajouterCouche() {
    Couche* nouvelle_couche = new Couche();
    
    bool aucune_couche_active = true;
    for(int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme.obtenirCouche(i);
        if(couche) {
            // We can try to change the state to ACTIVE - if it fails, 
            // it means the layer is already active
            if(couche->changerEtat(ACTIVE)) {
                // If we successfully changed it to active, change it back
                couche->changerEtat(INACTIVE);
            } else {
                // If we couldn't change it to active, it means it was already active
                aucune_couche_active = false;
                break;
            }
        }
    }
    
    if(aucune_couche_active) {
        nouvelle_couche->changerEtat(ACTIVE);
    } else {
        nouvelle_couche->changerEtat(INITIALISEE);
    }
    
    return vecteur_forme.ajouterCouche(nouvelle_couche);
}

bool Canevas::retirerCouche(int index) {
    if(index < 0 || index >= vecteur_forme.tailleVecteur()) 
        return false;
        
    Couche* couche = vecteur_forme.obtenirCouche(index);
    if(!couche) return false;
    
    Couche* couche_retiree = vecteur_forme.retirerCouche(index);
    if(couche_retiree) {
        couche_retiree->reinitialiserCouche();  // Do this before deleting
        delete couche_retiree;
        return true;
    }
    return false;
}

bool Canevas::reinitialiser() {
    while(!vecteur_forme.estVide()) {
        retirerCouche(vecteur_forme.tailleVecteur() - 1);
    }
    return true;
}

bool Canevas::reinitialiserCouche(int index) {
    if(index < 0 || index >= vecteur_forme.tailleVecteur()){ 
        return false;}
        
    Couche* couche = vecteur_forme.obtenirCouche(index);
    if(!couche){ return false;}
    
    couche->reinitialiserCouche();
    return true;
}

bool Canevas::activerCouche(int index) {
    if(index < 0 || index >= vecteur_forme.tailleVecteur()) 
        return false;
        
    Couche* couche = vecteur_forme.obtenirCouche(index);
    if(!couche) return false;
    
    for(int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* c = vecteur_forme.obtenirCouche(i);
        if(c && i != index) {
            c->changerEtat(INACTIVE);
        }
    }
    
    return couche->changerEtat(ACTIVE);
}

bool Canevas::desactiverCouche(int index) {
    if(index < 0 || index >= vecteur_forme.tailleVecteur()) 
        return false;
        
    Couche* couche = vecteur_forme.obtenirCouche(index);
    if(!couche) return false;
    
    return couche->changerEtat(INACTIVE);
}

bool Canevas::ajouterForme(Forme* p_forme) {
    if(!p_forme) return false;
    
    for(int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme.obtenirCouche(i);
        if(couche) {
            if(couche->ajoutForme(p_forme)) {
                return true;
            }
        }
    }
    delete p_forme;
    return false;
}

bool Canevas::retirerForme(int index) {
    for(int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme.obtenirCouche(i);
        if(couche) {
            Forme* forme = couche->retraitForme(index);
            if(forme) {
                delete forme;
                return true;
            }
        }
    }
    return false;
}

double Canevas::aire() {
    double aire_totale = 0.0;
    for(int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme.obtenirCouche(i);
        if(couche) {
            aire_totale += couche->aireTotale();
        }
    }
    return aire_totale;
}

bool Canevas::translater(int deltaX, int deltaY) {
    bool translate = false;
    for(int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
        Couche* couche = vecteur_forme.obtenirCouche(i);
        if(couche) {
            if(couche->translaterCouche(deltaX, deltaY)) {
                translate = true;
            }
        }
    }
    return translate;
}

void Canevas::afficher(ostream& s) {
    if(vecteur_forme.estVide()) {
        s << "--- Aucune couche ---" << endl;
    } 
    else {
        for(int i = 0; i < vecteur_forme.tailleVecteur(); i++) {
            s << "--- Couche " << i << " ---" << endl;
            Couche* couche = vecteur_forme.obtenirCouche(i);
            if(couche) {
                couche->afficherCouche(s);
            } else {
                s << "Couche inexistante" << endl;
            }
        }
    }
}
