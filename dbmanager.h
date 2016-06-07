#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include "pile.h"
/*!
 * \brief The DbManager class manages the SQLite database that stores the context (variables, programs and settings) of UTComputer.
 */
class DbManager {
  private:
    /*!
     * \brief Pointer to the unique instance of the DbManager object.
     */
    static DbManager* instance;
    /*!
     * \brief QSqlDatabase of UTComputer
     */
    QSqlDatabase db;
    /*!
     * \brief Private DbManager constructor to forbid instanciation by any other way than using the getInstance() method.
     *
     * It initializes the SQLite database, open the .bd file (creates a new one if it doesn't exist) and creates the "pile", "variables", "programs" and "options" tables if they do not exist.
     * The "pile" table has 3 columns : id (the serial number), typeLit (the type of the Litteral object) and lit (the QString representation of the Litteral object). E.g : 1 | Rationnel | 3/4
     * The "variables" table has 4 columns : id, nameVar (the identificator of the Variable object), typeLit and lit. E.g : 2 | X | Reel | 5.34
     * The "programs" table has 3 columns : id, nameProg (the identificator of the Programme object) and lit. E.g : 3 | FOO | [2 DUP +]
     * The "options" table has 3 columns : id, option (the name of the option) and valeur (the value of the option). E.g : 4 | Pile | 5
     */
    DbManager();
    /*!
      * \brief Destructor
      */
    ~DbManager();
    /*!
     * \brief Disabling the assignment possibility between DbManager objects.
     */
    DbManager& operator=(const DbManager&) = delete;
    /*!
     * \brief Disabling the copy constructor of the DbManager class.
     */
    DbManager (const DbManager&) = delete;
  public:
    /*!
     * \brief Method to access the DbManager singleton.
     * \return Pointer to the DbManager singleton. If the singleton is not instanciated yet, it returns a new DbManager. Otherwise, it returns the DbManager instance.
     */
    static DbManager* getInstance();
    /*!
     * \brief Deletes the DbManager instance.
     */
    static void libererInstance();
    /*!
     * \brief Method that saves the Litteral objects pushed into the Pile instance.
     *
     * It clears the "pile" table and copies the Litteral objects from the Pile instance into the "pile" table.
     */
    void savePile();
    /*!
     * \brief Method that saves the Variable objects into the database.
     *
     * It clears the "variables" table and copies the Variable objects from VariableMap into the "variables" table.
     */
    void saveVariables();
    /*!
     * \brief Method that saves the Programme objets into the database.
     *
     * It clears the "programs" table and copies the Programme objects from ProgrammeMap into the "programs" table.
     */
    void savePrograms();
    /*!
     * \brief Method that saves the settings into the database.
     *
     * It clears the "options" table and copies the values from the global Setting object into the "options" table.
     */
    void saveOptions();
    /*!
     * \brief Method that recovers the Litteral objects pushed from the database.
     *
     * It pushes the Litteral objects from the "pile" table into the Pile instance.
     */
    void setPile();
    /*!
     * \brief Method that recovers the Variable objects from the database.
     *
     * It inserts the Variable objects from the "variables" table into the VariableMap instance.
     */
    void setVariables();
    /*!
     * \brief Method that recovers the Programme objects from the database.
     *
     * It inserts the Programme objects from the "program" table into the ProgrammeMap instance.
     */
    void setPrograms();
    /*!
     * \brief Method that recovers the settings from the database.
     *
     * It updates the settings with the values from the "options" table.
     */
    void setOptions();
};

#endif // DBMANAGER_H
