#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>

class Litteral {
private:

public:
    virtual QString toString() const = 0;


};

class LitteralNumerique : public Litteral {
public:

};

class Entier : public LitteralNumerique {
private:
    int value;
public:
    Entier(int v): value(v){}
    int getValue() const;
    QString toString() const;
};

class Reel : public LitteralNumerique {
private:
    double value;
public:
    Reel(double v): value(v){}
    double getValue() const;
    QString toString() const;
};

#endif // LITTERAL_H
