#include "variable.h"
#include "controleur.h"
#include <QDebug>

Variable::Variable(Litteral *v, QString id): value(v), id(id) {
    QString type = typeLitteral(id);
    if (isOperatorLog(id) || isOperatorNum(id) || isOperatorPile(id)) {
        throw ComputerException("Une variable ne peut pas avoir un nom d'opérateur !");
    }
    else if(type!="Atome"){
        throw ComputerException("Une variable doit être un atome !");
    }
    else {
        VariableMap* varmap = VariableMap::getInstance();
        varmap->insertVar(id, this);
    }
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

template<class T>
bool isVariable(T& a){
    Variable *c = dynamic_cast<Variable*>(&a);
    return c!=nullptr;
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

void VariableMap::setVar(QString id, QString value) {
    map.value(id)->setValue(new Entier(value.toInt())); //ONLY ENTIER
}

unsigned int VariableMap::getCount() const {
    return map.count();
}

QMap<QString, Variable*>::const_iterator VariableMap::getIteratorBegin() const {
    QMap<QString, Variable*>::const_iterator i = map.constBegin();
    return i;
}

QMap<QString, Variable*>::const_iterator VariableMap::getIteratorEnd() const {
    QMap<QString, Variable*>::const_iterator i = map.constEnd();
    return i;
}
