#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>

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

#endif // LITTERAL_H
