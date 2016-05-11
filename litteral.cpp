#include "litteral.h"

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

int Rationnel::getDenominateur() const {
    return denominateur;
}

int Rationnel::getNumerateur() const {
    return numerateur;
}

QString Rationnel::toString() const {
    if (numerateur == 0) {
        return QString::number(0);
    }
    if (denominateur == 1) {
        return QString::number(numerateur);
    }
    return QString::number(numerateur) + "/" + QString::number(denominateur);
}

void Rationnel::simplifier() {
    if ((numerateur % denominateur) == 0) {
        numerateur = numerateur % denominateur;
        denominateur = 1;
    }

}
