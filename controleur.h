#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QString>
#include <QDebug>
#include "litteral.h"
#include "programme.h"
#include "variable.h"
#include "atome.h"
#include "pile.h"
#include "operateur.h"
#include "expression.h"

class Controleur {
    static Controleur* instance;
public:
    static Controleur* getInstance();
    void parse(const QString& com);//calls Pile::push() with a string argument for the type to push
    void applyOperatorNum(const QString& op, const int nbOp);
    void applyOperatorLog(const QString& op, const int nbOp);
    void applyOperatorPile(const QString& op);
};

QString typeLitteral(const QString& lit);
bool isOperatorNum(const QString& a);
bool isOperatorLog(const QString& a);
bool isOperatorPile(const QString& a);
bool isOperator(const QString& a);

#endif // CONTROLEUR_H
