#include "monInterface.h"

MonInterface::MonInterface(const char* theName)
    : GraphicusGUI(theName){
    reinitialiserCanevas();
    effacerInformations();
}

bool MonInterface::ouvrirFichier(const char* nom) {
    // Suppose canevas.charger(const char*) returns a bool and loads the file.
    if (canevas.charger(nom)) {
        dessiner(canevas.toString().c_str());
        message("Fichier ouvert avec succès.");
        // Optionally update info
        // info.nbCouches = canevas.getNbCouches(); etc.
        setInformations(info);
        return true;
    }
    else {
        messageErreur("Erreur lors de l'ouverture du fichier.");
        return false;
    }
}

bool MonInterface::sauvegarderFichier(const char* nom) {
    std::ofstream ofs(nom);
    if (!ofs) {
        messageErreur("Erreur lors de l'ouverture du fichier en écriture.");
        return false;
    }
    ofs << canevas.toString();
    ofs.close();
    message("Fichier sauvegardé avec succès.");
    return true;
}



void MonInterface::reinitialiserCanevas() {
    // Reset the underlying canvas
    canevas.reinitialiser();
    effacer();

    memset(&info, 0, sizeof(info));
    info.nbCouches = 0;
    info.nbFormesCanevas = 0;
    info.coucheActive = -1;
    info.aireCanevas = 0.0;
    info.nbFormesCouche = 0;
    strcpy(info.etatCouche, "I");
    info.aireCouche = 0.0;
    info.formeActive = -1;
    info.coordX = 0;
    info.coordY = 0;
    info.aireForme = 0.0;
    strcpy(info.informationForme, "");

    setInformations(info);
    message("Canevas réinitialisé.");
    dessiner(canevas.toString().c_str());
}

void MonInterface::coucheAjouter() {
    if (canevas.ajouterCouche()) {

        info.nbCouches = canevas.getNbCouches();
        info.coucheActive = canevas.getActiveCoucheIndex();
        info.nbFormesCouche = canevas.getNbFormesInActiveCouche();
        info.aireCouche = canevas.getAireActiveCouche();
        info.nbFormesCanevas = canevas.getNbFormes();
        info.aireCanevas = canevas.getAireTotale();
        strcpy(info.etatCouche, "Active");

        setInformations(info);
        message("Couche ajoutée.");
        dessiner(canevas.toString().c_str());
    }
    else {
        messageErreur("Erreur lors de l'ajout d'une couche.");
    }
}

void MonInterface::coucheRetirer() {
    int activeIndex = canevas.getActiveCoucheIndex();
    if (activeIndex >= 0 && canevas.retirerCouche(activeIndex)) {
        info.nbCouches = canevas.getNbCouches();
        info.coucheActive = (info.nbCouches > 0 ? canevas.getActiveCoucheIndex() : -1);
        info.nbFormesCouche = (info.coucheActive >= 0 ? canevas.getNbFormesInActiveCouche() : 0);
        info.aireCouche = (info.coucheActive >= 0 ? canevas.getAireActiveCouche() : 0.0);
        info.nbFormesCanevas = canevas.getNbFormes();
        info.aireCanevas = canevas.getAireTotale();
        setInformations(info);
        message("Couche retirée.");
        dessiner(canevas.toString().c_str());
    }
    else {
        messageErreur("Aucune couche active à retirer.");
    }
}
//TODO UPDATE INFO
void MonInterface::coucheTranslater(int deltaX, int deltaY) {
    if (canevas.translater(deltaX, deltaY)) {
        dessiner(canevas.toString().c_str());
        message("Couche translatée.");
    }
    else {
        messageErreur("Erreur lors de la translation de la couche active.");
    }
}



void MonInterface::ajouterRectangle(int x, int y, int longueur, int largeur) {
    if (canevas.getNbCouches() == 0 || canevas.getActiveCoucheIndex() < 0) {
        messageErreur("Aucune couche active pour ajouter un rectangle.");
        return;
    }

    Rectangle* r = new Rectangle(x, y, longueur, largeur);
    canevas.ajouterForme(r);  // Assume that this adds the form to the active layer.

    // Update Information
    info.nbFormesCanevas = canevas.getNbFormes();
    info.nbFormesCouche = canevas.getNbFormesInActiveCouche();
    info.formeActive = canevas.getActiveFormeIndex();
    info.coordX = x;
    info.coordY = y;
    info.aireForme = r->aire();
    std::snprintf(info.informationForme, sizeof(info.informationForme),
        "Rectangle (%d,%d,%d,%d)", x, y, longueur, largeur);
    info.aireCanevas = canevas.getAireTotale();
    info.aireCouche = canevas.getAireActiveCouche();

    setInformations(info);
    effacer();
    dessiner(canevas.toString().c_str());
    message("Rectangle ajouté.");
}

void MonInterface::ajouterCarre(int x, int y, int longueur) {
    if (canevas.getNbCouches() == 0 || canevas.getActiveCoucheIndex() < 0) {
        messageErreur("Aucune couche active pour ajouter un carré.");
        return;
    }

    Carre* k = new Carre(x, y, longueur);
    canevas.ajouterForme(k);  // Assume that this adds the form to the active layer.

    // Update Information
    info.nbFormesCanevas = canevas.getNbFormes();
    info.nbFormesCouche = canevas.getNbFormesInActiveCouche();
    info.formeActive = canevas.getActiveFormeIndex();
    info.coordX = x;
    info.coordY = y;
    info.aireForme = k->aire();
    std::snprintf(info.informationForme, sizeof(info.informationForme),
        "Carre (%d,%d,%d)", x, y, longueur);
    info.aireCanevas = canevas.getAireTotale();
    info.aireCouche = canevas.getAireActiveCouche();

    setInformations(info);
    effacer();
    dessiner(canevas.toString().c_str());
    message("Carré ajouté.");
}

void MonInterface::ajouterCercle(int x, int y, int rayon) {
    if (canevas.getNbCouches() == 0 || canevas.getActiveCoucheIndex() < 0) {
        messageErreur("Aucune couche active pour ajouter un cercle.");
        return;
    }

    Cercle* c = new Cercle(x, y, rayon);
    canevas.ajouterForme(c);

    // Update Information
    info.nbFormesCanevas = canevas.getNbFormes();
    info.nbFormesCouche = canevas.getNbFormesInActiveCouche();
    info.formeActive = canevas.getActiveFormeIndex();
    info.coordX = x;
    info.coordY = y;
    info.aireForme = c->aire();
    std::snprintf(info.informationForme, sizeof(info.informationForme),
        "Cercle (x:%d,y:%d, rayon:%d)", x, y, rayon);
    info.aireCanevas = canevas.getAireTotale();
    info.aireCouche = canevas.getAireActiveCouche();

    setInformations(info);
    effacer();
    dessiner(canevas.toString().c_str());
    message("Cercle ajouté.");
}
//TODO CHECK IF OK

void MonInterface::retirerForme() {
    // Only remove a shape if one is active.
    if (canevas.getNbCouches() == 0 || canevas.getActiveFormeIndex() < 0) {
        messageErreur("Aucune forme active à retirer.");
        return;
    }

    canevas.retirerForme(canevas.getActiveFormeIndex());
    info.nbFormesCanevas = canevas.getNbFormes();
    info.nbFormesCouche = canevas.getNbFormesInActiveCouche();
    info.formeActive = (info.nbFormesCouche > 0 ? canevas.getActiveFormeIndex() : -1);
    info.aireCanevas = canevas.getAireTotale();
    info.aireCouche = canevas.getAireActiveCouche();
    if (info.formeActive < 0) {
        info.coordX = info.coordY = 0;
        info.aireForme = 0.0;
        strcpy(info.informationForme, "");
    }

    setInformations(info);
    effacer();
    dessiner(canevas.toString().c_str());
    message("Forme retirée.");
}
//TODO UDATE INFO
void MonInterface::couchePremiere() {
    if (canevas.couchePremiere()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Première couche activée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la première couche.");
    }
}

void MonInterface::couchePrecedente() {
    if (canevas.couchePrecedente()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Couche précédente activée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la couche précédente.");
    }
}

void MonInterface::coucheSuivante() {
    if (canevas.coucheSuivante()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Couche suivante activée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la couche suivante.");
    }
}

void MonInterface::coucheDerniere() {
    if (canevas.coucheDerniere()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Dernière couche activée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la dernière couche.");
    }
}

void MonInterface::formePremiere() {
    if (canevas.formePremiere()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Première forme de la couche active sélectionnée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la première forme.");
    }
}

void MonInterface::formePrecedente() {
    if (canevas.formePrecedente()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Forme précédente de la couche active sélectionnée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la forme précédente.");
    }
}

void MonInterface::formeSuivante() {
    if (canevas.formeSuivante()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Forme suivante de la couche active sélectionnée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la forme suivante.");
    }
}

void MonInterface::formeDerniere() {
    if (canevas.formeDerniere()) {
        setInformations(info);
        dessiner(canevas.toString().c_str());
        message("Dernière forme de la couche active sélectionnée.");
    }
    else {
        messageErreur("Erreur lors du déplacement à la dernière forme.");
    }
}

bool Canevas::charger(const char* nom) {
    std::ifstream ifs(nom);
    if (!ifs)
        return false;

    // Clear current canvas
    reinitialiser();

    std::string line;
    Couche* currentLayer = nullptr;

    while (std::getline(ifs, line)) {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        char type;
        iss >> type;

        if (type == 'L') {
            char etat;
            iss >> etat;
            Couche* couche = new Couche();
            // Map the letter to the Etat value
            Etat e;
            switch (etat) {
            case 'a': e = ACTIVE; break;
            case 'i': e = INITIALISEE; break;
            case 'x': e = INACTIVE; break;
            default:  e = INITIALISEE; break;
            }
            couche->changerEtat(e);
            vecteur_couche += couche;
            currentLayer = couche;
        }
        else if (type == 'R') {
            int x, y, l, h;
            iss >> x >> y >> l >> h;
            Rectangle* rect = new Rectangle(x, y, l, h);
            if (!currentLayer) {
                currentLayer = new Couche();
                currentLayer->changerEtat(ACTIVE);
                vecteur_couche += currentLayer;
            }
            currentLayer->ajoutForme(rect);
        }
        // Add parsing for other shapes as needed...
    }
    return true;
}

void MonInterface::modePileChange(bool mode) {
    message(mode ? "Mode pile activé." : "Mode pile désactivé.");
}