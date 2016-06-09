#include "atome.h"
#include "programme.h"
#include "expression.h"

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

    if (lit) {
        return lit;
    }

    //else if pour Programme
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    lit = progmap->findProg(id);

    if (lit)
        return lit;

    //else pour Atome
    return new Atome(id);
}
