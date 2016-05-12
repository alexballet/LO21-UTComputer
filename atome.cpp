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

Litteral* Atome::getLitterale() const {
    VariableMap* varmap = VariableMap::getInstance();
    QMap<QString, Variable*>* map = varmap->getMap();
    if (map->contains(id)){
        qDebug() << "found!";
        return map->value(id);
    }
    return new Variable(new Entier(5), id); //should return an Expression
}
