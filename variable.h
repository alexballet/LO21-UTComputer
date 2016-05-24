#ifndef VARIABLE_H
#define VARIABLE_H
#include "litteral.h"
#include <QString>
#include <QMap>
#include <QList>
#include <QTableWidgetItem>

class Variable : public Litteral {
private:
    Litteral* value;
    QString id;
public:
    Variable(Litteral* v, QString id);
    Litteral* getValue() const;
    QString getId() const;
    QString toString() const;
    void setValue(Litteral* v);
};

template<class T>
bool isVariable(T& a);

class VariableMap {
private:
    QMap<QString, Variable*> map;
    static VariableMap* instance;
    VariableMap();
    //interdire la recopie et l affectation des singletons
public:
    static VariableMap* getInstance();
    static void libererInstance();
    Variable* findVar(QString id) const;
    void deleteVar(QString id);
    void insertVar(QString id, Variable* var);
    unsigned int getCount() const;
    QMap<QString, Variable*>::const_iterator getIteratorBegin() const;
    QMap<QString, Variable*>::const_iterator getIteratorEnd() const;
};


#endif // VARIABLE_H
