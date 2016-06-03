#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include <QStack>
#include <typeinfo>
#include "computerexception.h"
/*!
 * \brief The abstract Litteral class is the parent class (and factory) of LitteralNumerique, Complexe, Atome, Variable and Programme. It declares all the virtual operators and the toString() method.
 */
class Litteral {
public:
    /*!
     * \brief Factory method used to instanciate any type of Litteral.
     * This method parses the value parameter depending on the type parameter, then initializes a new Litteral with the parsed value.
     * \param value - the value of the Litteral to instanciate.
     * \param type - the type of the Litteral to instanciate.
     * \return Return a pointer to the instanciated Litteral object.
     */
    static Litteral* createLitteral(const QString& value, const QString& type);
    /*!
     * \brief Pure virtual method to be defined in the child classes.
     * Used to display any Litteral as a QString into the Pile.
     */
    virtual QString toString() const = 0;
    Litteral* operator +(Litteral& a);
    Litteral* operator -(Litteral& a);
    Litteral* operator *(Litteral& a);
    Litteral* operator /(Litteral& a);
    Litteral* operator ==(Litteral& a);
    Litteral* operator !=(Litteral& a);
    Litteral* operator <(Litteral& a);
    Litteral* operator >(Litteral& a);
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

template<class T>
bool isExpression(T& a);

template<class T>
bool isAtome(T& a);

//opérateurs numériques
Litteral* div(Litteral& a, Litteral& b);
Litteral* mod(Litteral& a, Litteral& b);
Litteral* neg(Litteral& a);
Litteral* num(Litteral& a);
Litteral* den(Litteral& a);
Litteral* createComplexe(Litteral& a, Litteral& b);
Litteral* re(Litteral& a);
Litteral* im(Litteral& a);
Litteral* sin(Litteral& a);
Litteral* cos(Litteral& a);
Litteral* tan(Litteral& a);
Litteral* arcSin(Litteral& a);
Litteral* arcCos(Litteral& a);
Litteral* arcTan(Litteral& a);
Litteral* exp(Litteral& a);
Litteral* ln(Litteral& a);

//opérateurs logiques
Litteral* andF(Litteral& a, Litteral& b);
Litteral* orF(Litteral& a, Litteral& b);
Litteral* notF(Litteral& a);

#endif // LITTERAL_H
