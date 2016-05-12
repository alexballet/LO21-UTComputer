#ifndef VARIABLE_H
#define VARIABLE_H
#include "litteral.h"
#include <QString>

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

#endif // VARIABLE_H
