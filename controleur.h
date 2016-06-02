#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QString>
#include <QDebug>
#include <QVector>
#include <QSettings>
#include <QStringList>
#include "litteral.h"
#include "programme.h"
#include "variable.h"
#include "atome.h"
#include "memento.h"
#include "pile.h"
#include "operateur.h"
#include "expression.h"
#include "dbmanager.h"

/*!
 * \brief The Controleur class parses and executes the user input. It also manages the Memento object and is a singleton.
 */
class Controleur {
private:
    /*!
     * \brief Attribute storing the last operator used. Usefull for the LASTOP operator.
     */
    QString lastOp;
    /*!
     * \brief Pointer to the unique instance of the Controler object.
     */
    static Controleur* instance;
    /*!
     * \brief Private Controleur constructor to forbid instanciation by any other way than using the getInstance() method.
     */
    Controleur() {}
    /*!
     * \brief Vector of pointers to the Memento objects created.
     */
    static QVector<Memento*> mementoList;
    /*!
     * \brief Index of the current Memento state (in the mementoList).
     */
    static int currentMemento;

    //disabling copy and assignment
    /*!
     * \brief Disabling the assignment possibility between Controleur objects.
     */
    Controleur& operator=(const Controleur&) = delete;
    /*!
     * \brief Disabling the copy constructor of the Controleur class.
     */
    Controleur (const Controleur&) = delete;
public:
    /*!
     * \brief Method to access the Controleur singleton.
     * \return Pointer to the Controleur singleton. If the singleton is not instanciated yet, it returns a new Controleur. Otherwise, it returns the Controleur instance.
     */
    static Controleur* getInstance();
    /*!
     * \brief Method that parses a QString to isolate the expressions to form Litteral objects or execute operators.
     * If it's a Programme or an Expression, it creates the associated Litteral and pushes it in the Pile.
     * Otherwise, it means it's one or a series of different Litterals. It splits the com parameter and analyzes each one independently.
     * \param com - QString to parse.
     */
    void parse(const QString& com);
    /*!
     * \brief Method that splits a QString into different expressions to be executed by the execute() method.
     * \param com - QString to split.
     * \return
     */
    QStringList manualSplit(const QString& com);
    /*!
     * \brief Method that processes an expression.
     * If it's an operator, it applies it. Otherwise, it's a Litteral and it pushes it in the Pile.
     * \param word - QString to process.
     */
    void process(const QString word);
    /*!
     * \brief Method that applies a numeric operator, poping nbOp Litteral objects from the Pile.
     * If there is enough Litteral objects in the Pile and if the operation is possible between those types of Litteral objects, it applies the operator.
     * \param op - id of the operator to apply.
     * \param nbOp - number of operands needed to apply the operator.
     */
    void applyOperatorNum(const QString& op, const int nbOp);
    /*!
     * \brief Method that applies a logical operator, poping nbOp Litteral objects from the Pile.
     * If there is enough Litteral objects in the Pile and if the operation is possible between those types of Litteral objects, it applies the operator.
     * \param op - id of the operator to apply.
     * \param nbOp - number of operands needed to apply the operator.
     */
    void applyOperatorLog(const QString& op, const int nbOp);
    /*!
     * \brief Method that applies a Pile operator, poping nbOp Litteral objects from the Pile.
     * If there is enough Litteral objects in the Pile and if the operation is possible between those types of Litteral objects, it applies the operator.
     * \param op - id of the operator to apply.
     * \param nbOp - number of operands needed to apply the operator.
     */
    void applyOperatorPile(const QString& op, const int nbOp);
    /*!
     * \brief Method that calls the apply method associated with the type of the operator.
     * \param op - id of the operator to apply.
     */
    void applyOperator(const QString& op);

    //taking care of memento
    /*!
     * \brief Method that adds the Memento state mem to mementoList. Called each time an expression is processed.
     * \param mem - Memento state to add.
     */
    static void addMementoState(Memento* mem);
    /*!
     * \brief Method that reinstate the previous Memento state.
     */
    static void undo();
    /*!
     * \brief Method that reinstate the next Memento state.
     */
    static void redo();
};

/*!
 * \brief Function that analyzes the QString to determine it's type. It is used in order to create a new Litteral object from a QString.
 * \param lit - QString to analyze.
 * \return Returns the type of the analyzed QString. E.g : typeLitteral("[ 2 DUP +]") -> "Programme".
 */
QString typeLitteral(const QString& lit);
/*!
 * \brief Checks if the QString corresponds to a numeric operator.
 * Searches for the parameter a in the QMap opsNum, containing all the numeric operators and their arity.
 * \param a - QString to check.
 * \return Return true if a is a numeric operator, false if it's not.
 */
bool isOperatorNum(const QString& a);
/*!
 * \brief Checks if the QString corresponds to a logical operator.
 * Searches for the parameter a in the QMap opsLog, containing all the logical operators and their arity.
 * \param a - QString to check.
 * \return Return true if a is a logical operator, false if it's not.
 */
bool isOperatorLog(const QString& a);
/*!
 * \brief Checks if the QString corresponds to a Pile operator.
 * Searches for the parameter a in the QMap opsPile, containing all the Pile operators and their arity.
 * \param a - QString to check.
 * \return Return true if a is a Pile operator, false if it's not.
 */
bool isOperatorPile(const QString& a);
/*!
 * \brief Checks if the QString corresponds to an operator.
 * Checks if the parameter a is a numeric operator, a logical operator or a Pile operator.
 * \param a - QString to check.
 * \return Return true if a is numeric operator, a logical operator or a Pile operator, false if it's none of them.
 */
bool isOperator(const QString& a);

#endif // CONTROLEUR_H
