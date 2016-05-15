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
