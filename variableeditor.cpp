#include "variableeditor.h"
#include "ui_variableeditor.h"
#include <QStringList>
#include <QMap>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

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
    ui->variableView->setHorizontalHeaderLabels(QStringList() << "Variable" << "Valeur" << "Supprimer");

    QMap<QString, Variable*>::const_iterator i;
    QTableWidgetItem* item;
    int row = 0;

    QWidget* pWidget;
    QPushButton* btn_delete;
    QHBoxLayout* pLayout;
    for (i = varmap->getIteratorBegin(); i != varmap->getIteratorEnd(); ++i) {
        item = new QTableWidgetItem(i.key());
        item->setFlags(item->flags() ^ Qt::ItemIsEditable); //Name column read only
        ui->variableView->setItem(row, 0, item);
        ui->variableView->setItem(row, 1, new QTableWidgetItem(i.value()->toString()));
        pWidget = new QWidget();
        btn_delete = new QPushButton();
        btn_delete->setText("-");
        btn_delete->setStyleSheet("background-color:red;");
        btn_delete->setObjectName(i.key());
        pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_delete);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->variableView->setCellWidget(row++, 2, pWidget);
        connect(btn_delete, SIGNAL(pressed()), this, SLOT(deleteVariableSlot()));
        //ui->variableView->setItem(row++, 2, new QTableWidgetItem())
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

void VariableEditor::deleteVariableSlot() {
    QObject* senderBtn = sender();
    VariableMap* varmap = VariableMap::getInstance();
    varmap->deleteVar(senderBtn->objectName());
    refreshTab();
}

void VariableEditor::editVariable(QTableWidgetItem* item) {
    VariableMap* varmap = VariableMap::getInstance();
    QString id = ui->variableView->item(item->row(), 0)->text();
    varmap->setVar(id, item->text());
}
