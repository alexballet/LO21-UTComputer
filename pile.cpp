#include "pile.h"

Pile* Pile::instance = nullptr;

Pile* Pile::getInstance() {
    if (!instance)
        return new Pile();
    else
        return instance;
}

void Pile::libererInstance() {
    if (instance)
        delete instance;
}

QString Pile::getMessage() const {
    return message;
}

void Pile::setMessage(const QString& msg) {
    message = msg;
}

unsigned int Pile::getMaxAffiche() const {
    return maxAffiche;
}

QStack<Litteral*>* Pile::getStack() {
    return &stack;
}
