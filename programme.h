#ifndef PROGRAMME_H
#define PROGRAMME_H

#include "litteral.h"
#include "controleur.h"
#include "programeditorwindow.h"
#include <QVector>
#include <QString>
#include <QMap>
#include <QList>
#include <QTableWidgetItem>
#include <QRegularExpressionMatch>

/*!
 * \brief Programme class
 */
class Programme : public Litteral {
private:
    /*!
     * \brief Program instructions: a list of strings.
     */
    QStringList instructions;
    /*!
     * \brief Unique name, used to identify the program.
     */
    QString id;
public:
    /*!
     * \brief Constructor used for named programs. Checks whether the program's name is correct and adds the variable to the ProgrammeMap.
     * \param i are the program's instructions.
     * \param id is the program's name.
     */
    Programme(const QStringList i, const QString& id);
    /*!
     * \brief Constructor used to initialize the Programme object from a string passed from the command line.
     * Parses the string and initializes the instructions attribute. Id is empty because the program is simply pushed to the stack without assigning it an id.
     * \param i is the string with all the program instructions.
     */
    Programme(const QString& i);
    /*!
     * \brief Used by the Controleur to create a named Programme from an unnamed one.
     * \param lit is the unnamed program.
     * \param id is the program's name.
     */
    Programme(Litteral* lit, const QString id);
    /*!
     * \brief Id getter.
     * \return Program's name.
     */
    QString getId() const;
    /*!
     * \brief Id setter.
     * \param s is the new id.
     */
    void setId(const QString& s);
    /*!
     * \brief Instructions setter.
     * \param Program's new instructions
     */
    void setInstructions(QStringList l);
    /*!
     * \brief Instructions getter.
     * \return Program's instructions
     */
    QStringList getInstructions() const;
    /*!
     * \brief Returns the Program's instructions in a QString format.
     */
    QString toString() const;
};

template<class T>
/*!
 * \brief Tests whether an object is a Programme.
 * \param a is the test object.
 * \return True or False.
 */
bool isProgramme(T& a);

bool isProgramme(const QString& i);

/*!
 * \brief ProgrammeMap is a singleton containing a QMap with all named programs.
 */
class ProgrammeMap {
private:
    /*!
     * \brief A QMap where all programs are stored. They are identified by their id.
     */
    QMap<QString, Programme*> map;
    /*!
     * \brief ProgrammeMap instance used for the Singleton design pattern.
     */
    static ProgrammeMap* instance;
    /*!
     * \brief Default constructor
     */
    ProgrammeMap(){}

    //disabling copy and assignment
    /*!
     * \brief Disables the assignment possibility between ProgrammeMap objects.
     */
    ProgrammeMap& operator=(const ProgrammeMap&) = delete;
    /*!
     * \brief Disables the copy constructor.
     */
    ProgrammeMap (const ProgrammeMap&) = delete;
public:
    /*!
     * \brief Singleton getter.
     * \return ProgrammeMap instance.
     */
    static ProgrammeMap* getInstance();
    /*!
     * \brief Deletes the ProgrammeMap instance.
     */
    static void libererInstance();
    /*!
     * \brief Checks whether a Programme with the specified id exisits.
     * \param id of the program
     * \return Programme pointer if it exists, nullptr if it doesn't.
     */
    Programme* findProg(QString id) const;
    /*!
     * \brief Deletes a Programme with the specified id.
     * \param id of the program to delete.
     */
    void deleteProg(QString id);
    /*!
     * \brief Inserts a new Programme in the QMap.
     * \param id of the program
     * \param prog is the pointer to the program.
     * If the id corresponds to the id of an exisiting Programme, its value is overriden.
     */
    void insertProg(QString id, Programme* prog);
    /*!
     * \brief Returns the count of existing programs.
     */
    unsigned int getCount() const;
    /*!
     * \brief Returns a const iterator pointing at the beginning of the QMap.
     */
    QMap<QString, Programme*>::const_iterator getIteratorBegin() const;
    /*!
     * \brief Returns a const iterator pointing at the end of the QMap.
     */
    QMap<QString, Programme*>::const_iterator getIteratorEnd() const;
};


#endif // PROGRAMME_H
