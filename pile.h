#ifndef PILE_H
#define PILE_H

#include <QObject>
#include <QString>
#include <QStack>
#include <QtCore/qmath.h>
#include <typeinfo>
#include "litteral.h"
#include "atome.h"
#include "controleur.h"

class Pile : public QObject {
    Q_OBJECT

private:
    static Pile* instance;

    QStack<Litteral*> stack;
    QString message;
    unsigned int maxAffiche;

    Pile():message(""), maxAffiche(4){}

public:
    static Pile* getInstance();
    static void libererInstance();

    QString getMessage() const;
    void setMaxAffiche(int);
    void setMessage(const QString& msg);
    unsigned int getMaxAffiche() const;
    QStack<Litteral*>* getStack();
    void push(Litteral* lit);
    Litteral* pop();
    Litteral* top() const;
signals:
    void modificationEtat();
};

#endif // PILE_H
