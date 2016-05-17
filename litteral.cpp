#include "litteral.h"
#include "controleur.h"
#include <QDebug>

//Litteral
Litteral* LitteralNumerique::operator +(Litteral& a){
    if(isEntier(*this) && isEntier(a)){
        Entier *op1 = dynamic_cast<Entier*>(this);
        Entier *op2 = dynamic_cast<Entier*>(&a);
        return new Entier(op2->getValue() + op1->getValue());
    }
    else if(isEntier(*this) && isReel(a)){
        Entier *op1 = dynamic_cast<Entier*>(this);
        Reel *op2 = dynamic_cast<Reel*>(&a);
        return new Reel(op2->getValue() + op1->getValue());
    }
    else if(isEntier(*this) && isRationnel(a)){
        Entier *op1 = dynamic_cast<Entier*>(this);
        Rationnel *op2 = dynamic_cast<Rationnel*>(&a);
        return new Rationnel(op1->getValue()*op2->getDenominateur().getValue()+op2->getNumerateur().getValue(), op2->getDenominateur().getValue());
    }
    else if(isEntier(*this) && isComplexe(a)){
        Entier *op1 = dynamic_cast<Entier*>(this);
        Complexe *op2 = dynamic_cast<Complexe*>(&a);
        if(isEntier(*op2->getPRe())){
            Entier *pRe = dynamic_cast<Entier*>(op2->getPRe());
            Entier *pIm = dynamic_cast<Entier*>(op2->getPIm());
            Entier *res = new Entier(pRe->getValue()+op1->getValue());
            return new Complexe(*res, *pIm);
        }
    }
}

Litteral* LitteralNumerique::operator -(Litteral& a){
    if(isEntier(*this) && isEntier(a)){
        Entier *ent1 = dynamic_cast<Entier*>(this);
        Entier *ent2 = dynamic_cast<Entier*>(&a);
        return new Entier(ent2->getValue() - ent1->getValue());
    }
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
