#ifndef VARIABLE_H
#define VARIABLE_H
#include "litteral.h"
#include "controleur.h"
#include <QString>
#include <QMap>
#include <QList>
#include <QTableWidgetItem>

/*!
 * \brief Variable class
 */
class Variable : public Litteral {
private:
    /*!
     * \brief The variable's value is another Litteral.
     */
    Litteral* value;
    /*!
     * \brief Unique name used to identify the variable.
     */
    QString id;
public:
    /*!
     * \brief Checks whether the variable's name is correct and adds the variable to the VariableMap.
     * \param v is the value.
     * \param id is the variable's name.
     */
    Variable(Litteral* v, QString id);
    /*!
     * \brief Value getter.
     * \return Variable's value.
     */
    Litteral* getValue() const;
    /*!
     * \brief Id getter.
     * \return Variable's name.
     */
    QString getId() const;
    /*!
     * \brief Returns the Variable's value in a QString format.
     * \return value->toString().
     */
    QString toString() const;
    /*!
     * \brief Value setter.
     * \param v is the new value.
     */
    void setValue(Litteral* v);
};


template<class T>
/*!
 * \brief Tests whether an object is a Variable.
 * \param a is the test object.
 * \return True or False.
 */
bool isVariable(T& a);

/*!
 * \brief VariableMap is a singleton containing a QMap with all variables.
 */
class VariableMap {
private:
    /*!
     * \brief A QMap where all variables are stored. They are identified by their id.
     */
    QMap<QString, Variable*> map;
    /*!
     * \brief VariableMap instance used for the Singleton design pattern.
     */
    static VariableMap* instance;
    /*!
     * \brief Default constructor
     */
    VariableMap(){}
    //disabling copy and assignment
    /*!
     * \brief Disables the assignment possibility between VariableMap objects.
     */
    VariableMap& operator=(const VariableMap&) = delete;
    /*!
     * \brief Disables the copy constructor.
     */
    VariableMap (const VariableMap&) = delete;
public:
    /*!
     * \brief Singleton getter.
     * \return VariableMap instance.
     */
    static VariableMap* getInstance();
    /*!
     * \brief Deletes the VariableMap instance.
     */
    static void libererInstance();
    /*!
     * \brief Checks whether a Variable with the specified id exisits.
     * \param id of the variable
     * \return Variable pointer if it exists, nullptr if it doesn't.
     */
    Variable* findVar(QString id) const;
    /*!
     * \brief Deletes a Variable with the specified id.
     * \param id of the variable to delete.
     */
    void deleteVar(QString id);
    /*!
     * \brief Inserts a new Variable in the QMap.
     * \param id of the Variable
     * \param var is the pointer to the Variable.
     * If the id corresponds to the id of an exisiting Variable, its value is overriden.
     */
    void insertVar(QString id, Variable* var);
    /*!
     * \brief Creates a corresponding Litteral object using Litteral Factory then sets the value of the Variable identified by id to this object.
     * \param id of the Variable
     * \param value
     */
    void setVar(QString id, QString value);
    /*!
     * \brief Returns the count of existing variables.
     */
    unsigned int getCount() const;
    /*!
     * \brief Returns a const iterator pointing at the beginning of the QMap.
     */
    QMap<QString, Variable*>::const_iterator getIteratorBegin() const;
    /*!
     * \brief Returns a const iterator pointing at the end of the QMap.
     */
    QMap<QString, Variable*>::const_iterator getIteratorEnd() const;
};


#endif // VARIABLE_H
