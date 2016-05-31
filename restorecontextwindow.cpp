#include "restorecontextwindow.h"
#include "ui_restorecontextwindow.h"

int RestoreContextWindow::answer=-1;

RestoreContextWindow::RestoreContextWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestoreContextWindow)
{
    ui->setupUi(this);
}

RestoreContextWindow::~RestoreContextWindow()
{
    delete ui;
}

void RestoreContextWindow::on_restore_accepted()
{
    answer=1;
}

void RestoreContextWindow::on_restore_rejected()
{
    answer=0;
}

int RestoreContextWindow::getAnswer(){
    return answer;
}

void RestoreContextWindow::on_RestoreContextWindow_finished()
{
    answer=0;
}
