#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include <typeinfo>
#include "computerexception.h"

class Litteral {
public:
    virtual QString toString() const = 0;
    template<class T>
    static Litteral& createLit(const T);
    Litteral* operator +(Litteral& a);
    Litteral* operator -(Litteral& a);
    Litteral* operator *(Litteral& a);
    Litteral* operator /(Litteral& a);
};

class LitteralNumerique : public Litteral {
public:
    virtual QString toString() const=0;
    virtual bool operator<(const int& a) const=0;
    virtual bool operator>(const int& a) const=0;
};

class Entier : public LitteralNumerique {
private:
    int value;
public:
    Entier(int v): value(v){}
    Entier(const QString& s):value(s.toInt()){};
    int getValue() const;
    QString toString() const;
    Entier& operator= (const Entier& e);
    bool operator<(const int& a) const;
    bool operator>(const int& a) const;
    static Entier* createLit(const int v);
};

class Reel : public LitteralNumerique {
private:
    double value;
public:
    Reel(double v): value(v){}
    Reel(const QString& s):value(s.toDouble()){};
    double getValue() const;
    QString toString() const;
    bool operator<(const int& a) const;
    bool operator>(const int& a) const;
    static Reel* createLit(const double v);
};

class Rationnel : public LitteralNumerique {
private:
    Entier numerateur;
    Entier denominateur;
public:
    Rationnel(int n, int d);
    Rationnel(const QString& s);
    Entier getNumerateur() const;
    Entier getDenominateur() const;
    QString toString() const;
    void simplifier();
    bool operator<(const int& a) const;
    bool operator>(const int& a) const;
    static Rationnel* createLit(const int n, const int d);
};

class Complexe : public Litteral {
    LitteralNumerique* pReelle;
    LitteralNumerique* pImaginaire;
public:
    Complexe(const QString& pRe, const QString& pIm);
    Complexe(LitteralNumerique& pRe, LitteralNumerique& pIm);
    LitteralNumerique* getPRe() const;
    LitteralNumerique* getPIm() const;
    QString toString() const;
};

template<class T>
bool isEntier(T& a);

template<class T>
bool isReel(T& a);

template<class T>
bool isRationnel(T& a);

template<class T>
bool isComplexe(T& a);

//opérateurs
Litteral* div(Litteral& a, Litteral& b);
Litteral* mod(Litteral& a, Litteral& b);
Litteral* neg(Litteral& a);
Litteral* num(Litteral& a);
Litteral* den(Litteral& a);
Litteral* createComplexe(Litteral& a, Litteral& b);
Litteral* re(Litteral& a);
Litteral* im(Litteral& a);


#endif // LITTERAL_H
