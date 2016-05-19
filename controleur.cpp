#include "controleur.h"
#include <QDebug>
#include <QRegularExpressionMatch>

Controleur* Controleur::instance = nullptr;

void Controleur::parse(const QString& com) {
    Pile* pile = Pile::getInstance();
    QStringList words = com.split(" ");

    foreach (QString word, words) {
        QString type = typeLitteral(word);
        if(type=="Operator"){
            try{
                applyOperator(word);
            }
            catch(ComputerException c){
                pile->setMessage(c.getInfo());
            }
        }
        else if(type != "Inconnu")
            pile->push(word, type);
    }
}

QString typeLitteral(const QString& lit){
    if(isOperator(lit)){
        return "Operator";
    }
    else if(lit.count('$')==1 || lit.count('i')==1){
        qDebug()<<"complexe";
        return "Complexe";
    }
    else if(lit.count('.') == 1){
        qDebug()<<"reel";
        return "Reel";
    }
    else if(lit.count('/') == 1) {
        qDebug()<<"rationnel";
        return "Rationnel";
    }
    else if(lit.count('.') == 0 && (lit[0].isDigit() || (lit[0]=='-' && lit[1].isDigit()))){
        qDebug()<<"entier";
        return "Entier";
    }
    else {
        QRegularExpression re("[A-Z][A-Z0-9]*"); //starts with a capital letter and is followed by letters or numbers
        QRegularExpressionMatch match = re.match(lit);
        //qDebug() << match.captured(0);
        if (match.hasMatch() && match.captured(0) == lit) { //if the whole string is matched
            qDebug() << "atome";
            return "Atome";
        }
    }

    return "Inconnu";
}

void Controleur::applyOperator(const QString& op){
    Pile *pile = Pile::getInstance();
    if(op=="+"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Litteral *res = *x+*y;
            pile->push(res->toString(), typeLitteral(res->toString()));
            qDebug()<<typeLitteral(res->toString());
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="-"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Litteral *res = *x-*y;
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="*"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Litteral *res = *x * *y;
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
}

Controleur* Controleur::getInstance() {
    if(!instance)
        instance = new Controleur();
    return instance;
}

bool isOperator(const QString& a){
    return a=="+" || a=="-" || a=="*" || a=="/";
}
