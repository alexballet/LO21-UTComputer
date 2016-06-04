#include "controleur.h"
#include <QDebug>
#include <QRegularExpressionMatch>

Controleur* Controleur::instance = nullptr;
QVector<Memento*> Controleur::mementoList;
int Controleur::currentMemento = -1;

void Controleur::parse(const QString& com) {
    if(com == "")
        throw ComputerException("La ligne de commande est vide !");

    Pile* pile = Pile::getInstance();

    if(typeLitteral(com) == "Programme") {
        pile->push(Litteral::createLitteral(com, "Programme"));
        addMementoState(pile->createMemento());
        return;
    }

    if(typeLitteral(com) == "Expression") {
        QString comTemp = com;
        pile->push(Litteral::createLitteral(comTemp.remove('\''), "Expression"));
        addMementoState(pile->createMemento());
        return;
    }

    QStringList words = manualSplit(com);

    foreach (QString word, words) {
        process(word);
    }
}

QStringList Controleur::manualSplit(const QString& com) {
    QStringList words;

    int i;
    QString temp;
    bool stop = false;

    for(i = 0; i < com.length(); i++) {
        if(com.at(i) == ' ') {
            if(temp != "") {
                words.append(temp);
                temp = "";
            }

            while(com.at(i) == ' ' && i != com.length() - 1) { //get to first character or end of string
                i++;
            }

            if(i == com.length() - 1) {
                if(com.at(i) != ' ')
                    temp.append(com.at(i));

                if(temp != "")
                    words.append(temp);

                temp = "";
                stop = true;
            }
        }

        if(!stop) {
            temp.append(com.at(i));

            if(com.at(i) == '[') {
                i++;

                do {
                    temp.append(com.at(i));
                    i++;
                } while(com.at(i) != ']');

                temp.append(com.at(i));
                words.append(temp);
                temp = "";
            }
        }
    }

    if(temp != "")
        words.append(temp);

    return words;
}

void Controleur::process(const QString word) {
    QString type = typeLitteral(word);
    Pile* pile = Pile::getInstance();
    Programme *p = ProgrammeMap::getInstance()->findProg(word);

    if(p) {
        try {
            pile->push(Litteral::createLitteral(word, type));
            return;
        } catch(ComputerException c) {
            pile->setMessage(c.getInfo());
        }
    } else if(isOperator(word)) {
        try {
            applyOperator(word);
        } catch(ComputerException c) {
            pile->setMessage(c.getInfo());
        }

        lastOp = word;
    } else if(type != "Inconnu") {
        try {
            pile->push(Litteral::createLitteral(word, type));
        } catch (ComputerException c) {
            pile->setMessage(c.getInfo());
        }
    } else {
        pile->setMessage("Commande inconnue !");
    }

    if (word != "EVAL") {
        addMementoState(pile->createMemento());
    }
}

void Controleur::addMementoState(Memento* mem) {
    if (currentMemento != mementoList.length() - 1) { //if changing something after undos
        mementoList.remove(currentMemento + 1, mementoList.length() - currentMemento - 1);
    }

    mementoList.append(mem);
    currentMemento++;
}

void Controleur::undo() {
    if (currentMemento == 0) {
        throw ComputerException("On ne peut plus revenir en arriere!");
    }

    Pile* pile = Pile::getInstance();
    pile->reinstateMemento(mementoList[--currentMemento]);
}

void Controleur::redo() {
    if (currentMemento == mementoList.length() - 1) {
        throw ComputerException("On ne peut plus revenir en avant!");
    }

    Pile* pile = Pile::getInstance();
    pile->reinstateMemento(mementoList[++currentMemento]);
}


QString typeLitteral(const QString& lit) {
    if(isProgramme(lit)) {
        return "Programme";
    }

    if(isExpression(lit)) {
        return "Expression";
    } else if(isOperatorNum(lit)) {
        return "OperatorNum";
    } else if(isOperatorLog(lit)) {
        return "OperatorLog";
    } else if(isOperatorPile(lit)) {
        return "OperatorPile";
    } else if(lit.count('$') == 1 || lit.count('i') == 1) {
        return "Complexe";
    } else if(lit.count('.') == 1) {
        return "Reel";
    } else if(lit.count('/') == 1) {
        return "Rationnel";
    } else if(lit == "0" || (lit.toInt() && lit.count('.') == 0 && (lit[0].isDigit() || (lit[0] == '-' && lit[1].isDigit())))) {
        return "Entier";
    } else {
        QRegularExpression re("[A-Z][A-Z0-9]*"); //starts with a capital letter and is followed by letters or numbers
        QRegularExpressionMatch match = re.match(lit);

        if (match.hasMatch() && match.captured(0) == lit) { //if the whole string is matched
            return "Atome";
        }
    }

    return "Inconnu";
}

void Controleur::applyOperatorNum(const QString& op, const int nbOp) {
    Pile *pile = Pile::getInstance();

    if(pile->getLength() < nbOp)
        throw ComputerException("Erreur : $ arguments empilés nécessaires", nbOp);

    Litteral *temp1 = pile->pop();
    Litteral *x;
    Litteral *y;
    Variable *var1 = dynamic_cast<Variable*>(temp1);

    if(var1) {
        x = var1->getValue();
    } else if(isEntier(*temp1) || isReel(*temp1) || isRationnel(*temp1) || isComplexe(*temp1) || isExpression(*temp1)) {
        x = temp1;
    } else {
        pile->push(Litteral::createLitteral(temp1->toString(), typeLitteral(temp1->toString())));
        throw ComputerException("Erreur : Un opérateur numérique ne peut pas être appliqué à un programme ou atome");
    }

    if(nbOp == 2) {
        Litteral *temp2 = pile->pop();
        Variable *var2 = dynamic_cast<Variable*>(temp2);

        if(var2)
            y = var2->getValue();
        else if(isEntier(*temp2) || isReel(*temp2) || isRationnel(*temp2) || isComplexe(*temp2) || isExpression(*temp2)) {
            y = temp2;
        } else {
            pile->push(Litteral::createLitteral(temp2->toString(), typeLitteral(temp2->toString())));
            pile->push(Litteral::createLitteral(temp1->toString(), typeLitteral(temp1->toString())));
            throw ComputerException("Erreur : Un opérateur numérique ne peut pas être appliqué à un programme ou atome");
        }
    }

    if(op == "+") {
        Litteral *res = *y + *x;
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    } else if(op == "-") {
        Litteral *res = *y - *x;
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    } else if(op == "*") {
        Litteral *res = *y **x;
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));

    } else if(op == "/") {
        Litteral *res;

        try {
            res = *y / *x;
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } catch(ComputerException c) {
            pile->setMessage(c.getInfo());
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
        }
    } else if(op == "DIV") {
        if(isEntier(*x) && isEntier(*y)) {
            Litteral *res;

            try {
                res = div(*y, *x);
                pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
            } catch(ComputerException c) {
                pile->setMessage(c.getInfo());
                pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
                pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            }
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur DIV s'applique sur des opérandes entières");
        }
    } else if(op == "MOD") {
        if(isEntier(*x) && isEntier(*y)) {
            Litteral *res;

            try {
                res = mod(*y, *x);
                pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
            } catch(ComputerException c) {
                pile->setMessage(c.getInfo());
                pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
                pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            }
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur MOD s'applique sur des opérandes entières");
        }
    } else if(op == "NEG") {
        Litteral *res = neg(*x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    } else if(op == "NUM") {
        if(isRationnel(*x) || isEntier(*x)) {
            Litteral *res;
            res = num(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur NUM s'applique sur une opérande rationnelle ou entière");
        }
    } else if(op == "DEN") {
        if(isRationnel(*x) || isEntier(*x)) {
            Litteral *res;
            res = den(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur NUM s'applique sur une opérande rationnelle ou entière");
        }
    } else if(op == "$") {
        if((isEntier(*x) || isReel(*x) || isRationnel(*x)) && (isEntier(*y) || isReel(*y) || isRationnel(*y))) {
            Litteral *res = createComplexe(*y, *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur $ s'applique sur des opérandes entières, réelles ou rationnelles");
        }
    } else if(op == "RE") {
        Litteral *res = re(*x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    } else if(op == "IM") {
        Litteral *res = im(*x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    } else if(op == "SIN") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = sin(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur SIN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    } else if(op == "COS") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = cos(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur COS s'applique sur une opérande entière, réelle ou rationnelle");
        }
    } else if(op == "TAN") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = tan(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur TAN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    } else if(op == "ARCSIN") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = arcSin(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur ARCSIN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    } else if(op == "ARCCOS") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = arcCos(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur ARCCOS s'applique sur une opérande entière, réelle ou rationnelle");
        }
    } else if(op == "ARCTAN") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = arcTan(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur ARCTAN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    } else if(op == "EXP") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = exp(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur EXP s'applique sur une opérande entière, réelle ou rationnelle");
        }
    } else if(op == "LN") {
        if(isEntier(*x) || isReel(*x) || isRationnel(*x)) {
            Litteral *res = ln(*x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur LN s'applique sur une opérande entière, réelle ou rationnelle");
        }
    }
}

void Controleur::applyOperatorLog(const QString& op, const int nbOp) {
    Pile *pile = Pile::getInstance();

    if(pile->getLength() < nbOp)
        throw ComputerException("Erreur : $ arguments empilés nécessaires", nbOp);

    Litteral *temp1 = pile->pop();
    Litteral *x;
    Litteral *y;
    Variable *var1 = dynamic_cast<Variable*>(temp1);

    if(var1)
        x = var1->getValue();
    else if(isEntier(*temp1) || isReel(*temp1) || isRationnel(*temp1) || isComplexe(*temp1)) {
        x = temp1;
    } else {
        pile->push(Litteral::createLitteral(temp1->toString().remove('\''), typeLitteral(temp1->toString().remove('\''))));
        throw ComputerException("Erreur : Un opérateur logique ne peut pas être appliqué à un programme");
    }

    if(nbOp == 2) {
        Litteral *temp2 = pile->pop();
        Variable *var2 = dynamic_cast<Variable*>(temp2);

        if(var2)
            y = var2->getValue();
        else if(isEntier(*temp2) || isReel(*temp2) || isRationnel(*temp2) || isComplexe(*temp2)) {
            y = temp2;
        } else {
            pile->push(Litteral::createLitteral(temp2->toString().remove('\''), typeLitteral(temp2->toString().remove('\''))));
            pile->push(Litteral::createLitteral(temp1->toString().remove('\''), typeLitteral(temp1->toString().remove('\''))));
            throw ComputerException("Erreur : Un opérateur logique ne peut pas être appliqué à un programme");
        }
    }

    if(op == "=") {
        Litteral *res = (*y == *x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    } else if(op == "!=") {
        Litteral *res = (*y != *x);
        pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
    } else if(op == "<") {
        if(!isComplexe(*x) && !isComplexe(*y)) {
            Litteral *res = (*y < *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    } else if(op == ">") {
        if(!isComplexe(*x) && !isComplexe(*y)) {
            Litteral *res = (*y > *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    } else if(op == ">=") {
        if(!isComplexe(*x) && !isComplexe(*y)) {
            Litteral *res1 = (*y > *x);
            Litteral *res2 = (*y == *x);
            Entier *e1 = dynamic_cast<Entier*>(res1);
            Entier *e2 = dynamic_cast<Entier*>(res2);
            Entier *res;

            if(e1->getValue() == 1 || e2->getValue() == 1)
                res = new Entier(1);
            else
                res = new Entier(0);

            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    } else if(op == "<=") {
        if(!isComplexe(*x) && !isComplexe(*y)) {
            Litteral *res1 = (*y < *x);
            Litteral *res2 = (*y == *x);
            Entier *e1 = dynamic_cast<Entier*>(res1);
            Entier *e2 = dynamic_cast<Entier*>(res2);
            Entier *res;

            if(e1->getValue() == 1 || e2->getValue() == 1)
                res = new Entier(1);
            else
                res = new Entier(0);

            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : On ne peut pas comparer des nombres complexes");
        }
    } else if(op == "AND") {
        if(isEntier(*x) && isEntier(*y)) {
            Litteral *res = andF(*y, *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur AND s'applique sur des opérandes entières ou des expressions");
        }
    } else if(op == "OR") {
        if(isEntier(*x) && isEntier(*y)) {
            Litteral *res = orF(*y, *x);
            pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
        } else {
            pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
            throw ComputerException("Erreur : L'opérateur OR s'applique sur des opérandes entières ou des expressions");
        }
    } else if(op == "NOT") {
        try {
            if(isEntier(*x)) {
                Litteral *res = notF(*x);
                pile->push(Litteral::createLitteral(res->toString(), typeLitteral(res->toString())));
            } else {
                pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
                throw ComputerException("Erreur : L'opérateur NOT s'applique sur une opérande entière ou une expression");
            }
        } catch(ComputerException e) {
            pile->setMessage(e.getInfo());
        }
    }
}

void Controleur::applyOperatorPile(const QString& op, const int nbOp) {
    Pile *pile = Pile::getInstance();
    Litteral *x;
    Litteral *y;

    if(nbOp != 0) {
        if(pile->getLength() < nbOp)
            throw ComputerException("Erreur : $ arguments empilés nécessaires", nbOp);

        x = pile->pop();

        if(nbOp == 2) {
            y = pile->pop();
        }
    }

    if(op == "DUP") {
        try {
            x = pile->top();
            pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
        } catch(ComputerException e) {
            pile->setMessage(e.getInfo());
        }
    } else if(op == "DROP") {
        try {
            pile->pop();
        } catch(ComputerException e) {
            pile->setMessage(e.getInfo());
        }
    } else if(op == "SWAP") {
        pile->push(Litteral::createLitteral(x->toString(), typeLitteral(x->toString())));
        pile->push(Litteral::createLitteral(y->toString(), typeLitteral(y->toString())));
    } else if(op == "CLEAR") {
        while(!pile->isEmpty())
            pile->pop();
    } else if(op == "EVAL") {
        Expression *e = dynamic_cast<Expression*>(x);
        Programme *pTemp = dynamic_cast<Programme*>(x);

        if(pTemp) {
            QString temp = x->toString();

            if(temp != "") {
                while(temp.at(0) == ' ')
                    temp.remove(0, 1);

                if(temp.at(0) == '[')
                    temp.remove(0, 1);

                while(temp.at(temp.length() - 1) == ' ') {
                    temp.remove(temp.length() - 1, 1);
                }

                if(temp.at(temp.length() - 1) == ']')
                    temp.remove(temp.length() - 1, 1);
            }

            parse(temp);
            return;
        } else if(e) {
            QString temp = e->toString().remove('\'');
            Programme *p = ProgrammeMap::getInstance()->findProg(temp);
            Variable *v = VariableMap::getInstance()->findVar(temp);

            if(p || v) {
                parse(temp);
            } else { //if it's not a variable neither a program => it's an operation like '1+SIN(3-X)'
                QString exp = parseExpression(temp);

                try {
                    parse(exp);
                } catch(ComputerException c) {
                    pile->setMessage(c.getInfo());
                }
            }
        } else {
            pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
            throw ComputerException("Erreur : l'argument empilé n'est pas une expression ou un programme");
        }
    } else if(op == "STO") {
        Programme *p2 = dynamic_cast<Programme*>(y);
        QString id = x->toString().remove('\'');
        Atome *a = dynamic_cast<Atome*>(x);
        if(typeLitteral(y->toString()) == "Programme") {
            QString strToSearch = x->toString().remove('\'');
            Programme *p = dynamic_cast<Programme*>(x);
            if(!p && !a){
                pile->push(Litteral::createLitteral(y->toString().remove('\''), typeLitteral(y->toString().remove('\''))));
                pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
                throw ComputerException("Un programme doit être un atome !");
            }

            if(p)
                strToSearch = p->getId();

            Programme *prog = ProgrammeMap::getInstance()->findProg(strToSearch);

            if(prog) {
                prog->setInstructions(p2->getInstructions());
            } else {
                p2->setId(id);
                ProgrammeMap::getInstance()->insertProg(id, p2);
                prog = p2;
            }

            pile->setMessage("Update : la valeur " + prog->toString() + " est stockée dans " + prog->getId());
        } else {
            QString strToSearch = x->toString().remove('\'');
            Variable *v = dynamic_cast<Variable*>(x);

            if(!v && !a){
                pile->push(Litteral::createLitteral(y->toString().remove('\''), typeLitteral(y->toString().remove('\''))));
                pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
                throw ComputerException("Une variable doit être un atome !");
            }

            if(v) {
                strToSearch = v->getId();
            }

            Variable *var = VariableMap::getInstance()->findVar(strToSearch);

            if(var) {
                var->setValue(y);
            } else {
                var = new Variable(y, id);
            }

            pile->setMessage("Update : la valeur " + y->toString() + " est stockée dans " + strToSearch);
        }
    } else if(op == "FORGET") {
        Programme *p = dynamic_cast<Programme*>(x);
        Variable *v = dynamic_cast<Variable*>(x);

        if(p) {
            QString strToSearch = p->getId();
            Programme *prog = ProgrammeMap::getInstance()->findProg(strToSearch);

            if(prog) {
                ProgrammeMap::getInstance()->deleteProg(strToSearch);
            } else {
                pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
                throw ComputerException("Erreur : l'expression n'est pas un programme enregistré");
            }

            pile->setMessage("Update : le programme " + strToSearch + " est oublié");
        } else if(v) {
            QString strToSearch = v->getId();
            Variable *var = VariableMap::getInstance()->findVar(strToSearch);

            if(var) {
                VariableMap::getInstance()->deleteVar(strToSearch);
            } else {
                pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
                throw ComputerException("Erreur : l'expression n'est pas une variable enregistrée");
            }

            pile->setMessage("Update : la variable " + strToSearch + " est oubliée");
        } else {
            pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
            throw ComputerException("Erreur : la litterale empilée n'est ni un programme, ni une variable");
        }
    } else if(op == "EDIT") {
        Programme *p = dynamic_cast<Programme*>(x);

        if(p) {
            QString strToSearch = p->getId();
            Programme *prog = ProgrammeMap::getInstance()->findProg(strToSearch);

            if(prog) {
                QObject* senderBtn = new QObject();
                senderBtn->setObjectName(prog->getId());
                ProgramEditorWindow *progEditorWindow = new ProgramEditorWindow(senderBtn);
                progEditorWindow->setModal(true);
                progEditorWindow->exec();
            } else {
                pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
                throw ComputerException("Erreur : l'expression n'est pas un programme enregistré");
            }

            pile->setMessage("Update : le programme " + strToSearch + " est modifié");
        } else {
            pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
            throw ComputerException("Erreur : la litterale empilée n'est pas un programme");
        }
    } else if(op == "IFT") {
        Programme *p = dynamic_cast<Programme*>(x);

        if(isEntier(*y) && p) {
            Entier *e = dynamic_cast<Entier*>(y);

            if(e->getValue() != 0) {
                pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
                parse("EVAL");
            }
        } else {
            pile->push(Litteral::createLitteral(y->toString().remove('\''), typeLitteral(y->toString().remove('\''))));
            pile->push(Litteral::createLitteral(x->toString().remove('\''), typeLitteral(x->toString().remove('\''))));
            throw ComputerException("Erreur : l'opérateur IFT s'applique sur un Entier et un Programme");
        }
    } else if(op == "LASTOP") {
        if(lastOp != "" && lastOp != "LASTOP") {
            parse(lastOp);
        } else {
            throw ComputerException("Erreur : Il n'y a pas de dernier opérateur");
        }
    }
}

void Controleur::applyOperator(const QString& op) {
    if(isOperatorLog(op))
        applyOperatorLog(op, opsLog.value(op));
    else if(isOperatorNum(op))
        applyOperatorNum(op, opsNum.value(op));
    else
        applyOperatorPile(op, opsPile.value(op));
}

Controleur* Controleur::getInstance() {
    if(!instance) {
        instance = new Controleur();
    }

    return instance;
}

void Controleur::libererInstance() {
    if (instance)
        delete instance;
}

Controleur::~Controleur() {
    libererInstance();
}

bool isOperatorNum(const QString& a) {
    return opsNum.contains(a);
}
bool isOperatorLog(const QString& a) {
    return opsLog.contains(a);
}
bool isOperatorPile(const QString& a) {
    return opsPile.contains(a);
}

bool isOperator(const QString& a) {
    return isOperatorNum(a) || isOperatorLog(a) || isOperatorPile(a);
}
