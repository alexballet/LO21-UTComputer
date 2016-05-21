#ifndef VARIABLEEDITOR_H
#define VARIABLEEDITOR_H

#include <QDialog>
#include "variable.h"

namespace Ui {
class VariableEditor;
}

class VariableEditor : public QDialog
{
    Q_OBJECT

public:
    explicit VariableEditor(QWidget *parent = 0);
    ~VariableEditor();

private:
    Ui::VariableEditor *ui;
};

#endif // VARIABLEEDITOR_H
