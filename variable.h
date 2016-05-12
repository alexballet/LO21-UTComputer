#ifndef VARIABLE_H
#define VARIABLE_H
#include "litteral.h"
#include <QString>
#include <QMap>

class Variable : public Litteral {
private:
    Litteral* value;
    QString id;
public:
    Variable(Litteral* v, QString id);
    const Litteral* getValue() const;
    QString getId() const;
    QString toString() const;
};

class VariableMap {
private:
    QMap<QString, Variable*> Map; //maybe switch
    static VariableMap* instance;
    VariableMap();
public:
    static VariableMap* getInstance();
    static void libererInstance();
    QMap<QString, Variable*>* getMap();

};


#endif // VARIABLE_H
