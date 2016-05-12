#include "variable.h"

Variable::Variable(Litteral *v, QString id): value(v), id(id) {
    VariableMap* varmap = VariableMap::getInstance();
    varmap->getMap()->insert(id, this);
}

const Litteral* Variable::getValue() const {
    return value;
}

QString Variable::getId() const {
    return id;
}

QString Variable::toString() const {
    return value->toString();
}

//Variable Map
VariableMap::VariableMap() {

}

VariableMap* VariableMap::instance = nullptr;

VariableMap* VariableMap::getInstance() {
    if (!instance)
        instance = new VariableMap;
    return instance;
}

void VariableMap::libererInstance() {
    if (instance)
        delete instance;
}

QMap<QString, Variable*>* VariableMap::getMap() {
    return &Map;
}
