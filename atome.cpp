#include "atome.h"
#include "programme.h"
#include "variable.h"
#include "expression.h"
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
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    lit = progmap->findProg(id);
    if (lit)
        return lit;
    //else pour Expression
    return new Expression(id);
}
