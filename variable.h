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
    void setValue(Litteral* v);
};

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

};


#endif // VARIABLE_H
