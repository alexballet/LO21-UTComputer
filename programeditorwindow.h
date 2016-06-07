#ifndef PROGRAMEDITORWINDOW_H
#define PROGRAMEDITORWINDOW_H

#include <QDialog>
#include <QTableWidgetItem>
#include "programme.h"

namespace Ui {
class ProgramEditorWindow;
}

/*!
 * \brief Small window where the user can edit a program.
 */
class ProgramEditorWindow : public QDialog {
    Q_OBJECT

  public:
    /*!
     * \brief ProgramEditorWindow constructor, sets up the ui.
     *
     * Displays the name and instructions of the program being edited.
     */
    explicit ProgramEditorWindow(QObject* sender, QWidget *parent = 0);
    /*!
     * \brief ProgramEditorWindow destructor, deletes the ui.
    */
    ~ProgramEditorWindow();

  private slots:
    /*!
     * \brief Parses and updates program's instructions.
     */
    void on_ProgramEditorWindow_accepted();

  private:
    /*!
     * \brief ui for Qt Designer
     */
    Ui::ProgramEditorWindow *ui;
    /*!
     * \brief id of the program being edited
     */
    QString progId;
};

#endif // PROGRAMEDITORWINDOW_H
