#ifndef PROGRAMEDITOR_H
#define PROGRAMEDITOR_H

#include <QDialog>
#include "programme.h"

namespace Ui {
class ProgramEditor;
}

/*!
 * \brief Window for adding, deleting and editing programs
 */
class ProgramEditor : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief ProgramEditor constructor, sets up the ui.
     */
    explicit ProgramEditor(QWidget *parent = 0);
    /*!
     * \brief ProgramEditor destructor, deletes the ui.
    */
    ~ProgramEditor();
private:
    /*!
     * \brief ui for Qt Designer
     */
    Ui::ProgramEditor *ui;
    /*!
     * \brief Refreshes the TableWidget that lists all programs.
     */
    void refreshTab();

private slots:
    /*!
     * \brief Verifies user input and creates a new empty program.
     */
    void newProgramSlot();
    /*!
     * \brief Lets the user delete a program. This slot is connected to all delete buttons in the 3rd column.
     */
    void deleteProgSlot();
    /*!
     * \brief Opens a new ProgramEditorWindow that lets the user edit the program.
     * This slot is connected to all edit buttons in the 2nd column.
     */
    void editProgWindowSlot();
};

#endif // PROGRAMEDITOR_H
