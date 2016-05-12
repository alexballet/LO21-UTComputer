#ifndef ATOME_H
#define ATOME_H
#include "litteral.h"
#include "variable.h"
#include <QString>

class Atome : public Litteral {
private:
    QString id;
public:
    Atome(QString id);
    QString getId() const;
    QString toString() const;
    Litteral* getLitterale() const;
};

#endif // ATOME_H
