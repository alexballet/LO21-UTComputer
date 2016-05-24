#include "pile.h"
#include <QDebug>

Pile* Pile::instance = nullptr;

Pile* Pile::getInstance() {
    if (!instance)
        instance = new Pile();
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

void Pile::setMaxAffiche(int i) {
    maxAffiche = i;
}

unsigned int Pile::getMaxAffiche() const {
    return maxAffiche;
}

QStack<Litteral*>* Pile::getStack() {
    return &stack;
}


void Pile::push(Litteral *lit) {
    stack.push(lit);
    emit modificationEtat();
}


Litteral* Pile::pop(){
    if(stack.length()==0)
        throw ComputerException("Erreur : Pile vide");
    else
        return stack.pop();
}

Litteral* Pile::top(){
    if(stack.length()==0)
        throw ComputerException("Erreur : Pile vide");
    else
        return stack.top();
}

