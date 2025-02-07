#include "Canevas.h"
#include <sstream>

using namespace std;

Canevas::Canevas() {}

Canevas::~Canevas() {
    reinitialiser();
}

bool Canevas::ajouterCouche() {
    Couche* nouvelle_couche = new Couche();
    // If no active layer exists, set the new layer to ACTIVE.
    if (getActiveCoucheIndex() < 0)
        nouvelle_couche->changerEtat(ACTIVE);
    else
        nouvelle_couche->changerEtat(INITIALISEE);

    vecteur_couche += nouvelle_couche;
    return true;
}

bool Canevas::retirerCouche(int index) {
    if (index < 0 || index >= vecteur_couche.tailleVecteur()) return false;

    Couche* couche_retiree = vecteur_couche[index];
    if (!couche_retiree) return false;

    couche_retiree->reinitialiserCouche();
    delete couche_retiree;

    for (int i = index; i < vecteur_couche.tailleVecteur() - 1; i++) {
        vecteur_couche[i] = vecteur_couche[i + 1];
    }
    vecteur_couche.taille--;
    return true;
}

bool Canevas::reinitialiser() {
    while (!vecteur_couche.estVide()) {
        retirerCouche(vecteur_couche.tailleVecteur() - 1);
    }
    return true;
}

bool Canevas::reinitialiserCouche(int index) {
    if (index < 0 || index >= vecteur_couche.tailleVecteur()) return false;

    Couche* couche = vecteur_couche[index];
    if (!couche) return false;

    couche->reinitialiserCouche();
    return true;
}

bool Canevas::desactiverCouche(int index) {
    if (index < 0 || index >= vecteur_couche.tailleVecteur()) return false;
    return vecteur_couche[index]->changerEtat(INACTIVE);
}

bool Canevas::ajouterForme(Forme* p_forme) {
    int activeLayer = getActiveCoucheIndex();
    if (activeLayer < 0 || !p_forme)
        return false;

    if (vecteur_couche[activeLayer]->ajoutForme(p_forme))
        return true;

    // If the active layer rejected the form, delete it and return false.
    delete p_forme;
    return false;
}

bool Canevas::retirerForme(int index) {
    int activeLayerIndex = getActiveCoucheIndex();
    if (activeLayerIndex < 0) return false;  // No active layer

    Couche* coucheActive = vecteur_couche[activeLayerIndex];
    if (coucheActive) {
        Forme* forme = coucheActive->retraitForme(index);
        if (forme) {
            delete forme;
            return true;
        }
    }
    return false;
}

double Canevas::aire() const {
    double aire_totale = 0.0;
    for (int i = 0; i < vecteur_couche.tailleVecteur(); i++) {
        if (vecteur_couche[i]) {
            aire_totale += vecteur_couche[i]->aireTotale();
        }
    }
    return aire_totale;
}

bool Canevas::translater(int deltaX, int deltaY) {
    bool translate = false;
    for (int i = 0; i < vecteur_couche.tailleVecteur(); i++) {
        if (vecteur_couche[i] && vecteur_couche[i]->translaterCouche(deltaX, deltaY)) {
            translate = true;
        }
    }
    return translate;
}

void Canevas::afficher(std::ostream& s) const {
    if (vecteur_couche.estVide()) {
        s << "--- Aucune couche ---" << std::endl;
    }
    else {
        for (int i = 0; i < vecteur_couche.tailleVecteur(); i++) {
            s << "--- Couche " << i << " ---" << std::endl;
            if (vecteur_couche[i]) {
                // This now calls the const version of afficherCouche()
                vecteur_couche[i]->afficherCouche(s);
            }
            else {
                s << "Couche inexistante" << std::endl;
            }
        }
    }
}

int Canevas::getNbCouches() const { 
    return vecteur_couche.tailleVecteur(); 
}

int Canevas::getActiveCoucheIndex() const {
    for (int i = 0; i < vecteur_couche.tailleVecteur(); ++i) {
        if (vecteur_couche[i] && vecteur_couche[i]->getEtat() == ACTIVE) {
            return i;
        }
    }
    return -1;  // No active layer found.
}

int Canevas::getNbFormes() const {
    int total = 0;
    for (int i = 0; i < vecteur_couche.tailleVecteur(); ++i) {
        if (vecteur_couche[i])
            total += vecteur_couche[i]->getNbFormes();
    }
    return total;
}

int Canevas::getNbFormesInActiveCouche() const {
    int activeIndex = getActiveCoucheIndex();
    if (activeIndex >= 0 && vecteur_couche[activeIndex])
        return vecteur_couche[activeIndex]->getNbFormes();
    return 0;
}

int Canevas::getActiveFormeIndex() const {
    int activeIndex = getActiveCoucheIndex();
    if (activeIndex >= 0 && vecteur_couche[activeIndex])
        return vecteur_couche[activeIndex]->getActiveFormeIndex();
    return -1;
}

double Canevas::getAireTotale() const {
    return aire();
}

double Canevas::getAireActiveCouche() const {
    int activeIndex = getActiveCoucheIndex();
    if (activeIndex >= 0 && vecteur_couche[activeIndex])
        return vecteur_couche[activeIndex]->aireTotale();
    return 0.0;
}

std::string Canevas::toString() const {
    std::ostringstream oss;

    // Loop over all layers.
    for (int i = 0; i < vecteur_couche.tailleVecteur(); i++) {
        Couche* couche = vecteur_couche[i];
        if (!couche)
            continue;

        // Convert the couche state into a character.
        char etatChar;
        Etat etat = couche->getEtat();
        if (etat == ACTIVE)
            etatChar = 'a';
        else if (etat == INITIALISEE)
            etatChar = 'i';
        else if (etat == INACTIVE)
            etatChar = 'x';
        else
            etatChar = 'i';  // default if unknown

        oss << "L " << etatChar << "\n";

        // For each shape in the layer, output one line.
        for (int j = 0; j < couche->getNbFormes(); j++) {
            Forme* forme = couche->obtenirForme(j);
            if (!forme)
                continue;

            // Use dynamic_cast to check the actual type.
            if (Rectangle* rect = dynamic_cast<Rectangle*>(forme)) {
                // Output: "R x y l h"
                oss << "R "
                    << rect->getX() << " "
                    << rect->getY() << " "
                    << rect->getWidth() << " "
                    << rect->getHeigth() << "\n";
            }
            else if (Carre* carre = dynamic_cast<Carre*>(forme)) {
                // Output: "K x y c"
                oss << "K "
                    << carre->getX() << " "
                    << carre->getY() << " "
                    << carre->getWidth() << "\n";
            }
            else if (Cercle* cercle = dynamic_cast<Cercle*>(forme)) {
                // Output: "C x y r"
                oss << "C "
                    << cercle->getX() << " "
                    << cercle->getY() << " "
                    << cercle->getRayon() << "\n";
            }
        }
    }
    return oss.str();
}

bool Canevas::couchePremiere() {
    if (vecteur_couche.tailleVecteur() > 0) {
        return activerCouche(0);
    }
    return false;
}

bool Canevas::coucheDerniere() {
    int nb = vecteur_couche.tailleVecteur();
    if (nb > 0) {
        return activerCouche(nb - 1);
    }
    return false;
}

bool Canevas::couchePrecedente() {
    int activeIndex = getActiveCoucheIndex();
    if (activeIndex > 0) {
        return activerCouche(activeIndex - 1);
    }
    return false;
}

bool Canevas::coucheSuivante() {
    int activeIndex = getActiveCoucheIndex();
    int nb = vecteur_couche.tailleVecteur();
    if (activeIndex >= 0 && activeIndex < nb - 1) {
        return activerCouche(activeIndex + 1);
    }
    return false;
}

bool Canevas::formePremiere() {
    int activeLayerIndex = getActiveCoucheIndex();
    if (activeLayerIndex < 0)
        return false;

    Couche* couche = vecteur_couche[activeLayerIndex];
    if (couche->getNbFormes() > 0) {
        return couche->setActiveFormeIndex(0);
    }
    return false;
}

bool Canevas::formeDerniere() {
    int activeLayerIndex = getActiveCoucheIndex();
    if (activeLayerIndex < 0)
        return false;

    Couche* couche = vecteur_couche[activeLayerIndex];
    int nbFormes = couche->getNbFormes();
    if (nbFormes > 0) {
        return couche->setActiveFormeIndex(nbFormes - 1);
    }
    return false;
}

bool Canevas::formePrecedente() {
    int activeLayerIndex = getActiveCoucheIndex();
    if (activeLayerIndex < 0)
        return false;

    Couche* couche = vecteur_couche[activeLayerIndex];
    int activeFormeIndex = couche->getActiveFormeIndex();
    if (activeFormeIndex > 0) {
        return couche->setActiveFormeIndex(activeFormeIndex - 1);
    }
    return false;
}

bool Canevas::formeSuivante() {
    int activeLayerIndex = getActiveCoucheIndex();
    if (activeLayerIndex < 0)
        return false;

    Couche* couche = vecteur_couche[activeLayerIndex];
    int nbFormes = couche->getNbFormes();
    int activeFormeIndex = couche->getActiveFormeIndex();
    if (activeFormeIndex < nbFormes - 1) {
        return couche->setActiveFormeIndex(activeFormeIndex + 1);
    }
    return false;
}

bool Canevas::activerCouche(int index) {
    if (index < 0 || index >= vecteur_couche.tailleVecteur()) return false;
    for (int i = 0; i < vecteur_couche.tailleVecteur(); i++) {
        if (vecteur_couche[i] && i != index) {
            vecteur_couche[i]->changerEtat(INACTIVE);
        }
    }
    return vecteur_couche[index]->changerEtat(ACTIVE);
}