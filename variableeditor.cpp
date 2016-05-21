#include "variableeditor.h"
#include "ui_variableeditor.h"
#include <QStringList>
#include <QMap>
#include <QDebug>

VariableEditor::VariableEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariableEditor)
{
    ui->setupUi(this);

    VariableMap* varmap = VariableMap::getInstance();

    ui->variableView->setRowCount(varmap->getCount());
    ui->variableView->setHorizontalHeaderLabels(QStringList() << "Variable" << "Valeur");

    QMap<QString, Variable*>::const_iterator i;
    int row = 0;
    for (i = varmap->getIterator(); i != varmap->getIteratorEnd(); ++i) {
        ui->variableView->setItem(row, 0, new QTableWidgetItem(i.key()));
        ui->variableView->setItem(row++, 1, new QTableWidgetItem(i.value()->toString()));
    }
}

VariableEditor::~VariableEditor()
{
    delete ui;
}
