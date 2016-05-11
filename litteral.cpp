#include "litteral.h"
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

//Rationnel
Rationnel::Rationnel(int n, int d) :numerateur(n), denominateur(d) {
    if (d == 0) {
        throw ComputerException("Le denominateur ne peut pas etre nul!");
    }
}

Entier Rationnel::getDenominateur() const {
    return denominateur;
}

Entier Rationnel::getNumerateur() const {
    return numerateur;
}

QString Rationnel::toString() const {
    if (numerateur.getValue() == 0) {
        return QString::number(0);
    }
    if (denominateur.getValue() == 1) {
        return numerateur.toString();
    }
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
   numerateur = numerateur.getValue() / g;
   denominateur = denominateur.getValue() / g;

}
