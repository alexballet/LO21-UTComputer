#include "variable.h"
#include <QDebug>

Variable::Variable(Litteral *v, QString id): value(v), id(id) {
    VariableMap* varmap = VariableMap::getInstance();
    varmap->insertVar(id, this);
}

Litteral* Variable::getValue() const {
    return value;
}

QString Variable::getId() const {
    return id;
}

QString Variable::toString() const {
    return value->toString();
}

void Variable::setValue(Litteral* v) {
    value = v;
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

Variable* VariableMap::findVar(QString id) const {
    if (map.contains(id)){
        qDebug() << "found!";
        return map.value(id);
    }
    return nullptr;
}

void VariableMap::deleteVar(QString id) {
    //try
    map.remove(id);
    //catch
}

void VariableMap::insertVar(QString id, Variable* var) {
    map.insert(id, var);
}

unsigned int VariableMap::getCount() const {
    return map.count();
}

QMap<QString, Variable*>::const_iterator VariableMap::getIterator() const {
    QMap<QString, Variable*>::const_iterator i = map.constBegin();
    return i;
}

QMap<QString, Variable*>::const_iterator VariableMap::getIteratorEnd() const {
    QMap<QString, Variable*>::const_iterator i = map.constEnd();
    return i;
}
