#include "litteral.h"
#include "controleur.h"
#include <QDebug>

//Litteral
Litteral* Litteral::operator +(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier + Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Entier(op2->getValue() + op1->getValue());
    }
    else if(isEntier(*this) && isReel(a)){//Entier + Reel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op2->getValue() + op1->getValue());
    }
    else if(isEntier(*this) && isRationnel(a)){//Entier + Rationnel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getValue()*op2->getDenominateur().getValue()+op2->getNumerateur().getValue(), op2->getDenominateur().getValue());
    }
    else if(isReel(*this) && isEntier(a)){//Reel + Entier
        Reel *op1 = dynamic_cast<Reel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Reel(op2->getValue() + op1->getValue());
    }
    else if(isReel(*this) && isReel(a)){//Reel + Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op2->getValue() + op1->getValue());
    }
    else if(isReel(*this) && isRationnel(a)){//Reel + Rationnel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Reel(op1->getValue()+(double)op2->getNumerateur().getValue()/op2->getDenominateur().getValue());
    }
    else if(isRationnel(*this) && isEntier(a)){//Rationnel + Entier
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Rationnel(op2->getValue()*op1->getDenominateur().getValue()+op1->getNumerateur().getValue(), op1->getDenominateur().getValue());
    }
    else if(isRationnel(*this) && isReel(a)){//Rationnel + Reel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op2->getValue()+(double)op1->getNumerateur().getValue()/op1->getDenominateur().getValue());
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel + Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getNumerateur().getValue()*op2->getDenominateur().getValue()+op2->getNumerateur().getValue()*op1->getDenominateur().getValue(),op1->getDenominateur().getValue()*op2->getDenominateur().getValue());
    }
    else if(isComplexe(a) && (isEntier(*this) || isReel(*this) || isRationnel(*this))){//LitteralNumerique + Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(&a);
        Litteral *op2 = dynamic_cast<Litteral*>(this);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *pRe1 = *op2 + *op1pRe;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm = dynamic_cast<LitteralNumerique*>(op1pIm);
        return new Complexe(*pRe2, *pIm);
    }
    else if(isComplexe(*this) && (isEntier(a) || isReel(a) || isRationnel(a))){//Complexe + LitteralNumerique
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Litteral *op2 = dynamic_cast<Litteral*>(&a);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *pRe1 = *op2 + *op1pRe;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm = dynamic_cast<LitteralNumerique*>(op1pIm);
        return new Complexe(*pRe2, *pIm);
    }
    else if(isComplexe(*this) && isComplexe(a)){//Complexe + Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        Litteral *pRe = *op1->getPRe() + *op2->getPRe();
        Litteral *pIm = *op1->getPIm() + *op2->getPIm();
        LitteralNumerique *resRe = dynamic_cast<LitteralNumerique*>(pRe);
        LitteralNumerique *resIm = dynamic_cast<LitteralNumerique*>(pIm);
        return new Complexe(*resRe, *resIm);
    }
}

Litteral* Litteral::operator -(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier - Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Entier(op1->getValue() - op2->getValue());
    }
    else if(isEntier(*this) && isReel(a)){//Entier - Reel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op1->getValue() - op2->getValue());
    }
    else if(isEntier(*this) && isRationnel(a)){//Entier - Rationnel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getValue()*op2->getDenominateur().getValue()-op2->getNumerateur().getValue(), op2->getDenominateur().getValue());
    }
    else if(isReel(*this) && isEntier(a)){//Reel - Entier
        Reel *op1 = dynamic_cast<Reel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Reel(op1->getValue() - op2->getValue());
    }
    else if(isReel(*this) && isReel(a)){//Reel - Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op1->getValue() - op2->getValue());
    }
    else if(isReel(*this) && isRationnel(a)){//Reel - Rationnel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Reel(op1->getValue()-(double)op2->getNumerateur().getValue()/op2->getDenominateur().getValue());
    }
    else if(isRationnel(*this) && isEntier(a)){//Rationnel - Entier
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Rationnel(op1->getNumerateur().getValue()-op2->getValue()*op1->getDenominateur().getValue(), op1->getDenominateur().getValue());
    }
    else if(isRationnel(*this) && isReel(a)){//Rationnel - Reel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(((double)op1->getNumerateur().getValue()/op1->getDenominateur().getValue())-op2->getValue());
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel - Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getNumerateur().getValue()*op2->getDenominateur().getValue()-op2->getNumerateur().getValue()*op1->getDenominateur().getValue(),op1->getDenominateur().getValue()*op2->getDenominateur().getValue());
    }
    else if(isComplexe(a) && (isEntier(*this) || isReel(*this) || isRationnel(*this))){//LitteralNumerique - Complexe
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        Litteral *op1 = dynamic_cast<Litteral*>(this);
        Litteral *op2pRe = dynamic_cast<Litteral*>(op2->getPRe());
        Litteral *op2pIm = dynamic_cast<Litteral*>(op2->getPIm());
        Litteral *pRe1 = *op1 - *op2pRe;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm = dynamic_cast<LitteralNumerique*>(op2pIm);
        return new Complexe(*pRe2, *pIm);
    }
    else if(isComplexe(*this) && (isEntier(a) || isReel(a) || isRationnel(a))){//Complexe - LitteralNumerique
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Litteral *op2 = dynamic_cast<Litteral*>(&a);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *pRe1 = *op1pRe - *op2;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm = dynamic_cast<LitteralNumerique*>(op1pIm);
        return new Complexe(*pRe2, *pIm);
    }
    else if(isComplexe(*this) && isComplexe(a)){//Complexe - Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        Litteral *pRe = *op1->getPRe() - *op2->getPRe();
        Litteral *pIm = *op1->getPIm() - *op2->getPIm();
        LitteralNumerique *resRe = dynamic_cast<LitteralNumerique*>(pRe);
        LitteralNumerique *resIm = dynamic_cast<LitteralNumerique*>(pIm);
        return new Complexe(*resRe, *resIm);
    }
}

Litteral* Litteral::operator *(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier * Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Entier(op2->getValue() * op1->getValue());
    }
    else if(isEntier(*this) && isReel(a)){//Entier * Reel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op2->getValue() * op1->getValue());
    }
    else if(isEntier(*this) && isRationnel(a)){//Entier * Rationnel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getValue()*op2->getNumerateur().getValue(), op2->getDenominateur().getValue());
    }
    else if(isReel(*this) && isEntier(a)){//Reel * Entier
        Reel *op1 = dynamic_cast<Reel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Reel(op2->getValue() * op1->getValue());
    }
    else if(isReel(*this) && isReel(a)){//Reel * Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op2->getValue() * op1->getValue());
    }
    else if(isReel(*this) && isRationnel(a)){//Reel * Rationnel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Reel(op1->getValue()*((double)op2->getNumerateur().getValue()/op2->getDenominateur().getValue()));
    }
    else if(isRationnel(*this) && isEntier(a)){//Rationnel * Entier
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Rationnel(op2->getValue()*op1->getNumerateur().getValue(), op1->getDenominateur().getValue());
    }
    else if(isRationnel(*this) && isReel(a)){//Rationnel * Reel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op2->getValue()*((double)op1->getNumerateur().getValue()/op1->getDenominateur().getValue()));
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel * Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getNumerateur().getValue()*op2->getNumerateur().getValue(), op1->getDenominateur().getValue()*op2->getDenominateur().getValue());
    }
    else if(isComplexe(a) && (isEntier(*this) || isReel(*this) || isRationnel(*this))){//LitteralNumerique * Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(&a);
        Litteral *op2 = dynamic_cast<Litteral*>(this);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *pRe1 = *op2 * *op1pRe;
        Litteral *pIm1 = *op2 * *op1pIm;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm2 = dynamic_cast<LitteralNumerique*>(pIm1);
        return new Complexe(*pRe2, *pIm2);
    }
    else if(isComplexe(*this) && (isEntier(a) || isReel(a) || isRationnel(a))){//Complexe * LitteralNumerique
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Litteral *op2 = dynamic_cast<Litteral*>(&a);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *pRe1 = *op2 * *op1pRe;
        Litteral *pIm1 = *op2 * *op1pIm;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm2 = dynamic_cast<LitteralNumerique*>(pIm1);
        return new Complexe(*pRe2, *pIm2);
    }
    else if(isComplexe(*this) && isComplexe(a)){//Complexe * Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *op2pRe = dynamic_cast<Litteral*>(op2->getPRe());
        Litteral *op2pIm = dynamic_cast<Litteral*>(op2->getPIm());
        Litteral *pRe1 = *(*op2pIm * *op1pIm) - *(*op2pRe * *op1pRe);
        qDebug()<<(*op2pRe * *op1pRe)->toString();
        qDebug()<<(*op2pIm * *op1pIm)->toString();
        qDebug()<<(*(*op2pRe * *op1pRe) - *(*op2pIm * *op1pIm))->toString();
        Litteral *pIm1 = *(*op1pRe * *op2pIm) + *(*op1pIm * *op2pRe);
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm2 = dynamic_cast<LitteralNumerique*>(pIm1);
        return new Complexe(*pRe2, *pIm2);
    }
}

Litteral* Litteral::operator /(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier / Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op2->getValue()==0)
            throw ComputerException("Erreur : Division par 0 impossible");
        if(op1->getValue() % op2->getValue()==0)
            return new Entier(op1->getValue() / op2->getValue());
        else
            return new Rationnel(op1->getValue(), op2->getValue());
    }
    else if(isEntier(*this) && isReel(a)){//Entier / Reel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op1->getValue() / op2->getValue());
    }
    else if(isEntier(*this) && isRationnel(a)){//Entier / Rationnel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getValue()*op2->getDenominateur().getValue(), op2->getNumerateur().getValue());
    }
    else if(isReel(*this) && isEntier(a)){//Reel / Entier
        Reel *op1 = dynamic_cast<Reel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op2->getValue()==0)
            throw ComputerException("Erreur : Division par 0 impossible");
        return new Reel(op1->getValue() / op2->getValue());
    }
    else if(isReel(*this) && isReel(a)){//Reel / Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op1->getValue() / op2->getValue());
    }
    else if(isReel(*this) && isRationnel(a)){//Reel / Rationnel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Reel(op1->getValue()*((double)op2->getDenominateur().getValue()/op2->getNumerateur().getValue()));
    }
    else if(isRationnel(*this) && isEntier(a)){//Rationnel / Entier
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op2->getValue()==0)
            throw ComputerException("Erreur : Division par 0 impossible");
        return new Rationnel(op1->getNumerateur().getValue(), op1->getDenominateur().getValue()*op2->getValue());
    }
    else if(isRationnel(*this) && isReel(a)){//Rationnel / Reel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(((double)op1->getNumerateur().getValue()/op1->getDenominateur().getValue())/op2->getValue());
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel / Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getNumerateur().getValue()*op2->getDenominateur().getValue(), op1->getDenominateur().getValue()*op2->getNumerateur().getValue());
    }
    else if(isComplexe(a) && (isEntier(*this) || isReel(*this) || isRationnel(*this))){//LitteralNumerique / Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(&a);
        Litteral *op2 = dynamic_cast<Litteral*>(this);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *invOp1PReTemp = *op1pRe / *(*(*op1pRe * *op1pRe) + *(*op1pIm * *op1pIm));
        Entier *e = new Entier(-1);
        Litteral *invOp1PImTemp = *e * *(*op1pIm / *(*(*op1pRe * *op1pRe) + *(*op1pIm * *op1pIm)));
        qDebug()<<(*op1pIm / *(*(*op1pRe * *op1pRe) + *(*op1pIm * *op1pIm)));
        Litteral *pRe1 = *op2 * *invOp1PReTemp;
        Litteral *pIm1 = *op2 * *invOp1PImTemp;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm2 = dynamic_cast<LitteralNumerique*>(pIm1);
        return new Complexe(*pRe2, *pIm2);
    }
    else if(isComplexe(*this) && (isEntier(a) || isReel(a) || isRationnel(a))){//Complexe / LitteralNumerique
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Litteral *op2 = dynamic_cast<Litteral*>(&a);
        if(isEntier(*op2)){
            Entier *op2Test = dynamic_cast<Entier*>(&a);
            if(op2Test->getValue()==0)
                throw ComputerException("Erreur : Division par 0 impossible");
        }
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *pRe1 = *op2 / *op1pRe;
        Litteral *pIm1 = *op2 / *op1pIm;
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm2 = dynamic_cast<LitteralNumerique*>(pIm1);
        return new Complexe(*pRe2, *pIm2);
    }
    else if(isComplexe(*this) && isComplexe(a)){//Complexe / Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *op2pRe = dynamic_cast<Litteral*>(op2->getPRe());
        Litteral *op2pIm = dynamic_cast<Litteral*>(op2->getPIm());
        Litteral *pRe1 = *(*(*op1pRe * *op2pRe) + *(*op1pIm * *op2pIm)) / *(*(*op2pRe * *op2pRe) + *(*op2pIm * *op2pIm));
        qDebug()<<(*op2pRe * *op1pRe)->toString();
        qDebug()<<(*op2pIm * *op1pIm)->toString();
        qDebug()<<(*(*op2pRe * *op1pRe) - *(*op2pIm * *op1pIm))->toString();
        Litteral *pIm1 = *(*(*op1pIm * *op2pRe) - *(*op1pRe * *op2pIm)) / *(*(*op2pRe * *op2pRe) + *(*op2pIm * *op2pIm));
        LitteralNumerique *pRe2 = dynamic_cast<LitteralNumerique*>(pRe1);
        LitteralNumerique *pIm2 = dynamic_cast<LitteralNumerique*>(pIm1);
        return new Complexe(*pRe2, *pIm2);
    }
}

Litteral* Litteral::operator ==(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier = Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        qDebug()<<"bli";
        if(op1->getValue()==op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isReel(*this) && isReel(a)){//Reel = Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        if(op1->getValue()==op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel = Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        double res2 = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(res1==res2)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isComplexe(*this) && isComplexe(a)){//Complexe = Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *op2pRe = dynamic_cast<Litteral*>(op2->getPRe());
        Litteral *op2pIm = dynamic_cast<Litteral*>(op2->getPIm());
        Litteral *t1Temp = (*op1pRe == *op2pRe);
        Litteral *t2Temp = (*op1pIm == *op2pIm);
        Entier *t1 = dynamic_cast<Entier*>(t1Temp);
        Entier *t2 = dynamic_cast<Entier*>(t2Temp);
        if(t1->getValue() && t2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else
        return new Entier(0);
}

Litteral* Litteral::operator !=(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier != Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op1->getValue()!=op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isReel(*this) && isReel(a)){//Reel != Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        if(op1->getValue()!=op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel != Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        double res2 = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(res1!=res2)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isComplexe(*this) && isComplexe(a)){//Complexe != Complexe
        Complexe *op1 = dynamic_cast<Complexe*>(this);
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        Litteral *op1pRe = dynamic_cast<Litteral*>(op1->getPRe());
        Litteral *op1pIm = dynamic_cast<Litteral*>(op1->getPIm());
        Litteral *op2pRe = dynamic_cast<Litteral*>(op2->getPRe());
        Litteral *op2pIm = dynamic_cast<Litteral*>(op2->getPIm());
        Litteral *t1Temp = (*op1pRe != *op2pRe);
        Litteral *t2Temp = (*op1pIm != *op2pIm);
        Entier *t1 = dynamic_cast<Entier*>(t1Temp);
        Entier *t2 = dynamic_cast<Entier*>(t2Temp);
        if(t1->getValue() || t2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else
        return new Entier(0);
}

Litteral* Litteral::operator <(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier < Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op1->getValue()<op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isEntier(*this) && isReel(a)){//Entier < Reel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        if(op1->getValue()<op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isEntier(*this) && isRationnel(a)){//Entier < Rationnel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double op2Res = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(op1->getValue()<op2Res)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isReel(*this) && isEntier(a)){//Reel < Entier
        Reel *op1 = dynamic_cast<Reel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op1->getValue()<op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isReel(*this) && isReel(a)){//Reel < Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        if(op1->getValue()<op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isReel(*this) && isRationnel(a)){//Reel < Rationnel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double op2Res = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(op1->getValue()<op2Res)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isEntier(a)){//Rationnel < Entier
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        if(res1<op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isReel(a)){//Rationnel < Reel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        if(res1<op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel < Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        double res2 = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(res1<res2)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else
        return new Entier(0);
}

Litteral* Litteral::operator >(Litteral& a){
    if(isEntier(*this) && isEntier(a)){//Entier >= Entier
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op1->getValue()>op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isEntier(*this) && isReel(a)){//Entier > Reel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        if(op1->getValue()>op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isEntier(*this) && isRationnel(a)){//Entier > Rationnel
        Entier *op1 = dynamic_cast<Entier*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double op2Res = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(op1->getValue()>op2Res)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isReel(*this) && isEntier(a)){//Reel > Entier
        Reel *op1 = dynamic_cast<Reel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        if(op1->getValue()>op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isReel(*this) && isReel(a)){//Reel > Reel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        if(op1->getValue()>op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    if(isReel(*this) && isRationnel(a)){//Reel > Rationnel
        Reel *op1 = dynamic_cast<Reel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double op2Res = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(op1->getValue()>op2Res)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isEntier(a)){//Rationnel > Entier
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        if(res1>op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isReel(a)){//Rationnel > Reel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        if(res1>op2->getValue())
            return new Entier(1);
        else
            return new Entier(0);
    }
    else if(isRationnel(*this) && isRationnel(a)){//Rationnel > Rationnel
        Rationnel *op1 = dynamic_cast<Rationnel*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        double res1 = (double)op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
        double res2 = (double)op2->getNumerateur().getValue() / op2->getDenominateur().getValue();
        if(res1>res2)
            return new Entier(1);
        else
            return new Entier(0);
    }
    else
        return new Entier(0);
}

Litteral* div(Litteral& a, Litteral& b){
    Entier *op1 = dynamic_cast<Entier*>(&a);
    Entier *op2 = dynamic_cast<Entier*>(&b);
    if(op2->getValue()==0)
        throw ComputerException("Erreur : Division par 0 impossible");
    return new Entier(op1->getValue() / op2->getValue());
}

Litteral* mod(Litteral& a, Litteral& b){
    Entier *op1 = dynamic_cast<Entier*>(&a);
    Entier *op2 = dynamic_cast<Entier*>(&b);
    if(op2->getValue()==0)
        throw ComputerException("Erreur : Division par 0 impossible");
    return new Entier(op1->getValue() % op2->getValue());
}

Litteral* neg(Litteral& a){
    Entier *op1 = new Entier(-1);
    return *op1 * a;
}

Litteral* num(Litteral& a){
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        Entier *res = new Entier(op1->getNumerateur().getValue());
        return res;
    }
    else
        return &a;
}

Litteral* den(Litteral& a){
    Entier *res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res= new Entier(op1->getDenominateur().getValue());
    }
    else{
        res = new Entier(1);
    }
    return res;
}

Litteral* createComplexe(Litteral& a, Litteral& b){
    LitteralNumerique *op1 = dynamic_cast<LitteralNumerique*>(&a);
    LitteralNumerique *op2 = dynamic_cast<LitteralNumerique*>(&b);
    return new Complexe(*op1, *op2);
}

Litteral* re(Litteral& a){
    if(isComplexe(a)){
        Complexe *op1 = dynamic_cast<Complexe*>(&a);
        return op1->getPRe();
    }
    else
        return &a;
}

Litteral* im(Litteral& a){
    if(isComplexe(a)){
        Complexe *op1 = dynamic_cast<Complexe*>(&a);
        return op1->getPIm();
    }
    else{
        Entier *res = new Entier(0);
        return res;
    }
}

Litteral* sin(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    return new Reel(qSin(res));
}

Litteral* cos(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    return new Reel(qCos(res));
}

Litteral* tan(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    return new Reel(qTan(res));
}

Litteral* arcSin(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    return new Reel(qAsin(res));
}

Litteral* arcCos(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    return new Reel(qAcos(res));
}

Litteral* arcTan(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    return new Reel(qAtan(res));
}

Litteral* exp(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    return new Reel(qExp(res));
}

Litteral* ln(Litteral& a){
    double res;
    if(isRationnel(a)){
        Rationnel *op1 = dynamic_cast<Rationnel*>(&a);
        res = op1->getNumerateur().getValue() / op1->getDenominateur().getValue();
    }
    else if(isReel(a)){
        Reel *op1 = dynamic_cast<Reel*>(&a);
        res = op1->getValue();
    }
    else{
        Entier *op1 = dynamic_cast<Entier*>(&a);
        res = op1->getValue();
    }
    if(res<=0)
        throw ComputerException("Erreur : La fonction LN est définie sur ]0;+infini[");
    return new Reel(qLn(res));
}

Litteral* andF(Litteral& a, Litteral& b){
    Entier *op1 = dynamic_cast<Entier*>(&a);
    Entier *op2 = dynamic_cast<Entier*>(&b);
    if(op1->getValue()!=0 && op2->getValue()!=0)
        return new Entier(1);
    else
        return new Entier(0);
}

Litteral* orF(Litteral& a, Litteral& b){
    Entier *op1 = dynamic_cast<Entier*>(&a);
    Entier *op2 = dynamic_cast<Entier*>(&b);
    if(op1->getValue()!=0 || op2->getValue()!=0)
        return new Entier(1);
    else
        return new Entier(0);
}

Litteral* notF(Litteral& a){
    Entier *op1 = dynamic_cast<Entier*>(&a);
    if(op1->getValue()==0)
        return new Entier(1);
    else
        return new Entier(0);
}

//Entier
int Entier::getValue() const {
    return value;
}

QString Entier::toString() const {
    return QString::number(value);
}

Entier* Entier::createLit(const int v){
    return new Entier(v);
}

bool Entier::operator<(const int& a) const{
    return value<a;
}

bool Entier::operator>(const int& a) const{
    return value>a;
}

//Reel
double Reel::getValue() const {
    return value;
}

Entier& Entier::operator= (const Entier& e) {
    value = e.value;
    return *this;
}

QString Reel::toString() const {
    return QString::number(value);
}

Reel* Reel::createLit(const double v){
    return new Reel(v);
}

bool Reel::operator<(const int& a) const{
    return value<a;
}

bool Reel::operator>(const int& a) const{
    return value>a;
}

//Rationnel
Rationnel::Rationnel(int n, int d) :numerateur(n), denominateur(d) {
    if (d == 0) {
        throw ComputerException("Le denominateur ne peut pas etre nul!");
    }
    simplifier();
}

Rationnel::Rationnel(const QString& s):numerateur(s.split('/').at(0).toInt()), denominateur(s.split('/').at(1).toInt()){
    if (s.split('/').at(1) == "0") {
        throw ComputerException("Le denominateur ne peut pas etre nul!");
    }
    simplifier();
}

Entier Rationnel::getDenominateur() const {
    return denominateur;
}

Entier Rationnel::getNumerateur() const {
    return numerateur;
}

bool Rationnel::operator<(const int& a) const{
    return (numerateur.getValue()/denominateur.getValue())<a;
}

bool Rationnel::operator>(const int& a) const{
    return ((double)numerateur.getValue()/denominateur.getValue())>a;
}

QString Rationnel::toString() const {
    return numerateur.toString() + "/" + denominateur.toString();
}

int gcd (int n1, int n2) { //computes the GCD using Euclidean algorithm
    int t;
    while (n2 != 0) {
        t = n1;
        n1 = n2;
        n2 = t % n2;
    }
    return n1;
}


void Rationnel::simplifier() {
   int g = gcd(numerateur.getValue(), denominateur.getValue());
   numerateur = numerateur.getValue() / qFabs(g);
   denominateur = denominateur.getValue() / qFabs(g);
   if(denominateur.getValue() < 0){
       numerateur = numerateur.getValue()*(-1);
       denominateur = denominateur.getValue()*(-1);
   }
}

//Complexe
Complexe::Complexe(const QString& pRe, const QString& pIm){
    if(typeLitteral(pRe)=="Entier")
        pReelle = new Entier(pRe);
    else if(typeLitteral(pRe)=="Reel")
        pReelle = new Reel(pRe);
    else if(typeLitteral(pRe)=="Rationnel"){
        Rationnel* rat = new Rationnel(pRe);
        rat->simplifier();
        if(rat->getDenominateur().getValue() == 1 || rat->getNumerateur().getValue() ==0){
            Entier* e = new Entier(rat->getNumerateur().getValue());
            pReelle = e;
        }
        else{
            pReelle = rat;
        }
    }

    if(typeLitteral(pIm)=="Entier")
        pImaginaire = new Entier(pIm);
    else if(typeLitteral(pIm)=="Reel")
        pImaginaire = new Reel(pIm);
    else if(typeLitteral(pIm)=="Rationnel"){
        Rationnel* rat = new Rationnel(pIm);
        rat->simplifier();
        if(rat->getDenominateur().getValue() == 1 || rat->getNumerateur().getValue() ==0){
            Entier* e = new Entier(rat->getNumerateur().getValue());
            pImaginaire = e;
        }
        else{
            pImaginaire = rat;
        }
    }
}

Complexe::Complexe(LitteralNumerique& pRe, LitteralNumerique& pIm){
    if(isEntier(pRe))
        pReelle = new Entier(pRe.toString());
    else if(isReel(pRe))
        pReelle = new Reel(pRe.toString());
    else if(isRationnel(pRe)){
        Rationnel* rat = new Rationnel(pRe.toString());
        rat->simplifier();
        if(rat->getDenominateur().getValue() == 1 || rat->getNumerateur().getValue() ==0){
            Entier* e = new Entier(rat->getNumerateur().getValue());
            pReelle = e;
        }
        else{
            pReelle = rat;
        }
    }

    if(isEntier(pIm))
        pImaginaire = new Entier(pIm.toString());
    else if(isReel(pIm))
        pImaginaire = new Reel(pIm.toString());
    else if(isRationnel(pIm)){
        Rationnel* rat = new Rationnel(pIm.toString());
        rat->simplifier();
        if(rat->getDenominateur().getValue() == 1 || rat->getNumerateur().getValue() ==0){
            Entier* e = new Entier(rat->getNumerateur().getValue());
            pImaginaire = e;
        }
        else{
            pImaginaire = rat;
        }
    }
}

LitteralNumerique* Complexe::getPRe() const{
    return pReelle;
}

LitteralNumerique* Complexe::getPIm() const{
    return pImaginaire;
}

QString Complexe::toString() const{
    QString im = getPIm()->toString();
    if(*getPIm()>0){
        if(im=="1") im="";
        return getPRe()->toString() + " + " + im + "i";
    }
    else{
        im.remove('-');
        if(im=="1") im="";
        return getPRe()->toString() + " - " + im + "i";
    }
}

template<class T>
bool isEntier(T& a){
    Entier *e = dynamic_cast<Entier*>(&a);
    return e!=nullptr;
}

template<class T>
bool isReel(T& a){
    Reel *r = dynamic_cast<Reel*>(&a);
    return r!=nullptr;
}

template<class T>
bool isRationnel(T& a){
    Rationnel *r = dynamic_cast<Rationnel*>(&a);
    return r!=nullptr;
}

template<class T>
bool isComplexe(T& a){
    Complexe *c = dynamic_cast<Complexe*>(&a);
    return c!=nullptr;
}
