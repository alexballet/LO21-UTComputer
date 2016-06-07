#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "litteral.h"
#include "controleur.h"
#include <QString>
#include <QTextStream>
#include <QChar>
#include <QStack>
/*!
 * \brief The Expression class is represented by a QString containing Litteral objects or operators.
 *
 * It can be an operation using the infix notation.
 */
class Expression : public Litteral {
  private:
    /*!
     * \brief Attribute storing the expression.
     */
    QString text;
  public:
    /*!
     * \brief Expression Constructor.
     *
     * If the parameter t is already in the expression form (e.g : 'X DUP'), the the character ' is removed from t an it is stored in the text attribute.
     * \param t - QString to initialize the text attribute.
     */
    Expression(QString t);
    /*!
     * \brief Accessor of the text attribute.
     * \return Returns the text attribute of the object.
     */
    QString getText() const;
    /*!
     * \brief Method used to display the text attribute in the Pile instance.
     * \return Returns a QString composed of the text attribute put between simple quotes. E.g : "X DUP" -> "'X DUP'".
     */
    QString toString() const;
};
/*!
 * \brief Checks whether the parameter is an Expression.
 *
 * Checks if the parameter i starts and ends with a simple quote.
 * \param i - QString to check.
 * \return Returns true if the parameter is an Expression, false if it's not.
 */
bool isExpression(const QString& i);

//parsing functions (infix to postfix)
/*!
 * \brief Function that parses an Expression previously considered as an operation.
 *
 * It uses the algorithm "infix-postfix" to transform an operation using the infix notation into an operation using the postfix notation.
 * This way, the Controleur instance can parse the expression as usual.
 * This is how it works : the algorithm reads each expression.
 * If it's an operand, it is added to the final postfix expression.
 * If it's an operator, the stack of operators in popped, and the operators are added to the postfix expression, until the operator to pop (from the stack) has lesser priority, is null or is '('. Then the operator is pushed into the back of the stack.
 * If it's a '(', it is pushed into the back of the stack of operators.
 * If it's a ')', the stack of operator is popped, and the operators are added to the postfix expression, until the operator to pop (from the stack) is ')'. Then ')' is popped and NOT added to the postfix expression.
 * If there is no more expression to read, all the remaining operators from the stack are popped and added to the postfix notation.
 * \param s - QString to parse.
 * \return Returns a QString representing a postfix operation.
 */
QString parseExpression(const QString& s);
/*!
 * \brief Checks if an operator a has a higher priority than b.
 * \param a - operator to compare
 * \param b - operator to compare
 * \return Returns true if the operator a has a higher priority than b, false if it hasn't.
 */
bool isHigher(QString a, QString b);
/*!
 * \brief Gets the priority of an operator.
 * \param op - operator
 * \return If it's 'NEG' it returns 4. If it's a logical operator, it returns 3. If it's '*' or '/', it returns 2. If it's '+' or '-' it returns 1. Else, it returns 0.
 */
int order(QString op);
/*!
 * \brief Checks if the QChar is not a symbol.
 * \param a - QChar to check.
 * \return Returns true if a is not a symbol, false if it is.
 */
bool isChar(QChar a);
/*!
 * \brief Checks if the QChar is a independent symbol or is part of the operand.
 *
 * E.g : '.' and '$' are part of an operand
 * \param a - QChar to check.
 * \return Returns true if a is part of an operand, false if it's not.
 */
bool isPartOperand(QChar a);

#endif // EXPRESSION_H
