#include "controleur.h"
#include <QDebug>
#include <QRegularExpressionMatch>

Controleur* Controleur::instance = nullptr;

void Controleur::parse(const QString& com) {
    Pile* pile = Pile::getInstance();
    QStringList words = com.split(" ");

    foreach (QString word, words) {
        QString type = typeLitteral(word);
        if(type=="OperatorNum"){
            try{
                applyOperatorNum(word);
            }
            catch(ComputerException c){
                pile->setMessage(c.getInfo());
            }
        }
        else if(type=="OperatorLog"){
            try{
                applyOperatorLog(word);
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
    if(isOperatorNum(lit)){
        return "OperatorNum";
    }
    else if(isOperatorLog(lit)){
        return "OperatorLog";
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

void Controleur::applyOperatorNum(const QString& op){
    Pile *pile = Pile::getInstance();
    if(op=="+"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Litteral *res = *y+*x;
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
            Litteral *res = *y-*x;
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="*"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Litteral *res = *y * *x;
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="/"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Litteral *res = *y / *x;
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="DIV"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            if(isEntier(*x) && isEntier(*y)){
                Litteral *res = div(*y,*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(y->toString(), typeLitteral(y->toString()));
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur DIV s'applique sur des opérandes entières");
            }
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="MOD"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            if(isEntier(*x) && isEntier(*y)){
                Litteral *res = mod(*y,*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(y->toString(), typeLitteral(y->toString()));
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur MOD s'applique sur des opérandes entières");
            }
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="NEG"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            Litteral *res = neg(*x);
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="NUM"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isRationnel(*x) || isEntier(*x)){
                Litteral *res = num(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur NUM s'applique sur une opérande rationnelle ou entière");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="DEN"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isRationnel(*x) || isEntier(*x)){
                Litteral *res = den(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur NUM s'applique sur une opérande rationnelle ou entière");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="$"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            if((isEntier(*x) || isReel(*x) || isRationnel(*x)) && (isEntier(*y) || isReel(*y) || isRationnel(*y))){
                Litteral *res = createComplexe(*y, *x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(y->toString(), typeLitteral(y->toString()));
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur $ s'applique sur des opérandes entières, réelles ou rationnelles");
            }
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="RE"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            Litteral *res = re(*x);
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="IM"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            Litteral *res = im(*x);
            pile->push(res->toString(), typeLitteral(res->toString()));
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="SIN"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = sin(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur SIN s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="COS"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = cos(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur COS s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="TAN"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = tan(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur TAN s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="ARCSIN"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = arcSin(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur ARCSIN s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="ARCCOS"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = arcCos(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur ARCCOS s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="ARCTAN"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = arcTan(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur ARCTAN s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="EXP"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = exp(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur EXP s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
    else if(op=="LN"){
        if(pile->getStack()->length()>=1){
            Litteral *x = pile->pop();
            if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
                Litteral *res = ln(*x);
                pile->push(res->toString(), typeLitteral(res->toString()));
            }
            else{
                pile->push(x->toString(), typeLitteral(x->toString()));
                throw ComputerException("Erreur : L'opérateur LN s'applique sur une opérande entière, réelle ou rationnelle");
            }
        }
        else
            throw ComputerException("Erreur : 1 argument empilé nécessaire");
    }
}

void Controleur::applyOperatorLog(const QString& op){
    Pile *pile = Pile::getInstance();
    if(op=="="){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Litteral *res = (*y == *x);
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

bool isOperatorNum(const QString& a){
    return a=="+" || a=="-" || a=="*" || a=="/" || a=="DIV" || a=="MOD" || a=="NEG" || a=="NUM" || a=="DEN" || a=="$" || a=="RE" || a=="IM" || a=="SIN" || a=="COS" || a=="TAN" || a=="ARCSIN" || a=="ARCCOS" || a=="ARCTAN" || a=="EXP" || a=="LN";
}
bool isOperatorLog(const QString& a){
    return a=="=" || a=="!=" || a=="<=" || a==">=" || a=="<" || a==">" || a=="AND" || a=="OR" || a=="NOT";
}
