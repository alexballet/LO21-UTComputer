#include "controleur.h"

Controleur* Controleur::instance = nullptr;

void Controleur::commande(const QString& com){
    bool ok=false;
    int e = com.toInt(&ok, 10);
    if(isnumber(e)) {
        Pile* pile = Pile::getInstance();
        Entier* entier = new Entier(e);
        pile->getStack()->push(entier);
        pile->modificationEtat();
    }
}

Controleur* Controleur::getInstance() {
    if(!instance)
        return new Controleur();
    return instance;
}
