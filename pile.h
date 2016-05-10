#ifndef PILE_H
#define PILE_H

#include <QObject>
#include <QString>
#include <QStack>
#include "litteral.h"

class Pile : public QObject {
    Q_OBJECT

private:
    static Pile* instance;

    QStack<Litteral*> stack;
    QString message;
    unsigned int maxAffiche;

    Pile():message(""), maxAffiche(5){}

public:
    static Pile* getInstance();
    static void libererInstance();

    QString getMessage() const;
    void setMessage(const QString& msg);
    unsigned int getMaxAffiche() const;
    QStack<Litteral*>* getStack();
signals:
void modificationEtat();
};

#endif // PILE_H
