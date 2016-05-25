#ifndef PROGRAMEDITOR_H
#define PROGRAMEDITOR_H

#include <QDialog>
#include "programme.h"

namespace Ui {
class ProgramEditor;
}

class ProgramEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramEditor(QWidget *parent = 0);
    ~ProgramEditor();

private:
    Ui::ProgramEditor *ui;
    void refreshTab();

private slots:
    void newProgramSlot();
    void editProgSlot(QTableWidgetItem* item);
    void deleteProgSlot();
    void editProgWindowSlot();
};

#endif // PROGRAMEDITOR_H
