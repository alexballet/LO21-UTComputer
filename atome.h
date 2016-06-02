#ifndef ATOME_H
#define ATOME_H
#include "litteral.h"
#include "variable.h"
#include <QString>

/*!
 * \brief The Atome class represents
 */
class Atome : public Litteral {
private:
    QString id;
public:
    /*!
     * \brief Constructor of Atome class.
     * \param id - QString to initialize the id of the Atome object.
     */
    Atome(QString id);
    /*!
     * \brief Accessor of the id attribute.
     * \return Returns the id attribute of the Atome object.
     */
    QString getId() const;
    /*!
     * \brief Displays the Atome object as a QString using its id attribute.
     * \return Returns a QString composed of the id attribute.
     *
     * This method is used to display the Atome object in the QTableWidget of the mainWindow.
     * The method creates a QString composed by the id put between two simple quotes.
     * E.g. the Atome X becomes 'X'.
     */
    QString toString() const;
    /*!
     * \brief Checks if the Atome is used as a Variable or a Programme.
     * \return If the Atome is used as a Variable or a Programme, it returns it's value. Otherwise, it returns a new Expression.
     *
     * This method searches for the Atome id attribute in VariableMap and ProgrammeMap.
     * If it finds the id in VariableMap, it returns the Variable.
     * If it finds ths id in ProgrammeMap, it returns the Programme.
     * If it doesn't find it, it returns a new Expression composed of the id attribute.
     */
    Litteral* getLitterale() const;
};

#endif // ATOME_H
