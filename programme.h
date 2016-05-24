#ifndef PROGRAMME_H
#define PROGRAMME_H

#include "litteral.h"
#include <QVector>
#include <QMap>

class Programme : public Litteral {
private:
    QVector<Litteral*> instructions; //best solution?
    QString id;
public:
    Programme(QVector<Litteral *> i, QString id);
    QString getId() const;
    QString toString() const;
};


class ProgrammeMap {
private:
    QMap<QString, Programme*> map;
    static ProgrammeMap* instance;
    ProgrammeMap();
public:
    static ProgrammeMap* getInstance();
    static void libererInstance();
    Programme* findProg(QString id) const;
    void deleteProg(QString id);
    void insertProg(QString id, Programme* prog);
    unsigned int getCount() const;
    QMap<QString, Programme*>::const_iterator getIteratorBegin() const;
    QMap<QString, Programme*>::const_iterator getIteratorEnd() const;
};


#endif // PROGRAMME_H
