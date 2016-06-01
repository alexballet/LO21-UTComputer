#include "programeditorwindow.h"
#include "ui_programeditorwindow.h"

ProgramEditorWindow::ProgramEditorWindow(QObject *sender, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgramEditorWindow),
    progId(sender->objectName())
{
    ui->setupUi(this);
    ui->progName->setText(progId);

    //get prog instructions
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    Programme* prog = progmap->findProg(progId);
    ui->progEdit->setText(prog->toString());
}

ProgramEditorWindow::~ProgramEditorWindow()
{
    delete ui;
}

void ProgramEditorWindow::on_ProgramEditorWindow_accepted()
{
    ProgrammeMap* progmap = ProgrammeMap::getInstance();
    QString temp = ui->progEdit->toPlainText().replace('\n', ' ');
    if(temp!=""){
        while(temp.at(0)==' ')
            temp.remove(0,1);
        if(temp.at(0)=='[')
            temp.remove(0, 1);
        while(temp.at(temp.length()-1)==' '){
            temp.remove(temp.length()-1,1);
        }
        if(temp.at(temp.length()-1)==']')
            temp.remove(temp.length()-1, 1);
    }
    QStringList inst = temp.split(' ', QString::SkipEmptyParts);
    Programme* prog = progmap->findProg(progId);
    prog->setInstructions(inst);
}
