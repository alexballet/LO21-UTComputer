#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "litteral.h"
#include "controleur.h"
#include <QString>
#include <QTextStream>
#include <QChar>
#include <QStack>

class Expression : public Litteral {
private:
    QString text;
public:
    Expression(QString t);
    QString getText() const;
    QString toString() const;
};

bool isExpression(const QString& i);

//parsing functions (infix to postfix)
QString parseExpression(const QString& s);
bool isHigher(QString a, QString b);
int order(QString op);
bool isChar(QChar a);
bool isPartOperand(QChar a, QString s, int i);

#endif // EXPRESSION_H
