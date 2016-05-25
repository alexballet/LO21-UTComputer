#include "controleur.h"
#include <QDebug>
#include <QRegularExpressionMatch>

Controleur* Controleur::instance = nullptr;
QVector<Memento*> Controleur::mementoList;
int Controleur::currentMemento = -1;

void Controleur::parse(const QString& com) {
    Pile* pile = Pile::getInstance();
    qDebug()<<"parsed : "<<com;
    qDebug()<<typeLitteral(com);
    if(typeLitteral(com)=="Programme"){
        pile->push(Litteral::createLitteral(com, "Programme"));
        return;
    }

    QStringList words = com.split(' ', QString::SkipEmptyParts);

    foreach (QString word, words) {
        QString type = typeLitteral(word);
        if(type=="OperatorNum"){
            try{
                applyOperatorNum(word, opsNum.value(word));
            }
            catch(ComputerException c){
                pile->setMessage(c.getInfo());
            }
        }
        else if(type=="OperatorLog"){
            try{
                applyOperatorNum(word, opsLog.value(word));
            }
            catch(ComputerException c){
                pile->setMessage(c.getInfo());
            }
        }
        else if(type=="OperatorPile"){
            try{
                applyOperatorPile(word);
            }
            catch(ComputerException c){
                pile->setMessage(c.getInfo());
            }
        }
        else if(type != "Inconnu") {
            try {
                pile->push(Litteral::createLitteral(word, type));
            }
            catch (ComputerException c) {
                pile->setMessage(c.getInfo());
            }
        }
        addMementoState(pile->createMemento());
    }
}

void Controleur::addMementoState(Memento* mem) {
    mementoList.append(mem);
    currentMemento++;
    qDebug() << "State saved! CM:" << currentMemento;
}

void Controleur::undo() {
    if (currentMemento == 0) {
        throw ComputerException("On ne peut plus revenir en arriere!");
    }
    qDebug() << "UNDO! CM:" << currentMemento;
    Pile* pile = Pile::getInstance();
    pile->reinstateMemento(mementoList[--currentMemento]);
}

void Controleur::redo() {
    if (currentMemento == mementoList.length()-1) {
        throw ComputerException("On ne peut plus revenir en avant!");
    }
    qDebug() << "REDO! CM:" << currentMemento;
    Pile* pile = Pile::getInstance();
    pile->reinstateMemento(mementoList[++currentMemento]);
}


QString typeLitteral(const QString& lit){
    if(isProgramme(lit)){
        qDebug()<<"typeLitteral : programme";
        return "Programme";
    }
    else if(isOperatorNum(lit)){
        return "OperatorNum";
    }
    else if(isOperatorLog(lit)){
        return "OperatorLog";
    }
    else if(isOperatorPile(lit)){
        return "OperatorPile";
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

void Controleur::applyOperatorNum(const QString& op, const int nbOp){
    Pile *pile = Pile::getInstance();
    if(pile->getStack()->length()<nbOp)
        throw ComputerException("Erreur : $ arguments empilés nécessaires", nbOp);
    Litteral *temp1 = pile->pop();
    Litteral *x;
    Litteral *y;
    Variable *var1 = dynamic_cast<Variable*>(temp1);
    if(var1)
        x = var1->getValue();
    else if(isEntier(*temp1) || isReel(*temp1) || isRationnel(*temp1) || isComplexe(*temp1)){
        x = temp1;
    }
    else{
        pile->push(Litteral::createLitteral(temp1->toString().remove('\''), typeLitteral(temp1->toString().remove('\''))));
        throw ComputerException("Erreur : Un opérateur numérique ne peut pas être appliqué à un programme");
    }

    if(nbOp==2){
        Litteral *temp2 = pile->pop();
        Variable *var2 = dynamic_cast<Variable*>(temp2);
        if(var2)
            y = var2->getValue();
        else if(isEntier(*temp2) || isReel(*temp2) || isRationnel(*temp2) || isComplexe(*temp2)){
            y = temp2;
        }
        else{
            pile->push(Litteral::createLitteral(temp2->toString().remove('\''), typeLitteral(temp2->toString().remove('\''))));
            pile->push(Litteral::createLitteral(temp1->toString(), typeLitteral(temp1->toString())));
            throw ComputerException("Erreur : Un opérateur numérique ne peut pas être appliqué à un programme");
        }
    }

    if(op=="+"){
        Litteral *res = *y+*x;
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    }
    else if(op=="-"){
        Litteral *res = *y-*x;
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    }
    else if(op=="*"){
        Litteral *res = *y * *x;
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));

    }
    else if(op=="/"){
        Litteral *res;
        try{
            res = *y / *x;
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }catch(ComputerException c){
            pile->setMessage(c.getInfo());
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
        }
    }
    else if(op=="DIV"){
        if(isEntier(*x) && isEntier(*y)){
            Litteral *res;
            try{
                res = div(*y, *x);
                pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
            }catch(ComputerException c){
                pile->setMessage(c.getInfo());
                pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
                pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            }
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur DIV s'applique sur des opérandes entières");
        }
    }
    else if(op=="MOD"){
        if(isEntier(*x) && isEntier(*y)){
            Litteral *res;
            try{
                res = mod(*y, *x);
                pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
            }catch(ComputerException c){
                pile->setMessage(c.getInfo());
                pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
                pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            }
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur MOD s'applique sur des opérandes entières");
        }
    }
    else if(op=="NEG"){
        Litteral *res = neg(*x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    }
    else if(op=="NUM"){
        if(isRationnel(*x) || isEntier(*x)){
            Litteral *res;
            res = num(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur NUM s'applique sur une opérande rationnelle ou entière");
        }
    }
    else if(op=="DEN"){
        if(isRationnel(*x) || isEntier(*x)){
            Litteral *res;
            res = den(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur NUM s'applique sur une opérande rationnelle ou entière");
        }
    }
    else if(op=="$"){
        if((isEntier(*x) || isReel(*x) || isRationnel(*x)) && (isEntier(*y) || isReel(*y) || isRationnel(*y))){
            Litteral *res = createComplexe(*y, *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur $ s'applique sur des opérandes entières, réelles ou rationnelles");
        }
    }
    else if(op=="RE"){
        Litteral *res = re(*x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    }
    else if(op=="IM"){
        Litteral *res = im(*x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    }
    else if(op=="SIN"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = sin(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur SIN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
    else if(op=="COS"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = cos(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur COS s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
    else if(op=="TAN"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = tan(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur TAN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
    else if(op=="ARCSIN"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = arcSin(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur ARCSIN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
    else if(op=="ARCCOS"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = arcCos(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur ARCCOS s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
    else if(op=="ARCTAN"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = arcTan(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur ARCTAN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
    else if(op=="EXP"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = exp(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur EXP s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
    else if(op=="LN"){
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)){
            Litteral *res = ln(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur LN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
}

void Controleur::applyOperatorLog(const QString& op, const int nbOp){
    Pile *pile = Pile::getInstance();
    if(pile->getStack()->length()<nbOp)
        throw ComputerException("Erreur : $ arguments empilés nécessaires", nbOp);
    Litteral *temp1 = pile->pop();
    Litteral *x;
    Litteral *y;
    Variable *var1 = dynamic_cast<Variable*>(temp1);
    if(var1)
        x = var1->getValue();
    else if(isEntier(*temp1) || isReel(*temp1) || isRationnel(*temp1) || isComplexe(*temp1)){
        x = temp1;
    }
    else{
        pile->push(Litteral::createLitteral(temp1->toString(), typeLitteral(temp1->toString())));
        throw ComputerException("Erreur : Un opérateur logique ne peut pas être appliqué à un programme");
    }

    if(nbOp==2){
        Litteral *temp2 = pile->pop();
        Variable *var2 = dynamic_cast<Variable*>(temp2);
        if(var2)
            y = var2->getValue();
        else if(isEntier(*temp2) || isReel(*temp2) || isRationnel(*temp2) || isComplexe(*temp2)){
            y = temp2;
        }
        else{
            pile->push(Litteral::createLitteral(temp2->toString(), typeLitteral(temp2->toString())));
            pile->push(Litteral::createLitteral(temp1->toString(), typeLitteral(temp1->toString())));
            throw ComputerException("Erreur : Un opérateur logique ne peut pas être appliqué à un programme");
        }
    }

    if(op=="="){
        Litteral *res = (*y == *x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    }
    else if(op=="!="){
        Litteral *res = (*y != *x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    }
    else if(op=="<"){
        if(!isComplexe(*x) && !isComplexe(*y)){
            Litteral *res = (*y < *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    }
    else if(op==">"){
        if(!isComplexe(*x) && !isComplexe(*y)){
            Litteral *res = (*y > *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    }
    else if(op==">="){
        if(!isComplexe(*x) && !isComplexe(*y)){
            Litteral *res1 = (*y > *x);
            Litteral *res2 = (*y == *x);
            Entier *e1 = dynamic_cast<Entier*>(res1);
            Entier *e2 = dynamic_cast<Entier*>(res2);
            Entier *res;
            if(e1->getValue()==1 || e2->getValue()==1)
                res = new Entier(1);
            else
                res = new Entier(0);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    }
    else if(op=="<="){
        if(!isComplexe(*x) && !isComplexe(*y)){
            Litteral *res1 = (*y < *x);
            Litteral *res2 = (*y == *x);
            Entier *e1 = dynamic_cast<Entier*>(res1);
            Entier *e2 = dynamic_cast<Entier*>(res2);
            Entier *res;
            if(e1->getValue()==1 || e2->getValue()==1)
                res = new Entier(1);
            else
                res = new Entier(0);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    }
    else if(op=="AND"){
        if(isEntier(*x) && isEntier(*y)){
            Litteral *res = andF(*y, *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur AND s'applique sur des opérandes entières ou des expressions");
        }
    }
    else if(op=="OR"){
        if(isEntier(*x) && isEntier(*y)){
            Litteral *res = orF(*y, *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        }
        else{
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur OR s'applique sur des opérandes entières ou des expressions");
        }
    }
    else if(op=="NOT"){
        try{
            if(isEntier(*x)){
                Litteral *res = notF(*x);
                pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
            }
            else{
                pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
                throw ComputerException("Erreur : L'opérateur NOT s'applique sur une opérande entière ou une expression");
            }
        }
        catch(ComputerException e){
            pile->setMessage(e.getInfo());
        }
    }
}

void Controleur::applyOperatorPile(const QString& op){
    Pile *pile = Pile::getInstance();
    if(op=="DUP"){
        try{
            Litteral *x = pile->top();
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
        }
        catch(ComputerException e){
            pile->setMessage(e.getInfo());
        }
    }
    else if(op=="DROP"){
        try{
            pile->pop();
        }
        catch(ComputerException e){
            pile->setMessage(e.getInfo());
        }
    }
    else if(op=="SWAP"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
        }
        else
            throw ComputerException("Erreur : 2 arguments empilés nécessaires");
    }
    else if(op=="CLEAR"){
        while(!pile->getStack()->isEmpty())
            pile->pop();
    }
    else if(op=="EVAL"){
        Litteral *x = pile->pop();
        Programme *p = dynamic_cast<Programme*>(x);
        if(p){
            QString temp = p->toString().remove('[').remove(']');
            Controleur::getInstance()->parse(temp);
        }
        else
            throw ComputerException("Erreur : l'argument empilé n'est pas un programme");
    }
    else if(op=="STO"){
        if(pile->getStack()->length()>=2){
            Litteral *x = pile->pop();
            Litteral *y = pile->pop();
            Variable *varTemp = dynamic_cast<Variable*>(x);
            Programme *p2 = dynamic_cast<Programme*>(y);
            QString id = x->toString().remove('\'');

            if(typeLitteral(y->toString())=="Programme"){
                Programme *prog = ProgrammeMap::getInstance()->findProg(id);
                if(prog){
                    qDebug()<<"1";
                    prog->setInstructions(p2->getInstructions());
                    qDebug()<<"2";
                }
                else{
                    qDebug()<<"3";
                    qDebug()<<"4";
                    prog = new Programme(y, id);
                    qDebug()<<"5";
                }
                pile->setMessage("Update : la valeur "+prog->toString()+" est stockée dans "+prog->getId());
            }
            else{
                Variable *var = VariableMap::getInstance()->findVar(x->toString());
                if(var){
                    var->setValue(y);
                }
                else{
                    var = new Variable(y, id);
                }
                pile->setMessage("Update : la valeur "+y->toString()+" est stockée dans "+id);
            }
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
bool isOperatorPile(const QString& a){
    return a=="DUP" || a=="DROP" || a=="SWAP" || a=="LASTOP" || a=="LASTARGS" || a=="CLEAR" || a=="EVAL" || a=="STO";
}

bool isOperator(const QString& a){
    return isOperatorNum(a) || isOperatorLog(a) || isOperatorPile(a);
}
