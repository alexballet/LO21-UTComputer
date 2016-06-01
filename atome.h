#ifndef ATOME_H
#define ATOME_H
#include "litteral.h"
#include "variable.h"
#include <QString>

/*!
 * \brief The Atome class
 */
class Atome : public Litteral {
private:
    QString id;
public:
    /*!
     * \brief Constructor of Atome class
     * \param id - QString to initialize the id of the Atome object
     */
    Atome(QString id);
    QString getId() const;
    QString toString() const;
    Litteral* getLitterale() const;
};

template<class T>
bool isAtome(T& a);

#endif // ATOME_H
