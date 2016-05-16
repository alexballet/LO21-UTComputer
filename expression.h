#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "litteral.h"
#include <QString>

class Expression : public Litteral {
private:
    QString text;
public:
    Expression(QString t);
    QString getText() const;
};

#endif // EXPRESSION_H