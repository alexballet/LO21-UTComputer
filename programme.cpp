#include "programme.h"
#include "controleur.h"
#include <QDebug>

//Programme
Programme::Programme(QStringList i, QString id): instructions(i), id(id) {
    QString type = typeLitteral(id);
    if (isOperatorLog(id) || isOperatorNum(id) || isOperatorPile(id)) {
        throw ComputerException("Un programme ne peut pas avoir un nom d'opérateur !");
    }
    else if(type!="Atome"){
        throw ComputerException("Un programme doit être un atome !");
    }
    else {
        ProgrammeMap* progmap = ProgrammeMap::getInstance();
        progmap->insertProg(id, this);
    }
}

Programme::Programme(const QString& i): id("") {
    QString temp = i;
    instructions = temp.remove('[').remove(']').split(' ', QString::SkipEmptyParts);
    qDebug()<<"instructions : "<<instructions;
}

Programme::Programme(Litteral* lit, const QString s){
    qDebug()<<"A";
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    Programme *p = dynamic_cast<Programme*>(lit);
    id = s;
    qDebug()<<"B";
    instructions = p->instructions;
    qDebug()<<"C";
    QString type = typeLitteral(id);
    if (isOperatorLog(id) || isOperatorNum(id) || isOperatorPile(id)) {
        throw ComputerException("Un programme ne peut pas avoir un nom d'opérateur !");
    }
    else if(type!="Atome"){
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
    qDebug()<<"tout : "<<i;
    qDebug()<<"premier : "<<i.at(0);
    qDebug()<<"taille : "<<i.length();
    qDebug()<<"dernier : "<<i.at(i.length()-1);
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
    //try
    map.remove(id);
    //catch
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
