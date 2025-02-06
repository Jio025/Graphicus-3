TEMPLATE     = vcapp
TARGET       = testGraphicusGUI
CONFIG      += warn_on qt debug windows console
HEADERS     += monInterface.h Vecteur.h rectangle.h forme.h couche.h coordonnee.h cercle.h carre.h canevas.h
SOURCES     += testGraphicusGUI.cpp monInterface.cpp rectangle.cpp forme.cpp couche.cpp cercle.cpp carre.cpp canevas.cpp
INCLUDEPATH += ../GraphicusGUI
LIBS        += graphicusGUI.lib
QT          += widgets
