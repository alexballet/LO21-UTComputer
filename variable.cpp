#include "variable.h"
#include "controleur.h"

Variable::Variable(Litteral *v, QString id): value(v), id(id) {
    QString type = typeLitteral(id);
    ProgrammeMap* progmap = ProgrammeMap::getInstance();

    if (isOperatorLog(id) || isOperatorNum(id) || isOperatorPile(id)) {
        throw ComputerException("Une variable ne peut pas avoir un nom d'opérateur !");
    } else if(type != "Atome") {
        throw ComputerException("Une variable doit être un atome !");
    } else if(progmap->findProg(id)) {
        throw ComputerException("Un programme avec le même nom existe deja!");
    } else {
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
bool isVariable(T& a) {
    Variable *c = dynamic_cast<Variable*>(&a);
    return c != nullptr;
}

//Variable Map

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

VariableMap::~VariableMap() {
    libererInstance();
}

Variable* VariableMap::findVar(QString id) const {
    if (map.contains(id)) {
        return map.value(id);
    }

    return nullptr;
}

void VariableMap::deleteVar(QString id) {
    map.remove(id);
}

void VariableMap::insertVar(QString id, Variable* var) {
    map.insert(id, var);
}

void VariableMap::setVar(QString id, QString value) {
    map.value(id)->setValue(Litteral::createLitteral(value, typeLitteral(value)));
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
