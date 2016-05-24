#include "programeditor.h"
#include "ui_programeditor.h"
#include <QStringList>
#include <QMap>
#include <QMessageBox>
#include <QDebug>


ProgramEditor::ProgramEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgramEditor)
{
    ui->setupUi(this);
    refreshTab();
    connect(ui->newProgBtn, SIGNAL(clicked()), this, SLOT(newProgramSlot()));
}

ProgramEditor::~ProgramEditor()
{
    delete ui;
}

void ProgramEditor::refreshTab() {
    ProgrammeMap* progmap = ProgrammeMap::getInstance();

    ui->progView->setRowCount(progmap->getCount());
    ui->progView->setHorizontalHeaderLabels(QStringList() << "Nom" << "Contenu");

    QMap<QString, Programme*>::const_iterator i;
    int row = 0;
    for (i = progmap->getIteratorBegin(); i != progmap->getIteratorEnd(); ++i) {
        ui->progView->setItem(row, 0, new QTableWidgetItem(i.key()));
        ui->progView->setItem(row++, 1, new QTableWidgetItem(i.value()->toString()));
    }
}


void ProgramEditor::newProgramSlot() {

}
