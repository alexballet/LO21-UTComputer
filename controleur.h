#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QString>
#include <QDebug>
#include <QVector>
#include "litteral.h"
#include "programme.h"
#include "variable.h"
#include "atome.h"
#include "memento.h"
#include "pile.h"
#include "operateur.h"
#include "expression.h"
#include "dbmanager.h"


class Controleur {
private:
    static Controleur* instance;
    Controleur() {} //private constructor to forbid instantiation
    static QVector<Memento*> mementoList;
    static int currentMemento;
    //INTERDIRE LA RECOPIE AUSSI
public:
    static Controleur* getInstance();
    void parse(const QString& com);//calls Pile::push() with a string argument for the type to push
    void applyOperatorNum(const QString& op, const int nbOp);
    void applyOperatorLog(const QString& op, const int nbOp);
    void applyOperatorPile(const QString& op);
    //taking care of memento
    static void addMementoState(Memento* mem);
    static void undo();
    static void redo();
};

QString typeLitteral(const QString& lit);
bool isOperatorNum(const QString& a);
bool isOperatorLog(const QString& a);
bool isOperatorPile(const QString& a);
bool isOperator(const QString& a);

#endif // CONTROLEUR_H
