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
     * Otherwise, it means it's one or a series of different Litterals. It splits the com parameter and analyses each one independently.
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
     * \brief applyOperatorNum
     * \param op
     * \param nbOp
     */
    void applyOperatorNum(const QString& op, const int nbOp);
    void applyOperatorLog(const QString& op, const int nbOp);
    void applyOperatorPile(const QString& op);
    void applyOperator(const QString& op);

    //taking care of memento
    static void addMementoState(Memento* mem);
    static void undo();
    static void redo();
};

QString typeLitteral(const QString& lit);
bool isOperatorNum(const QString& a);
bool isOperatorLog(const QString& a);
bool isOperatorPile(const QString& a);
bool isOperator(const QString& a);

#endif // CONTROLEUR_H
