#include "computer.h"

Pile* Pile::instance = nullptr;

Pile* Pile::getInstance() {
    if (!instance)
        return new Pile();
    else
        return instance;
}




/*
bool estUnOperateur(const QString s){
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*") return true;
    if (s=="/") return true;
    return false;
}

bool estUnNombre(const QString s){
   bool ok=false;
   s.toInt(&ok);
   return ok;
}


void Controleur::commande(const QString& c){

}
*/
