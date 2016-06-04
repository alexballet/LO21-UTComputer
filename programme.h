#ifndef PROGRAMME_H
#define PROGRAMME_H

#include "litteral.h"
#include "controleur.h"
#include "programeditorwindow.h"
#include <QVector>
#include <QString>
#include <QMap>
#include <QList>
#include <QTableWidgetItem>
#include <QRegularExpressionMatch>

class Programme : public Litteral {
private:
    QStringList instructions;
    QString id;
public:
    Programme(QStringList i, QString id);
    Programme(const QString& i);
    Programme(Litteral* lit, const QString id);
    QString getId() const;
    void setInstructions(QStringList l);
    void setId(const QString& s);
    QStringList getInstructions() const;
    QString toString() const;
};

template<class T>
bool isProgramme(T& a);

bool isProgramme(const QString& i);

class ProgrammeMap {
private:
    QMap<QString, Programme*> map;
    static ProgrammeMap* instance;
    ProgrammeMap(){}

    //disabling copy and assignment
    ProgrammeMap& operator=(const ProgrammeMap&) = delete;
    ProgrammeMap (const ProgrammeMap&) = delete;
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
