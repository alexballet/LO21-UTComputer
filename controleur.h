#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QString>
#include <QDebug>
#include "litteral.h"
#include "pile.h"

class Controleur {
    static Controleur* instance;
public:
    static Controleur* getInstance();
    void commande(const QString& com);
};

#endif // CONTROLEUR_H
