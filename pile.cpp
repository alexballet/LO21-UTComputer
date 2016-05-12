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

unsigned int Pile::getMaxAffiche() const {
    return maxAffiche;
}

QStack<Litteral*>* Pile::getStack() {
    return &stack;
}

void Pile::push(const QString& value, const QString& type){
    if(type == "Entier"){
        bool ok;
        Entier* entier = Entier::createLit(value.toInt(&ok, 10));
        getStack()->push(entier);
        emit modificationEtat();
        return;
    }
    else if(type == "Reel"){
        QStringList parts = value.split('.', QString::KeepEmptyParts);
        if(parts.at(1)=="" || parts.at(1)=="0"){
            Entier* entier = new Entier(parts.at(0).toInt());
            getStack()->push(entier);
            emit modificationEtat();
            return;
        }
        int e = 0;
        if(parts.at(0) != "")
            e = qFabs(parts.at(0).toInt());
        double d = e + parts.at(1).toInt()*(qPow(10,-(parts.at(1).length())));
        if(parts.at(0).toInt()<0 || parts.at(0)[0]=='-')
            d *= (-1);
        Reel* reel = Reel::createLit(d);
        getStack()->push(reel);
        emit modificationEtat();
        return;
    }
    else if (type == "Rationnel") {
        QStringList parts = value.split('/', QString::KeepEmptyParts);
        Rationnel* rationnel = new Rationnel(parts.at(0).toInt(), parts.at(1).toInt());
        rationnel->simplifier();
        try {
            if(rationnel->getDenominateur().getValue() == 1 || rationnel->getNumerateur().getValue() ==0){
                Entier* e = new Entier(rationnel->getNumerateur().getValue());
                getStack()->push(e);
                emit modificationEtat();
                return;
            }
            else{
                int numerateur = rationnel->getNumerateur().getValue();
                if(parts.at(0)=="")
                    numerateur=1;
                Rationnel* rationnel2 = new Rationnel(numerateur, parts.at(1).toInt());
                getStack()->push(rationnel2);
            }
        }
        catch (ComputerException e){
            setMessage(e.getInfo());
        }

        emit modificationEtat();
        return;
    }
    else if (type == "Complexe"){
        Controleur* controleur = Controleur::getInstance();
        QStringList parts = value.split('$', QString::KeepEmptyParts);
        if(parts.at(1)=="0" || parts.at(1)=="")//if it's not a complexe
            controleur->parse(parts.at(0));
        else{//if it's a complexe
            QString num = parts.at(0);
            QString denum = parts.at(1);
            Complexe* complexe = new Complexe(num, denum);
            getStack()->push(complexe);
            emit modificationEtat();
        }
    }
}
