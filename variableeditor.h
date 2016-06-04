#ifndef VARIABLEEDITOR_H
#define VARIABLEEDITOR_H

#include <QDialog>
#include <QTableWidgetItem>
#include "variable.h"

namespace Ui {
class VariableEditor;
}

/*!
 * \brief Window for adding, deleting and editing variables
 */
class VariableEditor : public QDialog {
    Q_OBJECT

public:
    /*!
     * \brief VariableEditor constructor, sets up the ui.
     */
    explicit VariableEditor(QWidget *parent = 0);
    /*!
      \brief VariableEditor destructor, deletes the ui.
    */
    ~VariableEditor();
private:
    /*!
     * \brief ui for Qt Designer
     */
    Ui::VariableEditor *ui;
    /*!
     * \brief Refreshes the TableWidget that lists all variables.
     */
    void refreshTab();
private slots:
    /*!
     * \brief Verifies user input and creates a new variable.
     * Uses Litteral factory to parse the input, create a corresponding Litteral object, then adds it to VariableMap.
     */
    void newVariableSlot();
    /*!
     * \brief Lets the user edit a variable directly in the TableWidget.
     */
    void editVariableSlot(QTableWidgetItem*);
    /*!
     * \brief Lets the user delete a variable. This slot is connected to all delete buttons in the 3rd column.
     */
    void deleteVariableSlot();
};

#endif // VARIABLEEDITOR_H
