#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include <QStack>
#include <typeinfo>
#include "computerexception.h"
/*!
 * \brief The abstract Litteral class is the parent class (and factory) of LitteralNumerique, Complexe, Atome, Variable and Programme.
 *
 * It declares all the virtual operators and the toString() method.
 */
class Litteral {
  public:
    /*!
     * \brief Factory method used to instanciate any type of Litteral.
     *
     * This method parses the value parameter depending on the type parameter, then initializes a new Litteral with the parsed value.
     * \param value - the value of the Litteral to instanciate.
     * \param type - the type of the Litteral to instanciate.
     * \return Return a pointer to the instanciated Litteral object.
     */
    static Litteral* createLitteral(const QString& value, const QString& type);
    /*!
     * \brief Pure virtual method to be defined in the child classes.
     *
     * Used to display any Litteral as a QString into the Pile.
     */
    virtual QString toString() const = 0;
    /*!
     * \brief Method to sum Litteral objects.
     * \param a - Litteral to sum to the current object.
     * \return Returns the sum of the two Litteral objects.
     */
    Litteral* operator +(Litteral& a);
    /*!
     * \brief Method to substract Litteral objects.
     * \param a - Litteral to substract to the current object.
     * \return Returns the substraction of the two Litteral objects : this - a
     */
    Litteral* operator -(Litteral& a);
    /*!
     * \brief Method to multiply Litteral objects.
     * \param a - Litteral to multiply to the current object.
     * \return Returns the multiplication of the two Litteral objects.
     */
    Litteral* operator *(Litteral& a);
    /*!
     * \brief Method to divide Litteral objects.
     * \param a - Divisor
     * \return Returns the division of the two Litteral objects : this / a;
     */
    Litteral* operator /(Litteral& a);
    /*!
     * \brief Method to check if two Litteral objects are equal to each other.
     * \param a - Litteral to compare to the current object.
     * \return Returns true if the Litteral objects are equal, false if they're different.
     */
    bool operator ==(Litteral& a);
    /*!
     * \brief Method to check if two Litteral objects are different to each other.
     * \param a - Litteral to compare to the current object.
     * \return Returns true if the Litteral objects are different, false if they're equal.
     */
    bool operator !=(Litteral& a);
    /*!
     * \brief Method to compare two Litteral objects.
     * \param a - Litteral to compare to the current object.
     * \return Returns true if this < a are equal, false if this > a.
     */
    bool operator <(Litteral& a);
    /*!
     * \brief Method to compare two Litteral objects.
     * \param a - Litteral to compare to the current object.
     * \return Returns true if this > a are equal, false if this < a.
     */
    bool operator >(Litteral& a);
};
/*!
 * \brief The abstract LitteralNumerique class is the parent class of Entier, Reel and Rationnel.
 */
class LitteralNumerique : public Litteral {
  public:
    virtual QString toString() const = 0;
    virtual bool operator<(const int& a) const = 0;
    virtual bool operator>(const int& a) const = 0;
};
/*!
 * \brief The Entier class contains an integer value.
 */
class Entier : public LitteralNumerique {
  private:
    /*!
     * \brief Value of the Entier object
     */
    int value;
  public:
    /*!
     * \brief Constructor of Entier.
     * \param v - initializes the value attribute.
     */
    Entier(int v): value(v) {}
    /*!
     * \brief Override of the constructor of Entier.
     *
     * Used when manipulating QStrings
     * \param s - initializes the value attribute.
     */
    Entier(const QString& s): value(s.toInt()) {}
    /*!
     * \brief Accessor of the value attribute.
     * \return Returns the value attribute.
     */
    int getValue() const;
    /*!
     * \brief Method used to display the value attribute in the Pile instance.
     * \return Returns a QString conversion of the value attribute.
     */
    QString toString() const;
    bool operator<(const int& a) const;
    bool operator>(const int& a) const;
};
/*!
 * \brief The Reel class contains a double value.
 */
class Reel : public LitteralNumerique {
  private:
    /*!
     * \brief Value of the Reel object
     */
    double value;
  public:
    /*!
     * \brief Constructor of Reel.
     * \param v - initializes the value attribute.
     */
    Reel(double v): value(v) {}
    /*!
     * \brief Override of the constructor of Reel.
     *
     * Used when manipulating QStrings
     * \param s - initializes the value attribute.
     */
    Reel(const QString& s): value(s.toDouble()) {}
    /*!
     * \brief Accessor of the value attribute.
     * \return Returns the value attribute.
     */
    double getValue() const;
    /*!
     * \brief Method used to display the value attribute in the Pile instance.
     * \return Returns a QString conversion of the value attribute.
     */
    QString toString() const;
    bool operator<(const int& a) const;
    bool operator>(const int& a) const;
};
/*!
 * \brief The Rationnel class contains two Entier objects : a numerator and a denominator. It is used to store Rationnal numbers as a fracion.
 */
class Rationnel : public LitteralNumerique {
  private:
    /*!
     * \brief Numerator of the Rationnel object
     */
    Entier numerateur;
    /*!
     * \brief Denomminator of the Rationnel object
     */
    Entier denominateur;
    /*!
     * \brief Method used to simplify the fraction of a Rationnal object. It is called within the constructor of Rationnel.
     *
     * If the numerator is 0, it creates a new Entier object initialized with 0. If the denominator is 1, it creates a new Entier object initialized with the numerator value.
     * If the fraction can be simplified, it simplifies it. E.g : 4/2 -> 2 or 3/6 -> 1/2
     */
    void simplifier();
  public:
    /*!
     * \brief Constructor of Rationnel.
     *
     * Sets the fraction by initializing both the numerator and denominator attributes.
     * \param n - Initializes the numerator attribute.
     * \param d - Initializes the denominator attribute.
     */
    Rationnel(int n, int d);
    /*!
     * \brief Override of the constructor of Rationnel.
     *
     * Used when manipulating QStrings. The QString is parsed ans splited at the '/' character to isolate the numerateur and denominateur attributes.
     * \param s - QString to be parsed
     */
    Rationnel(const QString& s);
    /*!
     * \brief Accessor of the numerateur attribute.
     * \return Returns the numerateur attribute.
     */
    Entier getNumerateur() const;
    /*!
     * \brief Accessor of the denominateur attribute.
     * \return Returns the denominateur attribute.
     */
    Entier getDenominateur() const;
    /*!
     * \brief Method used to display the fraction in the Pile instance.
     * \return Returns a QString composed of both the numerateur and denominateur attributes. E.g : "numerateur/denominateur"
     */
    QString toString() const;
    bool operator<(const int& a) const;
    bool operator>(const int& a) const;
};
/*!
 * \brief The Complexe class is used to represent a complex value. It stores 2 LitteralNumerique objects (Entier, Reel or Rationnel).
 */
class Complexe : public Litteral {
    /*!
     * \brief Real part of the Complexe object.
     *
     * Pointer to an Entier, Reel or Rationnel object.
     */
    LitteralNumerique* pReelle;
    /*!
     * \brief Imaginary part of the Complexe object.
     *
     * Pointer to an Entier, Reel or Rationnel object.
     */
    LitteralNumerique* pImaginaire;
  public:
    /*!
     * \brief Constructor of Complexe.
     *
     * Sets the complex number by initializing both the real part and imaginary part attributes.
     * \param pRe - Initializes the real part attribute.
     * \param pIm - Initializes the imaginary part attribute.
     */
    Complexe(LitteralNumerique& pRe, LitteralNumerique& pIm);
    /*!
     * \brief Override of the constructor of Complexe.
     *
     * Used when manipulating QStrings
     * \param pRe - Initializes the real part attribute, calling the overrided constructors of the different LitteralNumerique objects.
     * \param pIm - Initializes the imaginary part attribute, calling the overrided constructors of the different LitteralNumerique objects.
     */
    Complexe(const QString& pRe, const QString& pIm);
    /*!
     * \brief Accessor of the real part of the Complexe object.
     * \return Returns the pReelle attribute.
     */
    LitteralNumerique* getPRe() const;
    /*!
     * \brief Accessor of the imaginary part of the Complexe object.
     * \return Returns the pImaginaire attribute.
     */
    LitteralNumerique* getPIm() const;
    /*!
     * \brief Method used to display the Complexe object in the Pile instance.
     * \return Returns a QString composed of both the pReelle and pImaginaire attributes. E.g : "pReelle + pImaginaire i"
     */
    QString toString() const;
};

template<class T>
/*!
 * \brief Function that checks whether the a parameter is an Entier object, using a dynamic_cast.
 * \param a - object to cast
 * \return Returns true with the cast worked, false if it didn't.
 */
bool isEntier(T& a);

template<class T>
/*!
 * \brief Function that checks whether the a parameter is an Reel object, using a dynamic_cast.
 * \param a - object to cast
 * \return Returns true with the cast worked, false if it didn't.
 */
bool isReel(T& a);

template<class T>
/*!
 * \brief Function that checks whether the a parameter is an Rationnel object, using a dynamic_cast.
 * \param a - object to cast
 * \return Returns true with the cast worked, false if it didn't.
 */
bool isRationnel(T& a);

template<class T>
/*!
 * \brief Function that checks whether the a parameter is an Complexe object, using a dynamic_cast.
 * \param a - object to cast
 * \return Returns true with the cast worked, false if it didn't.
 */
bool isComplexe(T& a);

template<class T>
/*!
 * \brief Function that checks whether the a parameter is an Expression object, using a dynamic_cast.
 * \param a - object to cast
 * \return Returns true with the cast worked, false if it didn't.
 */
bool isExpression(T& a);

//opérateurs numériques
/*!
 * \brief Integer division operator
 *
 * Can be used between Entier objects only. Otherwise, throws a ComputerException.
 * \param a - Object to be divided
 * \param b - Divisor object
 * \return Returns the result of the Integer division between a and b : a div b.
 */
Litteral* div(Litteral& a, Litteral& b);
/*!
 * \brief Modulo operator
 *
 * Can be used between Entier objects only. Otherwise, throws a ComputerException.
 * \param a - Object to be divided
 * \param b - Divisor object
 * \return Returns the rest of the division between a and b : a mod b.
 */
Litteral* mod(Litteral& a, Litteral& b);
/*!
 * \brief Opposite operator
 *
 * Can be used on any LitteralNumerique or Complexe object.
 * \param a - Object on which the operator is applied.
 * \return Returns the opposite object of a. E.g : neg 3 -> -3 ; neg 5 - 4i -> -5 + 4i
 */
Litteral* neg(Litteral& a);
/*!
 * \brief Numerator operator
 *
 * Can only be used on a Rationnel object or an Entier object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return If the a parameter is a Rationnel object, it returns its numerateur attribute. If it's an Entier object, it returns the Entier object.
 */
Litteral* num(Litteral& a);
/*!
 * \brief Denominator operator
 *
 * Can only be used on a Rationnel object or an Entier object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return If the a parameter is a Rationnel object, it returns its denominateur attribute. If it's an Entier object, it returns a new Entier object initialized with 1.
 */
Litteral* den(Litteral& a);
/*!
 * \brief createComplexe operator
 *
 * Constructs a Complexe object from two LitteralNumerique objects. Called using the '$' operator on the UTComputer interface.
 * \param a - Object to initialize the pReelle attribute with.
 * \param b - Object to initialize the pImaginaire attribute with.
 * \return Returns a new Complexe
 */
Litteral* createComplexe(Litteral& a, Litteral& b);
/*!
 * \brief Real part operator
 *
 * Can be used on any LitteralNumerique or Complexe object.
 * \param a - Object on which the operator is applied.
 * \return If the a parameter is a Complexe object, it returns its pReelle attribute. Otherwise, it returns the object.
 */
Litteral* re(Litteral& a);
/*!
 * \brief Imaginary part operator
 *
 * Can be used on any LitteralNumerique or Complexe object.
 * \param a - Object on which the operator is applied.
 * \return If the a parameter is a Complexe object, it returns its pImaginaire attribute. Otherwise, it returns a new Entier initialized with 0.
 */
Litteral* im(Litteral& a);
/*!
 * \brief Sinus operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the sinus value, in radian, of the LitteralNumerique object.
 */
Litteral* sin(Litteral& a);
/*!
 * \brief Cosinus operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the cosinus value, in radian, of the LitteralNumerique object.
 */
Litteral* cos(Litteral& a);
/*!
 * \brief Tangent operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the tangent value, in radian, of the LitteralNumerique object.
 */
Litteral* tan(Litteral& a);
/*!
 * \brief Arcsin operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the arcsin value, in radian, of the LitteralNumerique object.
 */
Litteral* arcSin(Litteral& a);
/*!
 * \brief Arccos operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the arccos value, in radian, of the LitteralNumerique object.
 */
Litteral* arcCos(Litteral& a);
/*!
 * \brief Arctan operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the arctan value, in radian, of the LitteralNumerique object.
 */
Litteral* arcTan(Litteral& a);
/*!
 * \brief Exponential operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the value of the exp function applied to the LitteralNumerique object.
 */
Litteral* exp(Litteral& a);
/*!
 * \brief Natural logarithm operator
 *
 * Can be used on any LitteralNumerique object. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return Returns the value of the ln function applied to the LitteralNumerique object.
 */
Litteral* ln(Litteral& a);

//opérateurs logiques
/*!
 * \brief AND logical operator
 *
 * Can be used on Entier objects only. Otherwise, throws a ComputerException.
 * \param a - First operand.
 * \param b - Second operand.
 * \return If at least one of the two operands is 0, it returns a new Entier initialized with 0. Else, it returns a new Entier initialized with 1.
 */
Litteral* andF(Litteral& a, Litteral& b);
/*!
 * \brief OR logical operator
 *
 * Can be used on Entier objects only. Otherwise, throws a ComputerException.
 * \param a - First operand.
 * \param b - Second operand.
 * \return If at least one of the two operands is not 0, it returns a new Entier initialized with 1. Else, it returns a new Entier initialized with 0.
 */
Litteral* orF(Litteral& a, Litteral& b);
/*!
 * \brief NOT logical operator
 *
 * Can be used on Entier objects only. Otherwise, throws a ComputerException.
 * \param a - Object on which the operator is applied.
 * \return If the object is not 0, it returns a new Entier initialized with 0. Else, it returns a new Entier initialized with 1.
 */
Litteral* notF(Litteral& a);

#endif // LITTERAL_H
