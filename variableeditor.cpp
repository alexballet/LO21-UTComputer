#include "variableeditor.h"
#include "ui_variableeditor.h"
#include <QStringList>


VariableEditor::VariableEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariableEditor)
{
    ui->setupUi(this);

    VariableMap* varmap = VariableMap::getInstance();

    ui->variableView->setRowCount(varmap->getCount());
    ui->variableView->setHorizontalHeaderLabels(QStringList() << "Variable" << "Valeur");


}

VariableEditor::~VariableEditor()
{
    delete ui;
}
