#include "litteral.h"

int Entier::getValue() const {
    return value;
}

double Reel::getValue() const {
    return value;
}

QString Entier::toString() const {
    return QString::number(value);
}

QString Reel::toString() const {
    return QString::number(value);
}
