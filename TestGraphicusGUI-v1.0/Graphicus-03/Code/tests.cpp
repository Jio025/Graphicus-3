/********
 * Fichier: tests.cpp
 * Auteurs: C.-A. Brunet
 * Date: 13 juin 2024 (creation)
 * Modifie par : Guillaume Dumas - dumg2423, Alexis Beriault - bera8365
 * Date : 13 janvier 2024
 * Description: Implementation des methodes des classes decrites dans
 *    tests.h.  Ce fichier peut etre adapte a vos besoins de tests. 
 *    Ce fichier fait partie de la distribution de Graphicus.
********/

#include "tests.h"

void Tests::tests_unitaires_formes()
{
   Rectangle rect(10, 20, 5.0, 3.0);
   Carre car(2, 4, 5);
   Cercle cer(1, 5, 6);
   rect.afficher(cout);
   car.afficher(cout);
   cer.afficher(cout);
}

void Tests::tests_unitaires_couche()
{
   Couche couche;
   couche.changerEtat(ACTIVE);
   Forme* rect = new Rectangle(10, 20, 5.0, 3.0);
   Forme* car = new Carre(2, 3, 5);
   Forme* cer = new Cercle(1, 5, 6);
   couche.ajoutForme(rect);
   couche.ajoutForme(car);
   couche.ajoutForme(cer);
   couche.afficherCouche(cout);
   cout << couche.aireTotale() << endl;
}

void Tests::tests_unitaires_vecteur()
{
   // Tests sur la classe Vecteur
}

void Tests::tests_unitaires_canevas()
{
   // Tests sur la classe Canevas
}

void Tests::tests_unitaires()
{
   // Fait tous les tests unitaires
   tests_unitaires_formes();
   tests_unitaires_couche();
   tests_unitaires_vecteur();
   tests_unitaires_canevas();
}

void Tests::tests_application()
{
   // Fait tous les tests applicatifs
   tests_application_cas_01();
   tests_application_cas_02();
}

void Tests::tests_application_cas_01()
{
    cout << "\n=== DEBUT DES TESTS APPLICATION (CAS 01) ===\n" << endl;
    
    Canevas canvas;
    
    // ÉTAPES 1-2
    cout << "ÉTAPES 1-2:" << endl;
    cout << "1. Affichage initial du canevas:" << endl;
    canvas.afficher(cout);
    cout << "2. Aire totale du canevas: " << canvas.aire() << endl;
    
    // ÉTAPES 3-5
    cout << "\nÉTAPES 3-5:" << endl;
    cout << "3. Ajout de 5 couches au canevas" << endl;
    for(int i = 0; i < 5; i++) {
        canvas.ajouterCouche();
        cout << "  Couche " << i << " ajoutée" << endl;
    }
    cout << "4. Affichage du canevas après ajout des couches:" << endl;
    canvas.afficher(cout);
    cout << "5. Aire totale du canevas: " << canvas.aire() << endl;
    
    // ÉTAPES 6-9
    cout << "\nÉTAPES 6-9:" << endl;
    cout << "6. Activation de la couche 2 et ajout de formes:" << endl;
    canvas.activerCouche(2);
    canvas.ajouterForme(new Cercle(0, 1, 5));
    cout << "  Ajout cercle(0,1,r=5)" << endl;
    canvas.ajouterForme(new Carre(1, 2, 6));
    cout << "  Ajout carré(1,2,c=6)" << endl;
    canvas.ajouterForme(new Rectangle(2, 3, 4, 9));
    cout << "  Ajout rectangle(2,3,l=4,h=9)" << endl;
    
    cout << "7. Activation de la couche 1 et ajout de forme:" << endl;
    canvas.activerCouche(1);
    canvas.ajouterForme(new Rectangle(0, 0, 12, 3));
    cout << "  Ajout rectangle(0,0,l=12,h=3)" << endl;
    
    cout << "8. Affichage du canevas:" << endl;
    canvas.afficher(cout);
    cout << "9. Aire totale du canevas: " << canvas.aire() << endl;
    
    // ÉTAPES 10-13
    cout << "\nÉTAPES 10-13:" << endl;
    cout << "10. Activation de la couche 0 et ajout de formes:" << endl;
    canvas.activerCouche(0);
    canvas.ajouterForme(new Rectangle(0, 0, 1, 1));
    cout << "  Ajout rectangle(0,0,l=1,h=1)" << endl;
    canvas.ajouterForme(new Carre(0, 0, 1));
    cout << "  Ajout carré(0,0,c=1)" << endl;
    canvas.ajouterForme(new Cercle(0, 0, 1));
    cout << "  Ajout cercle(0,0,r=1)" << endl;
    
    cout << "11. Activation de la couche 2 et translation:" << endl;
    canvas.activerCouche(2);
    canvas.translater(2, 1);
    cout << "  Translation appliquée (x=2, y=1)" << endl;
    
    cout << "12. Affichage du canevas:" << endl;
    canvas.afficher(cout);
    cout << "13. Aire totale du canevas: " << canvas.aire() << endl;
    
    // ÉTAPES 14-20
    cout << "\nÉTAPES 14-20:" << endl;
    cout << "14. Activation couche 0 et retrait de la 2e forme:" << endl;
    canvas.activerCouche(0);
    canvas.retirerForme(1);
    cout << "15. Réinitialisation de la couche 1" << endl;
    canvas.reinitialiserCouche(1);
    cout << "16. Activation de la couche 2" << endl;
    canvas.activerCouche(2);
    cout << "17. Retrait de la couche 2" << endl;
    canvas.retirerCouche(2);
    cout << "18. Activation de la couche 4" << endl;
    canvas.activerCouche(4);
    
    cout << "19. Affichage du canevas:" << endl;
    canvas.afficher(cout);
    cout << "20. Aire totale du canevas: " << canvas.aire() << endl;
    
    // ÉTAPES 21-23
    cout << "\nÉTAPES 21-23:" << endl;
    cout << "21. Réinitialisation du canevas" << endl;
    canvas.reinitialiser();
    cout << "22. Affichage du canevas:" << endl;
    canvas.afficher(cout);
    cout << "23. Aire totale du canevas: " << canvas.aire() << endl;
    
    // ÉTAPES 24-27
    cout << "\nÉTAPES 24-27:" << endl;
    cout << "24. Activation de la couche 3 et ajout de formes:" << endl;
    canvas.activerCouche(3);
    canvas.ajouterForme(new Carre(10, 10, 10));
    cout << "  Ajout carré(10,10,c=10)" << endl;
    canvas.ajouterForme(nullptr);
    cout << "  Tentative d'ajout d'une forme null" << endl;
    
    cout << "25. Activation de la couche 6" << endl;
    canvas.activerCouche(6);
    
    cout << "26. Affichage du canevas:" << endl;
    canvas.afficher(cout);
    cout << "27. Aire totale du canevas: " << canvas.aire() << endl;
    
    cout << "\n=== FIN DES TESTS APPLICATION (CAS 01) ===\n" << endl;
}

void Tests::tests_application_cas_02()
{
   cout << "TESTS APPLICATION (CAS 02)" << endl;  
    // Il faut ajouter les operations realisant ce scenario de test.
}
