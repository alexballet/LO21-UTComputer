#include "programme.h"
#include <QDebug>

//Programme
Programme::Programme(QVector<Litteral*> i, QString id): instructions(i), id(id) {
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    progmap->insertProg(id, this);
}

QString Programme::getId() const {
    return id;
}

QString Programme::toString() const {
    return id; //todo
}

template<class T>
bool isProgramme(T& a){
    Programme *c = dynamic_cast<Programme*>(&a);
    return c!=nullptr;
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
