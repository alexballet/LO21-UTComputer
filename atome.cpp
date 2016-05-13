#include "atome.h"
#include "variable.h"
#include <QDebug>

Atome::Atome(QString id): id(id) {

}

QString Atome::getId() const {
    return id;
}

QString Atome::toString() const {
    return id;
}

Litteral* Atome::getLitterale() const { //finds the corresponding litterale
    //is this a Variable?
    VariableMap* varmap = VariableMap::getInstance();
    Litteral* lit = varmap->findVar(id);
    if (lit)
        return lit;
    //else if pour Programme
    //else pour Expression
    return new Variable(new Entier(5), id);
}
