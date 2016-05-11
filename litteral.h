#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include "computerexception.h"

class Litteral {
private:

public:
    virtual QString toString() const = 0;
    template<class T>
    static Litteral& createLit(const T);
};

class LitteralNumerique : public Litteral {
public:
    virtual QString toString() const=0;
};

class Entier : public LitteralNumerique {
private:
    int value;
public:
    Entier(int v): value(v){}
    int getValue() const;
    QString toString() const;
    Entier& operator= (const Entier& e);
    static Entier* createLit(const int v);
};

class Reel : public LitteralNumerique {
private:
    double value;
public:
    Reel(double v): value(v){}
    double getValue() const;
    QString toString() const;
    static Reel* createLit(const double v);
};

class Rationnel : public LitteralNumerique {
private:
    Entier numerateur;
    Entier denominateur;
public:
    Rationnel(int n, int d);
    Entier getNumerateur() const;
    Entier getDenominateur() const;
    QString toString() const;
    void simplifier();
    static Rationnel* createLit(const int n, const int d);
};


#endif // LITTERAL_H
