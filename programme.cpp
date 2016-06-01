#include "programme.h"
#include "controleur.h"
#include <QDebug>

//Programme
Programme::Programme(QStringList i, QString id): instructions(i), id(id) {
    QString type = typeLitteral(id);
    VariableMap* varmap = VariableMap::getInstance();
    if (isOperatorLog(id) || isOperatorNum(id) || isOperatorPile(id)) {
        throw ComputerException("Un programme ne peut pas avoir un nom d'opérateur !");
    }
    else if(varmap->findVar(id)) {
        throw ComputerException("Une variable avec le même nom existe deja!");
    }
    else if(type != "Atome"){
        throw ComputerException("Un programme doit être un atome !");
    }
    else {
        ProgrammeMap* progmap = ProgrammeMap::getInstance();
        progmap->insertProg(id, this);
    }
}

Programme::Programme(const QString& i): id("") {
    QString temp = i;
    if(temp!=""){
        while(temp.at(0)==' ')
            temp.remove(0,1);
        if(temp.at(0)=='[')
            temp.remove(0, 1);
        qDebug()<<"after : "<<temp;
        qDebug()<<temp.length();
        while(temp.at(temp.length()-1)==' '){
            temp.remove(temp.length()-1,1);
        }
        if(temp.at(temp.length()-1)==']')
            temp.remove(temp.length()-1, 1);
        qDebug()<<"after : "<<temp;
    }
    instructions = temp.split(' ', QString::SkipEmptyParts);
}

Programme::Programme(Litteral* lit, const QString s): id(s){
    Programme *p = dynamic_cast<Programme*>(lit);
    instructions = p->instructions;

    QString type = typeLitteral(id);
    VariableMap* varmap = VariableMap::getInstance();

    if (isOperatorLog(id) || isOperatorNum(id) || isOperatorPile(id)) {
        throw ComputerException("Un programme ne peut pas avoir un nom d'opérateur !");
    }
    else if(varmap->findVar(id)) {
        throw ComputerException("Une variable avec le même nom existe deja!");
    }
    else if(type != "Atome"){
        qDebug()<< "TYPYPPYPYPE:" << type << "id: " << id;
        throw ComputerException("Un programme doit être un atome !");
    }
    else {
        ProgrammeMap* progmap = ProgrammeMap::getInstance();
        progmap->insertProg(id, this);
    }
}

QString Programme::getId() const {
    return id;
}

QStringList Programme::getInstructions() const{
    return instructions;
}

void Programme::setInstructions(QStringList l){
    instructions = l;
}

QString Programme::toString() const {
    QString str;
    str.append('[');
    str.append(' ');
    foreach(QString s, instructions){
        str.append(s);
        str.append(' ');
    }
    str.append(']');
    return str;
}

template<class T>
bool isProgramme(T& a){
    Programme *c = dynamic_cast<Programme*>(&a);
    return c!=nullptr;
}

bool isProgramme(const QString& i){
    return i.at(0)=='[' && i.at(i.length()-1)==']';
}

//ProgrammeMap
ProgrammeMap::ProgrammeMap() {

}

ProgrammeMap* ProgrammeMap::instance = nullptr;

ProgrammeMap* ProgrammeMap::getInstance() {
    if (!instance)
        instance = new ProgrammeMap;
    return instance;
}

void ProgrammeMap::libererInstance() {
    if (instance)
        delete instance;
}

Programme* ProgrammeMap::findProg(QString id) const {
    if (map.contains(id)){
        qDebug() << "found!";
        return map.value(id);
    }
    return nullptr;
}

void ProgrammeMap::deleteProg(QString id) {
    map.remove(id);
}

void ProgrammeMap::insertProg(QString id, Programme* prog) {
    map.insert(id, prog);
}

unsigned int ProgrammeMap::getCount() const {
    return map.count();
}

QMap<QString, Programme*>::const_iterator ProgrammeMap::getIteratorBegin() const {
    QMap<QString, Programme*>::const_iterator i = map.constBegin();
    return i;
}

QMap<QString, Programme*>::const_iterator ProgrammeMap::getIteratorEnd() const {
    QMap<QString, Programme*>::const_iterator i = map.constEnd();
    return i;
}
