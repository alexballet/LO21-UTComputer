#ifndef VARIABLE_H
#define VARIABLE_H
#include "litteral.h"
#include "controleur.h"
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
    //disabling copy and assignment
    VariableMap& operator=(const VariableMap&) = delete;
    VariableMap (const VariableMap&) = delete;
public:
    static VariableMap* getInstance();
    static void libererInstance();
    Variable* findVar(QString id) const;
    void deleteVar(QString id);
    void insertVar(QString id, Variable* var);
    void setVar(QString id, QString value);
    unsigned int getCount() const;
    QMap<QString, Variable*>::const_iterator getIteratorBegin() const;
    QMap<QString, Variable*>::const_iterator getIteratorEnd() const;
};


#endif // VARIABLE_H
