#include "variableeditor.h"
#include "ui_variableeditor.h"
#include <QStringList>
#include <QMap>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>

VariableEditor::VariableEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariableEditor) {
    ui->setupUi(this);
    refreshTab();
    connect(ui->newVariableBtn, SIGNAL(clicked()), this, SLOT(newVariableSlot()));
}

VariableEditor::~VariableEditor() {
    delete ui;
}

void VariableEditor::refreshTab() {
    //disconnect prevents the sending of itemChanged signal when generating the table
    disconnect(ui->variableView, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editVariableSlot(QTableWidgetItem*)));
    VariableMap* varmap = VariableMap::getInstance();

    ui->variableView->setRowCount(varmap->getCount());
    ui->variableView->setHorizontalHeaderLabels(QStringList() << "Variable" << "Valeur" << "Supprimer");
    ui->variableView->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    ui->variableView->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);

    QMap<QString, Variable*>::const_iterator i;
    QTableWidgetItem* item;
    int row = 0;

    QWidget* pWidget;
    QPushButton* btn_delete; //delete button for each row
    QHBoxLayout* pLayout; //used to stretch the button so as it fills the cell

    for (i = varmap->getIteratorBegin(); i != varmap->getIteratorEnd(); ++i) {
        item = new QTableWidgetItem(i.key());
        item->setFlags(item->flags() ^ Qt::ItemIsEditable); //Name column is read only
        //name
        ui->variableView->setItem(row, 0, item);
        //value
        ui->variableView->setItem(row, 1, new QTableWidgetItem(i.value()->toString()));
        //delete button
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
    }

    //reconnect the signal
    connect(ui->variableView, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editVariableSlot(QTableWidgetItem*)));

}

void VariableEditor::newVariableSlot() {
    const QString name = ui->lineEdit->text();
    const QString value = ui->lineEdit_2->text();

    if (name.isEmpty() || value.isEmpty()) { //if fields are empty
        QMessageBox::critical(this, tr("Variable Editor"),
                              tr("Remplissez les champs!"),
                              QMessageBox::Ok);
        return;
    }

    try {
        new Variable(Litteral::createLitteral(value, typeLitteral(value)), name.toUpper());
    } catch (ComputerException e) { //if fields are incorrect
        QMessageBox::critical(this, tr("Variable Editor"),
                              tr(e.getInfo().toStdString().c_str()),
                              QMessageBox::Ok);
        return;
    }

    refreshTab();
}

void VariableEditor::editVariableSlot(QTableWidgetItem* item) {
    QString id = ui->variableView->item(item->row(), 0)->text(); //getting the id from column 0
    QString value = item->text();
    VariableMap* varmap = VariableMap::getInstance();
    varmap->setVar(id, value);
}

void VariableEditor::deleteVariableSlot() {
    QObject* senderBtn = sender();
    VariableMap* varmap = VariableMap::getInstance();
    varmap->deleteVar(senderBtn->objectName());
    refreshTab();
}

