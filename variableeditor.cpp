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
    QTableWidgetItem* item;
    int row = 0;
    for (i = varmap->getIterator(); i != varmap->getIteratorEnd(); ++i) {
        item = new QTableWidgetItem(i.key());
        item->setFlags(item->flags() ^ Qt::ItemIsEditable); //restricting editing for values in column 0
        ui->variableView->setItem(row, 0, item);
        ui->variableView->setItem(row++, 1, new QTableWidgetItem(i.value()->toString()));
    }
    connect(ui->variableView, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editVariable(QTableWidgetItem*)));

}

VariableEditor::~VariableEditor()
{
    delete ui;
}

void VariableEditor::editVariable(QTableWidgetItem* item) {
    VariableMap* varmap = VariableMap::getInstance();
    QString id = ui->variableView->item(item->row(), 0)->text();
    varmap->setVar(id, item->text());
}
