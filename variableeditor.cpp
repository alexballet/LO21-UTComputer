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

void VariableEditor::newVariableSlot() {
    const QString name = ui->lineEdit->text();
    const QString value = ui->lineEdit_2->text();
    if (name.isEmpty() || value.isEmpty()) {
        QMessageBox::critical(this, tr("Variable Editor"),
                                       tr("Invalid input!"),
                                       QMessageBox::Ok);
        return;
    }

    new Variable(Litteral::createLitteral(value, typeLitteral(value)), name.toUpper());
    refreshTab();
}

void VariableEditor::refreshTab() {
    VariableMap* varmap = VariableMap::getInstance();

    ui->variableView->setRowCount(varmap->getCount());
    ui->variableView->setHorizontalHeaderLabels(QStringList() << "Variable" << "Valeur");

    QMap<QString, Variable*>::const_iterator i;
    int row = 0;
    for (i = varmap->getIteratorBegin(); i != varmap->getIteratorEnd(); ++i) {
        ui->variableView->setItem(row, 0, new QTableWidgetItem(i.key()));
        ui->variableView->setItem(row++, 1, new QTableWidgetItem(i.value()->toString()));
    }
}
