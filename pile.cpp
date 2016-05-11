#include "pile.h"

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

unsigned int Pile::getMaxAffiche() const {
    return maxAffiche;
}

QStack<Litteral*>* Pile::getStack() {
    return &stack;
}

void Pile::push(const QString& value, const QString& type){
    if(type=="Entier"){
        bool ok;
        Entier* entier = Entier::createLit(value.toInt(&ok, 10));
        getStack()->push(entier);
        emit modificationEtat();
        return;
    }
    if(type=="Reel"){
        QStringList parts = value.split('.', QString::KeepEmptyParts);
        int e = 0;
        if(parts.at(0) != "")
            e = parts.at(0).toInt();
        double d = e + parts.at(1).toInt()*(qPow(10,-(parts.at(1).length())));
        Reel* reel = Reel::createLit(d);
        getStack()->push(reel);
        emit modificationEtat();
        return;
    }
}
