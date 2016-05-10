#include "controleur.h"

Controleur* Controleur::instance = nullptr;

void Controleur::commande(const QString& com){
    bool ok=false;
    int e = com.toInt(&ok, 10);
    if(ok) {
        qDebug()<<"tutu";
        Pile* pile = Pile::getInstance();
        Entier* entier = new Entier(e);
        pile->getStack()->push(entier);
        pile->modificationEtat();
    }
}

Controleur* Controleur::getInstance() {
    if(!instance)
        instance = new Controleur();
    return instance;
}
