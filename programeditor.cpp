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
    disconnect(ui->progView, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editProgSlot(QTableWidgetItem*)));
    ProgrammeMap* progmap = ProgrammeMap::getInstance();

    ui->progView->setRowCount(progmap->getCount());
    ui->progView->setHorizontalHeaderLabels(QStringList() << "Nom" << "Edit");

    QMap<QString, Programme*>::const_iterator i;
    int row = 0;
    QTableWidgetItem* item;
    QWidget* pWidget1;
    QPushButton* btn_delete;
    QHBoxLayout* pLayout1;
    QWidget* pWidget2;
    QPushButton* btn_edit;
    QHBoxLayout* pLayout2;
    for (i = progmap->getIteratorBegin(); i != progmap->getIteratorEnd(); ++i) {
        qDebug()<<"key : "<<i.key();
        item = new QTableWidgetItem(i.key());
        item->setFlags(item->flags() ^ Qt::ItemIsEditable); //Name column read only
        ui->progView->setItem(row, 0, item);
        //edit button
        pWidget2 = new QWidget();
        btn_edit = new QPushButton();
        btn_edit->setText("edit");
        btn_edit->setStyleSheet("background-color:blue;");
        btn_edit->setObjectName(i.key());
        pLayout2 = new QHBoxLayout(pWidget2);
        pLayout2->addWidget(btn_edit);
        pLayout2->setAlignment(Qt::AlignCenter);
        pLayout2->setContentsMargins(0, 0, 0, 0);
        pWidget2->setLayout(pLayout2);
        ui->progView->setCellWidget(row, 1, pWidget2);
        connect(btn_edit, SIGNAL(pressed()), this, SLOT(editProgWindowSlot()));
        //delete button
        pWidget1 = new QWidget();
        btn_delete = new QPushButton();
        btn_delete->setText("-");
        btn_delete->setStyleSheet("background-color:red;");
        btn_delete->setObjectName(i.key());
        pLayout1 = new QHBoxLayout(pWidget1);
        pLayout1->addWidget(btn_delete);
        pLayout1->setAlignment(Qt::AlignCenter);
        pLayout1->setContentsMargins(0, 0, 0, 0);
        pWidget1->setLayout(pLayout1);
        ui->progView->setCellWidget(row++, 2, pWidget1);
        connect(btn_delete, SIGNAL(pressed()), this, SLOT(deleteProgSlot()));
    }
    connect(ui->progView, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editProgSlot(QTableWidgetItem*)));
}


void ProgramEditor::newProgramSlot() {
    const QString id = ui->lineEditProg->text();
    if (id.isEmpty()) {
        QMessageBox::critical(this, tr("Program Editor"),
                                       tr("Remplissez le nom!"),
                                       QMessageBox::Ok);
        return;
    }
    try {
        new Programme(Litteral::createLitteral("", "Programme"), id.toUpper());
    }
    catch (ComputerException e) {
        QMessageBox::critical(this, tr("Program Editor"),
                                       tr(e.getInfo().toStdString().c_str()),
                                       QMessageBox::Ok);
        return;
    }
    //qDebug()<<"refreshing...";
    refreshTab();
    //qDebug()<<"new prog : "<<id;
}

void ProgramEditor::editProgSlot(QTableWidgetItem* item) {
    qDebug() << "EditProgSlot";
    QString id = ui->progView->item(item->row(), 0)->text();
    QString value = item->text();
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    progmap->deleteProg(id);
    new Programme(Litteral::createLitteral(value, typeLitteral(value)), id);
}

void ProgramEditor::deleteProgSlot() {
    QObject* senderBtn = sender();
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    progmap->deleteProg(senderBtn->objectName());
    refreshTab();
}

void ProgramEditor::editProgWindowSlot(){
    QObject* senderBtn = sender();
    //qDebug()<<"ouverture fenetre edition programme";
    ProgramEditorWindow *progEditorWindow = new ProgramEditorWindow(senderBtn);
    //qDebug()<<"créé avec succès";
    progEditorWindow->setModal(true);
    progEditorWindow->exec();
}
