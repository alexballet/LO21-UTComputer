#ifndef PILE_H
#define PILE_H

#include <QObject>
#include <QString>
#include <QStack>
#include <QtCore/qmath.h>
#include <typeinfo>
#include "memento.h"
#include "litteral.h"
#include "atome.h"
#include "controleur.h"

/*!
 * \brief Singleton containing the stack with all Litteral objects pointers
 */
class Pile : public QObject {
    Q_OBJECT

  private:
    /*!
     * \brief Pile instance used for the Singleton design pattern.
     */
    static Pile* instance;
    /*!
     * \brief Stack containing all Litteral object pointers.
     */
    QStack<Litteral*> stack;
    /*!
     * \brief Message displayed to the user.
     */
    QString message;
    /*!
     * \brief Maximum number of elements displayed to the user.
     */
    unsigned int maxAffiche;
    /*!
     * \brief Default constructor.
     */
    Pile();
    /*!
     * \brief Destructor.
     */
    ~Pile();
    //disabling copy and assignment
    /*!
     * \brief Disables the assignment possibility between Pile objects.
     */
    Pile& operator=(const Pile&) = delete;
    /*!
     * \brief Disables the copy constructor.
     */
    Pile (const Pile&) = delete;
  public:
    /*!
     * \brief Singleton getter.
     * \return Pile instance.
     */
    static Pile* getInstance();
    /*!
     * \brief Deletes the Pile instance.
     */
    static void libererInstance();
    /*!
     * \brief Message getter.
     * \return Pile message
     */
    QString getMessage() const;
    /*!
     * \brief Message setter.
     * \param msg - new message
     */
    void setMessage(const QString& msg);
    /*!
     * \brief maxAffiche getter.
     * \return maxAffiche
     */
    unsigned int getMaxAffiche() const;
    /*!
     * \brief maxAffiche setter.
     */
    void setMaxAffiche(unsigned int);
    /*!
     * \return number of elements on the stack
     */
    int getLength() const;
    /*!
     * \return True if the stack is empty, false otherwise
     */
    bool isEmpty();
    /*!
     * \brief Pushes a Litteral object pointer into the stack.
     * \param lit is the Litteral to push.
     */
    void push(Litteral* lit);
    /*!
     * \brief Pops a Litteral object pointer out of the stack.
     * \return Pointer to the popped Litteral object
     */
    Litteral* pop();
    /*!
     * \brief Peeks at the top item of the stack.
     * \return Pointer to the Litteral object at the top of the stack.
     */
    Litteral* top() const;
    /*!
     * \brief Returns a const iterator pointing at the beginning of the stack.
     */
    QStack<Litteral*>::const_iterator getIteratorBegin() const;
    /*!
     * \brief Returns a const iterator pointing at the end of the stack.
     */
    QStack<Litteral*>::const_iterator getIteratorEnd() const;

    //Memento
    /*!
     * \brief Creates a new Memento object with the current state of the stack.
     * \return Pointer to new Memento object
     */
    Memento* createMemento();
    /*!
     * \brief Gets the stack state from a Memento object.
     * \param mem is the pointer to a Memento object
     */
    void reinstateMemento(Memento* mem);
  signals:
    /*!
     * \brief Signal sent to QComputer to refresh the tableWidget every time the Pile object is modified.
     */
    void modificationEtat();
};

#endif // PILE_H
