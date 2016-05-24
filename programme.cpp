#include "programme.h"
#include "controleur.h"
#include <QDebug>

//Programme
Programme::Programme(QStringList i, QString id): instructions(i), id(id) {
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    progmap->insertProg(id, this);
}

Programme::Programme(const QString& i): id("lel") {
    QString temp = i;
    instructions = temp.remove('[').remove(']').split(' ');
    qDebug()<<"instructions : "<<instructions;
}

QString Programme::getId() const {
    return id;
}

QString Programme::toString() const {
    QString str;
    str.append('[');
    foreach(QString s, instructions){
        str.append(s);
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
    qDebug()<<i.at(0);
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
