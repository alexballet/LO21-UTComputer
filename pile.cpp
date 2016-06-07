#include "pile.h"

Pile* Pile::instance = nullptr;

Pile::Pile(): message(""), maxAffiche(0) {
}

Pile::~Pile() {
    libererInstance();
}

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

void Pile::setMaxAffiche(unsigned int i) {
    maxAffiche = i;
}

unsigned int Pile::getMaxAffiche() const {
    return maxAffiche;
}

void Pile::push(Litteral *lit) {
    stack.push(lit);
    emit modificationEtat();
}


Litteral* Pile::pop() {
    if(stack.length() == 0)
        throw ComputerException("Erreur : Pile vide");
    else
        return stack.pop();
}

Litteral* Pile::top() const {
    if(stack.length() == 0)
        throw ComputerException("Erreur : Pile vide");
    else
        return stack.top();
}

int Pile::getLength() const {
    return stack.length();
}

bool Pile::isEmpty() const {
    return stack.isEmpty();
}

QStack<Litteral*>::const_iterator Pile::getIteratorBegin() const {
    QStack<Litteral*>::const_iterator i = stack.constBegin();
    return i;
}

QStack<Litteral*>::const_iterator Pile::getIteratorEnd() const {
    QStack<Litteral*>::const_iterator i = stack.constEnd();
    return i;
}

Memento* Pile::createMemento() const {
    return new Memento(stack);
}

void Pile::reinstateMemento(Memento* mem) {
    stack = mem->state;
    emit modificationEtat();
}
