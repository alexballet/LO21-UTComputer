#include "litteral.h"
#include "controleur.h"
#include <QDebug>

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
Rationnel::Rationnel(int n, int d) :numerateur(Entier(n)), denominateur(Entier(d)) {
    if (d == 0) {
        throw ComputerException("Le denominateur ne peut pas etre nul!");
    }
    simplifier();
}

Rationnel::Rationnel(const QString& s):numerateur(Entier(s.split('/').at(0).toInt())), denominateur(Entier(s.split('/').at(1).toInt())){
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
   if(denominateur.getValue()<0){
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
