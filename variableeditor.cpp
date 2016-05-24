#include "variableeditor.h"
#include "ui_variableeditor.h"
#include <QStringList>
#include <QMap>
#include <QMessageBox>
#include <QDebug>
#include "controleur.h"

VariableEditor::VariableEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariableEditor)
{
    ui->setupUi(this);
    refreshTab();
    connect(ui->newVariableBtn, SIGNAL(clicked()), this, SLOT(newVariableSlot()));
}

VariableEditor::~VariableEditor()
{
    delete ui;
}

void VariableEditor::refreshTab() {
    disconnect(ui->variableView, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editVariableSlot(QTableWidgetItem*)));
    VariableMap* varmap = VariableMap::getInstance();

    ui->variableView->setRowCount(varmap->getCount());
    ui->variableView->setHorizontalHeaderLabels(QStringList() << "Variable" << "Valeur");

    QMap<QString, Variable*>::const_iterator i;
    int row = 0;
    QTableWidgetItem* item;
    for (i = varmap->getIteratorBegin(); i != varmap->getIteratorEnd(); ++i) {
        item = new QTableWidgetItem(i.key());
        item->setFlags(item->flags() ^ Qt::ItemIsEditable); //Name column read only
        ui->variableView->setItem(row, 0, item);
        ui->variableView->setItem(row++, 1, new QTableWidgetItem(i.value()->toString()));
    }
    connect(ui->variableView, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editVariableSlot(QTableWidgetItem*)));
}

void VariableEditor::newVariableSlot() {
    const QString name = ui->lineEdit->text();
    const QString value = ui->lineEdit_2->text();
    if (name.isEmpty() || value.isEmpty()) {
        QMessageBox::critical(this, tr("Variable Editor"),
                                       tr("Invalid input!"),
                                       QMessageBox::Ok);
        return;
    }
    try {
        new Variable(Litteral::createLitteral(value, typeLitteral(value)), name.toUpper());
    }
    catch (ComputerException e) {
        QMessageBox::critical(this, tr("Variable Editor"),
                                       tr("Invalid input!"),
                                       QMessageBox::Ok);
        return;
    }
    refreshTab();
}

void VariableEditor::editVariableSlot(QTableWidgetItem* item) {
    qDebug() << "EditVarSlot";
    QString id = ui->variableView->item(item->row(), 0)->text();
    QString value = item->text();
    VariableMap* varmap = VariableMap::getInstance();
    Variable* var = varmap->findVar(id);
    var->setValue(Litteral::createLitteral(value, typeLitteral(value)));

}
