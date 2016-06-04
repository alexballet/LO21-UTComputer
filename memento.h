#pragma once
//#include "pile.h"
#include "litteral.h"
#include <QStack>
/*!
 * \brief The Memento class stores states of the Pile instance, each time the Pile instance is modified.
 * It is used for the UNDO and REDO operators.
 */
class Memento {
  private:
    friend class Pile;
    /*!
     * \brief Stores the Pile instance stack's state, containing all the pushed Litteral objects.
     */
    QStack<Litteral*> state;
  public:
    /*!
     * \brief Constructor of Memento.
     * \param State of the Pile instance stack, to initialize the state attribute.
     */
    Memento(QStack<Litteral*> s);
};

