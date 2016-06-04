#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QMessageBox>
#include <QTableView>
#include <QAction>
#include <QTableWidgetItem>
#include <QMenuBar>
#include <QSettings>
#include <QStandardPaths>
#include <QShortcut>
#include "pile.h"
#include "controleur.h"
#include "options.h"
#include "variableeditor.h"
#include "programeditor.h"

namespace Ui {
class QComputer;
}

/*!
 * \brief Main class, controls the main window.
 */
class QComputer : public QWidget {
    Q_OBJECT

  public:
    /*!
     * \brief Constructor responsible for initializing the ui and app options
     * Asks the user whether he wants to restore the previous context. Then initializes the settings, the menu bar, the Pile tableWidget,
     * connects signals and sets the initial Memento
     */
    explicit QComputer(QWidget *parent = 0);
    /*!
     * \brief Saves the context into a SQLite DB then deletes the ui
    */
    ~QComputer();
  public slots:
    /*!
     * \brief Refreshes the Pile tableWidget.
     * Called every time the Pile object is modified.
     */
    void refresh();
    /*!
     * \brief Processes user input from the command line.
     * Activated by pressing Enter or by clicking on the SEND button.
     */
    void on_commande_returnPressed();
    /*!
     * \brief Opens the options window. Connects all signals from this window to QComputer slots.
     */
    void slotOptions();
    /*!
     * \brief Opens the Variable Editor window
     */
    void slotVarEditor();
    /*!
     * \brief Opens the Program Editor window
     */
    void slotProgEditor();
  private slots:
    /*!
     * \brief All buttons are connected to this slot.
     * Displays the button's text in the command line or directly performs an action (for example for UNDO/REDO buttons or the SEND button)
     */
    void editCommmande();
    /*!
     * \brief Shows or hides the keyboard.
     * Controlled by a signal sent from the Options window.
     */
    void activerClavier(bool);
    /*!
     * \brief Modifies the number of items displayed in the Pile tableWidget and refreshes the view.
     * Controlled by a signal sent from the Options window.
     * \param n is the new number of items
     */
    void setMaxAffiche(int);


  private:
    /*!
     * \brief ui for Qt Designer
     */
    Ui::QComputer *ui;
    /*!
     * \brief Displays a dialog asking a user whether he wants to restore the previous context.
     * Called from the constructor. If the users answers yes, Pile values, variables, programs and settings are loaded from the SQLite DB.
     * If the user answers no, default values are used (Pile->maxAffiche = 4, keyboard active)
     */
    void restoreContext();
    /*!
     * \brief Initializes the menu bar and connects all menu bar actions to correct slots.
     * Called from the constructor.
     */
    void initMenuBar();
    /*!
     * \brief Initializes the tableWidget displaying all Pile items.
     * Called from the constructor.
     */
    void initPile();
};

#endif // QCOMPUTER_H
