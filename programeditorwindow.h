#ifndef PROGRAMEDITORWINDOW_H
#define PROGRAMEDITORWINDOW_H

#include <QDialog>
#include <QTableWidgetItem>
#include "programme.h"

namespace Ui {
class ProgramEditorWindow;
}

class ProgramEditorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramEditorWindow(QObject* sender, QWidget *parent=0);
    ~ProgramEditorWindow();


private slots:
    void on_ProgramEditorWindow_accepted();

private:
    Ui::ProgramEditorWindow *ui;
    QString progId;
};

#endif // PROGRAMEDITORWINDOW_H
